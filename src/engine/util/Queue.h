// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_UTIL_QUEUE_H
#define ENGINE_UTIL_QUEUE_H

namespace engine {
namespace util {

	//Queue provides a RingBuffer container
	template <typename T>
	class Queue
	{
	private:
		T *data;

		unsigned capacity;
		unsigned head;
		unsigned tail;
		unsigned size;

	public:
		Queue(unsigned size)
			: head(0)
			, tail(0)
			, size(0)
			, capacity(size)
		{ 
			data = (T*)malloc(sizeof(T) * capacity);
		}

		Queue()
			: head(0)
			, tail(0)
			, size(0)
			, capacity(1)
		{ 
			data = (T*)malloc(sizeof(T) * capacity);
		}

		~Queue()
		{
			DEBUG_PRINT("QUEUE DESTRUCTOR NOT IMPLEMENTED!");
		}


		void reserve(unsigned c)
		{
			if (c <= capacity)
				return;

			data = (T*)realloc(data, c * sizeof (T));

			if (head == 0 )
				head = capacity;

			// Buffer doesn't cut through the end of data
			/*
			if (tail < head)
			{
				capacity = c;
				return;
			}
			*/

			/*
			unsigned oLastIndex = capacity - 1;
			unsigned nLastIndex = c - 1;
			unsigned s = oLastIndex - tail;
			*/

			// Move tail to the end of buffer

			/*
			if( head < tail )
			{
				head = size + 1;
			}
			*/

			if(head != tail)
				--tail;

			memmove(data + size, data , (tail) * sizeof(T));  
			 

			//memmove(data + tail, data + nLastIndex - s, (s + 1) * sizeof (T));
			head = size + tail;

			if(tail > capacity)
				tail = 0;

			//tail = (tail + 1) % capacity;

			++tail;

			capacity = c;
		}

		void push(const T &item)
		{
			if (size >= capacity)
				reserve(capacity * 2);

			new (data + head) T(item);
			head = (head + 1) % capacity;

			++size;
		}

		T &back() const
		{
			return data[tail];
		}

		bool pop()
		{
			if (head == tail)
				return false;

			data[tail].~T();
			tail = (tail + 1) % capacity;

			--size;

			return true;
		}

		unsigned getCapacity() { return capacity; }
		unsigned getSize() { return size; }
	};

}
}

#endif