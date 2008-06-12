#ifndef STP_BIGSPHERE
#define STP_BIGSPHERE

#pragma once
#include "stp_feature.h"

class STP_BigSphere :
	public STP_Feature
{
public:
	public:
	STP_BigSphere(Scalar radius, Point3 center);
	STP_BigSphere(const STP_BigSphere& s);
	~STP_BigSphere();

	const Point3& getCenter();
	//void setVVR(const Vector3* vvr);
	void setVVR(const STP_VVR* vvr);

	virtual void print() const;
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
	STP_VVR m_VVR0,m_VVR1,m_VVR2;
	int m_nextBV[3];
};

#endif