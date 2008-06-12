
#ifndef _CD_SIMPLEX
#define _CD_SIMPLEX

#pragma once


#define __ZERO 0

#include "../matrix/SCD_Types.h"


/*!
 * tells which points ware kept from the previous smplex
 */
struct CD_SimplexKeptPoints
{
	char b1,b2,b3,b4;

	inline CD_SimplexKeptPoints()
	{
		b1=b2=b3=b4=-1;
	}

	inline char & operator[]( unsigned char i)
	{
		return ((i==0) ? b1: (i==1)? b2: (i==2) ? b3 : b4);
	}

	inline const char & operator[]( unsigned char i) const
	{
		return ((i==0) ? b1: (i==1)? b2: (i==2) ? b3 : b4);
	}

	void Reset()
	{
		b1=b2=b3=b4=-1;
	}



};

class CD_Simplex
{
public:
	CD_Simplex(const Point3& p);
	CD_Simplex(const Point3& p1,const Point3& p2);
	CD_Simplex(const Point3& p1,const Point3& p2,const Point3& p3);
	CD_Simplex(const Point3& p1,const Point3& p2,const Point3& p3,const Point3& p4);


	virtual ~CD_Simplex();

	
	
	enum Type 
	{
		point,
		segment,
		triangle,
		tetrahedron
	};

	Type getType()const;
	

	


	Point3& operator[]( unsigned char);
	

	const Point3& operator[]( unsigned char) const;
	

	CD_Simplex& operator=(const CD_Simplex& s);
	
	CD_Simplex& operator=(const Point3& p);


	
	bool operator==(const CD_Simplex& s);

	bool operator!=(const CD_Simplex& s);



	/*! 
	 * \brief Adds a point to a simplex to transform it in a higher dimemsion simplex (doesn't work with tetrahedron) 
	 */
	CD_Simplex& operator+=(const Point3& p);
	


	CD_Simplex operator+(const Point3& p)const;


	void Filter(const CD_SimplexKeptPoints &);

	/*!
	 *\brief Gives the distance squared at the origin for a simplex, and according the direction v.
	 */
	Scalar SquareDistanceAtOrigin(const Vector3 &v)const;
	


	/*! 
	 * \brief Gets the closest subsimplex from the simplex to the point p 
	 * \param p Point p
	 * \param v Vector retuned telling the direction between p and the closest point in the simplex
	 */
	CD_Simplex GetClosestSubSimplex(const Point3& p,Vector3& v)const;

	/*!
	 * \brief optimized version of GetClosestSubSimplex((0,0,0),v) for GJK (the highest index point is the last inserted in the GJK algorithm) 
	 *		to make it work, updateVectors must be called before.
	 */
	CD_Simplex GetClosestSubSimplexGJK(CD_SimplexKeptPoints &k)const;
	
	/*!
	 * \brief Tells if the simplex is affinely dependant or not according to the static variable zero 
	 *		to make it work, updateVectors must be called before.
	 */
	bool IsAffinelyDependent() const;
	
	/*!
	 * \brief Updates AB,AC,AD vectors A is the last vertex inserted and B, C and D are previous vertex 
	 */
	void updateVectors();

	const Vector3& AB () const;
	const Vector3& AC () const;
	const Vector3& AD () const;

	private :
	

	Type type;

	Point3 S1,S2,S3,S4;
	Vector3 ab_,ac_,ad_;



	static const Scalar zero;
	static const Scalar zero2;
	static const Scalar zero3;
	static const Scalar zero4;

};

#include "CD_Simplex.hxx"
#endif

