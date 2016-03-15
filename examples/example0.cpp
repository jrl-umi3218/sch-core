/*
 * \file      example0.cpp
 * \author    Mehdi Benallegue
 * \date      2014
 * \brief     This file shows the normal use of the SCH library:
 *              The simplest proximity query
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
#include <limits>

/**********
 *The simplest proximity query
 */


//******************
// Includes for 3D objects

//Includes for standard objects
#include <sch/S_Object/S_Sphere.h>
#include <sch/S_Object/S_Box.h>
#include <sch/S_Object/S_Superellipsoid.h>

//*********************
//Includes for proximity queries

//Include file for proximity queries
#include <sch/CD/CD_Pair.h>

//Inlude file for the verification of the result
#include "example.hxx"

#ifdef ENABLE_SIGFPE
  #include <fenv.h>
#endif

using namespace sch;

int
main (int argc, char *argv[])
{
  #ifdef ENABLE_SIGFPE
  feenableexcept(FE_ALL_EXCEPT & ~FE_INEXACT);
  #endif

  //Set output precision
  std::cout.precision (std::numeric_limits<double>::digits10);
  std::cerr.precision (std::numeric_limits<double>::digits10);

  //***********
  //Object initializations

  // A box with height, width and depth
  S_Box box(0.2,0.1,0.4);

  //Set the position in the world reference frame
  box.setPosition(0.1,0.7,0.9);

  //Set the orientation of the Object
  //(many different orientations representations are supported, here Roll
  // pitch yaw)
  box.setOrientation(0.1,1,0.7);

  //A second object, a sphere with a radius
  S_Sphere sphere(0.3);

  //let's transform it into an ellipsoid
  //we add an anisotropic scale to the sphere
  // (the scale has to be the first operation as it affects also
  // rotations and translations)
  sphere.addScale(0.5,0.8,1.1);

  //Set the position in the world reference frame
  sphere.setPosition(0.1,-0.7,-0.9);

  //We turn it around the axis vrot defined by
  Vector3 vrot(0.2,0.4,0.5);
  vrot = vrot/vrot.norm();

  //let's turn it by 0.8 rad (we use addRotation instead of setRotation
  // to not loose the scale)
  sphere.addRotation(0.8,vrot);

  //********
  //Proximity queries

  //Create a proximity-query pair of objects. It takes the addresses of the
  //objects. The user is responsible of guaranteeing the existance of the
  //objects at these addresses during all the period of use of the pair and
  //desrtoying the objects at the end.
  //Note that STL containers (vectors, deque, etc.) do not guarantee that
  //objects remain at same address. Use them with care.
  CD_Pair pair1(&box, &sphere);

  //Are they in collision ?
  //This is the fastest proximity query as it runs GJK with the lowest
  // precision
  Scalar collision = pair1.isInCollision();

  //This runs GJK with 1e-6 precision.
  // WARNING : THE PROVIDED DISTANCE IS SQUARED for computation time
  // purpose, the real distance is then obtained by square root
  // this algorithm takes profit from the warm start provided by the
  // previous query, so there is virtually no additional cost at making
  // these two requests instead of directly the last one.
  // if there is a collision, this will compute the penetration depth
  Scalar d0 = sqrt(fabs(pair1.getDistance()));

  //Our witness points
  Point3 p1,p2;
  //get the Witness points without running GJK or depth computation again
  // (it detects that the object did not move since the last query, if
  // one or both moved, this query would trigger GJK algorithm).
  // this method returns the distance also.
  pair1.getClosestPoints(p1,p2);

  //Let's display all this stuff
  std::cout <<"First Query"<<std::endl;
  std::cout <<"Collision: " << (collision ? "True" : "False") <<std::endl;
  std::cout <<"Distance: "  << d0 <<std::endl;
  std::cout <<"Witness points: "  << std::endl;
  std::cout <<"P1: "<< p1 << std::endl;
  std::cout <<"P2: "<< p2 << std::endl;
  std::cout << std::endl;

  // compare the results for first query
  bool comparison = true;
  comparison = compare(d0, 1.75797057738, "First query, d0. ") && comparison;
  comparison = compare(p1, (Vector3(0.0292236259886, 0.601445137096, 0.705635281289)), "First query, p1. ") && comparison;
  comparison = compare(p2, (Vector3(0.0239874216807, -0.336387177086, -0.781275504057)), "First query, p2. ") && comparison;

  //Now we move the objects to enter in collision
  //We avoid symmetries to always get the same witness points.
  box.setPosition(0,0,0);
  sphere.setPosition(0.01,0,0);

  //Query again
  collision = pair1.isInCollision();

  //Let's run again the Distance computation, but not the penetration
  //depth, because the last algorithm is much slower, if there is a
  //collision, the output would be zero
  //
  Scalar d1 = sqrt(fabs(pair1.getDistanceWithoutPenetrationDepth()));

  //We call now the regular distance query (collision will trigger
  //depth query and the distance will be given in negative to distinguish
  // it from separating distance)
  Scalar d2 = sqrt(fabs(pair1.getDistance()));

  //Our witness points
  pair1.getClosestPoints(p1,p2);

  //Let's display all this stuff
  std::cout <<"Second Query"<<std::endl;
  std::cout <<"Collision: " << (collision ? "True" : "False") <<std::endl;
  std::cout <<"Distance: "  << d1 <<std::endl;
  std::cout <<"Depth: "  << d2 <<std::endl;
  std::cout <<"Witness points: "  << std::endl;
  std::cout <<"P1: "<< p1 << std::endl;
  std::cout <<"P2: "<< p2 << std::endl;
  std::cout << std::endl;

  // compare the results for second query
  comparison = compare(d1, 0., "Second query, d1. ") && comparison;
  comparison = compare(d2, 0.293744618861213, "Second query, d2. ") && comparison;
  comparison = compare(p1, (Vector3(0.0110146674327551, -0.0498945075944604, -0.0551780527427314)), "Second query, p1. ") && comparison;
  comparison = compare(p2, (Vector3(-0.158401731667896, 0.18954845401356, -0.0393334018450828)), "Second query, p2. ") && comparison;

  //******************
  //More objects

  //Create the third object
  // A superellipsoid with height, width, depth, epsilon1, epsilon2
  S_Superellipsoid super(0.1,0.9,0.3,0.5,0.8);

  //Position/Orientation
  super.setPosition(0.2,0.8,1);
  super.setOrientation(0.2,1.7,0.8);

  //Creation of new pairs related to the new objects. Each pair of 3D objects
  //is then a C++ objects
  CD_Pair pair2(&box, &super);
  CD_Pair pair3(&sphere, &super);

  //Our witness points
  Point3 p3,p4,p5,p6;

  //We can directly ask for the closest points
  //When the returned value is negative, it is the opposite of the squared
  //depth.
  d0 = pair1.getClosestPoints(p1,p2);
  d1 = pair2.getClosestPoints(p3,p4);
  d2 = pair3.getClosestPoints(p5,p6);

  // compare the results for third query
  comparison = compare(d0, -0.0862859011099191, "Third Query, d0") && comparison;
  comparison = compare(p1, (Vector3(0.0110146674327551, -0.0498945075944604, -0.0551780527427314)), "Third Query, p1") && comparison;
  comparison = compare(p2, (Vector3(-0.158401731667896, 0.18954845401356, -0.0393334018450828)), "Third Query, p2") && comparison;

  comparison = compare(d1,  0.659596933491, "Third Query, d1") && comparison;
  comparison = compare(p3, (Vector3(0.0707763740114, 0.0985548629043, 0.194364718711)), "Third Query, p3") && comparison;
  comparison = compare(p4, (Vector3(0.259412979986, 0.301096580075, 0.95790254828 )), "Third Query, p4") && comparison;

  comparison = compare(d2, 0.516365498703901, "Third Query, d2") && comparison;
  comparison = compare(p5, (sch::Vector3(0.126586144900461, 0.0390218116062935, 0.297048794226006)), "Third Query, p5") && comparison;
  comparison = compare(p6, (sch::Vector3(0.300323477842992, 0.23919818987692, 0.964963650647371)), "Third Query, p6") && comparison;


  //Let's display all this stuff
  std::cout <<"Third Query"<<std::endl;
  std::cout <<"Distance1 Squared: "  << d0 <<std::endl;
  std::cout <<"Witness points 1: "  << std::endl;
  std::cout <<"P1: "<< p1 << std::endl;
  std::cout <<"P2: "<< p2 << std::endl;
  std::cout <<"Distance2 Squared: "  << d1 <<std::endl;
  std::cout <<"Witness points 2: "  << std::endl;
  std::cout <<"P1: "<< p3 << std::endl;
  std::cout <<"P2: "<< p4 << std::endl;
  std::cout <<"Distance3 Squared: "  << d2 <<std::endl;
  std::cout <<"Witness points 3: "  << std::endl;
  std::cout <<"P1: "<< p5 << std::endl;
  std::cout <<"P2: "<< p6 << std::endl;
  std::cout << std::endl;

  return (comparison?0:1);
  //That's all folks
}

/* Standard output of this example:

First Query
Collision: False
Distance: 1.75797057738094
Witness points:
P1: 0.0292236259885692 0.601445137095698 0.705635281288737
P2: 0.0239874216806999 -0.336387177086141 -0.781275504057127

Second Query
Collision: True
Distance: 0
Depth: 0.293744618861213
Witness points:
P1: 0.0110146674327551 -0.0498945075944604 -0.0551780527427314
P2: -0.158401731667896 0.18954845401356 -0.0393334018450828

Third Query
Distance1 Squared: -0.0862859011099191
Witness points 1:
P1: 0.0110146674327551 -0.0498945075944604 -0.0551780527427314
P2: -0.158401731667896 0.18954845401356 -0.0393334018450828
Distance2 Squared: 0.659596933490814
Witness points 2:
P1: 0.0707763740114308 0.0985548629043023 0.194364718711263
P2: 0.259412979986433 0.301096580075066 0.957902548280017
Distance3 Squared: 0.516365498703901
Witness points 3:
P1: 0.126586144900461 0.0390218116062935 0.297048794226006
P2: 0.300323477842992 0.23919818987692 0.964963650647371
*/
