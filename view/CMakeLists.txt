# Create the SCD viewer library

include_directories(BEFORE ${PROJECT_INCLUDE_DIR})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#you need GLUT to display the objects or to run the test
include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
add_library(scd_viewer SHARED 
  S_Object_gl.cpp
  S_Object_Raw_gl.cpp
	STPBV_gl.cpp
  S_Box_gl.cpp
  S_Sphere_gl.cpp
  S_Supperellipsoid_gl.cpp
  Polyhedron_algorithms_gl.cpp
)
set_target_properties(scd_viewer PROPERTIES SOVERSION ${PROJECT_VERSION})
target_link_libraries(scd_viewer scd ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})


install(FILES S_Object_gl.h
     DESTINATION ${CMAKE_INSTALL_PREFIX}/include/SCD/view/
     PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)

install(TARGETS scd_viewer
        RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

