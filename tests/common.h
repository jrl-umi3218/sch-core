#ifndef COMMON_TEST_H
#define COMMON_TEST_H

//#define NON_STP_BV_OBJECTS
//#define DISPLAY_DISTANCE
#define DO_TEST
//#define OUTPUT_FILE
//#define LINES_DISPLAY

//#define MULTI_OBJECTS_TEST
//#define TEST_HOLD
//#define COLLISION_COUNTERS
//#define IRREGULARITIES_COUNTERS


#include "includes.h"

void display (void);

struct TestMaterial
{
  TestMaterial(bool nonSTPBV)
    : sObj()
    , CurrentObj(0)
    , stppObjects()
  {
      nonSTPBV_=nonSTPBV;
  }

  void DoTest();

  void RandomTestSupportFunction();

  void RandomTestSupportFunctionAllObjects();

  void initializeUniverse();
  void initializeUniverse(const std::vector<std::string> & filenamelist);

  void TestPrecision();

  void TestAnimation();

  void GeneralTest();

  sch::CD_Scene sObj;

  unsigned int CurrentObj;



private:
  std::vector<sch::STP_BV_P> stppObjects;
  bool nonSTPBV_;
};

#endif //COMMON_TEST_H
