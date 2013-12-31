# Francois Keith, JRL, CNRS/AIST
# Creation: 19/08/2010
# History:
#
# Copyright CNRS/AIST

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${PROJECT_INCLUDE_DIR})

add_executable(	test_no_display test_no_display.cpp common.cpp common.h includes.h)
target_link_libraries(test_no_display scd  ${Boost_LIBRARIES})
add_dependencies(test_no_display scd)


add_custom_command(TARGET test_no_display POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/unitTestings/sample_stpbv1.txt
  ${CMAKE_BINARY_DIR}/unitTestings/
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/unitTestings/sample_stpbv2.txt
  ${CMAKE_BINARY_DIR}/unitTestings/
)

if(GLUT_FOUND)
  include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${PROJECT_INCLUDE_DIR})
  add_executable(test_glut Test1.cpp common.cpp common.h includes.h)
  target_link_libraries(test_glut ${Boost_LIBRARIES})
  target_link_libraries(test_glut scd scd_viewer)
  target_link_libraries(test_glut ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
  add_dependencies(test_glut scd)
  add_dependencies(test_glut scd_viewer)
endif(GLUT_FOUND)

