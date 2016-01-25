solution { "PropellerEngine" }
	premake.gcc.cc = 'clang'
	premake.gcc.cxx = 'clang++'

	configurations { "Release" }

	configuration { "mac" }

		defines "CORE_X86_62"

		-- JsonCpp is amalgamated
		defines { "_MAC" }
		defines "JSON_IS_AMALGAMATION"
		includedirs { "../thirdparty/boost_1_55_0/", "../thirdparty/JsonCpp/src/", "../thirdparty/lua/src/", "../thirdparty/catch/" }

	configuration "Release"
		defines { "NDEBUG", "RELEASE" }

	project "lua"
		kind "StaticLib"
		language "C"
		files { "../thirdparty/lua/src/**.c" }
		defines { "_MAC" }
		defines "JSON_IS_AMALGAMATION"
		includedirs { "../thirdparty/boost_1_55_0/", "../thirdparty/JsonCpp/src/", "../thirdparty/lua/src/", "../thirdparty/catch/" }

	project "jsoncpp"
		kind "StaticLib"
		language "C++"
		files { "../thirdparty/JsonCpp/src/**.cpp" }
		defines { "_MAC" }
		defines "JSON_IS_AMALGAMATION"
		includedirs { "../thirdparty/boost_1_55_0/", "../thirdparty/JsonCpp/src/", "../thirdparty/lua/src/", "../thirdparty/catch/" }

	project "engine"
		kind "StaticLib"
		language "C++"
		files { "../src/engine/**.cpp" }
		includedirs { "../src/" }
		defines { "_MAC" }
		defines "JSON_IS_AMALGAMATION"
		includedirs { "../thirdparty/boost_1_55_0/", "../thirdparty/JsonCpp/src/", "../thirdparty/lua/src/", "../thirdparty/catch/" }

	project "game"
		kind "StaticLib"
		language "C++"
		--buildoptions "-fpermissive"
		files { "../src/game/**.cpp" }
		includedirs{ "../src/" }
		defines { "_MAC" }
		defines "JSON_IS_AMALGAMATION"
		includedirs { "../thirdparty/boost_1_55_0/", "../thirdparty/JsonCpp/src/", "../thirdparty/lua/src/", "../thirdparty/catch/" }

	project "standalone"
		kind "ConsoleApp"
		language "C++"
		files "../src/standalone/**.cpp"
		includedirs{ "../src/" }
		links {  "game", "engine", "jsoncpp", "lua" }
		defines { "_MAC" }
		defines "JSON_IS_AMALGAMATION"
		includedirs { "../thirdparty/boost_1_55_0/", "../thirdparty/JsonCpp/src/", "../thirdparty/lua/src/", "../thirdparty/catch/" }

	project "tests"
		kind "ConsoleApp"
		language "C++"
		files "../src/unittesting/**.cpp"
		defines { "_MAC" }
		defines "JSON_IS_AMALGAMATION"
		includedirs { "../thirdparty/boost_1_55_0/", "../thirdparty/JsonCpp/src/", "../thirdparty/lua/src/", "../thirdparty/catch/" }
		includedirs{ "../src/" }
		links {  "game", "engine", "jsoncpp", "lua" }
