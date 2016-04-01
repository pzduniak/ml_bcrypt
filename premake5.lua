solution "ml_bcrypt" 
	configurations { "Debug", "Release" }
	location "Build"
	
	flags { "C++14", "Symbols" }
	platforms { "x86", "x64" }
	defines { "_CRT_SECURE_NO_WARNINGS" }
	pic "On"

	include "lib/blowfish"

	project "ml_bcrypt"
		language "C++"
		kind "SharedLib"
		targetname "ml_bcrypt"
		
		includedirs { "include", "lib/blowfish" }
		libdirs { "lib" }
		links { "blowfish" }
		
		vpaths { 
			["Headers/*"] = "**.h",
			["Sources/*"] = "**.c",
			["*"] = "premake5.lua"
		}
		
		files {
			"premake5.lua",
			
			"*.h",
			"*.cpp",
			"extra/*.h",
			"extra/*.cpp",
			"include/*.h"
		}

		filter "configurations:Release"
			flags { "Optimize", "NoMinimalRebuild" }
	
		filter "system:not windows"
			links { "lua5.1" }
			
		filter { "system:windows", "platforms:x86" }
			links { "lua5.1.lib" }
			
		filter { "system:windows", "platforms:x64" }
			links { "lua5.1_64.lib" }

