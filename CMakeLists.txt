cmake_minimum_required(VERSION 2.6)

INCLUDE(cmake/base.cmake)
INCLUDE(cmake/eigen.cmake)
INCLUDE(cmake/boost.cmake)
INCLUDE(cmake/cpack.cmake)

set(CXX_DISABLE_WERROR True)
set(CMAKE_VERBOSE_MAKEFILE ON)

# ----------------------------------------------------------------
# --- Project declaration ----------------------------------------
# ----------------------------------------------------------------

SET(PROJECT_NAME sch-core)
SET(PROJECT_DESCRIPTION "Implementation of the Sphere-Torus Patches Bounding Volumes")
set(PROJECT_CONTACT francois.keith@lirmm.fr)
SET(PROJECT_URL "http://idh.lirmm.fr/projects/stpbv")
set(PROJECT_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

SETUP_PROJECT()

# Search for dependencies.
# Boost
SET(BOOST_COMPONENTS serialization)
SEARCH_FOR_BOOST()

PKG_CONFIG_APPEND_LIBS("sch-core")

option(ENABLE_SIGFPE "Enable floating-point exceptions" OFF)
if(ENABLE_SIGFPE)
  if(NOT WIN32)
    add_definitions(-DENABLE_SIGFPE)
  endif()
endif()

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(examples)
IF(NOT DISABLE_TESTS)
  ADD_SUBDIRECTORY(tests)
ELSE()
  MESSAGE(WARNING
    "Tests should only be disabled for speficic cases. Do it at your own risk.")
ENDIF()

SETUP_PROJECT_FINALIZE()
SETUP_PROJECT_CPACK()
