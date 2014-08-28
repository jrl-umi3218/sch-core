#include "common.h"
#include <sstream>
#include <fstream>


// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace sch;

void display() {}

/*
* main - this is the main programme.
*/
int main ()
{
  TestMaterial universe;
  std::vector<sch::STP_BV*> stpObjects;
//  objectVector.push_back(new S_Box(0.2,0.2,0.2));
//  objectVector.push_back(new S_Sphere(0.1));
//  objectVector.push_back(new S_Superellipsoid(.25,.30,.30,0.9,0.2));

  STP_BV* s1 = new STP_BV();
  s1->constructFromFileWithGL("sample_stpbv1.txt");
  stpObjects.push_back(s1);

  STP_BV* s2 = new STP_BV();
  s2->constructFromFileWithGL("sample_stpbv2.txt");
  stpObjects.push_back(s2);

  /*
    for (unsigned i=0; i<universe.objectVector.size(); ++i)
    {
      std::ofstream
      // save data to archive
      {
          boost::archive::text_oarchive oa(ofs);
          // write class instance to archive
          oa << g;
      	// archive and stream closed when destructors are called
      }

      universe.objectVector[i].save();
    }
  */
  for (unsigned i=0; i<stpObjects.size(); ++i)
  {
    std::ostringstream oss;
    oss << "/tmp/stpbv_" << i << ".txt";
    std::ofstream ofs(oss.str().c_str());
    boost::archive::text_oarchive oa(ofs);
    oa << stpObjects[i];
  }

//  for (unsigned i=0; i<universe.stppObjects.size(); ++i)
//    universe.stppObjects[i].save();

//  for (unsigned i=0; i<universe.polyObjects.size(); ++i)
//    universe.polyObjects[i].save();

  return 0;
}


