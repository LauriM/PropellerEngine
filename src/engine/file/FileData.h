// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_FILE_FILEDATA_H
#define ENGINE_FILE_FILEDATA_H

#include "engine/lang/ReferenceCountable.h"
#include "engine/lang/ReferenceCountedPointer.h"
#include "engine/file/Archive.h"
#include "engine/stream/InputStream.h"

namespace engine {
namespace file {

	class FileData : public lang::ReferenceCountable
	{
	private:
		void *data;
		unsigned size;

		Archive *archive;

	public:
		FileData()
			: data(NULL)
			, size(0)
			, archive(NULL)
		{}

		FileData(void *data, unsigned size, Archive *archive) 
			: ReferenceCountable()
			, data(data)
			, size(size)
			, archive(archive)
		{ }

		const void * getRawData() const
		{
			return data;
		}

		const unsigned getSize() const
		{
			return size;
		}

		void onReferenceReleased()
		{
			archive->releaseFile(this);
		}

		stream::InputStream<stream::NativeEndian> getInputStream() const
		{
			return stream::InputStream<stream::NativeEndian>(data);
		}
	};

	typedef engine::lang::ReferenceCountedPointer<FileData> File;

}
}

#endif