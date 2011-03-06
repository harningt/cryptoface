cmake_minimum_required(VERSION 2.6)
project(cf_gcrypt C)

find_package(gcrypt REQUIRED)

SET(SOURCES
	src/gcrypt_provider.c
	src/gcrypt_digest.c
)
SET(HEADERS
	include/gcrypt_digest.h
)

add_library(cf_gcrypt MODULE ${SOURCES} ${HEADERS})

set_target_properties(cf_gcrypt
	PROPERTIES
	PREFIX "")

target_link_libraries(cf_gcrypt cryptoface)
target_link_libraries(cf_gcrypt ${GCRYPT_LIBRARIES})

include_directories(include ../cryptoface/include ${GCRYPT_INCLUDE_DIR})
