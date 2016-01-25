// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.

#include "catch.hpp"

#include "engine/precompiled.h"
#include "engine/util/HashMap.h"

using namespace engine;
using namespace engine::util;

namespace helper {
	void gen_random(char *s, const int len) { // 'stolen' from stackoverflow "http://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c"
		static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

		for (int i = 0; i < len; ++i) {
			s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}

		s[len] = 0;
	}
}

TEST_CASE("HashMap insert/remove testing", "[HashMap]")
{
	HashMap<int> map;

	map.insert("jorma", 2000);
	map.insert("jarmo", 2);
	map.insert("pentti", 666);
	map.insert("hahahaha", -24);
	map.insert("moi", 1);

	REQUIRE(map.getSize() == 5);

	char *str = (char*)malloc(15);

	for (unsigned i = 0; i < 3500; ++i)
	{
		helper::gen_random(str, 10);
		str[10] = '\n';
		map.insert(str, i);
	}

	free(str);

	int retVal = 0;
	REQUIRE(map.find("jarmo", retVal) == true);
	REQUIRE(retVal == 2);
	REQUIRE(map.find("moi", retVal) == true);
	REQUIRE(retVal == 1);
	REQUIRE(map.find("jorma", retVal) == true);
	REQUIRE(retVal == 2000);

	REQUIRE(map.find("jormaa", retVal) == false);

	map.clear();

	REQUIRE(map.find("jorma", retVal) == false);
	REQUIRE(map.find("moi", retVal) == false);

	REQUIRE(map.getSize() == 0);

	map.insert("jorma", 2000);
	map.insert("jarmo", 2);
	map.insert("pentti", 666);
	map.insert("hahahaha", -24);
	map.insert("moi", 1);

	REQUIRE(map.find("jarmo", retVal) == true);
	REQUIRE(retVal == 2);
	REQUIRE(map.find("moi", retVal) == true);
	REQUIRE(retVal == 1);
	REQUIRE(map.find("jorma", retVal) == true);
	REQUIRE(retVal == 2000);

	map.remove("jorma");

	REQUIRE(map.find("jarmo", retVal) == true);
	REQUIRE(retVal == 2);
	REQUIRE(map.find("moi", retVal) == true);
	REQUIRE(retVal == 1);
	REQUIRE(map.find("jorma", retVal) == false);
}

TEST_CASE("Hashmap iterators", "[HashMap]")
{
	HashMap<int> map;

	map.insert("jorma", 2000);
	map.insert("jarmo", 2);
	map.insert("pentti", 666);
	map.insert("hahahaha", -24);
	map.insert("moi", 1);

	REQUIRE(map.getSize() == 5);

	HashMap<int>::Iterator it = map.begin();

	while (!it.isAtEnd())
	{
		bool found = (it.getKey() == "jorma" || it.getKey() == "jarmo" || it.getKey() == "pentti" || it.getKey() == "hahahaha" || it.getKey() == "moi");
		REQUIRE(found);

		REQUIRE(it.getValue() > -25);

		++it;
	}
}
