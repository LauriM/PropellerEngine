// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_FILE_ANDROIASSETMANAGERARCHIVE_H
#define ENGINE_FILE_ANDROIASSETMANAGERARCHIVE_H

#ifdef OS_ANDROID

#include "engine/file/FileData.h"
#include "engine/file/Archive.h"

PROPELLER_FORWARD_DECLARE(AAssetManager);

namespace engine {
namespace file {

	class AndroidAssetManagerArchive : public Archive
	{
	private:
		AAssetManager *assetManager;

	public:
		AndroidAssetManagerArchive(AAssetManager *assetManager)
			: assetManager(assetManager)
		{ }

		bool const canWrite() const;
		bool const canRead() const;

		bool listFiles(FileList &out);

		const String getName() const { return "AndroidAssetManager"; }

		File openFile(const String &path);
		void releaseFile(FileData *file);
	};

}
}


#endif
#endif