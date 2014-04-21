#include <sch/S_Polyhedron/S_Polyhedron.h>
#include <sch/STP-BV/STP_BV.h>

#define NBCORPS 29

std::string parts[NBCORPS] = {"body",
           "rleg0", "rleg1", "rleg2", "rleg3", "rleg4", "rleg5",
           "lleg0", "lleg1", "lleg2", "lleg3", "lleg4", "lleg5",
           "chest0", "chest1",
           "head0", "head1",
           "rarm0", "rarm1", "rarm2", "rarm3", "rarm4", "rarm5",
           "larm0", "larm1", "larm2", "larm3", "larm4", "larm5"};

using namespace sch;

int main()
{
  std::string aFile;
  for(int i = 0; i < NBCORPS; ++i)
  {
    STP_BV aSTPBV;
    aFile = "data/STPBV/"+parts[i]+".txt";
    aSTPBV.constructFromFile(aFile);
    aSTPBV.saveToBinary(aFile+".bin");

    S_Polyhedron aPolyhedron;
    aFile = "data/Polyedres/"+parts[i]+".otp";
    aPolyhedron.constructFromFile(aFile);
    aPolyhedron.saveToBinary(aFile+".bin");
  }
  return 0;
}
