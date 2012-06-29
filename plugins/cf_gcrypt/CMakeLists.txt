cmake_minimum_required(VERSION 2.6)
project(cf_gcrypt C)

find_package(cryptoface REQUIRED CONFIG PATHS ${CMAKE_MODULE_PATH})
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

target_link_libraries(cf_gcrypt ${CRYPTOFACE_LIBRARIES})

target_link_libraries(cf_gcrypt ${GCRYPT_LIBRARIES})

include_directories(
    include
    ${CRYPTOFACE_INCLUDE_DIRS}
    ${GCRYPT_INCLUDE_DIR}
)
