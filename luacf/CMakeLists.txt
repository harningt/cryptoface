cmake_minimum_required(VERSION 2.6)
project(luacf C)

find_package(Lua51 REQUIRED)

set(LUACF_SOURCES
	src/luacf.c
)

set(LUACF_HEADERS
	include/luacf.h
)

add_library(luacf MODULE ${LUACF_SOURCES} ${LUACF_HEADERS})

set_target_properties(luacf
	PROPERTIES PREFIX "")

target_link_libraries(luacf cryptoface)

include_directories(include ../cryptoface/include ${LUA_INCLUDE_DIR})
