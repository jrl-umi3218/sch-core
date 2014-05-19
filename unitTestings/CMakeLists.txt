# Francois Keith, JRL, CNRS/AIST
# Creation: 19/08/2010
# History:
#
# Copyright CNRS/AIST

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${PROJECT_INCLUDE_DIR})

add_executable(test_no_display test_no_display.cpp common.cpp common.h includes.h)
target_link_libraries(test_no_display sch-core ${Boost_LIBRARIES})
add_dependencies(test_no_display sch-core)
add_test(test_no_display ${CMAKE_CURRENT_BINARY_DIR}/test_no_display)

add_custom_command(TARGET test_no_display POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/unitTestings/sample_stpbv1.txt
  ${CMAKE_BINARY_DIR}/unitTestings/
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/unitTestings/sample_stpbv2.txt
  ${CMAKE_BINARY_DIR}/unitTestings/
)

