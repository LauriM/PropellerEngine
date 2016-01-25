// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.

#include "catch.hpp"

#include "engine/precompiled.h"
#include "engine/lang/ScopedPtr.h"

using namespace engine;
using namespace engine::lang;

// Counts how many allocations/deallocations happen
class CounterObject
{
private:
	int *value;

public:
	CounterObject(int *value)
		: value(value)
	{
		(*value)++;
	}

	~CounterObject()
	{
		(*value)--;
	}
};

lang::ScopedPtr<CounterObject> createCounterForVal(int *value)
{
	return lang::ScopedPtr<CounterObject>(new CounterObject(value));
}

TEST_CASE("UniquePtr", "[ScopedPtr]")
{
	int val = 0;

	REQUIRE(val == 0);

	{
		ScopedPtr<CounterObject> counter(new CounterObject(&val));

		REQUIRE(val == 1);

		{
			ScopedPtr<CounterObject> hahaJep(new CounterObject(&val));

			REQUIRE(val == 2);
		}

		REQUIRE(val == 1);
	}

	REQUIRE(val == 0);
}


TEST_CASE("Moving ownership", "[ScopedPtr]")
{
	int val = 0;

	REQUIRE(val == 0);
	{

		ScopedPtr<CounterObject> ptr;

		REQUIRE(val == 0);

		{
			ScopedPtr<CounterObject> upperPtr(new CounterObject(&val));

			REQUIRE(val == 1);

			// Move ownership from upperPtr to ptr, should not deallocate
			ptr.swap(upperPtr);

			REQUIRE(val == 1);
		}

		REQUIRE(val == 1);
	}

	//ptr deallocates, should remove the object
	REQUIRE(val == 0);
}

TEST_CASE("Returning from a function", "[ScopedPtr]")
{
	int val = 0;

	{
		lang::ScopedPtr<CounterObject> ptr = createCounterForVal(&val);

		REQUIRE(val == 1);
	}

	REQUIRE(val == 0);
}