set(SOURCES 
  S_Box.cpp
  S_Object.cpp
  S_ObjectNonNormalized.cpp
  S_ObjectNormalized.cpp
  S_Sphere.cpp
  S_Superellipsoid.cpp
)

set(HEADERS
  S_Box.h
  S_Object.h
  S_Object.hxx
  S_ObjectNonNormalized.h
  S_ObjectNonNormalized.hxx
  S_ObjectNormalized.h
  S_ObjectNormalized.hxx
  S_Sphere.h
  S_Superellipsoid.h
)

add_definitions( 
)

ADD_LIBRARY( s_object SHARED ${SOURCES} )
target_link_libraries(s_object ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
SET_TARGET_PROPERTIES( s_object
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ../lib
)

INSTALL(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/S_Object
      PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)

INSTALL(TARGETS s_object
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/SCD)
