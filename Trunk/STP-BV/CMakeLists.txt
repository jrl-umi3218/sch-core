set(SOURCES 
  STP_BigSphere.cpp
  STP_BV.cpp
  STP_BV_P.cpp
  STP_Feature.cpp
  STP_SmallSphere.cpp
  STP_Torus.cpp
)

set(HEADERS
  STP_BigSphere.h
  STP_BV.h
  STP_BV_P.h
  STP_Feature.h
  STP_Feature.hxx
  STP_SmallSphere.h
  STP_Torus.h
)

add_definitions( 
)

ADD_LIBRARY( stp-bv SHARED ${SOURCES} )
target_link_libraries(stp-bv ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
SET_TARGET_PROPERTIES( stp-bv
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ../lib
)

INSTALL(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/STP-BV
      PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)

INSTALL(TARGETS stp-bv
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/SCD)
