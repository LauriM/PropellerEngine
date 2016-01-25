// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/renderer/RendererDevice.h"

#if defined(D3D11)

#include <d3d11.h>
#include <comdef.h>

#include "engine/console/Cvar.h"
#include "engine/renderer/RendererEnums.h"
#include "engine/renderer/D3D11/D3D11Shader.h"
#include "engine/renderer/Pipeline.h"
#include "engine/renderer/StateDescriptor.h"
#include "engine/renderer/ShaderResource.h"
#include "engine/renderer/D3D11/D3D11InputLayout.h"
#include "engine/renderer/D3D11/D3D11RenderTarget.h"
#include "engine/renderer/D3D11/D3D11Texture.h"
#include "engine/renderer/D3D11/D3D11Buffer.h"
#include "engine/renderer/TextureResource.h"
#include "engine/renderer/InputLayout.h"
#include "engine/renderer/D3D11/D3D11DeviceData.h"
#include "engine/renderer/D3D11/D3D11Pipeline.h"
#include "engine/renderer/DrawDescriptor.h"
#include "engine/renderer/Viewport.h"
#include "engine/sys/Mutex.h"

namespace cvar {
	EXTERN_CVAR(int, r_width);
	EXTERN_CVAR(int, r_height);
	EXTERN_CVAR(int, r_vsync);
}

namespace engine {
namespace renderer {

	RendererDevice *createRendererDevice(void *hwnd)

	{
		RendererDevice *device = new RendererDevice();
		device->setHwnd(hwnd);
		return device;
	}

	RendererDevice::RendererDevice()
	{
		deviceData = new DeviceData();
	}

	RendererDevice::~RendererDevice()
	{
		delete deviceData;
	}

	bool checkError(HRESULT result)
	{
		if (FAILED(result))
		{
			_com_error err(result);
			LPCTSTR errMsg = err.ErrorMessage();
			LOG_ERROR("[D3D11 ERROR] " << errMsg);
			return true;
		}

		return false;
	}

	bool RendererDevice::init()
	{
		PROFILE;
		HRESULT result;

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		D3D_FEATURE_LEVEL featureLevel;
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		resolution.x = *cvar::r_width;
		resolution.y = *cvar::r_height;

		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		swapChainDesc.BufferDesc.Width = resolution.x;
		swapChainDesc.BufferDesc.Height = resolution.y;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = (HWND)hwnd;
		swapChainDesc.SampleDesc.Count = 4;
		swapChainDesc.Windowed = true;           //TODO: is windowed cvar here!

		//TODO: create different kind of device for release
		result = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, 0, 0, D3D11_SDK_VERSION, &deviceData->device, &featureLevel, &deviceData->context);
		checkError(result);

		result = D3D11CreateDeviceAndSwapChain(NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			NULL,
			NULL,
			NULL,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&deviceData->swapChain,
			&deviceData->device,
			NULL,
			&deviceData->context);
		checkError(result);

		// Backbuffer texture created, backbuffer rendertarget creation is on the user
		result = deviceData->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&deviceData->backBufferTexture);
		checkError(result);

		D3D11_TEXTURE2D_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
		depthStencilDesc.Width = resolution.x;
		depthStencilDesc.Height = resolution.y;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		//TODO: multiple depth stencil buffers ?
		result = deviceData->device->CreateTexture2D(&depthStencilDesc, NULL, &deviceData->depthStencilBuffer);
		checkError(result);
		result = deviceData->device->CreateDepthStencilView(deviceData->depthStencilBuffer, NULL, &deviceData->depthStencilView);
		checkError(result);

		return true;
	}

	void RendererDevice::uninit()
	{
		deviceData->context->Release();
		deviceData->context = 0;
		deviceData->device->Release();
		deviceData->device = 0;
		deviceData->swapChain->Release();
		deviceData->swapChain = 0;

		LOG_INFO("[RendererDevice] Released context & device!");
	}

	Shader *createVertexShader(const void *buffer, size_t bufferSize, ID3D11Device *device)
	{
		D3D11Shader *shader = new D3D11Shader();
		shader->header.type = SHADERTYPE_VERTEX;

		HRESULT result = device->CreateVertexShader(buffer, bufferSize, NULL, &shader->vertexShader);

		if (checkError(result))
		{
			delete shader;
			return NULL;
		}

		return &shader->header;
	}

	Shader *createPixelShader(const void *buffer, size_t bufferSize, ID3D11Device *device)
	{
		D3D11Shader *shader = new D3D11Shader();
		shader->header.type = SHADERTYPE_PIXEL;

		HRESULT result = device->CreatePixelShader(buffer, bufferSize, NULL, &shader->pixelShader);

		if (checkError(result))
		{
			delete shader;
			return NULL;
		}

		return &shader->header;
	}

	Shader *RendererDevice::createShader(ShaderType type, const void *buffer, size_t bufferSize)
	{
		PROFILE;
		switch (type)
		{
		case ShaderType::SHADERTYPE_VERTEX:
			return createVertexShader(buffer, bufferSize, deviceData->device);
		case ShaderType::SHADERTYPE_PIXEL:
			return createPixelShader(buffer, bufferSize, deviceData->device);
		default:
			LOG_ERROR("[D3D11 ERROR] Shader is invalid!");
			return NULL;
		}
	}

	void RendererDevice::beginFrame()
	{
		PROFILE;
		// Reset the state for the frame
		deviceData->context->ClearState();
		deviceData->context->ClearDepthStencilView(deviceData->depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void RendererDevice::endFrame()
	{
		PROFILE;

		if (*cvar::r_vsync == 1)
			deviceData->swapChain->Present(1, 0);
		else
			deviceData->swapChain->Present(0, 0);
	}

	Pipeline *RendererDevice::createRasterizerPipeline(const StateDescriptor *stateDescriptor, InputLayout *inputLayout, Shader *vertexShader, Shader *pixelShader)
	{
		PROFILE;
		D3D11Pipeline *pipeline = new D3D11Pipeline();

		pipeline->header.state = *stateDescriptor; // make a copy so that the stateDescriptor can be thrown away
		pipeline->header.pixelShader = pixelShader;
		pipeline->header.vertexShader = vertexShader;
		pipeline->header.inputLayout = inputLayout;

		// Create states here!
		//pipeline->blendState = deviceData->blendState;
		//pipeline->rasterState2D = deviceData->rasterState2D;
		//pipeline->samplerState = deviceData->samplerState;

		D3D11_RASTERIZER_DESC rasterDesc;
		ZeroMemory(&rasterDesc, sizeof(rasterDesc));

		switch (stateDescriptor->fillMode)
		{
		default:
			LOG_WARNING("[D3D11RendererDevice] Invalid fillmode!");
			return NULL;
		case FILL_WIREFRAME:
			rasterDesc.FillMode = D3D11_FILL_WIREFRAME;
			break;
		case FILL_SOLID:
			rasterDesc.FillMode = D3D11_FILL_SOLID;
			break;
		}

		switch (stateDescriptor->cullMode)
		{
		default:
			LOG_WARNING("[D3D11RendererDevice] Invalid cullmode!");
			return NULL;
		case CULL_BACK:
			rasterDesc.CullMode = D3D11_CULL_BACK;
			break;
		case CULL_FRONT:
			rasterDesc.CullMode = D3D11_CULL_FRONT;
			break;
		case CULL_NONE:
			rasterDesc.CullMode = D3D11_CULL_NONE;
			break;
		}

		rasterDesc.DepthClipEnable = stateDescriptor->depthClipEnabled;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0f;

		HRESULT result = deviceData->device->CreateRasterizerState(&rasterDesc, &pipeline->rasterState);
		checkError(result);

		// Create the sample state
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = -FLT_MAX;
		sampDesc.MaxLOD = FLT_MAX;
		result = deviceData->device->CreateSamplerState(&sampDesc, &pipeline->samplerState);
		checkError(result);

		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(blendDesc));
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;

		switch (stateDescriptor->blendMode)
		{
		default:
			LOG_WARNING("[D3D11RendererDevice] Invalid blendMode!");
			return NULL;
		case BLEND_NONE:
			blendDesc.RenderTarget[0].BlendEnable = false;
			blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MAX;
			blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			break;
		case BLEND_MAX:
			blendDesc.RenderTarget[0].BlendEnable = true;
			blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_COLOR;
			blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_DEST_COLOR;
			blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MAX;
			blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
			blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_DEST_ALPHA;
			blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
			blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			break;
		case BLEND_ADD:
			blendDesc.RenderTarget[0].BlendEnable = true;
			blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_INV_DEST_ALPHA;
			blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			break;
		}

		deviceData->device->CreateBlendState(&blendDesc, &pipeline->blendState);

		D3D11_DEPTH_STENCIL_DESC depthDesc;
		ZeroMemory(&depthDesc, sizeof(depthDesc));

		if (stateDescriptor->depthClipEnabled)
			depthDesc.DepthEnable = true;
		else
			depthDesc.DepthEnable = false;

		depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthDesc.DepthFunc = D3D11_COMPARISON_LESS;

		depthDesc.StencilEnable = false;
		depthDesc.StencilReadMask = 0xFF;
		depthDesc.StencilWriteMask = 0xFF;

		// Stencil operations if pixel is back-facing
		depthDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depthDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		deviceData->device->CreateDepthStencilState(&depthDesc, &pipeline->depthState);

		return &pipeline->header;
	}

	RenderTarget *RendererDevice::createBackbufferRenderTarget()
	{
		D3D11RenderTarget *renderTarget = new D3D11RenderTarget();
		renderTarget->header.width = resolution.x;
		renderTarget->header.height = resolution.x;

		renderTarget->renderTargetTexture = deviceData->backBufferTexture;
		HRESULT result = deviceData->device->CreateRenderTargetView(renderTarget->renderTargetTexture, NULL, &renderTarget->renderTargetView);

		if (checkError(result))
		{
			LOG_ERROR("[RendererDevice] Failed to create backbuffer rendertarget!");
			return NULL;
		}

		return &renderTarget->header;
	}

	RenderTarget *RendererDevice::createRenderTarget(unsigned width, unsigned height)
	{
		D3D11RenderTarget *renderTarget = new D3D11RenderTarget();
		renderTarget->header.width = width;
		renderTarget->header.height = height;

		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		desc.Width = width;
		desc.Height = height;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		HRESULT result = deviceData->device->CreateTexture2D(&desc, NULL, &renderTarget->renderTargetTexture);
		checkError(result);

		D3D11_RENDER_TARGET_VIEW_DESC rtvd;
		ZeroMemory(&rtvd, sizeof(rtvd));

		rtvd.Format = desc.Format;
		rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvd.Texture2D.MipSlice = 0;

		result = deviceData->device->CreateRenderTargetView(renderTarget->renderTargetTexture, &rtvd, &renderTarget->renderTargetView);
		checkError(result);

		D3D11_SHADER_RESOURCE_VIEW_DESC rvd;
		ZeroMemory(&rvd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		rvd.Format = desc.Format;
		rvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		rvd.Texture2D.MipLevels = 1;
		rvd.Texture2D.MostDetailedMip = 0;

		result = deviceData->device->CreateShaderResourceView(renderTarget->renderTargetTexture, &rvd, &renderTarget->shaderResourceView);
		checkError(result);

		return &renderTarget->header;
	}

	Buffer *RendererDevice::createBuffer(BufferType bufferType, size_t size, BufferUsage usage)
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		desc.ByteWidth = size;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		switch (bufferType)
		{
		case engine::renderer::BUFFERTYPE_VERTEX:
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			break;
		case engine::renderer::BUFFERTYPE_INDEX:
			desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			break;
		case engine::renderer::BUFFERTYPE_CONSTANT:
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			break;
		default:
			LOG_WARNING("[RendererDevice] Invalid bufferType!");
			return NULL;
		}

		switch (usage)
		{
		case engine::renderer::BUFFERUSAGE_STATIC:
			desc.Usage = D3D11_USAGE_DEFAULT;
			break;
		case engine::renderer::BUFFERUSAGE_DYNAMIC:
			desc.Usage = D3D11_USAGE_DYNAMIC;
			break;
		default:
			LOG_WARNING("[RendererDevice] Invalid bufferusage!");
			return NULL;
		}

		D3D11Buffer *buffer = new D3D11Buffer();

		HRESULT result = deviceData->device->CreateBuffer(&desc, NULL, &buffer->buffer);

		if (checkError(result))
		{
			LOG_WARNING("[RendererDevice] Could not create buffer!");
			delete buffer;
			return NULL;
		}

		buffer->header.size = size;
		buffer->header.type = bufferType;
		buffer->header.usage = usage;
		buffer->mappedPointer = NULL;
		buffer->mutex = sys::createMutex();

		return &buffer->header;
	}

	void RendererDevice::mapBuffer(Buffer *buffer)
	{
		D3D11_MAPPED_SUBRESOURCE ms;
		D3D11Buffer *b = (D3D11Buffer*)buffer;
		deviceData->context->Map(b->buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);

		b->mappedPointer = ms.pData;
	}

	void RendererDevice::unmapBuffer(Buffer *buffer)
	{
		D3D11Buffer *b = (D3D11Buffer*)buffer;
		deviceData->context->Unmap(b->buffer, NULL);
		b->mappedPointer = NULL;
	}

	void RendererDevice::copyData(Buffer *buffer, void *data, size_t size)
	{
		D3D11Buffer *b = (D3D11Buffer*)buffer;

		assert(b->mappedPointer != NULL);
		memcpy(b->mappedPointer, data, size);
	}

	void RendererDevice::copyData(Buffer *buffer, size_t offset, void *data, size_t size)
	{
		D3D11Buffer *b = (D3D11Buffer*)buffer;

		assert(b->mappedPointer != NULL);
		memcpy((char*)b->mappedPointer + offset, data, size);

	}

	InputLayout *RendererDevice::createInputLayout(const InputLayoutDesc &inputLayoutDesc, ShaderResource *vertexResource)
	{
		D3D11InputLayout *d3dlayout = new D3D11InputLayout();
		InputLayout *layout = &d3dlayout->header;

		assert(vertexResource != NULL);

		layout->stride = 0;
		layout->inputElementCount = inputLayoutDesc.inputElementCount;

		layout->inputElements = (InputElement*)malloc(sizeof(InputElement) * inputLayoutDesc.inputElementCount);

		size_t offset = 0;

		D3D11_INPUT_ELEMENT_DESC inputElementDescriptions[MAX_INPUTLAYOUT_SIZE];

		for (unsigned i = 0; i < inputLayoutDesc.inputElementCount; ++i)
		{
			// Copy data over
			layout->inputElements[i] = inputLayoutDesc.inputElements[i];

			D3D11_INPUT_ELEMENT_DESC desc;
			desc.SemanticIndex = 0;
			desc.InstanceDataStepRate = 0;
			desc.InputSlot = 0;
			desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

			switch (layout->inputElements[i].semantic)
			{
			case engine::renderer::SEMANTIC_POSITION:
				desc.SemanticName = "SV_POSITION";
				break;
			case engine::renderer::SEMANTIC_NORMAL:
				desc.SemanticName = "NORMAL";
				break;
			case engine::renderer::SEMANTIC_TEXCOORD:
				desc.SemanticName = "TEXCOORD";
				break;
			case engine::renderer::SEMANTIC_COLOR:
				desc.SemanticName = "COLOR";
			default:
				LOG_ERROR("Invalid semantic name!");
				return NULL;
			}

			switch (layout->inputElements[i].inputFormat)
			{
			case engine::renderer::INPUTFORMAT_FLOAT_X:
				desc.Format = DXGI_FORMAT_R32_FLOAT;
				break;
			case engine::renderer::INPUTFORMAT_FLOAT_XY:
				desc.Format = DXGI_FORMAT_R32G32_FLOAT;
				break;
			case engine::renderer::INPUTFORMAT_FLOAT_XYZ:
				desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			case engine::renderer::INPUTFORMAT_FLOAT_XYZW:
				desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;
			default:
				LOG_ERROR("Invalid input format!");
				return NULL;
			}

			desc.AlignedByteOffset = offset;

			inputElementDescriptions[i] = desc;

			// Handle stride
			layout->stride += InputFormatToSize[layout->inputElements[i].inputFormat];

			offset = layout->stride;
		}

		// inputElementDescriptions should now be full, create the D3D11 inputlayout
		D3D11Shader *vs = (D3D11Shader*)vertexResource->shader;

		HRESULT result = deviceData->device->CreateInputLayout(inputElementDescriptions, inputLayoutDesc.inputElementCount, vertexResource->file->getRawData(), vertexResource->file->getSize(), &d3dlayout->layout);
		checkError(result);

		return layout;
	}

	Texture *RendererDevice::createCubemapTextureFromTextures(TextureResource *textureResources[6])
	{
		// Get the D3D11 textures out form the textureResources
		D3D11Texture *sources[6];

		for (unsigned i = 0; i < 6; ++i)
			sources[i] = (D3D11Texture*)textureResources[i]->getTexture();

		D3D11Texture *texture = new D3D11Texture();

		texture->header.width = sources[0]->header.width;
		texture->header.height = sources[0]->header.width;
		texture->header.type = TEXTURETYPE_CUBEMAP;

		D3D11_TEXTURE2D_DESC texDesc;
		texDesc.Width = texture->header.width;
		texDesc.Height = texture->header.height;
		texDesc.MipLevels = 1;
		texDesc.ArraySize = 6;
		texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		texDesc.CPUAccessFlags = 0;
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		texDesc.CPUAccessFlags = 0;
		texDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

		D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
		SMViewDesc.Format = texDesc.Format;
		SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
		SMViewDesc.TextureCube.MipLevels = texDesc.MipLevels;
		SMViewDesc.TextureCube.MostDetailedMip = 0;

		D3D11_SUBRESOURCE_DATA pData[6];

		void *data = malloc(texture->header.width * texture->header.width * 6 * 2);

		size_t offset = 0;

		for (unsigned i = 0; i < 6; ++i)
		{
			assert(texture->header.width == sources[i]->header.width);
			assert(texture->header.height == sources[i]->header.height);

			GUID guid;
			size_t size;

			HRESULT result = sources[i]->resource->GetPrivateData(guid, &size, (char*)data + offset);
			checkError(result);

			offset += size;

			pData[i].SysMemPitch = texture->header.width * 4;
			pData[i].SysMemSlicePitch = 0;
			pData[i].pSysMem = data;
		}

		ID3D11Texture2D *tex;
		deviceData->device->CreateTexture2D(&texDesc, &pData[0], &tex);

		free(data);

		texture->resource = tex;

		// HEADER

		return NULL;
	}


	void RendererDevice::draw(const DrawDescriptor &desc)
	{
		switch (desc.topology)
		{
		default:
			LOG_WARNING("Invalid topology!");
			return;
		case PRIMITIVETOPOLOGY_LINELIST:
			deviceData->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
			break;
		case PRIMITIVETOPOLOGY_TRIANGLELIST:
			deviceData->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			break;
		}

		deviceData->context->DrawIndexed(desc.drawCount, 0, 0);
	}

	void RendererDevice::clear(const RenderTarget *target, const math::Vec4 color)
	{
		D3D11RenderTarget *t = (D3D11RenderTarget*)target;

		float c[4] = { color.x, color.y, color.z, color.w };

		deviceData->context->ClearRenderTargetView(t->renderTargetView, c);
	}

	void RendererDevice::setPipeline(Pipeline *p)
	{
		this->pipeline = p;

		D3D11Pipeline *pipeline = (D3D11Pipeline*)p;

		D3D11Shader *vertexShader = (D3D11Shader*)pipeline->header.vertexShader;
		D3D11Shader *pixelShader = (D3D11Shader*)pipeline->header.pixelShader;
		D3D11InputLayout *inputLayout = (D3D11InputLayout*)pipeline->header.inputLayout;

		deviceData->context->IASetInputLayout(inputLayout->layout);
		deviceData->context->VSSetShader(vertexShader->vertexShader, NULL, 0);
		deviceData->context->PSSetShader(pixelShader->pixelShader, NULL, 0);

		deviceData->context->PSSetSamplers(0, 1, &pipeline->samplerState);
		deviceData->context->RSSetState(pipeline->rasterState);
		deviceData->context->OMSetBlendState(pipeline->blendState, NULL, 0xFFFFFFFF);

		if (pipeline->header.state.depthClipEnabled == true)
			deviceData->context->OMSetDepthStencilState(pipeline->depthState, 0);
	}

	void RendererDevice::setPSTextureResource(unsigned slot, Texture *resource)
	{
		D3D11Texture *texture = (D3D11Texture*)resource;

		deviceData->context->PSSetShaderResources(slot, 1, &texture->shaderResource);
	}

	void RendererDevice::setPSTextureResource(unsigned slot, RenderTarget *resource)
	{
		D3D11RenderTarget *target = (D3D11RenderTarget*)resource;

		deviceData->context->PSSetShaderResources(slot, 1, &target->shaderResourceView);
	}

	void RendererDevice::setBackbuffer(RenderTarget *target)
	{
		D3D11RenderTarget *t = (D3D11RenderTarget*)target;

		if (pipeline->state.depthClipEnabled == false)
			deviceData->context->OMSetRenderTargets(1, &t->renderTargetView, NULL);
		else
			deviceData->context->OMSetRenderTargets(1, &t->renderTargetView, deviceData->depthStencilView);
	}

	void RendererDevice::setViewport(Viewport *viewport)
	{
		D3D11_VIEWPORT port;
		port.Width = float(viewport->width);
		port.Height = float(viewport->height);
		port.TopLeftX = float(viewport->leftX);
		port.TopLeftY = float(viewport->leftY);
		port.MinDepth = 0.f;
		port.MaxDepth = 1.f;

		deviceData->context->RSSetViewports(1, &port);
	}

	void RendererDevice::setVertexBuffer(Buffer *buffer)
	{
		D3D11Buffer *b = (D3D11Buffer*)buffer;
		assert(pipeline != NULL);

		unsigned offsetZero = 0;
		deviceData->context->IASetVertexBuffers(0, 1, &b->buffer, &pipeline->inputLayout->stride, &offsetZero);
	}

	void RendererDevice::setIndexBuffer(Buffer *buffer)
	{
		D3D11Buffer *b = (D3D11Buffer*)buffer;

		deviceData->context->IASetIndexBuffer(b->buffer, DXGI_FORMAT_R16_UINT, 0);
	}


	void RendererDevice::setVSConstantBuffer(Buffer *buffer, unsigned slot)
	{
		D3D11Buffer *b = (D3D11Buffer*)buffer;

		deviceData->context->VSSetConstantBuffers(slot, 1, &b->buffer);
	}

	void RendererDevice::setPSConstantBuffer(Buffer *buffer, unsigned slot)
	{
		D3D11Buffer *b = (D3D11Buffer*)buffer;

		deviceData->context->PSSetConstantBuffers(slot, 1, &b->buffer);
	}

}
}

#endif