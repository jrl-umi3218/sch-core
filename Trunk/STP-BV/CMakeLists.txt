set(SOURCES 
  STP_BigSphere.cpp
  STP_BV.cpp
  STP_BV_P.cpp
  STP_Feature.cpp
  STP_SmallSphere.cpp
  STP_Torus.cpp
)


add_definitions( 
)

ADD_LIBRARY( stp-bv SHARED ${SOURCES} )
target_link_libraries(stp-bv ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
SET_TARGET_PROPERTIES( stp-bv
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ../lib
)

