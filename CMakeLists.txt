cmake_minimum_required(VERSION 2.6)
project(cryptoface C CXX)
#C++ enabled for the few projects that consume it

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/Modules)

set(CF_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR}/Modules)

set(CMAKE_MODULE_PATH ${CF_MODULE_PATH} ${CMAKE_MODULE_PATH})

include(CMakeDependentOption)

find_package(BeeCrypt QUIET)
find_package(Botan QUIET)
find_package(Crypto++ QUIET)
find_package(OpenSSL QUIET)
find_package(MHASH QUIET)
find_package(Nettle QUIET)
find_package(TomCrypt QUIET)
find_package(gcrypt QUIET)
find_package(Lua51 QUIET)

CMAKE_DEPENDENT_OPTION(BUILD_CF_BEECRYPT "Build cf_beecrypt interface module" ON "BEECRYPT_LIBRARIES" OFF)
CMAKE_DEPENDENT_OPTION(BUILD_CF_BOTAN "Build cf_botan interface module" ON "BOTAN_LIBRARIES" OFF)
CMAKE_DEPENDENT_OPTION(BUILD_CF_CRYPTOPP "Build cf_cryptopp interface module" ON "CRYPTO++_LIBRARIES" OFF)
CMAKE_DEPENDENT_OPTION(BUILD_CF_MHASH "Build cf_mhash interface module" ON "MHASH_LIBRARIES" OFF)
CMAKE_DEPENDENT_OPTION(BUILD_CF_NETTLE "Build cf_nettle interface module" ON "NETTLE_FOUND" OFF)
CMAKE_DEPENDENT_OPTION(BUILD_CF_TOMCRYPT "Build cf_tomcrypt interface module" ON "TOMCRYPT_LIBRARIES" OFF)
CMAKE_DEPENDENT_OPTION(BUILD_CF_GCRYPT "Build cf_gcrypt interface module" ON "GCRYPT_LIBRARIES" OFF)
CMAKE_DEPENDENT_OPTION(BUILD_CF_OPENSSL "Build cf_openssl interface module" ON "OPENSSL_LIBRARIES" OFF)
CMAKE_DEPENDENT_OPTION(BUILD_LUACF "Build Lua CF client" ON "LUA_INCLUDE_DIR" OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

IF(NOT WIN32)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
ENDIF(NOT WIN32)

ADD_SUBDIRECTORY(submodules/cf_memsys)
ADD_SUBDIRECTORY(cryptoface)
ADD_SUBDIRECTORY(cf_buckets)

IF(BUILD_CF_BEECRYPT)
	ADD_SUBDIRECTORY(plugins/cf_beecrypt)
ENDIF(BUILD_CF_BEECRYPT)

IF(BUILD_CF_BOTAN)
	ADD_SUBDIRECTORY(plugins/cf_botan)
ENDIF(BUILD_CF_BOTAN)

IF(BUILD_CF_CRYPTOPP)
	ADD_SUBDIRECTORY(plugins/cf_cryptopp)
ENDIF(BUILD_CF_CRYPTOPP)

IF(BUILD_CF_MHASH)
	ADD_SUBDIRECTORY(plugins/cf_mhash)
ENDIF(BUILD_CF_MHASH)

IF(BUILD_CF_NETTLE)
	ADD_SUBDIRECTORY(plugins/cf_nettle)
ENDIF(BUILD_CF_NETTLE)

IF(BUILD_CF_TOMCRYPT)
	ADD_SUBDIRECTORY(plugins/cf_tomcrypt)
ENDIF(BUILD_CF_TOMCRYPT)

IF(BUILD_CF_GCRYPT)
	ADD_SUBDIRECTORY(plugins/cf_gcrypt)
ENDIF(BUILD_CF_GCRYPT)

IF(BUILD_CF_OPENSSL)
	ADD_SUBDIRECTORY(plugins/cf_openssl)
ENDIF(BUILD_CF_OPENSSL)
IF(BUILD_LUACF)
	ADD_SUBDIRECTORY(luacf)
ENDIF(BUILD_LUACF)
ADD_SUBDIRECTORY(cf_test)
