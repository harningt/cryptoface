cmake_minimum_required(VERSION 2.6)
project(cf_test)

SET(SOURCES
	src/cf_test.c
)

add_executable(cf_test ${SOURCES})

set_target_properties(cf_test
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ../bin)

target_link_libraries(cf_test cryptoface)

include_directories(../cryptoface/include)
