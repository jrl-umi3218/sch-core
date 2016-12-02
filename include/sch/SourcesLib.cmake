macro(InstallFiles  files  sub_folder)
  set (allfiles "")
  foreach(fileA ${${files}})
    list(APPEND  allfiles  "${PROJECT_SOURCE_DIR}/include/sch/${fileA}")
  endforeach(fileA)

  source_group("${sub_folder}" FILES ${allfiles})

  install(FILES ${allfiles}
       DESTINATION ${CMAKE_INSTALL_PREFIX}/include/sch/${sub_folder}
       PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
  )

  list(APPEND  HEADERS 	${allfiles})
endmacro(InstallFiles)

SET(HEADERS_ROOT
  sch_api.h
)
InstallFiles(HEADERS_ROOT  "")


SET(HEADERS_CD
  CD/CD_Pair.h
  CD/CD_Scene.h
  CD/CD_SimplexEnhanced.h
  CD/CD_Simplex.h
  CD/GJK.h
  CD/CD_SimplexEnhanced.hxx
  CD/CD_Simplex.hxx
)
InstallFiles(HEADERS_CD  "CD")


SET(HEADERS_CD_Penetration
  CD_Penetration/CD_Depth.h
  CD_Penetration/DT_TriEdge.h
)
InstallFiles(HEADERS_CD_Penetration  	"CD_Penetration")


SET(HEADERS_File_Parsing
  File_Parsing/SimplestParsing.h
)
InstallFiles(HEADERS_File_Parsing	"File_Parsing")


SET(HEADERS_Matrix
  Matrix/QuaternionT.h
  Matrix/SCH_Types.h
  Matrix/SmallMatrix3x3T.h
  Matrix/SmallMatrix4x4T.h
  Matrix/SmallVector3T.h
  Matrix/SmallVector4T.h
)
InstallFiles(HEADERS_Matrix  	"Matrix")


SET(HEADERS_S_Object
  S_Object/S_Box.h
  S_Object/S_Object.h
  S_Object/S_ObjectNonNormalized.h
  S_Object/S_ObjectNormalized.h
  S_Object/S_Sphere.h
  S_Object/S_Superellipsoid.h
  S_Object/S_Object.hxx
  S_Object/S_ObjectNonNormalized.hxx
  S_Object/S_ObjectNormalized.hxx
  S_Object/S_Point.h
  S_Object/S_Capsule.h
)
InstallFiles(HEADERS_S_Object	"S_Object")


SET(HEADERS_S_Polyhedron
  S_Polyhedron/Polyhedron_algorithms.h
  S_Polyhedron/S_Polyhedron.h
  S_Polyhedron/S_PolyhedronVertex.h
  S_Polyhedron/S_PolyhedronVertex.hxx
)
InstallFiles(HEADERS_S_Polyhedron  "S_Polyhedron")


SET(HEADERS_STP_BV
  STP-BV/STP_BigSphere.h
  STP-BV/STP_BV.h
  STP-BV/STP_BV_P.h
  STP-BV/STP_Feature.h
  STP-BV/STP_SmallSphere.h
  STP-BV/STP_Torus.h
  STP-BV/STP_Feature.hxx
)
InstallFiles(HEADERS_STP_BV  "STP-BV")
