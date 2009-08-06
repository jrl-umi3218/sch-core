SET(HEADERS
  CD/CD_Pair.h
  CD/CD_Scene.h
  CD/CD_SimplexEnhanced.h
  CD/CD_Simplex.h
  CD/GJK.h
  CD/CD_SimplexEnhanced.hxx
  CD/CD_Simplex.hxx
)
INSTALL(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/CD
      PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)

SET(HEADERS
  CD_Penetration/CD_Depth.h
  CD_Penetration/DT_TriEdge.h
)
INSTALL(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/CD_Penetration
      PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)

SET(HEADERS
  File_Parsing/SimplestParsing.h
)
INSTALL(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/File_Parsing
      PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)

SET(HEADERS
  Matrix/configMAL.h
  Matrix/MatrixAbstractLayerBoost.h
  Matrix/MatrixAbstractLayerDoc.h
  Matrix/MatrixAbstractLayer.h
  Matrix/MatrixAbstractLayerSmall.h
  Matrix/MatrixAbstractLayerT3D.h
  Matrix/MatrixAbstractLayerVNL.h
  Matrix/QuaternionM.h
  Matrix/SCD_Types.h
  Matrix/SmallMatrix3x3Default.h
  Matrix/SmallMatrix3x3Mod.h
  Matrix/SmallMatrix4x4Default.h
  Matrix/SmallVector3Default.h
  Matrix/SmallVector3Mod.h
  Matrix/SmallVector4Default.h
  Matrix/SmallVector4Mod.h
)
INSTALL(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/Matrix
      PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)

SET(HEADERS
  S_Object/S_Box.h
  S_Object/S_Object.h
  S_Object/S_ObjectNonNormalized.h
  S_Object/S_ObjectNormalized.h
  S_Object/S_Sphere.h
  S_Object/S_Superellipsoid.h
  S_Object/S_Object.hxx
  S_Object/S_ObjectNonNormalized.hxx
  S_Object/S_ObjectNormalized.hxx
)
INSTALL(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/S_Object
      PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)

SET(HEADERS
  S_Polyhedron/Polyhedron_algorithms.h
  S_Polyhedron/S_Polyhedron.h
  S_Polyhedron/S_PolyhedronVertex.h
  S_Polyhedron/S_PolyhedronVertex.hxx
)
INSTALL(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/S_Polyhedron
      PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)

SET(HEADERS
  STP-BV/STP_BigSphere.h
  STP-BV/STP_BV.h
  STP-BV/STP_BV_P.h
  STP-BV/STP_Feature.h
  STP-BV/STP_SmallSphere.h
  STP-BV/STP_Torus.h
  STP-BV/STP_Feature.hxx
)
INSTALL(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/STP-BV
      PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)
