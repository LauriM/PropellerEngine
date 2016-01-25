// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/renderer/TextureLoader.h"

#if defined (D3D11)

#include "engine/renderer/D3D11/D3D11Texture.h"
#include "engine/renderer/RendererSystem.h"
#include "engine/renderer/D3D11/D3D11DeviceData.h"
#include <DirectXTK/WICTextureLoader.h>
#include <DirectXTK/DDSTextureLoader.h>

namespace engine {
namespace renderer {

	resource::Resource *TextureLoader::handlePNG(const String &name)
	{
		PROFILE;

		ID3D11Resource *resource = NULL;
		ID3D11ShaderResourceView *shaderResource = NULL;

		file::File file = fileManager->openFile(name);

		if (!file.isValid())
		{
			LOG_WARNING("[TextureLoader] Could not open file " << name);
			return NULL;
		}

		LOG_INFO("PERKELE: " << rendererSystem->getDevice());
		LOG_INFO("JOTAIN: " << rendererSystem->getDevice()->getDeviceData());
		LOG_INFO("HAHAAA: " << rendererSystem->getDevice()->getDeviceData()->device);

		HRESULT res = DirectX::CreateWICTextureFromMemory(rendererSystem->getDevice()->getDeviceData()->device, (uint8_t*)file->getRawData(), size_t(file->getSize()), &resource, &shaderResource);

		if (res != S_OK)
		{
			LOG_WARNING("[TextureLoader] Could not load image from file! Broken image? " << name);
			return NULL;
		}

		ID3D11Texture2D *text = (ID3D11Texture2D*)resource;
		D3D11_TEXTURE2D_DESC desc;
		text->GetDesc(&desc);

		D3D11Texture *texture = new D3D11Texture();

		texture->resource = resource;
		texture->shaderResource = shaderResource;
		texture->header.width = desc.Width;
		texture->header.height = desc.Height;
		texture->header.type = TEXTURETYPE_NORMAL;

		LOG_INFO("[TextureLoader] Loaded " << name);

		TextureResource *textureResource = new TextureResource(&texture->header);
		textureResource->setName(name);

		return textureResource;
	}

	resource::Resource *TextureLoader::handleDDS(const String &name)
	{
		PROFILE;

		ID3D11Resource *resource;
		ID3D11ShaderResourceView *shaderResource;

		file::File file = fileManager->openFile(name);

		if (!file.isValid())
		{
			LOG_WARNING("[TextureLoader] Could not open file " << name);
			return NULL;
		}

		HRESULT res = DirectX::CreateDDSTextureFromMemory(rendererSystem->getDevice()->getDeviceData()->device, (uint8_t*)file->getRawData(), size_t(file->getSize()), &resource, &shaderResource);

		if (res != S_OK)
		{
			LOG_WARNING("[TextureLoader] Could not load image from file! Broken image? " << name);
			return NULL;
		}

		ID3D11Texture2D *text = (ID3D11Texture2D*)resource;
		D3D11_TEXTURE2D_DESC desc;
		text->GetDesc(&desc);

		D3D11Texture *texture = new D3D11Texture();

		texture->resource = resource;
		texture->shaderResource = shaderResource;
		texture->header.width = desc.Width;
		texture->header.height = desc.Height;
		texture->header.type = TEXTURETYPE_NORMAL;

		LOG_INFO("[TextureLoader] Loaded " << name);

		TextureResource *textureResource = new TextureResource(&texture->header);
		textureResource->setName(name);

		return textureResource;
	}

	resource::Resource *TextureLoader::getResourceByName(const String &name)
	{
		if (name.find(".dds") != String::npos)
			return handleDDS(name);

		if (name.find(".png") != String::npos)
			return handlePNG(name);

		LOG_WARNING("[TextureLoader] Failed to handle filename.");
		return NULL;
	}

	void TextureLoader::getTypesHandled(std::vector<String> &typesHandled)
	{
		typesHandled.push_back(".png");
		typesHandled.push_back(".dds");
	}

	void TextureLoader::disposeResource(resource::Resource *resource)
	{
		D3D11Texture *text = (D3D11Texture*)resource;

		LOG_WARNING("D3D11 texture dispose not implemented, hopefully the context destruction handles this...");
	}

}
}

#endif