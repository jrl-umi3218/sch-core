set(SOURCES 
  S_Box.cpp
  S_Object.cpp
  S_ObjectNonNormalized.cpp
  S_ObjectNormalized.cpp
  S_Sphere.cpp
  S_Superellipsoid.cpp
)


add_definitions( 
)

ADD_LIBRARY( s_object SHARED ${SOURCES} )
target_link_libraries(s_object ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
SET_TARGET_PROPERTIES( s_object
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ../lib
)

