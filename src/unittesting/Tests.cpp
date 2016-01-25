// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "engine/precompiled.h"

#include "engine/math/Vector.h"

#include "engine/math/Matrix.h"

#include "engine/stream/BufferedOutputStream.h"
#include "engine/stream/InputStream.h"

#include "engine/profiler/ProfilerManager.h"
#include "engine/profiler/AutoProfiler.h"

#include "engine/sys/Timer.h"

#include <xxhash.h>

using namespace engine;
using namespace engine::math;

TEST_CASE("Highperformance timer", "[timer]")
{
	sys::initTimer();

	sys::Timer timer;

	timer.start();

#ifndef OS_LINUX
	Sleep(500);
#else
	sleep(0);
#endif

	timer.stop();

	long timeInMilliseconds = timer.getTimeInMilliSeconds();

#ifndef OS_LINUX
	REQUIRE(timeInMilliseconds > 490);
#endif
}

TEST_CASE("Vector math", "[vector]")
{
	Vec2i vector1(10, 10);
	Vec2i vector2(20, 10);

	Vec2i vectorResult = vector1 + vector2;

//	REQUIRE(vector1 != vector2);

	REQUIRE(vectorResult.x == 30);
	REQUIRE(vectorResult.y == 20);

	Vec2i vectorResult2 = vector2 * 10;

	REQUIRE(vectorResult2.x == 200);
	REQUIRE(vectorResult2.y == 100);
}

TEST_CASE("Streams", "[stream]")
{
	stream::BufferedOutputStream<stream::NativeEndian> output;

	output.write(String("hello world!"));
	output.write(String("hello world!"));
	output.write(double(5034));
	output.write(int(234));
	output.write(String("hello world!"));
	output.write(String("hello world!"));

	stream::InputStream<stream::NativeEndian> input(output.getData());

	String str;
	double d;
	int i;

	input.read(str);
	input.read(str);
	input.read(d);
	input.read(i);
	input.read(str);
	input.read(str);

	REQUIRE(str == String("hello world!"));
	REQUIRE(d == double(5034));
	REQUIRE(i == 234);
}

TEST_CASE("Matrix", "[matrix]")
{
	{
		Matrix<int, 2, 2> matrix;

		matrix.m[0][0] = 200;
		matrix.v[2] = 2;

		REQUIRE(matrix.v[2] == 2);
		REQUIRE(matrix.v[0] == 200);
	}

	{
		Matrix4x4i matrix( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 );

		for (unsigned i = 0; i < 16; i++)
		{
			REQUIRE(matrix.v[i] == i);
		}
	}

	{
		Matrix<int, 2, 2> mat1(23, 45, 45, -234);
		Matrix<int, 2, 2> mat2(23, 45, 45, -234);
		Matrix<int, 2, 2> mat3(24, 45, -123, 34);

		REQUIRE(mat1 == mat2);

		REQUIRE(mat2 != mat3);
		REQUIRE(mat1 != mat3);
	}

	{
		Matrix2x2i matrix(5,10,20,-40);

		matrix.m[1][1] = -30;

		matrix *= 2;

		REQUIRE(matrix.v[0] == 10);
		REQUIRE(matrix.m[1][1] == -60);

		matrix /= 5;

		REQUIRE(matrix.v[0] == 2);
	}

	{
		Matrix2x2i matrix(2, 4, 8, 16);

		matrix += 4;

		REQUIRE(matrix.v[0] == 6);
		REQUIRE(matrix.v[1] == 8);

		matrix -= 6;

		REQUIRE(matrix.v[0] == 0);
		REQUIRE(matrix.v[1] == 2);
	}

	{
		Vec3 position(10, 0, 0);

		Matrix4x4 rotationX = Matrix4x4::getRotationX(0);
		Matrix4x4 rotationY = Matrix4x4::getRotationY(-90);
		Matrix4x4 rotationZ = Matrix4x4::getRotationZ(0);
		Matrix4x4 translation = Matrix4x4::getTranslation(position);

		translation *= rotationX;
		translation *= rotationY;
		translation *= rotationZ;

		LOG_INFO("hehe");
	}
}

TEST_CASE("Does Profiler work.", "[Profiler]")
{
	engine::profiler::g_profilerManager = new engine::profiler::ProfilerManager();

	{
		PROFILE("Frame");

		LOG_INFO("frame");
		{
			PROFILE("Logic");
			LOG_INFO("loogic");
			LOG_INFO("hehe");
		}

		{
			PROFILE("Render");

				LOG_INFO("hehe");
			{
				PROFILE("Scene");
				LOG_INFO("hehe");
				LOG_INFO("hehe");
				LOG_INFO("hehe");
			}
			{
				PROFILE("GUI");
				LOG_INFO("hehe");
				LOG_INFO("hehe");
				LOG_INFO("hehe");
				LOG_INFO("hehe");
				LOG_INFO("hehe");
				LOG_INFO("hehe");
			}
		}
	}

	//engine::profiler::g_profilerManager->outputToStdio();

	delete engine::profiler::g_profilerManager;

	LOG_INFO("Profiler tree building done");
}

TEST_CASE("xxhash test", "[hash]")
{
	int key1 = XXH32("jorma", 5, 666);
	int key2 = XXH32("pentti", 5, 666);
	int key3 = XXH32("jarmo", 5, 666);

	REQUIRE(key1 != key2);
	REQUIRE(key2 != key3);
	REQUIRE(key1 != key3);
}

/*
// Disabled...
TEST_CASE("creating propellerModel", "Debug")
{
	// fake hardcoded data
	float meshVertices[] =
	{
		0, 0, 1, //pos
		0, 0, 1, //normal

		-0.5, -0.5, 0,
		-0.5, -0.5, 0,

		0.5, -0.5, 0,
		0.5, -0.5, 0,

		0.5, 0.5, 0,
		0.5, 0.5, 0,

		-0.5, 0.5, 0,
		-0.5, 0.5, 0,

		0, 0, 0,
		0, 0, 0
	};

	uint16_t meshIndices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 1,
		1, 5, 2,
		2, 5, 3,
		3, 5, 4,
		4, 5, 1
	};

	// not actually a test
	engine::stream::BufferedOutputStream<engine::stream::SerializationEndian> header;

	// .PropellerModel header
	header.write("PROPELLERMODEL", 14);
	header.write(unsigned(1));

	header.write(unsigned(36));

	for (unsigned i = 0; i < 36; ++i)
		header.write(meshVertices[i]);

	header.write(unsigned(24));

	for (unsigned i = 0; i < 24; ++i)
		header.write(meshIndices[i]);

	std::ofstream output;

	output.open("pyramid.PropellerModel", std::ios::binary);
	output.write((char*)header.getData(), header.getIndex());
	output.close();

}
*/
