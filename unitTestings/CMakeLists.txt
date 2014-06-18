# Francois Keith, JRL, CNRS/AIST
# Creation: 19/08/2010
# History:
#
# Copyright CNRS/AIST

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${PROJECT_INCLUDE_DIR})

macro(addUnitTest name)
  add_executable(${name} ${name}.cpp common.cpp common.h includes.h)
  target_link_libraries(${name} sch-core ${Boost_LIBRARIES})
  add_dependencies(${name} sch-core)
  add_test(${name} ${CMAKE_CURRENT_BINARY_DIR}/${name})
endmacro(addUnitTest)

addUnitTest(test_no_display)
addUnitTest(test_random)

add_custom_command(TARGET test_no_display POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/unitTestings/sample_stpbv1.txt
  ${CMAKE_BINARY_DIR}/unitTestings/
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/unitTestings/sample_stpbv2.txt
  ${CMAKE_BINARY_DIR}/unitTestings/
)

