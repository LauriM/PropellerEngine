// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/lang/ReferenceCountedPointer.h"
#include "engine/file/AndroidAssetManagerArchive.h"

#ifdef OS_ANDROID

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

namespace engine {
namespace file {

	bool const AndroidAssetManagerArchive::canWrite() const
	{
		return false;
	}

	bool const AndroidAssetManagerArchive::canRead() const
	{
		return true;
	}

	bool AndroidAssetManagerArchive::listFiles(FileList &out)
	{
		AAssetDir *dir = AAssetManager_openDir(assetManager, "");

		const char *data;

		for (;;)
		{
			 data = AAssetDir_getNextFileName(dir);

			 if (data == NULL)
				 break;

			 LOG_INFO("Hahahahaha: " << data);
			 out.addFile(data);
		} 

		AAssetDir_close(dir);
	}

	File AndroidAssetManagerArchive::openFile(const String &path)
	{
		LOG_INFO("[AndroidAsset] opening file: " << path);
		AAsset *asset = AAssetManager_open(assetManager, path.c_str(), AASSET_MODE_BUFFER);
		LOG_INFO("[AndroidAsset] asset opened");

		if (asset == NULL)
			return File();

		const void *ptr = AAsset_getBuffer(asset);
		size_t size = AAsset_getLength(asset);

		if (ptr == NULL)
			return File();

		//TODO: MEMORY LEAKS, asset IS NOT HANDLED

		LOG_INFO("[AndroidAsset] asset pointers resolved");
		LOG_INFO("[AndroidAsset] ptr: " << ptr << " size: " << size);

		return File(new FileData((void*)ptr, size, this));
	}

	void AndroidAssetManagerArchive::releaseFile(FileData *file)
	{
		LOG_ERROR("AndroidAssetManagerArchive LEAKS MEMORY WITH asset !");
	}

}
}

#endif
