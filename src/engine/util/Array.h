// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_UTIL_ARRAY_H
#define ENGINE_UTIL_ARRAY_H

#include <new>

namespace engine {
namespace util {

	template <typename T>
	class Array
	{
	private:
		T *data;

		unsigned size;
		unsigned capacity;

	public:
		Array()
			: size(0)
			, capacity(1)
		{
			data = (T*)malloc(sizeof(T) * capacity);
		}

		~Array()
		{
			for (unsigned i = 0; i < size; ++i)
			{
				data[i].~T();
			}
			free(data);
		}

		void reserve(const unsigned count)
		{
			capacity = count * 2;

			data = (T*)realloc(data, capacity * sizeof(T));
		}

		T & operator [] (const unsigned index)
		{
			assert(index < size);
			return data[index];
		}

		const T & operator [] (const unsigned index) const
		{
			assert(index < size);
			return data[index];
		}

		const T & at(const unsigned index) const
		{
			assert(index < size);
			return data[index];
		}

		void push(const T &item)
		{
			if ((size + 1) > capacity)
				reserve(capacity * 2);

			new (&data[size]) T(item);

			++size;
		}

		T pop()
		{
			assert(size > 0);

			T item = data[size - 1];

			data[size - 1].~T();
			--size;

			return item;
		}

		void remove(const unsigned id)
		{
			assert(id <= size);

			data[id].~T();

			memmove(data + id, data + id + 1, sizeof(T) * (size - (id + 1)));

			--size;
		}

		void removeRange(const unsigned start, const unsigned end)
		{
			assert(start < size);
			assert(end < size);
			assert(start <= end);

			for (unsigned i = start; i <= end ; ++i)
				data[i].~T();

			memmove(data + start, data + end + 1, sizeof(T) * (size - (end - start + 1)));

			size = size - (end - start) - 1;
		}

		void clear()
		{
			for (unsigned i = 0; i < size; ++i)
				data[i].~T();

			size = 0;
		}

		const unsigned getSize() const { return size; }
		const unsigned getCapacity() const { return capacity; }

	};

}
}

#endif
