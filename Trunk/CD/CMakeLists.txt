set(SOURCES 
  CD_Pair.cpp
  CD_Scene.cpp
  CD_Simplex.cpp
  CD_SimplexEnhanced.cpp
)


add_definitions( 
)

ADD_LIBRARY( cd SHARED ${SOURCES} )
target_link_libraries(cd ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
SET_TARGET_PROPERTIES( cd
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ../lib
)
