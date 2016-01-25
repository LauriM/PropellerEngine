// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_LANG_STACKALLOCATOR_H
#define ENGINE_LANG_STACKALLOCATOR_H

#include <assert.h>

#include <vector>

namespace engine {
namespace lang {

	class StackAllocator
	{
	public:
		typedef size_t Marker;

	private:
		char *data;      // Actual data

		size_t capacity; // How much is memory is allocated for the StackAllocator?
		size_t size;     // How much memory is in use for this StackAllocator?

		// Offsets for the stack markers
		std::vector<Marker> markers;

	public:
		StackAllocator(const size_t capacity)
			: data(NULL)
			, size(0)
			, capacity(capacity)
		{
			data = (char*)malloc(capacity);
			assert(data != NULL);
		}

		~StackAllocator()
		{
			free(data);
		}

		// Allocate memory
		void *allocate(size_t amount)
		{
			assert(size + amount < capacity);

			if (size + amount > capacity)
				return NULL;

			void *ptr = data + size;

			// Add stack marker
			markers.push_back(size);

			// move size forward
			size += amount;

			return ptr;
		}

		// Release one stack
		void releaseStack()
		{
			assert(markers.empty() == false);

			size = markers.back();
			markers.pop_back();
		}

		// Clear the whole allocator
		void clear()
		{
			size = 0;
			markers.clear();
		}

		const size_t getCapacity() const { return capacity; }
		const size_t getSize() const { return size; }
		const unsigned getStackCount() const { return markers.size(); }
	};

}
}

#endif