// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_SHADERRESOURCE_H
#define ENGINE_RENDERER_SHADERRESOURCE_H

#include "engine/resource/Resource.h"
#include "engine/renderer/Shader.h"
#include "engine/file/FileData.h"

namespace engine {
namespace renderer {

	class ShaderResource : public resource::Resource
	{
	public:
		Shader *shader;
		file::File file;

		bool hasGPUResource() { return true; }
	};

}
}

#endif