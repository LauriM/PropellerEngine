// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_UTIL_STACK_H
#define ENGINE_UTIL_STACK_H

namespace engine {
namespace util {

	// Stack container
	template <typename T>
	class Stack
	{
	private:
		T *data;

		unsigned capacity;
		unsigned size;

	public:
		Stack()
			: capacity(1)
			, size(0)
		{
			data = (T*)malloc(sizeof(T) * capacity);
		}

		~Stack()
		{
			for(unsigned i = 0; i < size; ++i)
				data[i].~T();

			free(data);
		}

		void reserve(unsigned count)
		{
			data = (T*)realloc(data, count * sizeof(T));

			capacity = count;
		}

		void push(T item)
		{
			if(size >= capacity)
				reserve(size * 2);

			new (&data[size]) T(item);

			++size;
		}

		T pop()
		{
			if(size < 0)
				LOG_ERROR("Trying to pop empty stack!");

			//Get item
			T item = data[size];

			//Destruct item
			data[size].~T();
			--size;

			return item;
		}

		unsigned getSize() { return size + 1; }
	};

}
}

#endif