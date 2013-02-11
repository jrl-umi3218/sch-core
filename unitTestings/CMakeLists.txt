# Francois Keith, JRL, CNRS/AIST
# Creation: 19/08/2010
# History:
#
# Copyright CNRS/AIST

INCLUDE(CTest)

# For the test, we include the same files as the src
# SET(${PROJECT_NAME}_test_CXXFLAGS "-I${PROJECT_SOURCE_DIR}/include/ ${${PROJECT_NAME}_CXXFLAGS}")

if(GLUT_FOUND)
include_directories(${Boost_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${PROJECT_INCLUDE_DIR})
ADD_EXECUTABLE(	Test1 Test1.cpp includes.h)
target_link_libraries(Test1 ${GLUT_LIBRARIES} ${Boost_LIBRARIES} scd)

ADD_DEPENDENCIES(Test1 scd)
ADD_TEST(Test1 Test1)
endif(GLUT_FOUND)
