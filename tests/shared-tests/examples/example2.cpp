/*
 * \file      example1.cpp
 * \author    Mehdi Benallegue
 * \date      2014
 * \brief     This file shows the normal use of the SCH library:
 *              More complex objects
 *
 *            sch-core is an Efficient implementation of GJK algorithm for
 *            proximity queries (collision detection, distance computations,
 *            penetration depths and withness points) between convex shapes.
 *            The library can be extended to any convex shape for which we
 *            can compute the support function, but it already supports
 *            polyhedrons, boxes, spheres and ellipsoids, and it is
 *            particularly optimized for strictly convex hulls (SCH/STP-BV).
 *
 *
 */

#include <string>
#include "example_common.h"

#include <iostream>
#include <math.h>

/*******************
 *More complex objects
 */


//******************
//Includes for complex objects

//Include file for convex polyhedrons
#include <sch/S_Polyhedron/S_Polyhedron.h>

//Include file for STP-BVs (strictly convex hulls)
#include <sch/STP-BV/STP_BV.h>

//Include file for STP-BV with underlying polyhedron
#include <sch/STP-BV/STP_BV_P.h>


//*********************
//Includes for proximity queries

//Include file for scene management
#include <sch/CD/CD_Scene.h>

//Inlude file for the verification of the result
#include "example.hxx"

using namespace sch;

/*!
 * \brief verifyResult checks if the distance computation is the same as the
 *  one expected
 * \param i, first object
 * \param j, second object
 * \param distance, the computed distance
 * \param p1, the first witness point
 * \param p2, the second witness point
 * \return the result of the comparison
 */
bool verifyResult(const std::string & objI, const std::string & objJ,
                  double distance,
                  const Point3 & p1, const Point3 & p2);

void display (void);

void Example::initializeUniverse()
{
  //Scene (see example1.exe)

  //**********
  //Polyhedrons

  //Create a polyhedron.
  S_Polyhedron * poly = new S_Polyhedron ();

  //At creationm the polyhedron is empty, it has to be loaded from a file.
  poly->constructFromFile("sample_polyhedron.otp");

  //The file must have been generated with sch-creator, for details see
  //https://github.com/jrl-umi3218/sch-creator

  //An elternative solution is to use qconvex software from Qhull using the
  //following instruction:
  //"qconvex.exe TI <input_filename> TO <output_filename> Qt o f"
  //see http://www.qhull.org/html/qconvex.htm for details on using qconvex.

  //Position/Orientation
  poly->setPosition(0.1,0.7,0.9);
  poly->setOrientation(0.1,1,-0.7);

  //Add to scene
  sObj.addObject(poly);
  objName.push_back("poly");

  //*********
  //Strictly Convex Hull (STP-BV)
  //(see README.md for details)

  //Create a STP_BVs
  STP_BV* stp1 = new STP_BV();
  STP_BV* stp2 = new STP_BV();

  //Similarly to polyhedrons, it has to be loaded from file
  stp1->constructFromFile("sample_stpbv1.txt");
  stp2->constructFromFile("sample_stpbv2.txt");


  //Position/Orientation
  stp1->setPosition(0.15,0.6,0.8);
  stp1->setOrientation(0.4,-1.1,1.2);

  //Position/Orientation
  stp2->setPosition(0.4,0.0,0.1);
  stp2->setOrientation(0.7,-0.2,-1.1);

  //Add to scene
  sObj.addObject(stp1);
  sObj.addObject(stp2);
  objName.push_back("stp1");
  objName.push_back("stp2");
}

bool Example::unittest()
{
  //Scene proximity query (see example1.cpp)
  int collisionNbr = sObj.sceneProximityQuery();

  std::cout<<"Complex objects" << std::endl;
  std::cout<<"Number of objects: " << sObj.size() << std::endl;
  std::cout<<"Number of pairs: " << sObj.size()*(sObj.size()-1)/2<< std::endl;

  for (unsigned i=0; i<sObj.size(); ++i)
  {
    //We can also get back our object pointers
    S_Object * ptr = sObj[i];
    std::cout <<"Object "<<i<<" type:"<< ptr->getType() << std::endl;
  }

  std::cout<< std::endl<<"Number of collisions: "<< collisionNbr << std::endl;

  bool comparison = true;
  for (unsigned i=0; i<sObj.size(); ++i)
  {
    for (unsigned j=0; j<i; ++j)
    {
      std::cout << "The pair " << j <<" - "<< i <<std::endl;

      Point3 p1,p2;

      double distance = sObj.getWitnessPoints(i,j,p1,p2);


      std::cout << "Distance " << distance << i <<std::endl;
      std::cout <<"Witness points: "  << std::endl;
      std::cout <<"  P1: "<< p1 << std::endl;
      std::cout <<"  P2: "<< p2 << std::endl;
      // check the results
      if(!verifyResult(objName[i], objName[j], distance, p1, p2))
        comparison = false;
      std::cout << std::endl;
    }
  }

  return comparison;
}

void Example::displayScene()
{
  sObj.sceneProximityQuery();
  display();
}


bool verifyResult(const std::string & objI, const std::string & objJ,
                  double distance,
                  const Point3 & p1, const Point3 & p2)
{
  double dd(0);
  Point3 dp1(0, 0, 0);
  Point3 dp2(0, 0, 0);

  if(objJ== "poly" && objI == "stp1")
  {
    dd = -0.003622207057881;
    dp1.Set( 0.157367547718, 0.68942718023, 0.891961713557);
    dp2.Set(0.0986621048016, 0.691217002621, 0.905102283015);
  }
  else if(objJ == "poly" && objI == "stp2")
  {
    dd = 1.052877530262;
    dp1.Set(0.113009188603, 0.657740931859, 0.866412634224);
    dp2.Set(0.404379849329, 0.0191152898235, 0.117988985704);
  }
  else if(objJ == "stp1" && objI == "stp2")
  {
    dd = 0.7165631886362;
    dp1.Set(0.167062414197, 0.581943658784, 0.704052592159);
    dp2.Set(0.404383200422, 0.0191578029975, 0.117951821311);
  }

  bool res = true;
  res = compare(distance, dd, "distance ("+objI +", "+objJ+"): ") && res;
  res = compare(p1, dp1, "p1 ("+objI +", "+objJ+"): ") && res;
  res = compare(p2, dp2, "p2 ("+objI +", "+objJ+"): ") && res;
  return res;
}

/* Standard output of this example:

Complex objects
Number of objects: 3
Number of pairs: 3
Object 0 type:1
Object 1 type:2
Object 2 type:2

Number of collisions: 1
The pair 0 - 1
Distance -0.003622211
Witness points:
  P1: 0.157368 0.689427 0.891962
  P2: 0.0986621 0.691217 0.905102

The pair 0 - 2
Distance 1.052882
Witness points:
  P1: 0.113009 0.657741 0.866413
  P2: 0.40438 0.0191153 0.117989

The pair 1 - 2
Distance 0.7165632
Witness points:
  P1: 0.167062 0.581944 0.704053
  P2: 0.404383 0.0191578 0.117952

*/
