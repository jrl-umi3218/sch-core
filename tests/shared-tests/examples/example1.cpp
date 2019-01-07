/*
 * \file      example1.cpp
 * \author    Mehdi Benallegue
 * \date      2014
 * \brief     This file shows the normal use of the SCH library:
 *              Scene Management
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

//**********************
//Scene Management
//
//*********************

//******************
// Includes for 3D objects

// Includes for standard objects
#include <sch/S_Object/S_Sphere.h>
#include <sch/S_Object/S_Box.h>
#include <sch/S_Object/S_Superellipsoid.h>

//*********************
//Includes for proximity queries

//Include file for scene management
#include <sch/CD/CD_Scene.h>

//Inlude file for the verification of the result
#include "example.hxx"

using namespace sch;

bool verifyResult(const std::string & objI, const std::string & objJ,
                  double distance, double penetration,
                  const Point3 & p1, const Point3 & p2);

void Example::initializeUniverse()
{
  //Objects initializations
  S_Superellipsoid * super1 = new S_Superellipsoid (1.0,0.2,0.5,0.3,0.1);
  S_Superellipsoid * super2 = new S_Superellipsoid (0.1,0.9,0.3,0.5,0.8);
  S_Superellipsoid * super3 = new S_Superellipsoid (0.4,0.4,1.7,0.8,0.1);
  S_Box * box1 = new S_Box (0.2,0.1,0.4);
  S_Box * box2 = new S_Box (2.1,1.1,0.8);
  S_Box * box3 = new S_Box (1.4,4.1,1.2);
  S_Sphere * sphere1 = new S_Sphere (0.3);
  S_Sphere * sphere2 = new S_Sphere (0.5);
  S_Sphere * sphere3 = new S_Sphere (0.2);

  //Positions/Orientations
  super1->setPosition(1.0,0.2,0.5);
  super2->setPosition(-2.2,-1.1,1.3);
  super3->setPosition(0.4,0.4,-1.7);
  box1->setPosition(-0.2,0.1,-0.4);
  box2->setPosition(-2.1,-1.1,0.8);
  box3->setPosition(-2.0,-1.0,1.2);
  sphere1->setPosition(-2.1,1.1,0.8);
  sphere2->setPosition(2.1,1.1,-0.4);
  sphere3->setPosition(2.3,1.1,-0.5);

  super1-> setOrientation(-2.1,1.1,0.8);
  super2-> setOrientation(2.1,1.1,-0.4);
  super3-> setOrientation(2.1,1.1,-0.5);
  box1->   setOrientation(-0.2,0.1,-0.4);
  box2->   setOrientation(-2.1,-1.1,0.8);
  box3->   setOrientation(-2.0,-1.0,1.2);
  sphere1->setOrientation(1.0,0.2,0.5);
  sphere2->setOrientation(-2.2,-1.1,1.3);
  sphere3->setOrientation(0.4,0.4,-1.7);


  //This makes 36 pairs. We can use the scene manager to simplify pairs
  //allocation.

  //Scene manager
  // This is a minimal implementation of a scene manager. It stores
  // pointers and generates automatically collision detection pairs.
  // The library can be used without this scene manager.

  //Adding objects to the manager is simple As fo pairs, the scene does not
  //copy the objects and requires only addresses of the objects. The user
  //creates and destroys the objects separately.
  sObj.addObject(super1);
  sObj.addObject(super2);
  sObj.addObject(super3);
  sObj.addObject(box1);
  sObj.addObject(box2);
  sObj.addObject(box3);
  sObj.addObject(sphere1);
  sObj.addObject(sphere2);
  sObj.addObject(sphere3);

  objName.push_back("super1");
  objName.push_back("super2");
  objName.push_back("super3");
  objName.push_back("box1");
  objName.push_back("box2");
  objName.push_back("box3");
  objName.push_back("sphere1");
  objName.push_back("sphere2");
  objName.push_back("sphere3");
}

bool Example::unittest()
{
  //Calls the computation of the distance (including penertation and witness
  //points) for all the scene, it returns the number of collisions.
  //Other implementations of the scene management could be considered for
  //future versions.
  int collisionNbr = sObj.sceneProximityQuery();


  std::cout<<"The scene" << std::endl;
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

      //Our witness points
      Point3 p1,p2;

      //Get the SQUARED distance and witness points of the last proximity
      //query (see example0.cpp for details on output interpretation)
      //Warning: this does not recompute the distance, even if one object
      //moved after the scene proximity query.
      double distance = sObj.getWitnessPoints(i,j,p1,p2);


      std::cout << "Distance " << distance << i <<std::endl;
      std::cout <<"Witness points: "  << std::endl;
      std::cout <<"  P1: "<< p1 << std::endl;
      std::cout <<"  P2: "<< p2 << std::endl;

      //We can get access to the pairs of objects. This will recompute the
      //distance if the objects moved. See example0 for details on how to
      //use the pair object.
      CD_Pair * ptr = sObj(i,j);
      std::cout <<"The distance without penetration "
                << ptr->getDistanceWithoutPenetrationDepth() << std::endl;

      comparison = verifyResult(objName[i], objName[j], distance,
                                ptr->getDistanceWithoutPenetrationDepth(), p1, p2)
                   && comparison;
      std::cout << std::endl;
    }
  }

  return comparison;
}

void Example::displayScene()
{
  //Calls the computation of the distance (including penertation and witness
  //points) for all the scene, it returns the number of collisions.
  //Other implementations of the scene management could be considered for
  //future versions.
  int collisionNbr = sObj.sceneProximityQuery();

  for (unsigned i=0; i<sObj.size(); ++i)
  {
    for (unsigned j=0; j<i; ++j)
    {
      //Our witness points
      Point3 p1,p2;

      //Get the SQUARED distance and witness points of the last proximity
      //query (see example0.cpp for details on output interpretation)
      //Warning: this does not recompute the distance, even if one object
      //moved after the scene proximity query.
      sObj.getWitnessPoints(i,j,p1,p2);

      //We can get access to the pairs of objects. This will recompute the
      //distance if the objects moved. See example0 for details on how to
      //use the pair object.
      CD_Pair * ptr = sObj(i,j);
      ptr->getDistanceWithoutPenetrationDepth();
    }
  }
}


bool verifyResult(const std::string & objI, const std::string & objJ,
                  double distance, double penetration,
                  const Point3 & p1, const Point3 & p2)
{
  std::cerr.precision(14);

  double dd(0);
  double pd(0);
  Point3 dp1(0, 0, 0);
  Point3 dp2(0, 0, 0);

  if(objJ == "super1" && objI == "super2")
  {
    dd = 5.4487471575136;
    pd = 5.4487471575136;
    dp1.Set(0.28175284289769, -0.14299067182235, 1.1716656444909);
    dp2.Set(-1.7636106455221, -1.2250286690872, 1.4789588761567);
  }
  else if(objJ == "super1" && objI == "super3")
  {
    dd = 0.30421039852355;
    pd = 0.30421039852355;
    dp1.Set(0.96363716178523, 0.46511130288262, -0.52236418422971);
    dp2.Set(0.98382992853513, 0.57131577169444, -1.0632183803851);
  }
  else if(objJ == "super2" && objI == "super3")
  {
    dd = 9.9181149823984;
    pd = 9.9181149823984;
    dp1.Set(-2.2982641001418, -0.53893477159955, 1.0585206046519);
    dp2.Set(-0.63840167210456, -0.44938462670065, -1.6163536865882);
  }
  else if(objJ == "super1" && objI == "box1")
  {
    dd = 0.55758708510798;
    pd = 0.55758708510798;
    dp1.Set(0.61084807024591, 0.29440863418974, 0.069803781161034);
    dp2.Set(-0.056687617849561, 0.13575086229484, -0.22483311680702);
  }
  else if(objJ == "super2" && objI == "box1")
  {
    dd = 5.9443143905268;
    pd = 5.9443143905268;
    dp1.Set(-2.1732498476818, -0.63004749575528, 1.1490992568704);
    dp2.Set(-0.27631829569933, 0.12220296114932, -0.18509875231225);
  }
  else if(objJ == "super3" && objI == "box1")
  {
    dd = 0.51584655618165;
    pd = 0.51584655618165;
    dp1.Set(0.12785132793314, 0.015765330308717, -1.2847741886342);
    dp2.Set(-0.12368170430067, 0.077797038850676, -0.61490124768775);
  }
  else if(objJ == "super1" && objI == "box2")
  {
    dd = 2.78972586142;
    pd = 2.78972586142;
    dp1.Set(0.27677566692662, -0.13314609360976, 1.1658328403376);
    dp2.Set(-1.2995880118717, -0.57154615294118, 1.5014051895616);
  }
  else if(objJ == "super2" && objI == "box2")
  {
    dd = -0.31718567003746;
    pd = 0;
    dp1.Set(-1.787265308154, -1.1960497354292, 1.4450521781144);
    dp2.Set(-2.2686354608106, -1.3706878827971, 1.6795089196526);
  }
  else if(objJ == "super3" && objI == "box2")
  {
    dd = 3.440763819841;
    pd = 3.440763819841;
    dp1.Set(-0.83748878593566, -0.54621539306324, -1.7742688055859);
    dp2.Set(-2.060158969655, -0.96192382874358, -0.44271785342942);
  }
  else if(objJ == "box1" && objI == "box2")
  {
    dd = 3.1102603339576;
    pd = 3.1102603339576;
    dp1.Set(-0.27631829569933, 0.12220296114932, -0.18509875231225);
    dp2.Set(-1.6979671687682, -0.58899718550305, 0.57868732183491);
  }
  else if(objJ == "super1" && objI == "box3")
  {
    dd = 0.14762346168417;
    pd = 0.14762346168417;
    dp1.Set(0.29961124339566, 0.014926401743127, 0.97819026233414);
    dp2.Set(-0.067084392233482, 0.11181124267447, 0.91678097889576);
  }
  else if(objJ == "super2" && objI == "box3")
  {
    dd = -0.88486848336054;
    pd = 0;
    dp1.Set(-1.8258028062901, -1.2035457346373, 1.5672994449862);
    dp2.Set(-2.0099706249296, -1.6772532880947, 0.77574916121672);
  }
  else if(objJ == "super3" && objI == "box3")
  {
    dd = 1.2943618702035;
    pd = 1.2943618702035;
    dp1.Set(-0.2536866871953, -0.23957739656524, -1.4216076267573);
    dp2.Set(-0.65088388966599, -0.31132657081448, -0.35791203658708);
  }
  else if(objJ == "box1" && objI == "box3")
  {
    dd = 0.16648542041871;
    pd = 0.16648542041871;
    dp1.Set(-0.27631829569933, 0.12220296114932, -0.18509875231225);
    dp2.Set(-0.54770561715496, -0.10725192694837, 0.015362706576795);
  }
  else if(objJ == "box2" && objI == "box3")
  {
    dd = -1.7306786763394;
    pd = 0;
    dp1.Set(-1.1518981590561, -1.0179317129611, 1.6120145906702);
    dp2.Set(-2.0999010779384, -0.15510256812534, 1.3162190380463);
  }
  else if(objJ == "super1" && objI == "sphere1")
  {
    dd = 5.3186326388713;
    pd = 5.3186326388713;
    dp1.Set(0.3354800425203, 0.22033997371372, 1.0949514789063);
    dp2.Set(-1.8196178883092, 0.99878520299519, 0.83378376954228);
  }
  else if(objJ == "super2" && objI == "sphere1")
  {
    dd = 1.4183711535435;
    pd = 1.4183711535435;
    dp1.Set(-2.4779023328493, -0.32669997190278, 1.0113296028496);
    dp2.Set(-2.1762353652203, 0.8129674455965, 0.84243208458626);
  }
  else if(objJ == "super3" && objI == "sphere1")
  {
    dd = 7.4743489107843;
    pd = 7.4743489107843;
    dp1.Set(-0.53702693775031, 0.31921777729824, -1.6803624586656);
    dp2.Set(-1.9453484492689, 1.0228264075222, 0.55479174774896);
  }
  else if(objJ == "box1" && objI == "sphere1")
  {
    dd = 3.9663117059915;
    pd = 3.9663117059915;
    dp1.Set(-0.26442597555482, 0.15199775567757, -0.19156797444484);
    dp2.Set(-1.8596364794099, 0.9758575176791, 0.6703312348231);
  }
  else if(objJ == "box2" && objI == "sphere1")
  {
    dd = 1.7772851599536;
    pd = 1.7772851599536;
    dp1.Set(-1.6006569697181, -0.40929377232158, 1.1739828310352);
    dp2.Set(-2.0082863828167, 0.82274676021845, 0.86869682135086);
  }
  else if(objJ == "box3" && objI == "sphere1")
  {
    dd = 0.40873492947483;
    pd = 0.40873492947483;
    dp1.Set(-1.4233798793513, 0.48324374143217, 1.0100607143038);
    dp2.Set(-1.883840797678, 0.90317898477367, 0.86735450011444);
  }
  else if(objJ == "super1" && objI == "sphere2")
  {
    dd = 0.039104898627535;
    pd = 0.039104898627535;
    dp1.Set(1.6781720909763, 0.57648753892597, -0.21331741131897);
    dp2.Set(1.7976914901379, 0.7248905617555, -0.26619987217934);
  }
  else if(objJ == "super2" && objI == "sphere2")
  {
    dd = 18.906059441351;
    pd = 18.906059441351;
    dp1.Set(-2.0166352552171, -0.84324192220842, 1.2677212945354);
    dp2.Set(1.6754467644156, 0.89957633685848, -0.22799736802078);
  }
  else if(objJ == "super3" && objI == "sphere2")
  {
    dd = 0.096550440397139;
    pd = 0.096550440397139;
    dp1.Set(1.6697745078346, 1.1266310160472, -1.0866387839319);
    dp2.Set(1.8346899699717, 1.116376050407, -0.82348832046098);
  }
  else if(objJ == "box1" && objI == "sphere2")
  {
    dd = 3.4928506703209;
    pd = 3.4928506703209;
    dp1.Set(-0.056687617849561, 0.13575086229484, -0.22483311680702);
    dp2.Set(1.6443705367279, 0.89739891750289, -0.3631951963815);
  }
  else if(objJ == "box2" && objI == "sphere2")
  {
    dd = 13.535796551098;
    pd = 13.535796551098;
    dp1.Set(-1.4206285779347, -0.3034386790228, 1.3608007525762);
    dp2.Set(1.679309305274, 0.93099892363515, -0.18914940032874);
  }
  else if(objJ == "box3" && objI == "sphere2")
  {
    dd = 4.9068928394991;
    pd = 4.9068928394991;
    dp1.Set(-0.10352367186681, 0.018083890456479, 0.76016554875608);
    dp2.Set(1.6940746685943, 0.90096107279478, -0.18643939882083);
  }
  else if(objJ == "sphere1" && objI == "sphere2")
  {
    dd = 12.731096153983;
    pd = 12.731096153983;
    dp1.Set(-1.8114862908327, 1.1, 0.71778175614537);
    dp2.Set(1.6191438180545, 1.1, -0.26296959357561);
  }
  else if(objJ == "super1" && objI == "sphere3")
  {
    dd = 0.43645502641181;
    pd = 0.43645502641181;
    dp1.Set(1.6912459612619, 0.567053610651, -0.20657129901502);
    dp2.Set(2.158681625653, 0.97605586976899, -0.43168477729525);
  }
  else if(objJ == "super2" && objI == "sphere3")
  {
    dd = 23.550195655262;
    pd = 23.550195655262;
    dp1.Set(-1.9924580739264, -0.87944172212693, 1.2854835093993);
    dp2.Set(2.1300977188898, 1.0216519471083, -0.42932617426062);
  }
  else if(objJ == "super3" && objI == "sphere3")
  {
    dd = 0.42972022695158;
    pd = 0.42972022695158;
    dp1.Set(1.7058063536863, 1.1636066171891, -1.112225860713);
    dp2.Set(2.1610693162235, 1.1148044581997, -0.64310518202643);
  }
  else if(objJ == "box1" && objI == "sphere3")
  {
    dd = 5.5750152536297;
    pd = 5.5750152536297;
    dp1.Set(-0.056687617849561, 0.13575086229484, -0.22483311680702);
    dp2.Set(2.1157485332466, 1.0251955369043, -0.47865311966162);
  }
  else if(objJ == "box2" && objI == "sphere3")
  {
    dd = 17.558511336885;
    pd = 17.558511336885;
    dp1.Set(-1.4288100961977, -0.31186268568159, 1.3377283222371);
    dp2.Set(2.130156805579, 1.0356334715405, -0.41627282805178);
  }
  else if(objJ == "box3" && objI == "sphere3")
  {
    dd = 7.4049800506603;
    pd = 7.4049800506603;
    dp1.Set(-0.11233115341526, -0.0045702874952087, 0.72231113656579);
    dp2.Set(2.1346488277106, 1.0246599452678, -0.41643648386935);
  }
  else if(objJ == "sphere1" && objI == "sphere3")
  {
    dd = 16.711972710807;
    pd = 16.711972710807;
    dp1.Set(-1.8123385444469, 1.1, 0.71484785975054);
    dp2.Set(2.1082256962979, 1.1, -0.44323190650036);
  }
  else if(objJ == "sphere2" && objI == "sphere3")
  {
    dd = -0.22676975704217;
    pd = 0;
    dp1.Set(2.5376620746762, 1.098724063024, -0.64109671750724);
    dp2.Set(2.1249351701295, 1.1005103747904, -0.40356131299711);
  }

  bool res = true;
#ifdef WIN32
  double epsilon = 1e-10;
#else
  double epsilon = 1e-12;
#endif
  res = compare(distance, dd, "distance ("+objI +", "+objJ+"): ", epsilon) && res;
  res = compare(penetration, pd, "penetration ("+objI +", "+objJ+"): ", epsilon) && res;
  res = compare(p1, dp1, "p1 ("+objI +", "+objJ+"): ", epsilon) && res;
  res = compare(p2, dp2, "p2 ("+objI +", "+objJ+"): ", epsilon) && res;
  return res;
}

/*Standard output of this example:

The scene
Number of objects: 9
Number of pairs: 36
Object 0 type:5
Object 1 type:5
Object 2 type:5
Object 3 type:4
Object 4 type:4
Object 5 type:4
Object 6 type:3
Object 7 type:3
Object 8 type:3

Number of collisions: 4
The pair 0 - 1
Distance 5.448751
Witness points:
  P1: 0.281753 -0.142991 1.17167
  P2: -1.76361 -1.22503 1.47896
The distance without penetration 5.44875

The pair 0 - 2
Distance 0.304212
Witness points:
  P1: 0.963637 0.465111 -0.522364
  P2: 0.98383 0.571316 -1.06322
The distance without penetration 0.30421

The pair 1 - 2
Distance 9.918112
Witness points:
  P1: -2.29826 -0.538935 1.05852
  P2: -0.638402 -0.449385 -1.61635
The distance without penetration 9.91811

The pair 0 - 3
Distance 0.5575873
Witness points:
  P1: 0.610848 0.294409 0.0698038
  P2: -0.0566876 0.135751 -0.224833
The distance without penetration 0.557587

The pair 1 - 3
Distance 5.944313
Witness points:
  P1: -2.17325 -0.630047 1.1491
  P2: -0.276318 0.122203 -0.185099
The distance without penetration 5.94431

The pair 2 - 3
Distance 0.5158473
Witness points:
  P1: 0.127851 0.0157653 -1.28477
  P2: -0.123682 0.077797 -0.614901
The distance without penetration 0.515847

The pair 0 - 4
Distance 2.789734
Witness points:
  P1: 0.276776 -0.133146 1.16583
  P2: -1.29959 -0.571546 1.50141
The distance without penetration 2.78973

The pair 1 - 4
Distance -0.3171864
Witness points:
  P1: -1.78726 -1.19605 1.44505
  P2: -2.26864 -1.37069 1.67951
The distance without penetration 0

The pair 2 - 4
Distance 3.440764
Witness points:
  P1: -0.837489 -0.546215 -1.77427
  P2: -2.06016 -0.961924 -0.442718
The distance without penetration 3.44076

The pair 3 - 4
Distance 3.110264
Witness points:
  P1: -0.276318 0.122203 -0.185099
  P2: -1.69797 -0.588997 0.578687
The distance without penetration 3.11026

The pair 0 - 5
Distance 0.1476235
Witness points:
  P1: 0.299611 0.0149264 0.97819
  P2: -0.0670844 0.111811 0.916781
The distance without penetration 0.147623

The pair 1 - 5
Distance -0.8848685
Witness points:
  P1: -1.8258 -1.20355 1.5673
  P2: -2.00997 -1.67725 0.775749
The distance without penetration 0

The pair 2 - 5
Distance 1.294365
Witness points:
  P1: -0.253687 -0.239577 -1.42161
  P2: -0.650884 -0.311327 -0.357912
The distance without penetration 1.29436

The pair 3 - 5
Distance 0.1664855
Witness points:
  P1: -0.276318 0.122203 -0.185099
  P2: -0.547706 -0.107252 0.0153627
The distance without penetration 0.166485

The pair 4 - 5
Distance -1.730685
Witness points:
  P1: -1.1519 -1.01793 1.61201
  P2: -2.0999 -0.155103 1.31622
The distance without penetration 0

The pair 0 - 6
Distance 5.318636
Witness points:
  P1: 0.33548 0.22034 1.09495
  P2: -1.81962 0.998785 0.833784
The distance without penetration 5.31863

The pair 1 - 6
Distance 1.418376
Witness points:
  P1: -2.4779 -0.3267 1.01133
  P2: -2.17624 0.812967 0.842432
The distance without penetration 1.41837

The pair 2 - 6
Distance 7.474356
Witness points:
  P1: -0.537027 0.319218 -1.68036
  P2: -1.94535 1.02283 0.554792
The distance without penetration 7.47435

The pair 3 - 6
Distance 3.966316
Witness points:
  P1: -0.264426 0.151998 -0.191568
  P2: -1.85964 0.975858 0.670331
The distance without penetration 3.96631

The pair 4 - 6
Distance 1.777296
Witness points:
  P1: -1.60066 -0.409294 1.17398
  P2: -2.00829 0.822747 0.868697
The distance without penetration 1.77729

The pair 5 - 6
Distance 0.4087356
Witness points:
  P1: -1.42338 0.483244 1.01006
  P2: -1.88384 0.903179 0.867355
The distance without penetration 0.408735

The pair 0 - 7
Distance 0.03910497
Witness points:
  P1: 1.67817 0.576488 -0.213317
  P2: 1.79769 0.724891 -0.2662
The distance without penetration 0.0391049

The pair 1 - 7
Distance 18.90617
Witness points:
  P1: -2.01664 -0.843242 1.26772
  P2: 1.67545 0.899576 -0.227997
The distance without penetration 18.9061

The pair 2 - 7
Distance 0.09655047
Witness points:
  P1: 1.66977 1.12663 -1.08664
  P2: 1.83469 1.11638 -0.823488
The distance without penetration 0.0965504

The pair 3 - 7
Distance 3.492857
Witness points:
  P1: -0.0566876 0.135751 -0.224833
  P2: 1.64437 0.897399 -0.363195
The distance without penetration 3.49285

The pair 4 - 7
Distance 13.53587
Witness points:
  P1: -1.42063 -0.303439 1.3608
  P2: 1.67931 0.930999 -0.189149
The distance without penetration 13.5358

The pair 5 - 7
Distance 4.906897
Witness points:
  P1: -0.103524 0.0180839 0.760166
  P2: 1.69407 0.900961 -0.186439
The distance without penetration 4.90689

The pair 6 - 7
Distance 12.73117
Witness points:
  P1: -1.81149 1.1 0.717782
  P2: 1.61914 1.1 -0.26297
The distance without penetration 12.7311

The pair 0 - 8
Distance 0.4364558
Witness points:
  P1: 1.69125 0.567054 -0.206571
  P2: 2.15868 0.976056 -0.431685
The distance without penetration 0.436455

The pair 1 - 8
Distance 23.55028
Witness points:
  P1: -1.99246 -0.879442 1.28548
  P2: 2.1301 1.02165 -0.429326
The distance without penetration 23.5502

The pair 2 - 8
Distance 0.429728
Witness points:
  P1: 1.70581 1.16361 -1.11223
  P2: 2.16107 1.1148 -0.643105
The distance without penetration 0.42972

The pair 3 - 8
Distance 5.575028
Witness points:
  P1: -0.0566876 0.135751 -0.224833
  P2: 2.11575 1.0252 -0.478653
The distance without penetration 5.57502

The pair 4 - 8
Distance 17.55858
Witness points:
  P1: -1.42881 -0.311863 1.33773
  P2: 2.13016 1.03563 -0.416273
The distance without penetration 17.5585

The pair 5 - 8
Distance 7.404988
Witness points:
  P1: -0.112331 -0.00457029 0.722311
  P2: 2.13465 1.02466 -0.416436
The distance without penetration 7.40498

The pair 6 - 8
Distance 16.7128
Witness points:
  P1: -1.81234 1.1 0.714848
  P2: 2.10823 1.1 -0.443232
The distance without penetration 16.712

The pair 7 - 8
Distance -0.2267578
Witness points:
  P1: 2.54716 1.10524 -0.623309
  P2: 2.12114 1.09791 -0.410677
The distance without penetration 0
*/
