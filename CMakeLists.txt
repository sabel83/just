# Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

set(CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required

cmake_minimum_required(VERSION 2.6)
project(just)
set(CMAKE_PROJECT_NAME just)
set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIR})

enable_testing()

include_directories("include")

# Warning level
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")

  # Boost.Config says that variadic macros are available when they should not be
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-variadic-macros")

  message("Setting warning level for GCC")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")

  # Boost.Config says that variadic macros are available when they should not be
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-variadic-macros")

  message("Setting warning level for Clang")
endif()

subdirs(libs)

# Installation
macro(install_with_dir PREFIX_TO_CUT)
 
 string(LENGTH ${PREFIX_TO_CUT} PREFIX_LEN)

 foreach(F ${ARGN})
   string(REGEX MATCH "(.*)[/\\]" DIR ${F})
   string(LENGTH ${DIR} DIR_LEN)
   math(EXPR DIR_KEEP "${DIR_LEN} - ${PREFIX_LEN}")
   string(SUBSTRING ${DIR} ${PREFIX_LEN} ${DIR_KEEP} DIR2)
   install(FILES ${F} DESTINATION include/${DIR2})
 endforeach(F)
          
endmacro(install_with_dir)

set(CMAKE_INSTALL_PREFIX "/usr")

file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/just/*.hpp)
install_with_dir(${CMAKE_CURRENT_SOURCE_DIR} ${HEADER_FILES})

# Debian package
if(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
  include(InstallRequiredSystemLibraries)
   
  set(CPACK_SET_DESTDIR "on")
  set(CPACK_PACKAGING_INSTALL_PREFIX "/tmp")
  set(CPACK_GENERATOR "DEB")
   
  set(CPACK_PACKAGE_DESCRIPTION "Just")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Lightweight C++ libraries")
  set(CPACK_PACKAGE_VENDOR "Abel Sinkovics")
  set(CPACK_PACKAGE_CONTACT "abel@sinkovics.hu")
  set(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
  set(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
  set(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
  set(CPACK_PACKAGE_FILE_NAME "lib${CMAKE_PROJECT_NAME}-${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}-dev")
  set(CPACK_SOURCE_PACKAGE_FILE_NAME "lib${CMAKE_PROJECT_NAME}-${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}-dev")

  set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-dev")
   
  set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
  set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
  set(CPACK_DEBIAN_ARCHITECTURE "all") # Header-only
   
  set(CPACK_COMPONENTS_ALL headers)
  include(CPack)
   
endif(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")



