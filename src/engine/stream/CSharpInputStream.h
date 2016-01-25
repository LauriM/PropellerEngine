// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_STREAM_CSHARPINPUTSTREAM_H
#define ENGINE_STREAM_CSHARPINPUTSTREAM_H

#include "engine/stream/InputStream.h"

#include "editorbackend/entityeditor/EntityEditTargetType.h"

namespace engine {
namespace stream {

	// Extends the regular InputStream with c# types.
	class CSharpInputStream : public InputStream<NativeEndian>
	{
	public:
		CSharpInputStream(volatile void *data)
			: InputStream(data)
		{ }

		using InputStream::read;

		void read(intptr_t &v)
		{
			v = *(intptr_t *)(data + index);
			NativeEndian::convert(v);
			index += sizeof v;
		}
		
		void read(uintptr_t &v)
		{
			v = *(uintptr_t *)(data + index);
			NativeEndian::convert(v);
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