cmake_minimum_required(VERSION 2.6)

enable_language(CXX)

SET(PROJECT_NAME SCD)

SET(CMAKE_VERBOSE_MAKEFILE ON)

project(${PROJECT_NAME})

IF(WIN32)
  SET(LIBDIR_KW "/LIBPATH:")
  SET(LIBINCLUSION_KW "")
  SET(LIBINCLUSION_EXT ".lib")
ENDIF(WIN32)

IF(UNIX)
  SET(LIBDIR_KW "-L")
  SET(LIBINCLUSION_KW "-l")
  SET(LIBINCLUSION_EXT "")
  SET(${PROJECT_NAME}_CXXFLAGS "-DUNIX" )
ENDIF(UNIX)

include_directories(${PROJECT_SOURCE_DIR})
find_package(GLUT)
find_package(OpenGL)


add_subdirectory(CD)
add_subdirectory(CD_Penetration)
add_subdirectory(File_Parsing)
add_subdirectory(Matrix)
add_subdirectory(S_Object)
add_subdirectory(S_Polyhedron)
add_subdirectory(STP-BV)

# Build a pkgconfig file
SET(install_pkg_libdir "\${libdir}")
SET(install_pkg_include_dir "\${includedir}")

CONFIGURE_FILE(${${PROJECT_NAME}_SOURCE_DIR}/${PROJECT_NAME}.pc.cmake
          ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}.pc)
INSTALL(FILES ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}.pc
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)
