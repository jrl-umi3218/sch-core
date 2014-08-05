# Mehdi Benallegue, JRL, CNRS/AIST
# Creation: 19/08/2010
# History:
#
# Copyright CNRS/AIST

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${PROJECT_INCLUDE_DIR})

macro(add_example name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} sch-core ${Boost_LIBRARIES})
  add_dependencies(${name} sch-core)
  add_test(${name} ${name})

endmacro(add_example)

add_example(example0)
add_example(example1)
add_example(example2)

add_custom_command(TARGET example2 POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/examples/sample_stpbv1.txt
  ${CMAKE_BINARY_DIR}/examples/
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/examples/sample_stpbv2.txt
  ${CMAKE_BINARY_DIR}/examples/
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/examples/sample_polyhedron.otp
  ${CMAKE_BINARY_DIR}/examples/
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/examples/sample_stp_p.txt
  ${CMAKE_BINARY_DIR}/examples/
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/examples/sample_stp_p.txt.otp
  ${CMAKE_BINARY_DIR}/examples/
)

