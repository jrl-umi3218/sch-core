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

