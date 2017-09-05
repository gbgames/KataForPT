CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

SET(GB_PROJECT_NAME KataForPT)
PROJECT (${GB_PROJECT_NAME})
IF(DEFINED CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of
   build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug
   Release RelWithDebInfo MinSizeRel.")
ELSE()
   SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build,
	  options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release
	  RelWithDebInfo MinSizeRel.")
ENDIF()
SET(CMAKE_CXX_FLAGS_Debug "-g -O0 -Wall -W -Wreturn-type -Wno-unused-parameter -Werror")
SET(CMAKE_CXX_FLAGS_Release "-O2 -Wall -Werror -Wstrict-aliasing=2 -mwindows") 

SET (CMAKE_INCLUDE_CURRENT_DIR ON)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

ADD_SUBDIRECTORY (source)
