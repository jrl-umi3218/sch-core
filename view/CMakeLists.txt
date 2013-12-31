include_directories(BEFORE ${PROJECT_INCLUDE_DIR})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})


find_package(GLUT)
find_package(OpenGL)

# GLUT is a bit tricky, so check the search result.
if(GLUT_FOUND)
	message("-- GLUT found! Libraries: ${GLUT_LIBRARIES}")
else(GLUT_FOUND)
	message("-- GLUT not found! Trying with the alternative FindGLUT")
	include(CMakeModules/FindGLUT_fix1.cmake)
	if(GLUT_FOUND)
		message("-- GLUT found! Libraries: ${GLUT_LIBRARIES}")
	else(GLUT_FOUND)
		message("-- GLUT not found!")
	endif(GLUT_FOUND)
endif(GLUT_FOUND)


#you need GLUT to display the objects or to run the test
# used variable in SCD.pc.cmake
include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
add_library(scd_viewer SHARED 
  S_Object_gl.cpp
#	STPBV_gl.cpp
  S_Box_gl.cpp
  S_Sphere_gl.cpp
  S_Supperellipsoid_gl.cpp
  Polyhedron_algorithms_gl.cpp
)
target_link_libraries(scd_viewer scd ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})


