cmake_minimum_required(VERSION 2.6)
project(cryptoface_core)

SET(SOURCES
	src/provider.c include/provider.h
	include/cryptoface.h
)

add_library(cryptoface SHARED  ${SOURCES})

set_target_properties(cryptoface
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY ../bin)

include_directories(include)
