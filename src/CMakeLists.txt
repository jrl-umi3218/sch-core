# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# CMake file for the sch project: src subdirectory
#
# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# --- sources ---

include(${PROJECT_INCLUDE_DIR}/sch/SourcesLib.cmake)

# --- def, cflags and link flags ---




set(SOURCES "")
macro(AddSourceGroup  files  sub_folder)
  source_group("${sub_folder}" FILES ${${files}})
  list(APPEND  SOURCES 	${${files}})
endmacro(AddSourceGroup)

SET(SOURCES_CD
  CD/CD_Pair.cpp
  CD/CD_Scene.cpp
  CD/CD_Simplex.cpp
  CD/CD_SimplexEnhanced.cpp
)
AddSourceGroup(SOURCES_CD "CD")

SET(SOURCES_CD_Penetration
  CD_Penetration/CD_Depth.cpp
)
if(NOT ${BUILD_BSD})
  list(APPEND SOURCES_CD_Penetration CD_Penetration/DT_TriEdge.h)
  list(APPEND SOURCES_CD_Penetration CD_Penetration/DT_TriEdge.cpp)
endif()
AddSourceGroup(SOURCES_CD_Penetration "CD_Penetration")

SET(SOURCES_File_Parsing
  File_Parsing/SimplestParsing.cpp
)
AddSourceGroup(SOURCES_File_Parsing "File_Parsing")

SET(SOURCES_S_Object
  S_Object/S_Sphere.cpp
  S_Object/S_ObjectNormalized.cpp
  S_Object/S_Object.cpp
  S_Object/S_ObjectNonNormalized.cpp
  S_Object/S_Box.cpp
  S_Object/S_Superellipsoid.cpp
  S_Object/S_Point.cpp
  S_Object/S_Capsule.cpp
)
AddSourceGroup(SOURCES_S_Object "S_Object")

SET(SOURCES_S_Polyhedron
  S_Polyhedron/S_PolyhedronVertex.cpp
  S_Polyhedron/Polyhedron_algorithms.cpp
  S_Polyhedron/S_Polyhedron.cpp
)
AddSourceGroup(SOURCES_S_Polyhedron "S_Polyhedron")

SET(SOURCES_STP_BV
  STP-BV/STP_SmallSphere.cpp
  STP-BV/STP_Feature.cpp
  STP-BV/STP_BV.cpp
  STP-BV/STP_BV_P.cpp
  STP-BV/STP_BigSphere.cpp
  STP-BV/STP_Torus.cpp
)
AddSourceGroup(SOURCES_STP_BV "STP-BV")

add_library(sch-core SHARED ${SOURCES} ${HEADERS})
target_include_directories(sch-core PUBLIC  $<BUILD_INTERFACE:${PROJECT_INCLUDE_DIR}> $<INSTALL_INTERFACE:${include_install_destination}>)
target_link_libraries(sch-core PUBLIC Boost::serialization Boost::disable_autolinking)
if(${BUILD_BSD})
  target_compile_definitions(sch-core PRIVATE "-DBUILD_BSD")
endif()


set_target_properties(sch-core PROPERTIES SOVERSION ${PROJECT_VERSION}
                                          COMPILE_OPTIONS "-Dsch_EXPORTS")


# Targets:
#   * <prefix>/lib/libbar.a
#   * <prefix>/lib/libbaz.a
#   * header location after install: <prefix>/include/foo/Bar.hpp
#   * headers can be included by C++ code `#include <foo/Bar.hpp>`
install(
    TARGETS sch-core
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${INCLUDE_INSTALL_DIR}"
)
install(FILES ${HEADERS} DESTINATION ${INCLUDE_INSTALL_DESTINATION})

