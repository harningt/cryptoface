cmake_minimum_required(VERSION 2.6)
project(luacf)

find_package(Lua51 REQUIRED)

add_library(luacf MODULE src/luacf.c)

set_target_properties(luacf
	PROPERTIES PREFIX ""
	LIBRARY_OUTPUT_DIRECTORY ../bin)

target_link_libraries(luacf cryptoface)

include_directories(../cryptoface/include include ${LUA_INCLUDE_DIR})