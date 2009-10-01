cmake_minimum_required(VERSION 2.6)
project(cryptoface_core C)

SET(SOURCES
	src/provider.c
	src/digest.c
)
SET(HEADERS
	include/cryptoface.h
	include/provider.h
	include/digest.h
	include/cryptoface_impl.h
)

add_library(cryptoface SHARED ${SOURCES} ${HEADERS})

set_target_properties(cryptoface
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY ../bin)

target_link_libraries(cryptoface dl)

include_directories(include)
