cmake_minimum_required(VERSION 3.22)

if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()
set(CXX_DISABLE_WERROR True)

# ----------------------------------------------------------------
# --- Project declaration ----------------------------------------
# ----------------------------------------------------------------

set(PROJECT_NAME sch-core)
set(PROJECT_DESCRIPTION
    "Implementation of the Sphere-Torus Patches Bounding Volumes")
set(PROJECT_CONTACT pierre.gergondet@gmail.com)
set(PROJECT_URL "http://idh.lirmm.fr/projects/stpbv")
set(PROJECT_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
if(NOT DEFINED PROJECT_DEBUG_POSTFIX)
  set(PROJECT_DEBUG_POSTFIX "_d")
endif()

set(PROJECT_VERSION 1.4.5)
set(PROJECT_USE_CMAKE_EXPORT TRUE)

# Check if the submodule cmake have been initialized
set(JRL_CMAKE_MODULES "${CMAKE_CURRENT_LIST_DIR}/cmake")
if(EXISTS "${JRL_CMAKE_MODULES}/base.cmake")
  message(STATUS "JRL cmakemodules found in 'cmake/' git submodule")
else()
  find_package(jrl-cmakemodules QUIET CONFIG)
  if(jrl-cmakemodules_FOUND)
    get_property(
      JRL_CMAKE_MODULES
      TARGET jrl-cmakemodules::jrl-cmakemodules
      PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
    message(STATUS "JRL cmakemodules found on system at ${JRL_CMAKE_MODULES}")
  else()
    message(STATUS "JRL cmakemodules not found. Let's fetch it.")
    include(FetchContent)
    FetchContent_Declare(
      "jrl-cmakemodules"
      GIT_REPOSITORY "https://github.com/jrl-umi3218/jrl-cmakemodules.git")
    FetchContent_MakeAvailable("jrl-cmakemodules")
    FetchContent_GetProperties("jrl-cmakemodules" SOURCE_DIR JRL_CMAKE_MODULES)
  endif()
endif()
include(${JRL_CMAKE_MODULES}/base.cmake)
include(${JRL_CMAKE_MODULES}/cpack.cmake)
include(${JRL_CMAKE_MODULES}/msvc-specific.cmake)

project(sch-core CXX)

# We add a recent version of FindBoost.cmake in our path
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

# Search for dependencies. Boost
add_project_dependency(Boost REQUIRED COMPONENTS serialization)

option(SCH_BUILD_BSD "Build without GPL components." OFF)

option(ENABLE_SIGFPE "Enable floating-point exceptions" OFF)
if(ENABLE_SIGFPE)
  if(NOT WIN32)
    add_definitions(-DENABLE_SIGFPE)
  endif()
endif()

# For MSVC, set local environment variable to enable finding the built dll of
# the main library when launching ctest with RUN_TESTS
if(MSVC)
  set(CMAKE_MSVCIDE_RUN_PATH "\$(SolutionDir)/src/\$(Configuration)")
endif(MSVC)

add_subdirectory(src)
add_subdirectory(examples)
if(${BUILD_TESTING})
  add_subdirectory(tests)
endif()

pkg_config_append_libs(sch-core)
