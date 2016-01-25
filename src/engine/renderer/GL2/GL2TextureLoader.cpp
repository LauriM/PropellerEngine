// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/renderer/TextureLoader.h"

#if defined (GL2)

#include "engine/renderer/RendererSystem.h"
#include "engine/file/FileData.h"
#include "engine/renderer/GL2/GL2Helper.h"
#include "engine/renderer/GL2/GL2Texture.h"

#include <lodepng/lodepng.h>
#ifndef OS_ANDROID
#include <GL/glew.h>
#include <GL/GL.h>
#else
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

namespace engine {
namespace renderer {

	resource::Resource *TextureLoader::handlePNG(const String &name)
	{
		file::File file = fileManager->openFile(name);

		if (!file.isValid())
			return NULL;

		std::vector<unsigned char> imageData;
		unsigned width, height;

		//TODO: add forcing check that the texture is power of two.

		unsigned error = lodepng::decode(imageData, width, height, (unsigned char*)file->getRawData(), (size_t)file->getSize());

		if (error != 0)
		{
			LOG_ERROR("Failed to decode image with lodepng!");
			return NULL;
		}

		GLuint id;

		glGenTextures(1, &id);
		GLERRORCHECK;

		glBindTexture(GL_TEXTURE_2D, id);
		GLERRORCHECK;

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		GLERRORCHECK;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		GLERRORCHECK;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &imageData[0]);
		GLERRORCHECK;


		LOG_INFO("Texture loaded ! w: " << width << " h: " << height << " texture_id: " << id);

		GL2Texture *texture = new GL2Texture();

		texture->textureId = id;
		texture->header.width = width;
		texture->header.height = height;
		texture->header.type = TEXTURETYPE_NORMAL;

		TextureResource *textureResource = new TextureResource(&texture->header);
		textureResource->setName(name);

		return textureResource;
	}

	resource::Resource *TextureLoader::handleDDS(const String &name)
	{
		LOG_WARNING("[TextureLoader] GL2 doesn't support DDS files!");
		return NULL;
	}

	resource::Resource *TextureLoader::getResourceByName(const String &name)
	{
		if (name.find(".png") != String::npos)
			return handlePNG(name);

		return NULL;
	}

	void TextureLoader::getTypesHandled(std::vector<String> &typesHandled)
	{
		typesHandled.push_back(".png");
	}

	void TextureLoader::disposeResource(resource::Resource *resource)
	{
		LOG_ERROR("Texture disposing invalid! LEAKS MEMORY!");
	}

}
}

#endif