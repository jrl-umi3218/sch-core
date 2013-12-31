# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# CMake file for the scd project: src subdirectory
#
# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# --- sources ---

include(${PROJECT_INCLUDE_DIR}/SCD/SourcesLib.cmake)

# --- def, cflags and link flags ---

ADD_AMELIF_DEFS()

include_directories(BEFORE ${PROJECT_INCLUDE_DIR})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})



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
  CD_Penetration/DT_TriEdge.cpp
)
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

link_directories(${Boost_LIBRARY_DIRS})
ADD_LIBRARY(scd SHARED ${SOURCES} ${HEADERS})

set_target_properties(scd PROPERTIES SOVERSION ${PROJECT_VERSION})
target_link_libraries(scd ${Boost_LIBRARIES})


install(TARGETS scd
        RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

