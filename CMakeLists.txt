project("bcrypt module")
set(LIB_NAME ml_bcrypt)

cmake_minimum_required(VERSION 2.8)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

set(SOURCE_FILES
	CFunctions.cpp
	ml_base.cpp
)
set(BLOWFISH_SOURCES
	lib/blowfish/crypt_blowfish.c
	lib/blowfish/crypt_gensalt.c
	lib/blowfish/wrapper.c
	lib/blowfish/x86.S
)
FILE(GLOB LUA_SOURCES lib/lua-5.1.5/src/*.c)

if (UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(UNIX)

add_library(${LIB_NAME} SHARED ${SOURCE_FILES} ${LUA_SOURCES} ${BLOWFISH_SOURCES})
target_link_libraries(${LIB_NAME})
