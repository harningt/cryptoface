# Find the native BeeCrypt includes, library, and flags
#
#  BEECRYPT_INCLUDE_DIR - where to find beecrypt.h, etc.
#  BEECRYPT_LIBRARIES   - List of libraries when using BeeCrypt.
#  BEECRYPT_FOUND       - True if BeeCrypt found.
#  BEECRYPT_C_FLAGS     - List of C flags to set when using BeeCrypt
#  BEECRYPT_CXX_FLAGS   - List of C++ flags to set when using BeeCrypt
#  BEECRYPT_LINK_FLAGS  - List of linker flags to set when using BeeCrypt

IF (BEECRYPT_INCLUDE_DIR)
  # Already in cache, be silent
  SET(BEECRYPT_FIND_QUIETLY TRUE)
ENDIF (BEECRYPT_INCLUDE_DIR)

IF(BEECRYPT_FIND_QUIETLY OR NOT BEECRYPT_FIND_REQUIRED)
	find_package(OpenMP)
ELSE(BEECRYPT_FIND_QUIETLY OR NOT BEECRYPT_FIND_REQUIRED)
	find_package(OpenMP REQUIRED)
ENDIF(BEECRYPT_FIND_QUIETLY OR NOT BEECRYPT_FIND_REQUIRED)

IF(OPENMP_FOUND)
	FIND_PATH(BEECRYPT_INCLUDE_DIR beecrypt/beecrypt.h)

	SET(BEECRYPT_NAMES beecrypt)
	FIND_LIBRARY(BEECRYPT_LIBRARY NAMES ${BEECRYPT_NAMES} )
	# Workaround missing libgomp for gcc linking... may eventually fix other platforms

	# handle the QUIETLY and REQUIRED arguments and set BEECRYPT_FOUND to TRUE if
	# all listed variables are TRUE
	INCLUDE(FindPackageHandleStandardArgs)
	FIND_PACKAGE_HANDLE_STANDARD_ARGS(BEECRYPT DEFAULT_MSG BEECRYPT_LIBRARY BEECRYPT_INCLUDE_DIR)
ELSE(OPENMP_FOUND)
	message(STATUS "BeeCrypt currently required OpenMP support")
ENDIF(OPENMP_FOUND)

IF(BEECRYPT_FOUND)
	SET(BEECRYPT_LIBRARIES ${BEECRYPT_LIBRARY})
	SET(BEECRYPT_C_FLAGS ${OpenMP_C_FLAGS})
	SET(BEECRYPT_CXX_FLAGS ${OpenMP_CXX_FLAGS})
	# UNKNOWN if correct - but it works for me
	SET(BEECRYPT_LINK_FLAGS ${OpenMP_C_FLAGS})
ELSE(BEECRYPT_FOUND)
	SET( BEECRYPT_LIBRARIES )
ENDIF(BEECRYPT_FOUND)

MARK_AS_ADVANCED( BEECRYPT_LIBRARY BEECRYPT_C_FLAGS BEECRYPT_CXX_FLAGS BEECRYPT_LINK_FLAGS BEECRYPT_INCLUDE_DIR )
