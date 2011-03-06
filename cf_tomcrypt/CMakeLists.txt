cmake_minimum_required(VERSION 2.6)
project(cf_tomcrypt C)

find_package(TomCrypt REQUIRED)

SET(SOURCES
	src/tomcrypt_provider.c
	src/tomcrypt_digest.c
)
SET(HEADERS
	include/tomcrypt_provider.h
	include/tomcrypt_digest.h
)

add_library(cf_tomcrypt MODULE ${SOURCES} ${HEADERS})

set_target_properties(cf_tomcrypt
	PROPERTIES
	PREFIX "")

target_link_libraries(cf_tomcrypt cryptoface)
target_link_libraries(cf_tomcrypt ${TOMCRYPT_LIBRARIES})

include_directories(include ../cryptoface/include ${TOMCRYPT_INCLUDE_DIR})
