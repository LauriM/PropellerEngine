// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/renderer/RendererBackend.h"
#include "engine/renderer/TextureLoader.h"

#if defined (NULLRENDERER)

#include <lodepng/lodepng.h>

namespace engine {
namespace renderer {

	resource::Resource *TextureLoader::handlePNG(const String &name)
	{
		PROFILE;
		std::vector<unsigned char> imageData;
		unsigned width, height;

		file::File file = fileManager->openFile(name);

		//TODO: add forcing check that the texture is power of two.

		unsigned error = lodepng::decode(imageData, width, height, (unsigned char*)file->getRawData(), (size_t)file->getSize());

		assert(error == 0);

		LOG_INFO("Texture loaded !");

		Texture *texture = new Texture();

		texture->width = width;
		texture->height = height;
		texture->type = TEXTURETYPE_NORMAL;

		return new TextureResource(texture);
	}

	resource::Resource *TextureLoader::handleDDS(const String &name)
	{
		PROFILE;

		assert(false); //This should never be called

		return NULL;
	}

	resource::Resource *TextureLoader::getResourceByName(const String &name)
	{
		PROFILE;

		if (name.find(".png") != String::npos)
			return handlePNG(name);

		LOG_WARNING("[TextureLoader] Failed to handle filename.");
		return NULL;
	}

	void TextureLoader::getTypesHandled(std::vector<String> &typesHandled)
	{
		typesHandled.push_back(".png");
	}

	void TextureLoader::disposeResource(resource::Resource *resource) { }

}
}

#endif
