# Francois Keith, JRL, CNRS/AIST
# Creation: 19/08/2010
# History:
#
# Copyright CNRS/AIST

INCLUDE(CTest)

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# For the test, we include the same files as the src
# SET(${PROJECT_NAME}_test_CXXFLAGS "-I${PROJECT_SOURCE_DIR}/include/ ${${PROJECT_NAME}_CXXFLAGS}")

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
  add_executable(	test_glut Test1.cpp common.cpp common.h includes.h)
  target_link_libraries(test_glut ${GLUT_LIBRARIES} scd  ${Boost_LIBRARIES})

  add_dependencies(test_glut scd)
endif(GLUT_FOUND)


