cmake_minimum_required(VERSION 2.6)
project(cf_mhash)

find_package(MHASH REQUIRED)

SET(SOURCES
	src/mhash_provider.c
	src/mhash_digest.c
)
SET(HEADERS
	include/mhash_digest.h
)

add_library(cf_mhash MODULE ${SOURCES} ${HEADERS})

set_target_properties(cf_mhash
	PROPERTIES
	PREFIX ""
	LIBRARY_OUTPUT_DIRECTORY ../bin)

target_link_libraries(cf_mhash cryptoface)
target_link_libraries(cf_mhash ${MHASH_LIBRARIES})

include_directories(include ../cryptoface/include ${MHASH_INCLUDE_DIR})
