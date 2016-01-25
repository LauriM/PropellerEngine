// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/renderer/PropellerModelLoader.h"
#include "engine/renderer/ModelResource.h"

#include "engine/renderer/RendererSystem.h"
#include "engine/renderer/Buffer.h"
#include "engine/preprocessor/macros.h"
#include "engine/renderer/RendererBackend.h"

#include "engine/renderer/PropellerModelVersionIdentifier.h"

/*

# PropellerModel version history:

1 - first version
2 - Adding textureCoordinates to the format

.PropellerModel format description

static, "PROPELLERMODEL"
unsigned, version

unsigned, verticesCount
	float, vertices

unsigned indicesCount
	uint16_t indices
*/

namespace engine {
namespace renderer {

	void PropellerModelLoader::getTypesHandled(std::vector<String> &typesHandled)
	{
		typesHandled.push_back(".PropellerModel");
	}

	resource::Resource *PropellerModelLoader::getResourceByName(const String &name)
	{
		PROFILE;
		LOG_INFO("PROPELLERLOADER! Now handling: " << name);

		LOG_INFO("[PropellerModelLoader] Loading file " << name);

		file::File modelFile = fileManager->openFile(name);

		LOG_INFO("[PropellerModelLoader] Load done!");

		if (!modelFile)
		{
			LOG_WARNING("Failed to open model file!");
			return NULL;
		}

		// check the model header
#ifndef HTML5
		stream::InputStream<stream::SerializationEndian> inputStream = modelFile->getInputStream();
#else
		LOG_WARNING("INPUTSTREAM HACK IMPLEMENTED FOR HTML5! WARN! TODO!");
		stream::InputStream<stream::NativeEndian> nativeStream= modelFile->getInputStream();
		stream::InputStream<stream::SerializationEndian> *strm = (stream::InputStream<stream::SerializationEndian>*)&nativeStream;
		engine::stream::InputStream<stream::SerializationEndian> inputStream = *strm;
#endif

		LOG_INFO("[PropellerModelLoader] Stream created");

		char versionIdentifier[sizeof(PROPELLER_MODEL_IDENTIFIER)];
		inputStream.read(versionIdentifier, PROPELLER_MODEL_IDENTIFIER_SIZE);

		char correctIdentifier[] = PROPELLER_MODEL_IDENTIFIER;

		if (String(versionIdentifier).substr(0, PROPELLER_MODEL_IDENTIFIER_SIZE) != String(PROPELLER_MODEL_IDENTIFIER).substr(0, PROPELLER_MODEL_IDENTIFIER_SIZE))
		{
			LOG_WARNING(name << " is not a valid PropellerModel!");
			return NULL;
		}

		unsigned modelFormatVersion;
		inputStream.read(modelFormatVersion);

		LOG_INFO("[PropellerModelLoader] Model version identified as: " << modelFormatVersion);

		resource::Resource *res = NULL;

		switch (modelFormatVersion)
		{
		case 1:
			res = loadModelVersion1(inputStream);
			res->setName(name);
			break;
		case 2:
			res = loadModelVersion2(inputStream);
			res->setName(name);
			break;
		default:
			LOG_ERROR("invalid model version! (" << modelFormatVersion << ")");
			return NULL;
		}

		return res;

	}

	resource::Resource *PropellerModelLoader::loadModelVersion1(stream::InputStream<stream::SerializationEndian> &inputStream)
	{
		LOG_INFO("loading model version 1");

		float *meshVertices;
		uint16_t *meshIndices;

		unsigned verticesCount;
		unsigned indicesCount;

		inputStream.read(verticesCount);

		meshVertices = (float*)malloc(sizeof(float) * verticesCount);

		for (unsigned i = 0; i < verticesCount; ++i)
			inputStream.read(meshVertices[i]);

		inputStream.read(indicesCount);

		meshIndices = (uint16_t*)malloc(sizeof(uint16_t) * indicesCount);

		for (unsigned i = 0; i < indicesCount; ++i)
			inputStream.read(meshIndices[i]);

		// Create the buffers in the GPU
		RendererDevice *device = rendererSystem->getDevice();

		lang::ScopedPtr<Buffer> vertexBuffer = device->createBuffer(BUFFERTYPE_VERTEX, sizeof(float) * verticesCount, BUFFERUSAGE_STATIC);
		lang::ScopedPtr<Buffer> indexBuffer = device->createBuffer(BUFFERTYPE_INDEX, sizeof(uint16_t) * indicesCount, BUFFERUSAGE_STATIC);;

		device->mapBuffer(vertexBuffer.getPtr());
		device->copyData(vertexBuffer.getPtr(), meshVertices, sizeof(float) * verticesCount);
		device->unmapBuffer(vertexBuffer.getPtr());

		device->mapBuffer(indexBuffer.getPtr());
		device->copyData(indexBuffer.getPtr(), meshIndices, sizeof(uint16_t) * indicesCount);
		device->unmapBuffer(indexBuffer.getPtr());;

		//TODO: check error!

		ModelResource *resource = new ModelResource();

		resource->indexBuffer.swap(indexBuffer);
		resource->vertexBuffer.swap(vertexBuffer);
		resource->strideSize = sizeof(float) * 6;
		resource->indicesCount = indicesCount;

		free(meshIndices);
		free(meshVertices);

		return resource;
	}

	resource::Resource *PropellerModelLoader::loadModelVersion2(stream::InputStream<stream::SerializationEndian> &inputStream)
	{
		LOG_INFO("loading model version 2");

		float *meshVertices;
		uint16_t *meshIndices;

		unsigned verticesCount;
		unsigned indicesCount;

		inputStream.read(verticesCount);

		meshVertices = (float*)malloc(sizeof(float) * verticesCount);

		for (unsigned i = 0; i < verticesCount; ++i)
			inputStream.read(meshVertices[i]);

		inputStream.read(indicesCount);

		meshIndices = (uint16_t*)malloc(sizeof(uint16_t) * indicesCount);

		for (unsigned i = 0; i < indicesCount; ++i)
			inputStream.read(meshIndices[i]);

		// Create the buffers in the GPU
		RendererDevice *device = rendererSystem->getDevice();

		lang::ScopedPtr<Buffer> vertexBuffer = device->createBuffer(BUFFERTYPE_VERTEX, sizeof(float) * verticesCount, BUFFERUSAGE_DYNAMIC);
		lang::ScopedPtr<Buffer> indexBuffer = device->createBuffer(BUFFERTYPE_INDEX, sizeof(uint16_t) * indicesCount, BUFFERUSAGE_DYNAMIC);

		device->mapBuffer(vertexBuffer.getPtr());
		device->copyData(vertexBuffer.getPtr(), meshVertices, sizeof(float) * verticesCount);
		device->unmapBuffer(vertexBuffer.getPtr());

		device->mapBuffer(indexBuffer.getPtr());
		device->copyData(indexBuffer.getPtr(), meshIndices, sizeof(uint16_t) * indicesCount);
		device->unmapBuffer(indexBuffer.getPtr());

		//TODO: check error!

		ModelResource *resource = new ModelResource();

		resource->indexBuffer.swap(indexBuffer);
		resource->vertexBuffer.swap(vertexBuffer);
		resource->strideSize = sizeof(float) * 9;
		resource->indicesCount = indicesCount;

		free(meshIndices);
		free(meshVertices);

		return resource;
	}

	void PropellerModelLoader::disposeResource(resource::Resource *resource)
	{
		LOG_INFO("Disposing mesh stuff not implemented! Context reload is going to fail!");
	}

}
}
