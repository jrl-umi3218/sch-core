cmake_minimum_required(VERSION 2.8.12)

INCLUDE(cmake/base.cmake)
INCLUDE(cmake/eigen.cmake)
INCLUDE(cmake/boost.cmake)
INCLUDE(cmake/cpack.cmake)
INCLUDE(cmake/msvc-specific.cmake)

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
INCLUDE(cmake/msvc-specific.cmake)

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

# For MSVC, set local environment variable to enable finding the built dll
# of the main library when launching ctest with RUN_TESTS
IF(MSVC)
  SET(CMAKE_MSVCIDE_RUN_PATH "\$(SolutionDir)/src/\$(Configuration)")
ENDIF(MSVC)

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
