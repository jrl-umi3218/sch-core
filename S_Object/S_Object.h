#pragma once

#ifndef _S_OBJECT
#define _S_OBJECT


#include "../matrix/SCD_Types.h"




class S_Object
{

protected:
	virtual Point3 N_Support(const Vector3& v, int& lastFeature)const=0;


public:
	
	S_Object(void);
	
	virtual ~S_Object(void);

	
	virtual Point3 Support(const Vector3& v) const;
	virtual Point3 Support(const Vector3& v, int & LastFeature) const;


	/*! Sets the rotation matrix to Rotation*/
	void SetOrientation(const Matrix3x3& Rotation);

	void SetOrientation(const Scalar& r00,const Scalar& r01,const Scalar& r02,
					 const Scalar& r10,const Scalar& r11,const Scalar& r12,
					 const Scalar& r20,const Scalar& r21,const Scalar& r22);

	void SetOrientation(const Quaternion quaternion);

	void SetOrientation(const Scalar& q0,const Scalar& q1,const  Scalar& q2,const  Scalar& q3);

	void SetOrientation(const Scalar& yaw,const Scalar& pitch,const Scalar& roll);

	void SetOrientation(const Scalar* const p);

	void SetOrientation(const Scalar& angle, const Vector3& axe);




	void SetPosition(const Vector3& v);

	void SetPosition(const Scalar& x,const Scalar& y, const Scalar& z);

	void SetPosition(const Scalar* const v);

	void SetTransformation(const Matrix4x4& transformation);

	// composes the current orientation with a Rotation
	void AddRotation(const Matrix3x3& Rotation);

	void AddRotation(const Scalar& r00,const Scalar& r01,const Scalar& r02,
					 const Scalar& r10,const Scalar& r11,const Scalar& r12,
					 const Scalar& r20,const Scalar& r21,const Scalar& r22);

	void AddRotation(const Quaternion quaternion);

	void AddRotation(const Scalar& q0,const Scalar& q1,const  Scalar& q2,const  Scalar& q3);

	void AddRotation(const Scalar& angle, const Vector3& axe);

	void AddRotation(const Scalar& yaw,const Scalar& pitch,const Scalar& roll);

	void AddRotation(const Scalar  * const p);

	void AddTranslation(const Vector3& v);

	void AddTranslation(const Scalar* const v);

	void AddTranslation(const Scalar& x,const Scalar& y, const Scalar& z);

	
	void AddScale(const Scalar& x,const Scalar& y, const Scalar& z);
	
	
	void AddTransformation(const Matrix4x4& transformation);

	void ResetTransformation();

	const Vector3& GetPosition()const;

	const Matrix3x3& GetOrientation()const;	


	void GetTransformationMatrix(Scalar *S) const;


	virtual void DrawGL() const;



	
	//type of Solid object
		static enum S_ObjectType	
	{
		TS_Object,
		TPoint,
		TSegment,
		TPolyhedron,
		TSTP_BV,
		TCylinder,
		TSphere,
		TBox,
		TSuperellipsoid
		
	};


	virtual	S_ObjectType GetType() const;

	typedef struct _TimeStamp 
	{
		unsigned long int value1,value2,value3,value4;

		explicit _TimeStamp():value1(0),value2(0),value3(0),value4(0)
		{}

		bool operator==(const _TimeStamp t)const
		{
			return ((value1==t.value1)&&(value2==t.value2));
		}

		void operator++()
		{
			value1++;
			if (!value1)
			{	
				value2++;
				if (!value2)
				{	
					value3++;
					if (!value3)
					{	
						value4++;

					}
				}
			}
		}

		void operator--()
		{
			value1--;
			if (value1==unsigned long int(-1))
			{	
				value2--;
				if (value2==unsigned long int(-1))
				{	
					value3--;
					if (value3==unsigned long int(-1))
					{	
						value4--;

					}
				}
			}

		}



	
	} TimeStamp;


	const TimeStamp& CheckStamp()const;


	
	
	
	

protected:

	

	

	TimeStamp stamp;
	

	
	Matrix3x3 mRot;
	
	Vector3 trans;




};

#include "S_Object.hxx"

#endif