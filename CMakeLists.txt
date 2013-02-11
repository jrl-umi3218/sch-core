cmake_minimum_required(VERSION 2.6)

INCLUDE(cmake/base.cmake)
INCLUDE(cmake/eigen.cmake)
INCLUDE(cmake/boost.cmake)
INCLUDE(cmake/cpack.cmake)
INCLUDE(cmake/amelif.cmake)

DEFINE_PREFIX_SUFFIX()

# set(CXX_DISABLE_WALL True)
set(CXX_DISABLE_WERROR True)
set(CMAKE_VERBOSE_MAKEFILE ON)

# ----------------------------------------------------------------
# --- Project declaration ----------------------------------------
# ----------------------------------------------------------------

SET(PROJECT_NAME scd)
SET(PROJECT_DESCRIPTION "Implementation of the Sphere-Torus Patches Bounding Volumes")
set(PROJECT_CONTACT francois.keith@lirmm.fr)
SET(PROJECT_URL "http://idh.lirmm.fr/projects/stpbv")
set(PROJECT_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

SETUP_PROJECT()

# Search for dependencies.
# Boost
SET(BOOST_COMPONENTS serialization)
SEARCH_FOR_BOOST()

find_package(GLUT)
find_package(OpenGL)

# GLUT is a bit tricky, so check the search result.
if(GLUT_FOUND)
	message("-- GLUT found! Libraries: ${GLUT_LIBRARIES}")
else(GLUT_FOUND)
	message("-- GLUT not found! Trying with the alternative FindGLUT")
	include(CMakeModules/FindGLUT_fix1.cmake)
	if(GLUT_FOUND)
		message("-- GLUT found! Libraries: ${GLUT_LIBRARIES}")
	else(GLUT_FOUND)
		message("-- GLUT not found!")
	endif(GLUT_FOUND)
endif(GLUT_FOUND)


#you need GLUT to display the objects or to run the test
if(GLUT_FOUND)
  set(WITH_OPENGL 1)
  # used variable in SCD.pc.cmake
  PKG_CONFIG_APPEND_CFLAGS("-DWITH_OPENGL")
  add_definitions("-DWITH_OPENGL")
endif(GLUT_FOUND)


# Optimisation flags when building with RELEASE
#----------------------------------------------
IF(CMAKE_BUILD_TYPE MATCHES "RELEASE")
  IF(CMAKE_COMPILER_IS_GNUCXX)
#    SET (${PROJECT_NAME}_CXXFLAGS "-O3 -funroll-loops -frerun-loop-opt -fschedule-insns2 -frerun-cse-after-loop -falign-functions -falign-labels -falign-loops -falign-jumps -fexpensive-optimizations ${${PROJECT_NAME}_CXXFLAGS}")
  ENDIF(CMAKE_COMPILER_IS_GNUCXX)
ENDIF(CMAKE_BUILD_TYPE MATCHES "RELEASE")

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(unitTestings)

# Add dependency toward dynamic graph library in pkg-config file.
PKG_CONFIG_APPEND_LIBS("dynamic-graph")

SETUP_PROJECT_FINALIZE()
SETUP_PROJECT_CPACK()
