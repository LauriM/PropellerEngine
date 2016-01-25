#include "catch.hpp"

#include "engine/memory/StackAllocator.h"

using namespace engine::lang;

struct Entity
{
	std::string name;
	float x;
	float y;
};

struct RGB
{
	unsigned R;
	unsigned G;
	unsigned B;
};

TEST_CASE("StackAllocator", "[stackallocator]")
{
	StackAllocator *allocator = new StackAllocator(2048); // this prevents the leak detection to kick in during the tests

	Entity *ent = (Entity*)allocator->allocate(sizeof(Entity));
	// Placement new the Entity into the memory block
	new (ent) Entity();

	// We got entity
	REQUIRE(ent != NULL);

	ent->name = "jorma";
	ent->x = 123.f;
	ent->y = 500.f;

	// Allocator actually allocated something
	REQUIRE(allocator->getCapacity() >= sizeof(Entity));

	// We have only one allocation, the size should be the same
	REQUIRE(allocator->getSize() == sizeof(Entity));

	double *d = (double*)allocator->allocate(sizeof(double));
	float *f = (float*)allocator->allocate(sizeof(float));

	*d = 123123;
	*f = 123.f;

	// Stack count should be now three with the previous allocations
	REQUIRE(allocator->getStackCount() == 3);

	allocator->releaseStack();
	allocator->releaseStack();

	REQUIRE(allocator->getStackCount() == 1);

	// Check that the first allocation is ok
	REQUIRE(ent->name == "jorma");

	allocator->allocate(666);
	Entity *secondEntity = (Entity*)allocator->allocate(sizeof(Entity));
	new (secondEntity) Entity();
	allocator->allocate(666);

	secondEntity->name = ent->name;

	REQUIRE(ent->name == "jorma");

	allocator->releaseStack();
	REQUIRE(secondEntity->name == ent->name);
	allocator->releaseStack();
	allocator->releaseStack();
	allocator->releaseStack();
}

TEST_CASE("Frame allocation proof of concept", "[stackallocator]")
{
	StackAllocator frameAllocator(5024);

	size_t allocSize = 0;

	Entity *player = (Entity*)frameAllocator.allocate(sizeof(Entity));
	new (player) Entity();

	player->name = "Jorma";

	for (unsigned i = 0; i < 100; ++i)
	{
		player->x += 1;
		player->y -= player->x * 2;

		{
			unsigned *color = (unsigned*)frameAllocator.allocate(sizeof(unsigned) * 3);

			color[0] = 153;
			color[1] = 255;
			color[2] = 53;

			{
				unsigned *red = (unsigned*)frameAllocator.allocate(sizeof(unsigned));

				*red = 100;
				color[0] += *red;

				player->x += 1;

				// --- alloc size tester
				if (allocSize == 0)
				{
					allocSize = frameAllocator.getSize();
				}
				else
				{
					// The size should be the same for each frame
					REQUIRE(allocSize == frameAllocator.getSize());
					allocSize = frameAllocator.getSize();
				}

				frameAllocator.releaseStack();
			}

			REQUIRE(color[0] == (153 + 100));

			frameAllocator.releaseStack();
		}
	}

	frameAllocator.releaseStack();
}
