	solution "CitizenMP"
		configurations { "Debug NY", "Release NY" }
		
		flags { "StaticRuntime", "No64BitChecks", "Symbols", "Unicode" }
		
		flags { "NoIncrementalLink", "NoEditAndContinue" } -- this breaks our custom section ordering in citilaunch, and is kind of annoying otherwise
		
		includedirs { "shared/", "client/shared/", "../vendor/jitasm/", "deplibs/include/", os.getenv("BOOST_ROOT") }
		
		libdirs { "deplibs/lib/" }
	
		configuration "Debug*"
			targetdir "bin/debug"
			defines "NDEBUG"
			
		configuration "Release*"
			targetdir "bin/release"
			defines "NDEBUG"
			optimize "Speed"
			
		configuration "* NY"
			defines "GTA_NY"
			
	project "CitiLaunch"
		targetname "CitizenFX"
		language "C++"
		kind "WindowedApp"
		
		defines "COMPILING_LAUNCH"
		
		links { "Shared", "dbghelp", "psapi", "libcurl", "tinyxml", "liblzma", "comctl32" }
		
		files
		{
			"client/launcher/**.cpp", "client/launcher/**.h", 
			"client/launcher/launcher.rc", "client/launcher/launcher.def",
			"client/common/Error.cpp"
		}
		
		libdirs { "client/libcef/lib/" }
		
		linkoptions "/DELAYLOAD:libcef.dll"
		
		includedirs { "client/libcef/" }
		
		configuration "Debug*"
			links { "cef_sandboxd", "libcefd" }
			
		configuration "Release*"
			links { "cef_sandbox", "libcef" }
		
		configuration "windows"
			linkoptions "/ENTRY:main /IGNORE:4254 /DYNAMICBASE:NO /SAFESEH:NO /LARGEADDRESSAWARE" -- 4254 is the section type warning we tend to get
		
	project "CitiGame"
		targetname "CitizenGame"
		language "C++"
		kind "SharedLib"
		
		files
		{
			"client/citigame/**.cpp", "client/citigame/**.h", "client/common/Error.cpp", "client/citigame/**.c"
		}
		
		links { "Shared", "yaml-cpp", "lua51", "winmm", "winhttp", "ws2_32", "libcef_dll", "libcef", "delayimp", "libnp" }
		
		defines "COMPILING_GAME"
		
		libdirs { "../vendor/luajit/src/", "client/libcef/lib/", "client/shared/np" }
		includedirs { "client/citigame/include/", "../vendor/luajit/src/", "../vendor/yaml-cpp/include/", "client/libcef/", "client/shared/np" }
		
		linkoptions "/DELAYLOAD:libcef.dll"
		
		configuration "* NY"
			includedirs { "client/game_ny/base/", "client/game_ny/gta/", "client/game_ny/rage/", "client/citigame/net/" }
			links { "HooksNY", "GameNY" }
			
		configuration "Debug*"
			links { "libcefd" }
			
		configuration "Release*"
			links { "libcef" }
			
	project "GameNY"
		targetname "game_ny"
		language "C++"
		kind "SharedLib"
		
		links { "Shared" }
		
		defines "COMPILING_GAMESPEC"
		
		configuration "* NY"
			includedirs { "client/game_ny/base/", "client/game_ny/gta/", "client/game_ny/rage/" }
		
			files
			{
				"client/game_ny/**.cpp", "client/game_ny/**.h", "client/common/Error.cpp"
			}
			
	project "HooksNY"
		targetname "hooks_ny"
		language "C++"
		kind "SharedLib"
		
		links { "Shared", "GameNY", "ws2_32", "avformat", "avcodec", "avresample", "avutil"	}
		
		defines "COMPILING_HOOKS"		
		
		configuration "* NY"
			includedirs { "client/game_ny/base/", "client/game_ny/gta/", "client/game_ny/rage/", "client/hooks_ny/base/" }
			files
			{
				"client/hooks_ny/**.cpp", "client/hooks_ny/**.h", "client/common/Error.cpp"
			}
		
	project "Shared"
		targetname "shared"
		language "C++"
		kind "StaticLib"
		
		includedirs { "client/game_ny/base/", "client/game_ny/gta/", "client/game_ny/rage/" }
		
		files
		{
			"shared/**.cpp", "shared/**.h", "client/shared/**.cpp", "client/shared/**.h"
		}
		
	project "libcef_dll"
		targetname "libcef_dll_wrapper"
		language "C++"
		kind "StaticLib"
		
		defines { "USING_CEF_SHARED", "NOMINMAX" }
		
		includedirs { ".", "client/libcef" }
		
		files
		{
			"client/libcef/libcef_dll/**.cc", "client/libcef/libcef_dll/**.cpp", "client/libcef/libcef_dll/**.h"
		}
		
	project "yaml-cpp"
		targetname "yaml-cpp"
		language "C++"
		kind "StaticLib"
		
		includedirs { "../vendor/yaml-cpp/include" }
		
		files
		{
			"../vendor/yaml-cpp/src/*.cpp"
		}