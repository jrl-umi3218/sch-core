# Mehdi Benallegue, JRL, CNRS/AIST
# Creation: 19/08/2010
# History:
#
# Copyright CNRS/AIST

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${PROJECT_INCLUDE_DIR})

function(add_example name)
  if(CMAKE_SYSTEM_PROCESSOR STREQUAL aarch64)
    return()
  endif()
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} sch-core)
  add_test(${name} ${name})
  if(${SCH_BUILD_BSD})
    target_compile_definitions(${name} PRIVATE "-DSCH_BUILD_BSD")
  endif()
endfunction()

add_example(example0)

