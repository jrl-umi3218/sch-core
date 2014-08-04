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

using namespace sch;

int
main (int argc, char *argv[])
{
  //Scene (see example1.exe)
  CD_Scene sObj;

  //**********
  //Polyhedrons

  //Create a polyhedron.
  S_Polyhedron poly;

  //At creationm the polyhedron is empty, it has to be loaded from a file.
  poly.constructFromFile("sample_polyhedron.otp");

  //The file must have been generated with sch-creator, for details see
  //https://github.com/jrl-umi3218/sch-creator

  //An elternative solution is to use qconvex software from Qhull using the
  //following instruction:
  //"qconvex.exe TI <input_filename> TO <output_filename> Qt o f"
  //see http://www.qhull.org/html/qconvex.htm for details on using qconvex.

  //Position/Orientation
  poly.setPosition(0.1,0.7,0.9);
  poly.setOrientation(0.1,1,-0.7);

  //Add to scene
  sObj.addObject(&poly);

  //*********
  //Strictly Convex Hull (STP-BV)
  //(see README.md for details)

  //Create a STP_BVs
  STP_BV stp1;
  STP_BV stp2;

  //Similarly to polyhedrons, it has to be loaded from file
  stp1.constructFromFile("sample_stpbv1.txt");
  stp2.constructFromFile("sample_stpbv2.txt");


  //Position/Orientation
  stp1.setPosition(0.15,0.6,0.8);
  stp1.setOrientation(0.4,-1.1,1.2);

  //Position/Orientation
  stp2.setPosition(0.4,0.0,0.1);
  stp2.setOrientation(0.7,-0.2,-1.1);

  //Add to scene
  sObj.addObject(&stp1);
  sObj.addObject(&stp2);


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
      std::cout << std::endl;
    }
  }
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
