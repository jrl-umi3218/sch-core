# Francois Keith, JRL, CNRS/AIST
# Creation: 19/08/2010
# History:
#
# Copyright CNRS/AIST

#### examples
macro(add_example name)
  add_executable(${name} shared-tests/examples/${name}.cpp example_test.cpp)
  target_link_libraries(${name} sch-core)
  add_test(${name} ${name})
  if(${SCH_BUILD_BSD})
    target_compile_definitions(${name} PRIVATE "-DSCH_BUILD_BSD")
  endif()
  # Adding a project configuration file (for MSVC only)
  generate_msvc_dot_user_file(${name})
endmacro(add_example)

if(NOT APPLE)
  add_example(example1)
endif()
add_example(example2)

#tests
macro(addUnitTest name)
  add_executable(${name} ${name}.cpp shared-tests/tests/common.cpp shared-tests/tests/common.h shared-tests/tests/includes.h)
  target_link_libraries(${name} sch-core)
  add_test(${name} ${CMAKE_CURRENT_BINARY_DIR}/${name})
  # Adding a project configuration file (for MSVC only)
  GENERATE_MSVC_DOT_USER_FILE(${name})
endmacro(addUnitTest)

addUnitTest(test_animation)
addUnitTest(test_precision)
addUnitTest(test_general)
addUnitTest(test_random)
addUnitTest(test_stp_bv_performance)

#### Data
set(DATA_FOLDER ${CMAKE_SOURCE_DIR}/tests/shared-tests/data/)
add_custom_command(TARGET test_animation POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${DATA_FOLDER}/sample_stpbv1.txt
  ${CMAKE_BINARY_DIR}/tests/
  COMMAND ${CMAKE_COMMAND} -E copy ${DATA_FOLDER}/sample_stpbv2.txt
  ${CMAKE_BINARY_DIR}/tests/
  COMMAND ${CMAKE_COMMAND} -E copy ${DATA_FOLDER}/sample_stp_p.txt
  ${CMAKE_BINARY_DIR}/tests/
  COMMAND ${CMAKE_COMMAND} -E copy ${DATA_FOLDER}/sample_polyhedron.otp
  ${CMAKE_BINARY_DIR}/tests/
)


