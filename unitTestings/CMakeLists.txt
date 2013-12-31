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

ADD_EXECUTABLE(	test_no_display test_no_display.cpp common.cpp common.h includes.h)
target_link_libraries(test_no_display scd  ${Boost_LIBRARIES})
ADD_DEPENDENCIES(test_no_display scd)
# ADD_TEST(Test1 Test1)


if(GLUT_FOUND)
include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${PROJECT_INCLUDE_DIR})
ADD_EXECUTABLE(	Test1 Test1.cpp common.cpp common.h includes.h)
target_link_libraries(Test1 ${GLUT_LIBRARIES} scd  ${Boost_LIBRARIES})

ADD_DEPENDENCIES(Test1 scd)
endif(GLUT_FOUND)
