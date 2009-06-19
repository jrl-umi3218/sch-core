set(SOURCES 
  Polyhedron_algorithms.cpp
  S_Polyhedron.cpp
  S_PolyhedronVertex.cpp
)


add_definitions( 
)

add_library( s_polyhedron SHARED ${SOURCES} )
target_link_libraries(s_polyhedron ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
SET_TARGET_PROPERTIES( s_polyhedron
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ../lib
)

