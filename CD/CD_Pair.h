
#ifndef _CD_PAIR
#define _CD_PAIR

#pragma once


#include "../S_Object/S_Object.h"
#include "CD_Simplex.h"
#include "../CD_Penetration/CD_Depth.h"

class CD_Pair
{
public:
	CD_Pair(S_Object *Obj1, S_Object *Obj2);

	
	virtual ~CD_Pair(void);

	/*!
	 *\brief function that returns les distance SQUARED between two convex objects, and computes the witness points, 
	 *\param p1 is the witness point on the first object
	 *\param p2 is the witness point on the second object
	 */
	Scalar getClosestPoints(Point3& p1,Point3& p2);
	
	/*!
	 *\brief function that returns les distance SQUARED between two convex objects, retarting the computations from the beginning and computes the witness points,
	 *\param p1 is the witness point on the first object
	 *\param p2 is the witness point on the second object
	 */
	Scalar reComputeClosestPoints(Point3& p1,Point3& p2);
	
	/*!
	 *\brief function that returns les distance SQUARED between two convex objects, 
	 */
	Scalar getDistance();

	/*!
	 *\brief Intializes the direction vector (the vector between expected closest points) with a given value.
	 */
	void setVector(const Vector3 &);

	/*!
	 *\brief sets the relative precision of the proximity queries to a given value. Default is 1e-3
	 */
	void setRelativePrecision(Scalar);

	/*
	 *\brief Sets the machine epsilon. Default is 1e-24
	 */
	void setEpsilon(Scalar);

	/*
	 *\brief returns the ith object in the scene
	 */

	S_Object * operator[](unsigned char i)
	{
		return (i==0)?sObj1_:sObj2_;
	}




private :
	S_Object* sObj1_, * sObj2_;
	Vector3 lastDirection_;
	int lastFeature1_,lastFeature2_;

	Scalar GJK();
	void witPoints(Point3& p1,Point3& p2);

	Point3 p1_,p2_;
	Scalar distance_;

	Scalar precision_,epsilon_;
	
	S_ObjectTimeStamp stamp1_,stamp2_;

	Scalar lambda0_,lambda1_,lambda2_;
	Scalar det_;

	bool projectionComputed_;

	bool collision_;

	bool witPointsAreComputed_;

	CD_Simplex s1_,s2_,s_;

	CD_Depth depthPair;


	
	

};

#endif
