// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/memory/BlockPoolAllocator.h"

#include "engine/console/Command.h"
#include "engine/console/Console.h"

//TODO: namespace should be changed from lang to memory
namespace engine {
namespace lang {

	BlockPoolAllocator g_blockPoolAllocator;

	struct Slot
	{
		void *data;
	};

	BlockPoolAllocator::~BlockPoolAllocator()
	{
		BlockMap::iterator it = blockMap.begin();

		size_t totalSizeAllocated = 0;
		size_t totalSizeUsed = 0;

		while (it != blockMap.end())
		{
			MemoryReportForBlockSize report;
			BlockHeader *header = it->second;

			report.elementSize = header->slotSize;
			report.elementsPerBlock = header->slotCount;
			report.blockCount = 0;
			report.elementCount = 0;

			fillMemoryReportForBlockList(header, &report);

			totalSizeAllocated += report.elementsPerBlock * report.elementSize;
			totalSizeUsed += report.elementCount * report.elementSize;
			++it;
		}

		// Everything should be deallocated when the application closes
		assert(totalSizeUsed == 0);

		if (totalSizeUsed > 0)
			LOG_WARNING("BlockPoolAllocator detected memory leak! size: " << totalSizeUsed);
	}

	void *BlockPoolAllocator::allocate(size_t size)
	{
		BlockMap::iterator it = blockMap.find(size);

		BlockHeader *header = NULL;
		if (it == blockMap.end())
		{
			// could not find any block, we need to create it
			header = createNewBlockHeader(size);

			blockMap.insert(BlockMap::value_type(size, header));
		}
		else
		{
			// iterator contains a valid header, lets use it
			header = it->second;
		}

		if (header->slotsLeft == 0)
		{
			// could not find any block, if no next block, create new

			BlockHeader *block = findBlockWithFreeSlots(header);

			if (block == NULL)
			{
				// Could not find any blocks with free slots! creating a new one
				BlockHeader *newHeader = createNewBlockHeader(size);
				header->nextBlockHeader = newHeader;
				header = newHeader;
			}
			else
			{
				header = block;
			}
		}

		void *ptr = NULL;

		if (header->rmCount <= 0)
		{
			// Use a new slot
			ptr = header->nextSlot;
			header->nextSlot = (char*)header->nextSlot + size;
		}
		else
		{
			// Fetch the next slot from the slot we are going to use
			char* p = (char*)header->nextSlot; // next usable slot was stored behind the *nextSlot

			Slot *slot = (Slot*)header->nextSlot;

			// this is the next slot
			ptr = header->nextSlot;

			//header->nextSlot = (void*)*p;
			header->nextSlot = slot->data;

			// we are going to use p as ptr
			--header->rmCount;
		}

		--header->slotsLeft;
		
		return ptr;
	}

	void BlockPoolAllocator::free(void *ptr)
	{
		BlockHeader *header = NULL;

		for (unsigned i = 0; i < headerLocations.getSize(); ++i)
		{
			if (ptr >= headerLocations[i].lower)
			{
				if (ptr < headerLocations[i].upper)
				{
					header = headerLocations[i].header;
					break;
				}
			}
		}

#ifndef RELEASE
		if (header == NULL)
			assert(false);
#endif

		// ASSIGN VALUE FROM nextSlot INTO the *PTR
		void* value = (void*)header->nextSlot;
		*(void**)ptr = value;

		// ASSIGN nextSlot to the ptr
		header->nextSlot = ptr;

		++header->rmCount;
		++header->slotsLeft;
	}

	BlockHeader *BlockPoolAllocator::findBlockWithFreeSlots(BlockHeader *header)
	{
		if (header->slotsLeft > 0)
			return header;

		if (header->nextBlockHeader == NULL)
			return NULL;

		return findBlockWithFreeSlots(header->nextBlockHeader);
	}

	BlockHeader *BlockPoolAllocator::createNewBlockHeader(size_t size)
	{
		BlockHeader *header = (BlockHeader*)malloc(sizeof(BlockHeader) + size * poolSize);
		header->slotSize = size;
		header->slotCount = poolSize;
		header->slotsLeft = poolSize;
		header->nextSlot = header + 1;
		header->rmCount = 0;
		header->nextBlockHeader = NULL;

		HeaderLocationInfo headerLocationInfo;
		headerLocationInfo.header = header;
		headerLocationInfo.lower = header + 1;
		headerLocationInfo.upper = (char*)headerLocationInfo.lower + header->slotCount * header->slotSize;

		headerLocations.push(headerLocationInfo);

#ifdef DEBUG 
		LOG_INFO("[BlockPoolAllocator] New block: " << sizeof(BlockHeader) + size * poolSize << " b " << " Obj-size: " << size << " b");
#endif
		return header;
	}

	void BlockPoolAllocator::reportMemoryUsageToConsole()
	{
		BlockMap::iterator it = blockMap.begin();

		size_t totalSizeAllocated = 0;
		size_t totalSizeUsed = 0;

		while (it != blockMap.end())
		{
			MemoryReportForBlockSize report;
			BlockHeader *header = it->second;

			report.elementSize = header->slotSize;
			report.elementsPerBlock = header->slotCount;
			report.blockCount = 0;
			report.elementCount = 0;

			fillMemoryReportForBlockList(header, &report);

			LOG_INFO("Object size: " << report.elementSize << "b Object count: " << report.elementCount << "/" << report.elementsPerBlock << " Block count: " << report.blockCount);

			totalSizeAllocated += report.elementsPerBlock * report.elementSize;
			totalSizeUsed += report.elementCount * report.elementSize;
			++it;
		}

		LOG_INFO("Total of " << totalSizeUsed << "b/" << totalSizeAllocated << "b allocated by the BlockPoolAllocator");
	}

	void BlockPoolAllocator::fillMemoryReportForBlockList(BlockHeader *header, MemoryReportForBlockSize *report)
	{
		report->elementCount += header->slotCount - header->slotsLeft;
		++report->blockCount;

		if (header->nextBlockHeader == NULL)
			return;

		fillMemoryReportForBlockList(header->nextBlockHeader, report);
	}

}
}

namespace command {

	CREATE_COMMAND(memstat, "Report memory statistics of the engine")
	{
		engine::lang::g_blockPoolAllocator.reportMemoryUsageToConsole();

		return 0;
	}

}

