set(HEADERS
  configMAL.h
  MatrixAbstractLayerBoost.h
  MatrixAbstractLayerDoc.h
  MatrixAbstractLayer.h
  MatrixAbstractLayerSmall.h
  MatrixAbstractLayerT3D.h
  MatrixAbstractLayerVNL.h
  QuaternionM.h
  SCD_Types.h
  SmallMatrix3x3Default.h
  SmallMatrix3x3Mod.h
  SmallMatrix4x4Default.h
  SmallVector3Default.h
  SmallVector3Mod.h
  SmallVector4Default.h
  SmallVector4Mod.h
)

INSTALL(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/Matrix
      PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)
