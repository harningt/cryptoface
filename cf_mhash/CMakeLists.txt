cmake_minimum_required(VERSION 2.6)
project(cf_mhash)

SET(SOURCES
	src/mhash_provider.c
	src/mhash_digest.c
)
SET(HEADERS
	include/mhash_digest.h
)

add_library(cf_mhash SHARED ${SOURCES} ${HEADERS})

set_target_properties(cf_mhash
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY ../bin)

target_link_libraries(cf_mhash cryptoface)
#TODO ADD CMAKE DETECT
target_link_libraries(cf_mhash mhash)

include_directories(include ../cryptoface/include)
