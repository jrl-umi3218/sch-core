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
SET_TARGET_PROPERTIES( s_object
    PROPERTIES
    COMPILE_FLAGS ${${PROJECT_NAME}_CXXFLAGS}
)

