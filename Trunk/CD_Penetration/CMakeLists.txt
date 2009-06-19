set(SOURCES 
  CD_Depth.cpp
  DT_TriEdge.cpp
)


add_definitions( 
)

add_library( cd_penetration SHARED ${SOURCES} )
SET_TARGET_PROPERTIES( cd_penetration
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ../lib
)
