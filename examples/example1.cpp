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

using namespace sch;

int
main (int argc, char *argv[])
{
    //Objects initializations
    S_Superellipsoid super1(1.0,0.2,0.5,0.3,0.1);
    S_Superellipsoid super2(0.1,0.9,0.3,0.5,0.8);
    S_Superellipsoid super3(0.4,0.4,1.7,0.8,0.1);
    S_Box box1(0.2,0.1,0.4);
    S_Box box2(2.1,1.1,0.8);
    S_Box box3(1.4,4.1,1.2);
    S_Sphere sphere1(0.3);
    S_Sphere sphere2(0.5);
    S_Sphere sphere3(0.2);

    //Positions/Orientations
    super1.setPosition(1.0,0.2,0.5);
    super2.setPosition(-2.2,-1.1,1.3);
    super3.setPosition(0.4,0.4,-1.7);
    box1.setPosition(-0.2,0.1,-0.4);
    box2.setPosition(-2.1,-1.1,0.8);
    box3.setPosition(-2.0,-1.0,1.2);
    sphere1.setPosition(-2.1,1.1,0.8);
    sphere2.setPosition(2.1,1.1,-0.4);
    sphere3.setPosition(2.3,1.1,-0.5);

    super1. setOrientation(-2.1,1.1,0.8);
    super2. setOrientation(2.1,1.1,-0.4);
    super3. setOrientation(2.1,1.1,-0.5);
    box1.   setOrientation(-0.2,0.1,-0.4);
    box2.   setOrientation(-2.1,-1.1,0.8);
    box3.   setOrientation(-2.0,-1.0,1.2);
    sphere1.setOrientation(1.0,0.2,0.5);
    sphere2.setOrientation(-2.2,-1.1,1.3);
    sphere3.setOrientation(0.4,0.4,-1.7);


    //This makes 36 pairs. We can use the scene manager to simplify pairs
    //allocation.

    //Scene manager
    // This is a minimal implementation of a scene manager. It stores
    // pointers and generates automatically collision detection pairs.
    // The library can be used without this scene manager.
    sch::CD_Scene sObj;

    //Adding objects to the manager is simple As fo pairs, the scene does not
    //copy the objects and requires only addresses of the objects. The user
    //creates and destroys the objects separately.
    sObj.addObject(&super1);
    sObj.addObject(&super2);
    sObj.addObject(&super3);
    sObj.addObject(&box1);
    sObj.addObject(&box2);
    sObj.addObject(&box3);
    sObj.addObject(&sphere1);
    sObj.addObject(&sphere2);
    sObj.addObject(&sphere3);


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

            std::cout << std::endl;
        }

    }


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
