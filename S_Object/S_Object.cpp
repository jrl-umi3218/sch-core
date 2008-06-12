#include "S_Object.h"

S_Object::S_Object():mRot(1,0,0,0,1,0,0,0,1),trans(0,0,0)
{
	++stamp;
}

S_Object::~S_Object()
{
}

S_Object::S_ObjectType S_Object::GetType() const
{
	return S_Object::TS_Object;
}


void S_Object::SetOrientation(const Matrix3x3& rotation)
{
	++stamp;
	mRot=rotation;
	
}


void S_Object::SetOrientation(const Quaternion quaternion)
{
	++stamp;
	mRot.Set(quaternion);
	
	
}


void S_Object::SetOrientation(const Scalar& q0,const Scalar& q1,const Scalar& q2,const Scalar& q3)
{
	++stamp;
	mRot.Set(q0,q1,q2,q3);
	
	
}

void S_Object::SetOrientation(const Scalar& r00,const Scalar& r01,const Scalar& r02,
						   const Scalar& r10,const Scalar& r11,const Scalar& r12,
						   const Scalar& r20,const Scalar& r21,const Scalar& r22)
{
	++stamp;
	mRot.Set( r00, r01, r02, 
			  r10, r11, r12, 
			  r20, r21, r22);
	

}

void S_Object::SetOrientation(const Scalar* const p)
{
	++stamp;
	mRot.Set(p);
	

}

void S_Object::SetOrientation(const Scalar& s, const Vector3& v)
{
	++stamp;
	mRot.Set(s,v);
	
}


void S_Object::SetPosition(const Vector3 &v)
{
	++stamp;
	trans=v;
	

}

void S_Object::SetPosition(const Scalar &x,const Scalar &y, const  Scalar &z)
{
	++stamp;
	trans.Set(x,y,z);

	

}


void S_Object::SetPosition(const Scalar * const p)
{
	++stamp;
	trans.Set(p);

	

}





void S_Object::AddRotation(const Matrix3x3& rotation)
{
	++stamp;
	mRot*=rotation;
	trans=rotation*trans;


}


void S_Object::AddRotation(const Quaternion quaternion)
{
	++stamp;
	Matrix3x3 m(quaternion);
	mRot*=m;
	trans=m*trans;	
	
}


void S_Object::AddRotation(const Scalar& q0,const Scalar& q1,const Scalar& q2,const Scalar& q3)
{
	++stamp;
	Matrix3x3 m(q0,q1,q2,q3);
	mRot*=m;
	trans=m*trans;	
}

void S_Object::AddRotation(const Scalar& s, const Vector3& v)
{
	++stamp;
	Matrix3x3 m(s,v);
	mRot*=m;
	trans=m*trans;
	
}

void S_Object::AddRotation(const Scalar& r00,const Scalar& r01,const Scalar& r02,
						   const Scalar& r10,const Scalar& r11,const Scalar& r12,
						   const Scalar& r20,const Scalar& r21,const Scalar& r22)
{
	++stamp;
	Matrix3x3 m( r00, r01, r02,
				 r10, r11, r12, 
				 r20, r21, r22);
	mRot*=m;
	trans=m*trans;

	

	
	
}




void S_Object::AddRotation(const Scalar* const p)
{

	++stamp;
	Matrix3x3 m(p);
	mRot*=m;
	trans=m*trans;
	
}

void S_Object::AddRotation(const Scalar &yaw, const Scalar &pitch, const Scalar &roll)
{
	++stamp;
	Matrix3x3 m(yaw,pitch,roll);
	mRot*=m;
	trans=m*trans;
	
}


void S_Object::AddTranslation(const Vector3& v)
{
	++stamp;
	trans+=v;

	
}



void S_Object::AddTranslation(const Scalar & x,const Scalar & y,const Scalar & z)
{
	++stamp;
	trans+=Vector3(x,y,z);
		
}


void S_Object::AddTranslation(const Scalar * const p)
{
	++stamp;
	trans+=Vector3(p);
}

void S_Object::AddScale(const Scalar & x,const Scalar & y,const Scalar & z)
{
	++stamp;
	mRot(0,0)*=x;	mRot(0,1)*=x;	mRot(0,2)*=x; trans(0)*=x;
	mRot(1,0)*=y;	mRot(1,1)*=y;	mRot(1,2)*=y; trans(1)*=y;
	mRot(2,0)*=z;	mRot(2,1)*=z;	mRot(2,2)*=z; trans(2)*=z;
		
}

void S_Object::SetTransformation(const Matrix4x4& t)
{
	++stamp;
	SetOrientation(t(0,0),t(0,1),t(0,2),
				   t(1,0),t(1,1),t(1,2),
				   t(2,0),t(2,1),t(2,2));
	SetPosition(t(0,3),t(1,3),t(2,3));
}





void S_Object::AddTransformation(const Matrix4x4& tr)
{
	++stamp;
	Matrix4x4 k;
	k(0,0)=mRot(0,0);	k(0,1)=mRot(0,1);	k(0,2)=mRot(0,2); k(0,3)=trans(0);
	k(1,0)=mRot(1,0);	k(1,1)=mRot(1,1);	k(1,2)=mRot(1,2); k(1,3)=trans(1);
	k(2,0)=mRot(2,0);	k(2,1)=mRot(2,1);	k(2,2)=mRot(2,2); k(2,3)=trans(2);
															  k(3,3)=1;
	
	Matrix4x4 t(tr*k);

	SetOrientation(t(0,0),t(0,1),t(0,2),
				   t(1,0),t(1,1),t(1,2),
				   t(2,0),t(2,1),t(2,2));
	SetPosition(t(0,3),t(1,3),t(2,3));

}

void S_Object::ResetTransformation()
{
	++stamp;
	SetOrientation(1,0,0,
				   0,1,0,
				   0,1,0);
	SetPosition(0,0,0);

}


void S_Object::DrawGL() const
{
}