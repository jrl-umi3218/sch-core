#ifndef _CD_SIMPLEX_ENHANCED_H
#define _CD_SIMPLEX_ENHANCED_H

#pragma once
#include <SCD/scd_api.h>
#include <SCD/CD/CD_Simplex.h>

namespace SCD
{
	class CD_SimplexEnhanced :
		public CD_Simplex
	{
	public:
		SCD_API CD_SimplexEnhanced(const Point3& p);
		SCD_API CD_SimplexEnhanced(const Point3& p1,const Point3& p2);
		SCD_API CD_SimplexEnhanced(const Point3& p1,const Point3& p2,const Point3& p3);
		SCD_API CD_SimplexEnhanced(const Point3& p1,const Point3& p2,const Point3& p3,const Point3& p4);

		SCD_API CD_SimplexEnhanced(const Point3& p, Scalar norm );
		SCD_API CD_SimplexEnhanced(const Point3& p1,const Point3& p2, Scalar norm1, Scalar norm2);
		SCD_API CD_SimplexEnhanced(const Point3& p1,const Point3& p2,const Point3& p3, Scalar norm1, Scalar norm2, Scalar norm3);
		SCD_API CD_SimplexEnhanced(const Point3& p1,const Point3& p2,const Point3& p3,const Point3& p4, Scalar norm1, Scalar norm2, Scalar norm3, Scalar norm4);



		SCD_API virtual ~CD_SimplexEnhanced(void);


		/*! 
		* \brief Updates the simplex by supressing some vertexes and/or change their order according to a filter
		* \param k is the filter used to know wich vertexes will be kept and in wich order
		* \updateVetors must be called after this function to keep the vectors up to date.
		*/
		SCD_API virtual void filter(const CD_SimplexKeptPoints &k);

		/*
		* \brief returns the distances of the simplex points to the origin
		*/
		SCD_API Scalar norms(const char i)const;

		/*
		* \brief returns the distances of the simplex points to the origin
		*/
		SCD_API Scalar& norms(const char i);



		using CD_Simplex::operator [];


		SCD_API CD_SimplexEnhanced& operator =(const CD_SimplexEnhanced&);

		/*! 
		* \brief Adds a point to a simplex to transform it in a higher dimemsion simplex (doesn't work with tetrahedron) 
		* \updateVetors must be called after this operator to keep the vectors up to date.
		*/
		SCD_API CD_SimplexEnhanced& operator+=(const Point3&);


		/*! 
		* \brief Adds a point to a simplex to transform it in a higher dimemsion simplex (doesn't work with tetrahedron) 
		* \updateVetors must be called after this operator to keep the vectors up to date.
		*/
		SCD_API CD_SimplexEnhanced operator+(const Point3&)const;


		/*!
		* \brief gives the distance squared between the origin and the furthest simplex vertices
		*/
		SCD_API Scalar farthestPointDistance()const;

		/*!
		* \brief optimized version of GetClosestSubSimplex((0,0,0),v) for GJK (the highest index point is the last inserted in the GJK algorithm) 
		*		to make it work, updateVectors must be called before.
		*/
		SCD_API void getClosestSubSimplexGJK(CD_SimplexKeptPoints &k)const;

		
		/*!
		* \brief Tells if the simplex is affinely dependant or not according to the static variable zero 
		*		to make it work, updateVectors must be called before.
		*/
		SCD_API bool isAffinelyDependent() const;


	protected:
		Scalar norm1_,norm2_,norm3_,norm4_;

	private:
		static Scalar square_(const Scalar& a);
		static Scalar cube_(const Scalar& a);





	};


#include "CD_SimplexEnhanced.hxx"
}
#endif
