#include "common.h"

using namespace sch;

TestMaterial universe;

void display(){}

/*
* main - this is the main programme.
*/
int main ()
{
	universe.initializeUniverse();

//	universe.CurrentObj=(universe.CurrentObj+1)%universe.sObj.size();
//	universe.CurrentObj=(universe.CurrentObj-1)%universe.sObj.size();
	universe.TestAnimation();
	universe.TestPrecision();
	universe.GeneralTest();
	universe.RandomTestSupportFunction();
	universe.RandomTestSupportFunctionAllObjects();

	return 0;
}


