set(SOURCES 
  Polyhedron_algorithms.cpp
  S_Polyhedron.cpp
  S_PolyhedronVertex.cpp
)

set(HEADERS
  Polyhedron_algorithms.h
  S_Polyhedron.h
  S_PolyhedronVertex.h
  S_PolyhedronVertex.hxx
)

add_definitions( 
)

add_library( s_polyhedron SHARED ${SOURCES} )
target_link_libraries(s_polyhedron ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
SET_TARGET_PROPERTIES( s_polyhedron
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ../lib
)

INSTALL(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/S_Polyhedron
      PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)

INSTALL(TARGETS s_polyhedron
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/SCD)
