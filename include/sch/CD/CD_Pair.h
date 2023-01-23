#ifndef _CD_PAIR
#define _CD_PAIR

#pragma once

#include <sch/sch_api.h>
#include <sch/S_Object/S_Object.h>
#include <sch/CD/CD_SimplexEnhanced.h>
#include <sch/CD_Penetration/CD_Depth.h>

namespace sch
{

  class CD_Pair
  {
  public:

    /*!
    *\brief constructor
    *\IMPORTANT: to create a CD::Pair, two CD::S_Objects must have been created before, these objects moust not be destroyed before this instance
    *\param Obj1 is a pointer to the first object
    *\param Obj1 is a pointer to the second object
    */
    SCH_API CD_Pair(S_Object *Obj1, S_Object *Obj2);


    SCH_API virtual ~CD_Pair(void);

    /*!
    *\brief function that returns the distance SQUARED between two convex objects, and computes the witness points, the distance is set to negative if interpentration
    *\details The witness points are on the surface of the objects with opposite normals. If there is a collision and the penetration depth computation is deactivated 
    * then the witness points will only reflect the last step of the distance computation algorithm. Otherwise the witness points are points each on the surface of the other,
    *  having opposite normals and being the closest each to the other. In any case the returned distance should be used to obtain the distance.
    *\param p1 is the witness point on the first object
    *\param p2 is the witness point on the second object
    *\return the distance squared (set to negative when there is penetration)
    */
    SCH_API Scalar getClosestPoints(Point3 &p1, Point3 &p2);

    /*!
    *\brief function that returns the distance SQUARED between two convex objects, restarting the computations from the beginning and computes the witness points, the distance is set to negative if interpentration
    *\param p1 is the witness point on the first object
    *\param p2 is the witness point on the second object
    */
    SCH_API Scalar reComputeClosestPoints(Point3& p1,Point3& p2);

    /*!
    *\brief function that returns the distance SQUARED between two convex objects, the distance is set to negative if interpentration
    */
    SCH_API Scalar getDistance();


    /*!
    *\brief function that returns the distance SQUARED between two convex objects, no interpenetration depth computations done the distance is set to zero in this case
    */
    SCH_API Scalar getDistanceWithoutPenetrationDepth();

    /*!
    * \brief returns if there is collision or not. If the distance is not already computed, it does not recompute, just returns the result.
    */

    SCH_API bool isInCollision();

    /*!
    *\brief Intializes the direction vector (the vector between expected closest points) with a given value.
    */
    SCH_API void setVector(const Vector3 &);

    /*!
     *\brief Gets the last direction vector (can be used to get a normal vector, especially when the distance is zero).
     * This vector is likely NOT normalized
     */
    SCH_API const Vector3 & getVector() const;

    /*!
    *\brief sets the relative precision of the proximity queries to a given value. The effective precision is precision^2 . Default is precision=1e-3.
    */
    SCH_API void setRelativePrecision(Scalar precision);

    /*!
    *\brief Sets the machine epsilon. Default is 1e-24
    */
    SCH_API void setEpsilon(Scalar);

    /*!
    *\brief returns a pointer to the ith object in the pair
    */

    SCH_API S_Object * operator[](unsigned char i)
    {
      return (i==0)?sObj1_:sObj2_;
    }

  protected :
    S_Object* sObj1_, * sObj2_;
    Vector3 lastDirection_;
    int lastFeature1_,lastFeature2_;

    Scalar GJK();
    Scalar penetrationDepth();

    Point3 p1_,p2_;
    Scalar distance_;


    S_ObjectTimeStamp stamp1_,stamp2_;

    Scalar precision_,epsilon_;

    Scalar lambda0_,lambda1_,lambda2_;
    Scalar det_;

    bool projectionComputed_;

    bool collision_;

    bool witPointsAreComputed_;

    CD_Simplex s1_,s2_,s_;

    CD_SimplexEnhanced sp_;

    void witPoints(Point3& p1,Point3& p2);

    CD_Depth depthPair;
  };
}


/**
 * \example      example0.cpp
 * This example shows the normal use of the SCH library:
 * The simplest proximity queries
 */

/**
* \example      example1.cpp
* This example shows the normal use of the SCH library:
* Scene managements
*/

#endif
