set(SOURCES 
  CD/CD_Pair.cpp
  CD/CD_Scene.cpp
  CD/CD_Simplex.cpp
  CD/CD_SimplexEnhanced.cpp
  CD_Penetration/CD_Depth.cpp
  CD_Penetration/DT_TriEdge.cpp
  File_Parsing/SimplestParsing.cpp
  S_Object/S_Sphere.cpp
  S_Object/S_ObjectNormalized.cpp
  S_Object/S_Object.cpp
  S_Object/S_ObjectNonNormalized.cpp
  S_Object/S_Box.cpp
  S_Object/S_Superellipsoid.cpp
  S_Polyhedron/S_PolyhedronVertex.cpp
  S_Polyhedron/Polyhedron_algorithms.cpp
  S_Polyhedron/S_Polyhedron.cpp
  STP-BV/STP_SmallSphere.cpp
  STP-BV/STP_Feature.cpp
  STP-BV/STP_BV.cpp
  STP-BV/STP_BigSphere.cpp
  STP-BV/STP_BV_P.cpp
  STP-BV/STP_Torus.cpp
)

ADD_LIBRARY( scd SHARED ${SOURCES} )
target_link_libraries(scd ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
SET_TARGET_PROPERTIES( scd
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ../lib
)

INSTALL(TARGETS scd
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
