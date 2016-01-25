// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_LANG_BLOCKPOOLALLOCATOR_H
#define ENGINE_LANG_BLOCKPOOLALLOCATOR_H

#include "engine/util/Array.h"
#include <boost/unordered_map.hpp>

namespace engine {
namespace lang {

	struct BlockHeader
	{
		size_t slotSize;
		unsigned slotCount;

		unsigned slotsLeft;
		void *nextSlot;
		unsigned rmCount;

		BlockHeader *nextBlockHeader; // If this block is full, the next one is positioned to here

		// + will also contain the data after the header
	};

	// Used to store what header contains ptrs from values
	struct HeaderLocationInfo
	{
		BlockHeader *header;
		void *upper;
		void *lower;
	};

	//TODO: rename to BlockPoolAllocator
	class BlockPoolAllocator
	{
	public:
		typedef boost::unordered_map<size_t, BlockHeader*> BlockMap;

		static const unsigned int poolSize = 100; // how many items per pool? 

		~BlockPoolAllocator();

	private:
		struct MemoryReportForBlockSize
		{
			unsigned blockCount; // how many blocks
			unsigned elementCount; // how many used elements
			unsigned elementSize; // size of the elements
			unsigned elementsPerBlock; // how many elements per block
		};

	private:
		BlockMap blockMap;
		util::Array<HeaderLocationInfo> headerLocations;

	public:
		void *allocate(size_t size);
		void free(void *ptr);

		void flush(); //TODO: implement the flush!

		void reportMemoryUsageToConsole();

	private:
		BlockHeader *createNewBlockHeader(size_t size);

		BlockHeader *findBlockWithFreeSlots(BlockHeader *rootHeader);
		BlockHeader *findBlockHeaderForPtr(BlockHeader *rootHeader, void *ptr); //deprecrated

		void fillMemoryReportForBlockList(BlockHeader *header, MemoryReportForBlockSize *report);

	};

	extern BlockPoolAllocator g_blockPoolAllocator;

}
}

#endif