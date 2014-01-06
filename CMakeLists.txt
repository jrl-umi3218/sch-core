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

option(PYTHON_BINDINGS "Generate Python bindings." ON)

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


# Optimisation flags when building with RELEASE
#----------------------------------------------
IF(CMAKE_BUILD_TYPE MATCHES "RELEASE")
  IF(CMAKE_COMPILER_IS_GNUCXX)
#    SET (${PROJECT_NAME}_CXXFLAGS "-O3 -funroll-loops -frerun-loop-opt -fschedule-insns2 -frerun-cse-after-loop -falign-functions -falign-labels -falign-loops -falign-jumps -fexpensive-optimizations ${${PROJECT_NAME}_CXXFLAGS}")
  ENDIF(CMAKE_COMPILER_IS_GNUCXX)
ENDIF(CMAKE_BUILD_TYPE MATCHES "RELEASE")

PKG_CONFIG_APPEND_LIBS("scd")

ADD_SUBDIRECTORY(src)
if(GLUT_FOUND)
 ADD_SUBDIRECTORY(view)
endif(GLUT_FOUND)
ADD_SUBDIRECTORY(unitTestings)

IF(PYTHON_BINDINGS)
 ADD_SUBDIRECTORY(bindings/python)
ENDIF(PYTHON_BINDINGS)

SETUP_PROJECT_FINALIZE()
SETUP_PROJECT_CPACK()
