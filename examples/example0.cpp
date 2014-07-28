/**
 * \file      example0.hpp
 * \author    Mehdi Benallegue
 * \date      2014
 * \brief     This file shows the normal use of the SCH library.
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
#include <vector>

///******************
/// Includes for 3D objects

/// Includes for standard objects
#include <sch/S_Object/S_Sphere.h>
#include <sch/S_Object/S_Box.h>
#include <sch/S_Object/S_Superellipsoid.h>

///Include file for convex polyhedrons
#include <sch/S_Polyhedron/S_Polyhedron.h>

///Include file for STP-BVs (strictly convex hulls)
#include <sch/STP-BV/STP_BV.h>

///Include file for STP-BV with underlying polyhedron
#include <sch/STP-BV/STP_BV_P.h>



///*********************
///Includes for proximity queries

///Include file for proximity queries
#include <sch/CD/CD_Pair.h>

///Include file for scene management
#include <sch/CD/CD_Scene.h>

#include <math.h>


using namespace sch;

/*
* main - this is the main programme.
*/
int
main (int argc, char *argv[])
{

    {
        ///**********
        ///The simplest proximity query

        ///Objects initializations

        /// A box with height, width and depth
        S_Box box(0.2,0.1,0.4);

        ///Set the position in the world reference frame
        box.setPosition(0.1,0.7,0.9);

        ///Set the orientation of the Object
        ///(many different orientations representations are supported, here Roll
        /// pitch yaw)
        box.setOrientation(0.1,1,0.7);

        ///A second object, a sphere with a radius
        S_Sphere sphere(0.3);

         ///Set the position in the world reference frame
        sphere.setPosition(0.1,0.7,0.9);

        ///let's transform it into an ellipsoid
        ///we add an anisotropic scale to the sphere
        sphere.addScale(0.5,0.8,1.1);

        ///We turn it around the axis vrot defined by
        Vector3 vrot(0.2,0.4,0.5);
        vrot = vrot/vrot.norm();

        ///let's turn it by 0.8 radian
        sphere.addRotation(0.8,vrot);


    }

    ///Container for the solid 3D objects.
///  -we use pointers instead of objects directly because the vector container
/// does not guarantee that the objects keep addresses when pushing or pulling
/// new values. This vector is not mandatory for using the library, but the user
/// is responsible of creating objects, guaranteeing that the objects keep same
/// addresses and detroying them. The library only requires pointers on these
/// objects.
std::vector<S_Object *> objectVector;


///Scene manager
/// This is a minimal implementation of a scene manager. It stores pointers and
/// generates automatically collision detection pairs. The library can be used
/// without this scene manager.
sch::CD_Scene sObj;



  objectVector.push_back(new S_Box(0.2,0.2,0.2));
  objectVector.push_back(new S_Box(0.2,0.2,0.2));
  objectVector.push_back(new S_Sphere(0.1));
  objectVector.push_back(new S_Sphere(0.12));
  objectVector.push_back(new S_Superellipsoid(.25,.30,.30,0.9,0.2));
  objectVector.push_back(new S_Superellipsoid(.11,.30,.14,0.4,0.8));



  for(unsigned i=0; i<objectVector.size(); ++i)
    sObj.addObject(objectVector[i]);



#ifdef MULTI_OBJECTS_TEST
  {
    bool b=true;
    int i=0;
    do
    {
      std::string s;
      s="";
      std::stringstream istr;
      istr<<std::string("C:/Mehdi/nuage_points/simplifies/testspace/jobj(")<<i<<").txt";


      getline(istr,s);
      std::fstream testfile;
      testfile.open(s.c_str());

      if (testfile.is_open())
      {
        b=true;
        testfile.close();

        //STP_BV stp;
        STP_BV_P stp;
        stp.constructFromFileWithGL(s.c_str());

        stppObjects.push_back(stp);
        //  stpObjects.push_back(stp);
      }
      else
        b=false;

      i++;

      //if (i==8) b=false;


    }
    while(b);

    for (int j=0; j<stppObjects.size(); j++)
    {
      sObj.addObject(&(stppObjects[j]));
    }
  }
#else
  {
    STP_BV* s1 = new STP_BV();
    s1->constructFromFileWithGL("sample_stpbv1.txt");
    stpObjects.push_back(s1);
    sObj.addObject(s1);

    STP_BV* s2 = new STP_BV();
    s2->constructFromFileWithGL("sample_stpbv2.txt");
    stpObjects.push_back(s2);
    sObj.addObject(s2);
  }
#endif
  for (size_t i=0; i<sObj.size(); i++)
  {
    Vector3 position(
      (1.+7*i%5-3.),
      (5*i%6-3.)*(5.0/6.),
      (5*i%7-3.)*(5.0/7.)
    );
    position *= DispersionScale;
    sObj[i]->setPosition(position);
  }

  DoTest();

}
