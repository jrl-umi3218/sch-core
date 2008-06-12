
#ifndef _CD_PAIR
#define _CD_PAIR

#pragma once


#include "../S_Object/S_Object.h"
#include "CD_Simplex.h"

class CD_Pair
{
public:
	CD_Pair(S_Object *Obj1, S_Object *Obj2);

	
	virtual ~CD_Pair(void);

	/*!
	 *\brief function that returns les distance SQUARED between two convex objects, 
	 *\param p1 is the witness point on the first object
	 *\param p2 is the witness point on the second object
	 */
	Scalar GetClosestPoints(Point3& p1,Point3& p2);
	Scalar ReComputeClosestPoints(Point3& p1,Point3& p2);
	
	/*!
	 *\brief function that returns les distance SQUARED between two convex objects, 
	 *\param p1 is the witness point on the first object
	 *\param p2 is the witness point on the second object
	 */
	Scalar GetDistance();


	void SetRelativePrecision(Scalar);

	void SetEpsilon(Scalar);


	S_Object * operator[](unsigned char i)
	{
		return (i==0)?sObj1:sObj2;
	}




private :
	S_Object* sObj1, * sObj2;
	Vector3 lastDirection;
	int lastFeature1,lastFeature2;

	Scalar GJK();
	void WitPoints(Point3& p1,Point3& p2);

	Point3 p1,p2;
	Scalar distance;

	Scalar precision_,epsilon_;
	
	S_Object::TimeStamp stamp1,stamp2;

	Scalar lambda0_,lambda1_,lambda2_;
	Scalar det;
	bool projectionComputed_;


	bool WitPointsAreComputed;

	CD_Simplex s1,s2,s;


	
	

};

#endif
