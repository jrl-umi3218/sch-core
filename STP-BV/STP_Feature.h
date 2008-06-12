



#ifndef _STP_FEATURE
#define _STP_FEATURE

#pragma once


#include "../matrix/scd_types.h"
#include <vector>

typedef struct s_STP_VVR
{
	s_STP_VVR();
	s_STP_VVR(Scalar cosangle, const Vector3& axis);
	s_STP_VVR(const s_STP_VVR& vvr);

	bool isInside(const Vector3& v) const;

	double isInsidePrime(const Vector3& v) const;

	double isInsidePlane(const Vector3& v) const;

	float getDistance(const Vector3& v) const;

	bool isSameLimit(const s_STP_VVR& vvr) const;

	s_STP_VVR& operator=(const s_STP_VVR& vvr);
	bool operator==(const s_STP_VVR& vvr) const;
	
	Vector3 m_axis;
	Scalar m_cosangle;
	int m_outerSTP;
	int m_displayList;
} STP_VVR;


/*! \struct s_STN_STBVData
 *  \brief
 *  \author Cochet-Grasset Amelie
 *  \date    october 2007
 *
 *  
 */
typedef struct s_STN_VVR
{
	s_STN_VVR();
	s_STN_VVR(Scalar cosangle, const Vector3& axis);
	s_STN_VVR(const s_STN_VVR& vvr);

	bool isInside(const Vector3& v) const;
	Scalar getDistance(const Vector3& v) const;

	bool isSameLimit(const s_STN_VVR& vvr) const;

	s_STN_VVR& operator=(const s_STN_VVR& vvr);
	bool operator==(const s_STN_VVR& vvr) const;
	
	Vector3 m_axis;
	Scalar m_cosangle;
	int m_outerSTP;
	int m_displayList;
} STN_VVR;


/*! \struct s_STP_STBVData
 *  \brief
 *  \author Cochet-Grasset Amelie
 *  \date    august 2007
 *
 *  
 */
typedef struct s_STP_STBVData
{
	std::vector<Point3> m_points;
	std::vector<STN_VVR> m_VVRlimits;
	std::vector<bool> m_reverse;
	int m_BVID;
} STP_STBVData;



enum STP_Featuretype
{
	SMALLSPHERE,
	BIGSPHERE,
	TORUS
};


class STP_Feature
{
public:
	
	virtual ~STP_Feature(void);

	void setDisplayList(int l) {m_displayList = l;}

	virtual void print() const = 0;
	virtual void GLdisplay() const;
	virtual void GLdisplayVVR() const = 0;

	virtual STP_Feature* clone() const =0;

	virtual Point3 support(const Vector3& v) const=0;

	virtual bool isHere(const Vector3& v) const = 0;
	virtual bool isHereFarthestNeighbour(const Vector3& v) = 0;
	virtual bool isHereFarthestNeighbourPrime(const Vector3& v) = 0;
	virtual bool isHereFirstNeighbour(const Vector3& v) = 0;
	virtual bool isHereFirstNeighbourPrime(const Vector3& v,int idp) = 0;
	virtual int getNextBV(unsigned int id) const= 0;
	virtual int getNextBVPrime() const=0 ;

protected:
	STP_Feature(void);

protected:
	int m_displayList;
	int m_nextBVPrime;


};


#endif