#ifndef COMMON_TEST_H
#define COMMON_TEST_H

#define NON_STP_BV_OBJECTS
//#define DISPLAY_DISTANCE
#define DO_TEST
//#define OUTPUT_FILE
//#define LINES_DISPLAY

//#define MULTI_OBJECTS_TEST
//#define TEST_HOLD
//#define COLLISION_COUNTERS
//#define IRREGULARITIES_COUNTERS

#include <sch/S_Object/S_Sphere.h>
#include <sch/S_Object/S_Box.h>
#include <sch/S_Object/S_Superellipsoid.h>
#include <sch/STP-BV/STP_BV.h>
#include <sch/CD/CD_Pair.h>
#include <sch/CD/CD_Scene.h>
#include <sch/S_Polyhedron/S_Polyhedron.h>
#include <sch/STP-BV/STP_BV_P.h>

//#include "includes.h"

void display (void);

struct Example
{
  Example(): CurrentObj(0){}

  void initializeUniverse();
  void displayScene();
  bool unittest();

  sch::CD_Scene sObj;

  unsigned int CurrentObj;

private:
  // a simple vector containing the names of the object to make display of
  // error easier
  std::vector<std::string> objName;
};

#endif //COMMON_TEST_H
