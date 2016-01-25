// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_STREAM_LITTLEENDIAN_H
#define ENGINE_STREAM_LITTLEENDIAN_H

#include "engine/preprocessor/platform.h"

#include <stdint.h>

namespace engine {
namespace stream {

	class LittleEndian
	{
	public:
		#if CORE_CPU(LITTLE_ENDIAN)
			static inline void convert(uint16_t &v)      { }
			static inline void convert(uint32_t &v)      { }
			static inline void convert(uint64_t &v)      { }
			static inline void convert(int16_t &v)       { }
			static inline void convert(int32_t &v)       { }
			static inline void convert(int64_t &v)       { }
			static inline void convert(double &v)        { }
			static inline void convert(float &v)         { }
        #ifdef OS_MAC
            static inline void convert(long &v)          { }
            static inline void convert(unsigned long &v) { }
        #endif
        #else
			static inline void convert(int16_t &v)  { v = (v << 8 & 0xff00) | (v >> 8 & 0x00ff); }
			static inline void convert(int32_t &v)  { v = (v << 24 & 0xff000000) | (v << 8 & 0x00ff0000) | (v >> 8 & 0x0000ff00) | (v >> 24 & 0x000000ff); }
			static inline void convert(int64_t &v)  { v = (v << 56 & 0xff00000000000000) | (v << 40 & 0x00ff000000000000) | (v << 24 & 0x0000ff0000000000) | (v << 8 & 0x000000ff00000000) | (v >> 8 & 0x00000000ff000000) | (v >> 24 & 0x0000000000ff0000) | (v >> 40 & 0x000000000000ff00) | (v >> 56 & 0x00000000000000ff); }

			static inline void convert(uint16_t &v) { v = (v << 8 & 0xff00) | (v >> 8 & 0x00ff); }
			static inline void convert(uint32_t &v) { v = (v << 24 & 0xff000000) | (v << 8 & 0x00ff0000) | (v >> 8 & 0x0000ff00) | (v >> 24 & 0x000000ff); }
			static inline void convert(uint64_t &v) { v = (v << 56 & 0xff00000000000000) | (v << 40 & 0x00ff000000000000) | (v << 24 & 0x0000ff0000000000) | (v << 8 & 0x000000ff00000000) | (v >> 8 & 0x00000000ff000000) | (v >> 24 & 0x0000000000ff0000) | (v >> 40 & 0x000000000000ff00) | (v >> 56 & 0x00000000000000ff); }

			static inline void convert(float &v)         { convert((uint32_t&) v); }
			static inline void convert(double &v)        { convert((uint64_t&) v); }
        #ifdef OS_MAC
            static inline void convert(long &v)          { convert((int32_t&) v); }
            static inline void convert(unsigned long &v) { convert((uint32_t&) v); }
        #endif
        #endif
	};

	class BigEndian
	{
	public:
		#if CORE_CPU(BIG_ENDIAN)
			static inline void convert(uint16_t &v)      { }
			static inline void convert(uint32_t &v)      { }
			static inline void convert(uint64_t &v)      { }
			static inline void convert(int16_t &v)       { }
			static inline void convert(int32_t &v)       { }
			static inline void convert(int64_t &v)       { }
			static inline void convert(double &v)        { }
			static inline void convert(float &v)         { }
            static inline void convert(long &v)          { }
            static inline void convert(unsigned long &v) { }
		#else
			static inline void convert(int16_t &v)  { v = (v << 8 & 0xff00) | (v >> 8 & 0x00ff); }
			static inline void convert(int32_t &v)  { v = (v << 24 & 0xff000000) | (v << 8 & 0x00ff0000) | (v >> 8 & 0x0000ff00) | (v >> 24 & 0x000000ff); }
			static inline void convert(int64_t &v)  { v = (v << 56 & 0xff00000000000000) | (v << 40 & 0x00ff000000000000) | (v << 24 & 0x0000ff0000000000) | (v << 8 & 0x000000ff00000000) | (v >> 8 & 0x00000000ff000000) | (v >> 24 & 0x0000000000ff0000) | (v >> 40 & 0x000000000000ff00) | (v >> 56 & 0x00000000000000ff); }

			static inline void convert(uint16_t &v) { v = (v << 8 & 0xff00) | (v >> 8 & 0x00ff); }
			static inline void convert(uint32_t &v) { v = (v << 24 & 0xff000000) | (v << 8 & 0x00ff0000) | (v >> 8 & 0x0000ff00) | (v >> 24 & 0x000000ff); }
			static inline void convert(uint64_t &v) { v = (v << 56 & 0xff00000000000000) | (v << 40 & 0x00ff000000000000) | (v << 24 & 0x0000ff0000000000) | (v << 8 & 0x000000ff00000000) | (v >> 8 & 0x00000000ff000000) | (v >> 24 & 0x0000000000ff0000) | (v >> 40 & 0x000000000000ff00) | (v >> 56 & 0x00000000000000ff); }

            static inline void convert(float &v)         { convert((uint32_t&) v); }
            static inline void convert(double &v)        { convert((uint64_t&) v); }
        #ifdef OS_MAC
            static inline void convert(long &v)          { convert((int32_t&) v); }
            static inline void convert(unsigned long &v) { convert((uint32_t&) v); }
        #endif
        #endif
	};

#if CORE_CPU(LITTLE_ENDIAN)
	typedef LittleEndian NativeEndian;
#else
	typedef BigEndian NativeEndian;
#endif

	typedef LittleEndian SerializationEndian;


}
}

#endif