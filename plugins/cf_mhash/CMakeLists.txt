cmake_minimum_required(VERSION 2.6)
project(cf_mhash C)

find_package(cryptoface REQUIRED CONFIG PATHS ${CMAKE_MODULE_PATH})
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
	PREFIX "")

target_link_libraries(cf_mhash ${CRYPTOFACE_LIBRARIES})

target_link_libraries(cf_mhash ${MHASH_LIBRARIES})

include_directories(
    include
    ${CRYPTOFACE_INCLUDE_DIRS}
    ${MHASH_INCLUDE_DIR}
)
