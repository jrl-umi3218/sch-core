project( S_Polyhedron )

set(SOURCES 
  Polyhedron_algorithms.cpp
  S_Polyhedron.cpp
  S_PolyhedronVertex.cpp
)


add_definitions( 
)

add_library( S_Polyhedron STATIC ${SOURCES} )

