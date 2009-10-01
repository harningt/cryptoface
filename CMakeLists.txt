cmake_minimum_required(VERSION 2.6)
project(cryptoface C)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Modules)

OPTION(BUILD_CF_MHASH "Build cf_mhash interface module" ON)
OPTION(BUILD_CF_OPENSSL "Build cf_openssl interface module" ON)

ADD_SUBDIRECTORY(cryptoface)
IF(BUILD_CF_MHASH)
	ADD_SUBDIRECTORY(cf_mhash)
ENDIF(BUILD_CF_MHASH)

IF(BUILD_CF_OPENSSL)
	ADD_SUBDIRECTORY(cf_openssl)
ENDIF(BUILD_CF_OPENSSL)
ADD_SUBDIRECTORY(luacf)

ADD_SUBDIRECTORY(cf_test)
