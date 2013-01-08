#
# This module looks for clucene (http://clucene.sf.net) support
# It will define the following values
#
# CLUCENE_INCLUDE_DIRS = CLUCENE_INCLUDE_DIR + CLUCENE_LIBRARY_DIR
# CLUCENE_INCLUDE_DIR  = where CLucene/StdHeader.h can be found
# CLUCENE_LIBRARY_DIR  = where CLucene/clucene-config.h can be found
# CLUCENE_LIBRARIES    = the libraries to link against CLucene
# CLUCENE_VERSION      = The CLucene version string
# CLucene_FOUND        = set to 1 if clucene is found
#

INCLUDE(CheckSymbolExists)
INCLUDE(FindLibraryWithDebug)

# try to locate a patched unstable version (for comp's sake *sigh*) first
FIND_PACKAGE(CLuceneUnstable QUIET)
IF(CLUCENEUNSTABLE_FOUND)
    SET(CLucene_FOUND TRUE)
    SET(CLUCENE_INCLUDE_DIR ${CLUCENE_UNSTABLE_INCLUDE_DIRS})
    SET(CLUCENE_INCLUDE_DIRS ${CLUCENE_INCLUDE_DIR})
    SET(CLUCENE_LIBRARIES ${CLUCENE_UNSTABLE_LIBS})

    #MESSAGE(FATAL_ERROR NARF)
ELSE(CLUCENEUNSTABLE_FOUND)
IF(CLucene_FIND_VERSION)
  SET(CLUCENE_MIN_VERSION ${CLucene_FIND_VERSION})
ELSEIF()
  SET(CLUCENE_MIN_VERSION "0.9.23")
ENDIF(CLucene_FIND_VERSION)

IF(EXISTS ${PROJECT_CMAKE}/CLuceneConfig.cmake)
  INCLUDE(${PROJECT_CMAKE}/CLuceneConfig.cmake)
ENDIF(EXISTS ${PROJECT_CMAKE}/CLuceneConfig.cmake)

SET(TRIAL_LIBRARY_PATHS
  $ENV{CLUCENE_HOME}/lib${LIB_SUFFIX}
  ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}
  /usr/local/lib${LIB_SUFFIX}
  /usr/lib${LIB_SUFFIX}
  /sw/lib${LIB_SUFFIX}
  /usr/pkg/lib${LIB_SUFFIX}
  /usr/lib64
  /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}
  )
SET(TRIAL_INCLUDE_PATHS
  $ENV{CLUCENE_HOME}/include
  ${CMAKE_INSTALL_PREFIX}/include
  /usr/local/include
  /usr/include
  /sw/include
  /usr/pkg/include
  )
FIND_LIBRARY_WITH_DEBUG(CLUCENE_CORE_LIBRARY
  WIN32_DEBUG_POSTFIX d
  NAMES clucene-core
  PATHS ${TRIAL_LIBRARY_PATHS})
IF (CLUCENE_CORE_LIBRARY)
  MESSAGE(STATUS "Found CLucene core library: ${CLUCENE_CORE_LIBRARY}")
ENDIF (CLUCENE_CORE_LIBRARY)
FIND_LIBRARY_WITH_DEBUG(CLUCENE_SHARED_LIBRARY
  WIN32_DEBUG_POSTFIX d
  NAMES clucene-shared
  PATHS ${TRIAL_LIBRARY_PATHS})
IF (CLUCENE_SHARED_LIBRARY)
  MESSAGE(STATUS "Found CLucene shared library: ${CLUCENE_SHARED_LIBRARY}")
ENDIF (CLUCENE_SHARED_LIBRARY)

IF(CLUCENE_CORE_LIBRARY AND CLUCENE_SHARED_LIBRARY)
  SET(CLUCENE_LIBRARIES ${CLUCENE_CORE_LIBRARY} ${CLUCENE_SHARED_LIBRARY})
ENDIF(CLUCENE_CORE_LIBRARY AND CLUCENE_SHARED_LIBRARY)

FIND_PATH(CLUCENE_INCLUDE_DIR
  NAMES CLucene.h
  PATHS ${TRIAL_INCLUDE_PATHS})

IF (CLUCENE_INCLUDE_DIR)
  MESSAGE(STATUS "Found CLucene include dir: ${CLUCENE_INCLUDE_DIR}")
ENDIF (CLUCENE_INCLUDE_DIR)

IF(WIN32)
  SET(TRIAL_LIBRARY_PATHS ${CLUCENE_INCLUDE_DIR})
ENDIF(WIN32)

SET(CLUCENE_GOOD_VERSION TRUE)

FIND_PATH(CLUCENE_LIBRARY_DIR
	NAMES CLuceneConfig.cmake/CLuceneConfig.cmake CLucene/CLuceneConfig.cmake
       	PATHS ${TRIAL_LIBRARY_PATHS} ${TRIAL_INCLUDE_PATHS} NO_DEFAULT_PATH)
IF (CLUCENE_LIBRARY_DIR)
  MESSAGE(STATUS "Found CLucene library dir: ${CLUCENE_LIBRARY_DIR}")
  # include CLuceneConfig/CLuceneConfig.cmake
  IF(EXISTS ${CLUCENE_LIBRARY_DIR}/CLuceneConfig.cmake/CLuceneConfig.cmake)
        INCLUDE(${CLUCENE_LIBRARY_DIR}/CLuceneConfig.cmake/CLuceneConfig.cmake)
  ENDIF(EXISTS ${CLUCENE_LIBRARY_DIR}/CLuceneConfig.cmake/CLuceneConfig.cmake)
  # include CLucene/CLuceneConfig.cmake
  IF(EXISTS ${CLUCENE_LIBRARY_DIR}/CLucene/CLuceneConfig.cmake)
        INCLUDE(${CLUCENE_LIBRARY_DIR}/CLucene/CLuceneConfig.cmake)
  ENDIF(EXISTS ${CLUCENE_LIBRARY_DIR}/CLucene/CLuceneConfig.cmake)
  IF (CLUCENE_VERSION STRLESS "${CLUCENE_MIN_VERSION}")
    MESSAGE(ERROR " CLucene version ${CLUCENE_VERSION} is less than the required minimum ${CLUCENE_MIN_VERSION}")
    SET(CLUCENE_GOOD_VERSION FALSE)
  ENDIF (CLUCENE_VERSION STRLESS "${CLUCENE_MIN_VERSION}")
  IF (CLUCENE_VERSION STREQUAL "0.9.17")
    MESSAGE(ERROR "CLucene version 0.9.17 is not supported.")
    SET(CLUCENE_GOOD_VERSION FALSE)
  ENDIF (CLUCENE_VERSION STREQUAL "0.9.17")
ENDIF (CLUCENE_LIBRARY_DIR)

IF(CLUCENE_INCLUDE_DIR AND CLUCENE_LIBRARIES AND CLUCENE_LIBRARY_DIR AND CLUCENE_GOOD_VERSION)
  SET(CLucene_FOUND TRUE)
  SET(CLUCENE_INCLUDE_DIRS ${CLUCENE_LIBRARY_DIR} ${CLUCENE_INCLUDE_DIR})
ENDIF(CLUCENE_INCLUDE_DIR AND CLUCENE_LIBRARIES AND CLUCENE_LIBRARY_DIR AND CLUCENE_GOOD_VERSION)

ENDIF(CLUCENEUNSTABLE_FOUND)

IF(CLucene_FOUND)
  IF(NOT CLucene_FIND_QUIETLY)
    MESSAGE(STATUS "Found CLucene: ${CLUCENE_LIBRARIES} version ${CLUCENE_VERSION}")
  ENDIF(NOT CLucene_FIND_QUIETLY)
ELSE(CLucene_FOUND)
  IF(CLucene_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find CLucene.")
  ENDIF(CLucene_FIND_REQUIRED)
ENDIF(CLucene_FOUND)

MARK_AS_ADVANCED(
  CLUCENE_INCLUDE_DIRS
  CLUCENE_INCLUDE_DIR
  CLUCENE_LIBRARY_DIR
  CLUCENE_LIBRARIES
  )
