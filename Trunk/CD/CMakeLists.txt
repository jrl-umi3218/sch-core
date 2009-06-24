set(SOURCES 
  CD_Pair.cpp
  CD_Scene.cpp
  CD_Simplex.cpp
  CD_SimplexEnhanced.cpp
)

set(HEADERS
  CD_Pair.h
  CD_Scene.h
  CD_Simplex.h
  CD_Simplex.hxx
  CD_SimplexEnhanced.h  
  CD_SimplexEnhanced.hxx
  GJK.h
)

add_definitions( 
)

ADD_LIBRARY( cd SHARED ${SOURCES} )
target_link_libraries(cd ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
SET_TARGET_PROPERTIES( cd
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ../lib
)

INSTALL(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/CD
      PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)

INSTALL(TARGETS cd
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/SCD)
