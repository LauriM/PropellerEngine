// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#pragma once

namespace engine {
namespace memory {

	// Ring buffer of raw data.
	// This is optimized for fast access.
	class RingBuffer
	{
	private:
		unsigned bufferSize;
		char *data;

		unsigned head;
		unsigned tail;

	public:
		RingBuffer(unsigned s)
			: bufferSize(s)
			, head(0)
			, tail(0)
		{ 
			data = (char*)malloc(s);
		}

		// data,       data where to write
		// bytes,      how many bytes requested
		// bytesGiven, how many bytes has been written to "data"
		void getData(char *d, const unsigned bytes, unsigned &bytesGiven)
		{
			if (head <= (tail + bytes))
			{
				// Ain't nothing to give to the client!

				bytesGiven = 0;
				return;
			}

			if (bufferSize > (tail + bytes))
			{

				// We get a "clean" read, not going to hit the end of the buffer!
				bytesGiven = bytes;

				memcpy(d, (void*)data[tail], bytes);
			}
			else
			{
				// Not a "clean" read! We are going around the buffer

				unsigned s1 = bufferSize - tail;
				unsigned s2 = bytes - s1;

				memcpy((void*)d, (void*)data[tail], s1);
				memcpy((void*)d[s1], (void*)data[0], s2);

				tail = s2;
			}
		}

		// Copy "data" to the buffer
		void insertData(const char* d, size_t size)
		{
			//TODO HACK: WE DO NOT HAVE A CHECK IF WE HIT THE TAIL! !!!

			if ((head + size) < bufferSize)
			{
				// we can just write the data into the buffer, without looping around

				memcpy((void*)data[head], d, size);
				head += size;
			}
			else
			{
				// We are going to loop around! 
				// s1 = size of section before loop (from head -> bufferSize)
				// s2 = size of section after loop (from 0 -> s2)

				unsigned s1 = bufferSize - head;
				unsigned s2 = size - s1;

				memcpy((void*)data[head], d, s1);
				memcpy((void*)data[0], (void*)d[s1], s2);

				head = s2;
			}
		}

	};

}
}