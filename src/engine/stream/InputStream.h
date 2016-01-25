// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_STREAM_INPUTSTREAM_H
#define ENGINE_STREAM_INPUTSTREAM_H

#include "engine/stream/Endian.h"

namespace engine {
namespace stream {

	template <typename Endianess>
	class InputStream
	{
	private:
		volatile char *data;
		unsigned index;

	public:
		friend class CSharpInputStream;

		InputStream(volatile void *data)
			: data((char *)data)
			, index(0)
		{}

		const unsigned getIndex() const { return index; }

		void read(bool &v)
		{
			v = *(bool *)(data + index);
			index += sizeof v;
		}

		void read(float &v)
		{
			v = *(float *)(data + index);
			Endianess::convert(v);
			index += sizeof v;
		}

		void read(double &v)
		{
			v = *(double *)(data + index);
			Endianess::convert(v);
			index += sizeof v;
		}
        
#ifdef OS_MAC
        void read(long &v)
		{
			v = *(long *)(data + index);
			Endianess::convert(v);
			index += sizeof v;
		}
        
        void read(unsigned long &v)
		{
			v = *(unsigned long *)(data + index);
			Endianess::convert(v);
			index += sizeof v;
		}
#endif

		void read(uint8_t &v)
		{
			v = *(uint8_t *)(data + index);
			index += sizeof v;
		}

		void read(uint16_t &v)
		{
			v = *(uint16_t *)(data + index);
			Endianess::convert(v);
			index += sizeof v;
		}

		void read(uint32_t &v)
		{
			v = *(uint32_t *)(data + index);
			Endianess::convert(v);
			index += sizeof v;
		}

		void read(uint64_t &v)
		{
			v = *(uint64_t *)(data + index);
			Endianess::convert(v);
			index += sizeof v;
		}

		void read(int8_t &v)
		{
			v = *(int8_t *)(data + index);
			index += sizeof v;
		}

		void read(int16_t &v)
		{
			v = *(int16_t *)(data + index);
			Endianess::convert(v);
			index += sizeof v;
		}

		void read(int32_t &v)
		{
			v = *(int32_t *)(data + index);
			Endianess::convert(v);
			index += sizeof v;
		}

		void read(int64_t &v)
		{
			v = *(int64_t *)(data + index);
			Endianess::convert(v);
			index += sizeof v;
		}

		//String
		void read(std::string &dest)
		{
			size_t size;
			read(size);
			dest.resize(size);
			read(&dest[0], size);
		}

		//Unspecific amount
		void read(void *dest, unsigned size)
		{
			memcpy(dest, (char*)data + index, size);
			//memcpy(dest, data + index, size); //doesnt work with volatilation
			index += size;
		}

		//Serialization stuff
		template <typename T>
		void load(const T &src)
		{
			src.load(*this);
		}

		template <typename T>
		void load(const T *src)
		{
			src->load(*this);
		}

	};
}
}

#endif