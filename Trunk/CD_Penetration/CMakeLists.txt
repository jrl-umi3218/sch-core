set(SOURCES 
  CD_Depth.cpp
  DT_TriEdge.cpp
)

set(HEADERS
  CD_Depth.h
  DT_TriEdge.h
)

add_definitions( 
)

add_library( cd_penetration SHARED ${SOURCES} )
SET_TARGET_PROPERTIES( cd_penetration
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ../lib
)

INSTALL(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/CD_Penetration
      PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)

INSTALL(TARGETS cd_penetration
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/SCD)
