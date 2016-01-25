// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/renderer/RendererBackend.h"

#if defined(GL2)

#ifndef OS_ANDROID
#include <GL/glew.h>
#include <GL/GL.h>
#else
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#include "engine/renderer/ShaderLoader.h"
#include "engine/renderer/RendererSystem.h"
#include "engine/file/FileData.h"
#include "engine/renderer/GL2/GL2Helper.h"
#include "engine/renderer/GL2/GL2Shader.h"

namespace engine {
namespace renderer {

	void ShaderLoader::getTypesHandled(std::vector<String> &typesHandled)
	{
		typesHandled.push_back(".cso");
	}

	bool handleShaderCompileErrors(GLuint shader)
	{
		GLint result;
		int logLength;
		bool error = false;

		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		char errorMsg[1200] = "\n";
		glGetShaderInfoLog(shader, logLength, NULL, errorMsg);

		if (result == GL_FALSE)
			error = true;

		if (logLength < 2)
			return true; // no error output

		if (error)
		{
			LOG_ERROR(errorMsg);
			return false;
		}
		else
		{
			LOG_WARNING(errorMsg);
			return true;
		}
	}

	GL2Shader *createVertexShader(const void *buffer, const size_t bufferSize)
	{
		LOG_INFO("[ShaderLoader] creating vertex shader");
		GLuint shaderId = glCreateShader(GL_VERTEX_SHADER);
		GLERRORCHECK;

		const GLchar *str = (GLchar*)buffer;

		glShaderSource(shaderId, 1, &str, (GLint*)&bufferSize);
		glCompileShader(shaderId);

		if (handleShaderCompileErrors(shaderId))
			LOG_INFO("Vertex Shader loaded succesfully.");

		GL2Shader *shader = new GL2Shader();
		shader->header.type = SHADERTYPE_VERTEX;
		shader->shaderId = shaderId;

		return shader;
	}

	GL2Shader *createFragmentShader(const void *buffer, const size_t bufferSize)
	{
		LOG_INFO("[ShaderLoader] creating fragment shader");
		GLuint shaderId = glCreateShader(GL_FRAGMENT_SHADER);
		GLERRORCHECK;

		const GLchar *str = (GLchar*)buffer;

		glShaderSource(shaderId, 1, &str, (GLint*)&bufferSize);
		glCompileShader(shaderId);

		if (handleShaderCompileErrors(shaderId))
			LOG_INFO("Vertex Shader loaded succesfully.");

		GL2Shader *shader = new GL2Shader();
		shader->header.type = SHADERTYPE_PIXEL;
		shader->shaderId = shaderId;

		return shader;
	}

	resource::Resource *ShaderLoader::getResourceByName(const String &n)
	{
		// Swap out .cso to .glsl, this way we can find the glsl version of the shader
		String name = n.substr(0, n.find(".cso")) + ".glsl";

		file::File file = fileManager->openFile(name);

		if (!file.isValid())
			return NULL;

		GL2Shader *shader = NULL;

		if (name.find("_p.glsl") != String::npos)
			shader = createFragmentShader(file->getRawData(), file->getSize());

		if (name.find("_vv.glsl") != String::npos)
			shader = createVertexShader(file->getRawData(), file->getSize());

		ShaderResource *resource = new ShaderResource();

		resource->setName(name);
		resource->file = file;
		resource->shader = &shader->header;

		LOG_INFO("[ShaderLoader] Shader loaded: " << name);
		return resource;
	}

	void ShaderLoader::disposeResource(resource::Resource *resource)
	{
		LOG_ERROR("Shader disposing not implemented! Shader should be freed and memory released!");
	}
}
}

#endif