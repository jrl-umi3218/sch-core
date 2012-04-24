cmake_minimum_required(VERSION 2.6)

enable_language(CXX)
if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
  set (CONFIG_EXT "d") #Extension corresponding to the configuration debug
endif ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")


SET(PROJECT_NAME SCD)
SET(LIB_NAME scd${CONFIG_EXT})

SET(CMAKE_VERBOSE_MAKEFILE ON)

project(${PROJECT_NAME})

IF(WIN32)
  SET(LIBDIR_KW "/LIBPATH:")
  SET(LIBINCL_KW "")
  SET(LIB_EXT ".lib")
ENDIF(WIN32)

IF(UNIX)
  SET(LIBDIR_KW "-L")
  SET(LIBINCL_KW "-l")
  SET(LIB_EXT "")
  SET(${PROJECT_NAME}_CXXFLAGS "-DUNIX" )
ENDIF(UNIX)

set(Boost_ADDITIONAL_VERSIONS "1.39" "1.39.0" CACHE PATH "Additional versions of boost")
find_package(Boost COMPONENTS serialization REQUIRED)
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
  set(WITH_OPENGL_CFLAGS "-DWITH_OPENGL")
  add_definitions("-DWITH_OPENGL")
endif(GLUT_FOUND)





IF(${Boost_MINOR_VERSION} LESS 36)
  SET(${PROJECT_NAME}_CXXFLAGS "-D WITH_BOOST_1_36 ${${PROJECT_NAME}_CXXFLAGS}")
ENDIF(${Boost_MINOR_VERSION} LESS 36)

include_directories(${PROJECT_SOURCE_DIR}/include  ${Boost_INCLUDE_DIR})
# Optimisation flags when building with RELEASE
#----------------------------------------------
IF(CMAKE_BUILD_TYPE MATCHES "RELEASE")
  IF(CMAKE_COMPILER_IS_GNUCXX)
    SET (${PROJECT_NAME}_CXXFLAGS "-O3 -funroll-loops -frerun-loop-opt -fschedule-insns2 -frerun-cse-after-loop -falign-functions -falign-labels -falign-loops -falign-jumps -fexpensive-optimizations ${${PROJECT_NAME}_CXXFLAGS}")
  ENDIF(CMAKE_COMPILER_IS_GNUCXX)
ENDIF(CMAKE_BUILD_TYPE MATCHES "RELEASE")

add_subdirectory(src)
add_subdirectory(unitTestings)

# ----------------------------------------------------------------
# --- Documentation ----------------------------------------------
# ----------------------------------------------------------------

option(GENERATE_DOC "Generate the documentation " OFF)
if (GENERATE_DOC)
  include(FindDoxygen)
  if(DOXYGEN_FOUND)
    add_subdirectory(doc)
  endif(DOXYGEN_FOUND)
endif (GENERATE_DOC)

# Build a pkgconfig file
SET(install_pkg_libdir "\${libdir}")
SET(install_pkg_include_dir "\${includedir}")

CONFIGURE_FILE(${${PROJECT_NAME}_SOURCE_DIR}/${PROJECT_NAME}.pc.cmake
          ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}.pc)
INSTALL(FILES ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}.pc
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)
