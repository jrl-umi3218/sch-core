cmake_minimum_required(VERSION 2.8.12)

if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()
set(CXX_DISABLE_WERROR True)

# ----------------------------------------------------------------
# --- Project declaration ----------------------------------------
# ----------------------------------------------------------------

set(PROJECT_NAME sch-core)
set(PROJECT_DESCRIPTION "Implementation of the Sphere-Torus Patches Bounding Volumes")
set(PROJECT_CONTACT pierre.gergondet@gmail.com)
set(PROJECT_URL "http://idh.lirmm.fr/projects/stpbv")
set(PROJECT_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
if (NOT DEFINED PROJECT_DEBUG_POSTFIX)
    set(PROJECT_DEBUG_POSTFIX "_d")
endif()

set(PROJECT_VERSION 1.2.0)
set(PROJECT_USE_CMAKE_EXPORT TRUE)

include(cmake/base.cmake)
include(cmake/cpack.cmake)
include(cmake/msvc-specific.cmake)

project(sch-core CXX)

# We add a recent version of FindBoost.cmake in our path
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

# Search for dependencies.
# Boost
add_project_dependency(Boost REQUIRED COMPONENTS serialization)

option(SCH_BUILD_BSD "Build without GPL components." OFF)

option(ENABLE_SIGFPE "Enable floating-point exceptions" OFF)
if(ENABLE_SIGFPE)
  if(NOT WIN32)
    add_definitions(-DENABLE_SIGFPE)
  endif()
endif()

# For MSVC, set local environment variable to enable finding the built dll
# of the main library when launching ctest with RUN_TESTS
if(MSVC)
  set(CMAKE_MSVCIDE_RUN_PATH "\$(SolutionDir)/src/\$(Configuration)")
endif(MSVC)

add_subdirectory(src)
add_subdirectory(examples)
if(${BUILD_TESTING})
  add_subdirectory(tests)
endif()

pkg_config_append_libs(sch-core)
