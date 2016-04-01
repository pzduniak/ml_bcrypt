solution "ml_bcrypt" 
	configurations { "Debug", "Release" }
	location "Build"
	
	flags { "C++14", "Symbols" }
	platforms { "x86", "x64" }
	defines { "_CRT_SECURE_NO_WARNINGS" }

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
		
		configuration "windows"
			filter "platforms:x86"
				links { "lua5.1.lib" }
				
			filter "platforms:x64"
				links { "lua5.1_64.lib" }
			
		configuration "not windows"
			links { "liblua5.1" }
			
		configuration "Release"
			flags { "Optimize", "NoMinimalRebuild" }
