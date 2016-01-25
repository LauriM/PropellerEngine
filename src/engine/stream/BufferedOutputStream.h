// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_STREAM_BUFFEREDOUTPUTSTREAM_H
#define ENGINE_STREAM_BUFFEREDOUTPUTSTREAM_H

#include "engine/stream/OutputStream.h"

namespace engine {
namespace stream {

	template <typename Endianess>
	class BufferedOutputStream : public OutputStream<Endianess>
	{
	private:
		typedef OutputStream<Endianess> BaseClass;

		using BaseClass::data;
		using BaseClass::size;

	public:
		BufferedOutputStream()
			: BaseClass(NULL, 0)
		{}

		~BufferedOutputStream()
		{
			free(data);
		}

		void reset()
		{
			BaseClass::index = 0;
		}

		//return true if writing the size is ok
		bool tryResize(unsigned size)
		{
			this->size = size + size / 2;
			data = (char *) realloc(data, this->size);
			return true;
		}

		const void *getData() const { return data;  }
		void *getData() { return data; }

		const size_t getSize() const { return size; }

	};

}
}

#endif
