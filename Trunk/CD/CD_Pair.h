
#ifndef _CD_PAIR
#define _CD_PAIR

#pragma once


#include "../S_Object/S_Object.h"
#include "CD_SimplexEnhanced.h"
#include "../CD_Penetration/CD_Depth.h"

namespace SCD
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
		CD_Pair(S_Object *Obj1, S_Object *Obj2);


		virtual ~CD_Pair(void);

		/*!
		*\brief function that returns les distance SQUARED between two convex objects, and computes the witness points, the distance is set to negative if interpentration
		*\param p1 is the witness point on the first object
		*\param p2 is the witness point on the second object
		*/
		Scalar getClosestPoints(Point3& p1,Point3& p2);

		/*!
		*\brief function that returns les distance SQUARED between two convex objects, restarting the computations from the beginning and computes the witness points, the distance is set to negative if interpentration
		*\param p1 is the witness point on the first object
		*\param p2 is the witness point on the second object
		*/
		Scalar reComputeClosestPoints(Point3& p1,Point3& p2);

		/*!
		*\brief function that returns les distance SQUARED between two convex objects, the distance is set to negative if interpentration
		*/
		Scalar getDistance();


		/*!
		*\brief function that returns les distance SQUARED between two convex objects, no interpenetration depth computations done the distance is set to zero in this case
		*/
		Scalar getDistanceWithoutPenetrationDepth();

		/*
		* brief returns if there is collision or not. If the distance is not already computed, it does not recompute, just returns the result.
		*/

		bool isInCollision();

		/*!
		*\brief Intializes the direction vector (the vector between expected closest points) with a given value.
		*/
		void setVector(const Vector3 &);

		/*!
		*\brief sets the relative precision of the proximity queries to a given value. The effective precision is precision^2 . Default is precision=1e-3.
		*/
		void setRelativePrecision(Scalar precision);

		/*
		*\brief Sets the machine epsilon. Default is 1e-24
		*/
		void setEpsilon(Scalar);

		/*
		*\brief returns a pointer to the ith object in the pair
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
		Scalar penetrationDepth();
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

		bool computePenetration;

		CD_Simplex s1_,s2_,s_;

		CD_SimplexEnhanced sp_;



		CD_Depth depthPair;





	};
}
#endif
