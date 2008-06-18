#ifndef CD_SIMPLEX_ENHANCED_H
#define CD_SIMPLEX_ENHANCED_H

#pragma once
#include "cd_simplex.h"

class CD_SimplexEnhanced :
	public CD_Simplex
{
public:
	CD_SimplexEnhanced(const Point3& p);
	CD_SimplexEnhanced(const Point3& p1,const Point3& p2);
	CD_SimplexEnhanced(const Point3& p1,const Point3& p2,const Point3& p3);
	CD_SimplexEnhanced(const Point3& p1,const Point3& p2,const Point3& p3,const Point3& p4);

	CD_SimplexEnhanced(const Point3& p, Scalar norm );
	CD_SimplexEnhanced(const Point3& p1,const Point3& p2, Scalar norm1, Scalar norm2);
	CD_SimplexEnhanced(const Point3& p1,const Point3& p2,const Point3& p3, Scalar norm1, Scalar norm2, Scalar norm3);
	CD_SimplexEnhanced(const Point3& p1,const Point3& p2,const Point3& p3,const Point3& p4, Scalar norm1, Scalar norm2, Scalar norm3, Scalar norm4);



	virtual ~CD_SimplexEnhanced(void);

	CD_SimplexEnhanced& operator =(const CD_SimplexEnhanced&);

	/*! 
	 * \brief Adds a point to a simplex to transform it in a higher dimemsion simplex (doesn't work with tetrahedron) 
	 * \updateVetors must be called after this operator to keep the vectors up to date.
	 */
	CD_SimplexEnhanced& operator+=(const Point3&);
	

	/*! 
	 * \brief Adds a point to a simplex to transform it in a higher dimemsion simplex (doesn't work with tetrahedron) 
	 * \updateVetors must be called after this operator to keep the vectors up to date.
	 */
	CD_SimplexEnhanced operator+(const Point3&)const;


	/*!
	 * \brief gives the distance squared between the origin and the furthest simplex vertices
	 */
	Scalar farthestPointDistance()const;

	/*!
	 * \brief optimized version of GetClosestSubSimplex((0,0,0),v) for GJK (the highest index point is the last inserted in the GJK algorithm) 
	 *		to make it work, updateVectors must be called before.
	 */
	CD_SimplexEnhanced GetClosestSubSimplexGJK(CD_SimplexKeptPoints &k)const;
	

protected:
	Scalar norm1_,norm2_,norm3_,norm4_;

};


#include "CD_SimplexEnhanced.hxx"

#endif