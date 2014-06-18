#ifndef COMMON_TEST_H
#define COMMON_TEST_H

#define NON_STP_BV_OBJECTS
//#define DISPLAY_DISTANCE
#define DO_TEST
//#define LINES_DISPLAY

//#define MULTI_OBJECTS_TEST
//#define TEST_HOLD
//#define COLLISION_COUNTERS
//#define IRREGULARITIES_COUNTERS


#include "includes.h"

void display (void);

struct TestMaterial
{
  ~TestMaterial();

  void DoTest();

  void RandomTestSupportFunction();

  void RandomTestSupportFunctionAllObjects();

  void initializeUniverse();

  void TestPrecision();

  void TestAnimation();

  void GeneralTest();

  sch::CD_Scene sObj;

  unsigned int CurrentObj;

private:
  std::vector<sch::S_Object*> objectVector;
  std::vector<sch::STP_BV*> stpObjects;
  std::vector<sch::STP_BV_P> stppObjects;
  std::vector<sch::S_Polyhedron> polyObjects;
};

#endif //COMMON_TEST_H
