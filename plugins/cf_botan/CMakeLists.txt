cmake_minimum_required(VERSION 2.6)
project(cf_botan CXX)

find_package(cryptoface REQUIRED CONFIG PATHS ${CMAKE_MODULE_PATH})
find_package(Botan REQUIRED)

SET(SOURCES
	src/botan_provider.cpp
	src/botan_digest.cpp
)
SET(HEADERS
	include/botan_digest.h
	include/botan_provider.h
)

add_library(cf_botan MODULE ${SOURCES} ${HEADERS})

set_target_properties(cf_botan
	PROPERTIES
	PREFIX ""
	COMPILE_FLAGS "${BOTAN_CFLAGS}")

target_link_libraries(cf_botan ${CRYPTOFACE_LIBRARIES})

target_link_libraries(cf_botan ${BOTAN_LIBRARIES})

include_directories(
    include
    ${CRYPTOFACE_INCLUDE_DIRS}
    ${BOTAN_INCLUDE_DIR}
)
