// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/renderer/RendererBackend.h"

#if defined(D3D11)

#include "engine/renderer/ShaderLoader.h"
#include "engine/renderer/RendererSystem.h"

//Hack
#include "engine/renderer/RendererDevice.h"

namespace engine {
namespace renderer {

	void ShaderLoader::getTypesHandled(std::vector<String> &typesHandled)
	{
		typesHandled.push_back(".cso");
	}

	resource::Resource *ShaderLoader::getResourceByName(const String &name)
	{
		file::File file = fileManager->openFile(name);

		if (!file.isValid())
		{
			LOG_WARNING("[ShaderLoader] Could not open file " << name);
			return NULL;
		}

		//Detect shader type
		ShaderType type = SHADERTYPE_INVALID;

		if (name.find("_p") != String::npos)
			type = SHADERTYPE_PIXEL;

		if (name.find("_vv") != String::npos)
			type = SHADERTYPE_VERTEX;

		if (type == SHADERTYPE_INVALID)
		{
			LOG_WARNING("[ShaderLoader] Could not detect shader type! Did you forget the _p/_vv suffix?");
			return NULL;
		}

		LOG_INFO("PERKELE: " << rendererSystem->getDevice());
		LOG_INFO("JOTAIN: " << rendererSystem->getDevice()->getDeviceData());

		Shader *shader = rendererSystem->getDevice()->createShader(type, file->getRawData(), file->getSize());

		if (shader == NULL)
		{
			LOG_WARNING("[ShaderLoader] Failed to create shader on the GPU!");
			return NULL;
		}

		ShaderResource *shaderResource = new ShaderResource();

		shaderResource->shader = shader;
		shaderResource->file = file;

		shaderResource->setName(name);

		LOG_INFO("[ShaderLoader] Loaded shader " << name);
		return shaderResource;
	}


	void ShaderLoader::disposeResource(resource::Resource *resource)
	{
		LOG_WARNING("D3D11 shader disposing not implemented, hopefully the context destruction takes care of this...");
	}
}
}

#endif