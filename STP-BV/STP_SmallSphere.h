#ifndef _STP_SMALLSPHERE
#define _STP_SMALLSPHERE

#pragma once
#include "stp_feature.h"
#include <vector>

/*!  \class STP_SmallSphere
  *  \brief 
  *  \author Cochet-Grasset Amelie
  *  \date    july 2007
  *
  *  
  */

class STP_SmallSphere :
	public STP_Feature
{
public:
	STP_SmallSphere(Scalar radius, Point3 center);
	STP_SmallSphere(const STP_SmallSphere& s);



	~STP_SmallSphere();

	STP_SmallSphere & operator =(const STP_SmallSphere &s);

	const Point3& getCenter();
	void setVVR(const std::vector<STP_VVR>& vvr);

	virtual void print() const;
	virtual void GLdisplay() const;
	void GLdisplayBVVVRaxes() const;
	virtual void GLdisplayVVR() const;

	virtual bool isHere(const Vector3& v) const;
	virtual bool isHereFarthestNeighbour(const Vector3& v);
	virtual bool isHereFarthestNeighbourPrime(const Vector3& v);
	virtual bool isHereFirstNeighbour(const Vector3& v);
	virtual bool isHereFirstNeighbourPrime(const Vector3& v,int idp);
	virtual int getNextBV(unsigned int id) const;
	virtual Scalar supportH(const Vector3& v) const;
	virtual Point3 support(const Vector3& v) const;

	virtual bool ray_cast(const Point3& source, const Point3& target,
						  Scalar& param, Vector3& normal) const;

	virtual STP_Feature* clone() const;

	virtual int getNextBVPrime() const
	{
		return m_nextBVPrime;	
	}


protected:
    Scalar m_radius;
	Point3 m_center;
	std::vector<STP_VVR> m_VVR;
	std::vector<int> m_nextBV;
	int m_nextBVPrime;

	STP_VVR * m_neighbors;
	STP_VVR * m_endneighbors;
	void updateVector();




};


#endif