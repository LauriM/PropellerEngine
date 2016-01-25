// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.

#include "catch.hpp"

#include "engine/precompiled.h"
#include "engine/util/Array.h"
#include "engine/math/Random.h"

#include <boost/lexical_cast.hpp>

using namespace engine;
using namespace engine::util;

TEST_CASE("Simple array insertion and popping", "[array]")
{
	Array<unsigned> array;

	unsigned rounds = 10;

	for(unsigned i = 0; i < rounds; ++i)
	{
		array.push(i);
	}

	//simple access
	for(unsigned i = 0; i < rounds; ++i)
	{
		REQUIRE(array[i] == i);
	}

	REQUIRE(array.getSize() == rounds);
	REQUIRE(array.getCapacity() >= rounds);

	//reverse popping
	for(unsigned i = rounds; i > 0; --i)
	{
		REQUIRE(array.pop() == (i - 1));
	}
}

struct Entity
{
	Entity(String name, float x, float y)
		: name(name)
		  , x(x)
		  , y(y)
	{ }

	String name;
	float x;
	float y;
};

TEST_CASE("Different data types", "[array]")
{

	Array<float> floatters;

	floatters.push(3.123f);
	floatters.push(234.f);

	REQUIRE(floatters.getSize() == 2);

	Array<Entity> entities;

	entities.push(Entity("Jorma", 12.f, 223.f));
	entities.push(Entity("Pentti", 212.f, 3.23f));
	entities.push(Entity("Hehehe", 2.f, -23.f));

	entities[2] = Entity("Pentti", 212.f, 3.23f);

	REQUIRE(entities[0].name == "Jorma");
	REQUIRE(entities[1].name == "Pentti");
	REQUIRE(entities[2].name == "Pentti");

	entities.clear();
	REQUIRE(entities.getSize() == 0);
}


TEST_CASE("PTR array", "[array]")
{
	Array<Entity*> entities;

	for(unsigned i = 0; i < 100; ++i)
	{
		entities.push(new Entity("pentti", i * 10.f, i * 20.f));
	}

	REQUIRE(entities[50]->name == "pentti");

	for(unsigned i = 0; i < 100; ++i)
	{
		delete entities[i];
	}

	entities.clear();
	REQUIRE(entities.getSize() == 0);
}

TEST_CASE("Removing item from array", "[array]")
{
	Array<int> numbers;

	numbers.push(0);
	numbers.push(1);
	numbers.push(1);
	numbers.push(2);
	numbers.push(3);

	REQUIRE(numbers.getSize() == 5);

	numbers.remove(1);

	REQUIRE(numbers.getSize() == 4);

	for (unsigned i = 0; i < numbers.getSize(); ++i)
		REQUIRE(numbers[i] == i);

	numbers.clear();
	REQUIRE(numbers.getSize() == 0);
}

TEST_CASE("Removing multiple items from array", "[array]")
{
	Array<int> numbers;

	numbers.push(0);
	numbers.push(1);
	numbers.push(9); //2
	numbers.push(9); //3
	numbers.push(9); //4
	numbers.push(2);
	numbers.push(3);

	REQUIRE(numbers.getSize() == 7);

	numbers.removeRange(2, 4);

	REQUIRE(numbers.getSize() == 4);

	for (unsigned i = 0; i < numbers.getSize(); ++i)
		REQUIRE(numbers[i] == i);

	numbers.clear();
	REQUIRE(numbers.getSize() == 0);
}

TEST_CASE("Filling lots of items into an array", "[array]")
{
	Array<String> strs;

	size_t stringsize = sizeof(String);

	for (unsigned i = 0; i < 100; ++i)
	{
		String str("haha");

		size_t asdfff = sizeof(String("haha"));

		unsigned val = math::randomRange(0, 25);

		for (unsigned x = 0; x < val; ++x)
			str.append("hehe");

		strs.push(str);

		REQUIRE(strs[i] == str);
		REQUIRE(strs[i] == str);
		REQUIRE(strs[i] == str);
	}
	strs.getSize();

}