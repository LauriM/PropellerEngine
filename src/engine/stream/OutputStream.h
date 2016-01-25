// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_STREAM_OUTPUTSTREAM_H
#define ENGINE_STREAM_OUTPUTSTREAM_H

#include "engine/stream/Endian.h"

namespace engine {
namespace stream {

	template <typename Endianess>
	class OutputStream
	{
	protected:
		char *data;
		unsigned size;
		unsigned index;

		virtual bool tryResize(unsigned size)
		{
			return true;
		}

	public:
		OutputStream(void *data, unsigned size)
			: data((char *)data)
			, size(size)
			, index(0)
		{}

		unsigned getIndex() const { return index; }

		char *getData()
		{
			return data;
		}

		void write(bool v)
		{
			if (!tryResize(index + sizeof v))
				return;

			*(bool *)(data + index) = v;
			index += sizeof v;
		}

		void write(float v)
		{
			if (!tryResize(index + sizeof v))
				return;
			Endianess::convert(v);
			*(float *)(data + index) = v;
			index += sizeof v;
		}

		void write(double v)
		{
			if (!tryResize(index + sizeof v))
				return;
			Endianess::convert(v);
			*(double *)(data + index) = v;
			index += sizeof v;
		}
        
#ifdef OS_MAC
        void write(long v)
		{
			if (!tryResize(index + sizeof v))
				return;
			Endianess::convert(v);
			*(long *)(data + index) = v;
			index += sizeof v;
		}

        void write(unsigned long v)
		{
			if (!tryResize(index + sizeof v))
				return;
			Endianess::convert(v);
			*(unsigned long *)(data + index) = v;
			index += sizeof v;
		}
#endif
        
		void write(uint8_t v)
		{
			if (!tryResize(index + sizeof v))
				return;
			*(uint8_t *)(data + index) = v;
			index += sizeof v;
		}

		void write(uint16_t v)
		{
			if (!tryResize(index + sizeof v))
				return;
			Endianess::convert(v);
			*(uint16_t *)(data + index) = v;
			index += sizeof v;
		}

		void write(uint32_t v)
		{
			if (!tryResize(index + sizeof v))
				return;
			Endianess::convert(v);
			*(uint32_t *)(data + index) = v;
			index += sizeof v;
		}

		void write(uint64_t v)
		{
			if (!tryResize(index + sizeof v))
				return;
			Endianess::convert(v);
			*(uint64_t *)(data + index) = v;
			index += sizeof v;
		}

		void write(int8_t v)
		{
			if (!tryResize(index + sizeof v))
				return;
			*(int8_t *)(data + index) = v;
			index += sizeof v;
		}

		void write(int16_t v)
		{
			if (!tryResize(index + sizeof v))
				return;
			Endianess::convert(v);
			*(int16_t *)(data + index) = v;
			index += sizeof v;
		}

		void write(int32_t v)
		{
			if (!tryResize(index + sizeof v))
				return;
			Endianess::convert(v);
			*(int32_t *)(data + index) = v;
			index += sizeof v;
		}

		void write(int64_t v)
		{
			if (!tryResize(index + sizeof v))
				return;
			Endianess::convert(v);
			*(int64_t *)(data + index) = v;
			index += sizeof v;
		}

		//String
		void write(const std::string &src)
		{
			write(src.size());
			write(src.c_str(), src.size());
		}

		//Unspecific amount
		void write(const void *src, unsigned size)
		{
			if (!tryResize(index + size))
				return;
			memcpy(data + index, src, size);
			index += size;
		}

		void seekToStart()
		{
			index = 0;
		}

		//void save(OutputStream &strm)  To serialize something!
		template <typename T>
		void save(const T &src)
		{
			src.save(*this);
		}

		template <typename T>
		void save(const T *src)
		{
			src->save(*this);
		}
	};

}
}

#endif