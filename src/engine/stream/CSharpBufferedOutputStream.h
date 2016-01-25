// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_STREAM_CSHARPOUTPUTSTREAM_H
#define ENGINE_STREAM_CSHARPOUTPUTSTREAM_H

#include "engine/stream/BufferedOutputStream.h"
#include "engine/stream/Endian.h"

#include "editorbackend/entityeditor/EntityEditTargetType.h"

namespace engine {
namespace stream {

	// CSharp output streams are always buffered and nativeEndian.

	class CSharpBufferedOutputStream : public BufferedOutputStream<NativeEndian>
	{
	public:
		CSharpBufferedOutputStream()
			: BufferedOutputStream()
		{ }

		using OutputStream::write;
		using OutputStream::data;

		void write(intptr_t v)
		{
			if (!tryResize(index + sizeof v))
				return;
			NativeEndian::convert(v);
			*(intptr_t *)(data + index) = v;
			index += sizeof v;
		}

		void read(editor::EntityEditTargetType &v)
		{
			v = *(editor::EntityEditTargetType *)(data + index);
			//TODO: Conversion should happen here? hack todo
			index += sizeof v;
		}
	};

}
}

#endif