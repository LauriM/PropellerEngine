solution { "PropellerEngine" }
	premake.gcc.cc = 'clang'
	premake.gcc.cxx = 'clang++'

	configurations { "Release", "Debug" }

	configuration { "linux" }
		defines { "_LINUX" }
		defines { "DEDICATED_SERVER" }

		buildoptions { "-Wno-c++11-compat-deprecated-writable-strings" }

		-- JsonCpp is amalgamated
		defines { "JSON_IS_AMALGAMATION", "NULLRENDERER" }

		includedirs {
			"../thirdparty/boost_1_55_0/",
			"../thirdparty/JsonCpp/src/",
			"../thirdparty/catch/",
			"../thirdparty/xxhash/src/",
			"../thirdparty/lodepng/src/",
			"../thirdparty/stb/src/",
			"../thirdparty/Box2D/src/",
			"../thirdparty/Bullet/src/"
		}

	configuration "Release"
		defines { "NDEBUG", "RELEASE" }
		flags { "Optimize" }

	configuration "Debug"
		defines { "DEBUG", "DEBUG" }
		flags { "Symbols" }

	project "xxhash"
		kind "StaticLib"
		language "C"
		files { "../thirdparty/xxhash/src/**.c" }

	project "lodepng"
		kind "StaticLib"
		language "C++"
		files { "../thirdparty/lodepng/src/**.cpp" }

	project "box2d"
		kind "StaticLib"
		language "C++"
		files { "../thirdparty/Box2D/src/**.cpp" }

	project "bullet"
		kind "StaticLib"
		language "C++"
		defines { "B3_USE_CLEW" }
		files { "../thirdparty/Bullet/src/**.cpp" }

	project "jsoncpp"
		kind "StaticLib"
		language "C++"
		files { "../thirdparty/JsonCpp/src/**.cpp" }

	project "engine"
		kind "StaticLib"
		language "C++"
		files { "../src/engine/**.cpp" }
		includedirs { "../src/" }

	project "game"
		kind "StaticLib"
		language "C++"
		--buildoptions "-fpermissive"
		files { "../src/game/**.cpp" }
		includedirs{ "../src/" }

	project "standalone"
		kind "ConsoleApp"
		language "C++"
		files "../src/standalone/**.cpp"
		includedirs{ "../src/" }
		links {  "game", "engine", "jsoncpp", "xxhash", "lodepng", "box2d", "bullet", "rt" }

	project "tests"
		kind "ConsoleApp"
		language "C++"
		files "../src/unittesting/**.cpp"
		includedirs{ "../src/" }
		links {  "game", "engine", "jsoncpp", "xxhash", "lodepng", "box2d", "bullet", "rt" }
