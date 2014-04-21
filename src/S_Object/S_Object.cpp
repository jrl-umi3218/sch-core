#include <sch/S_Object/S_Object.h>

#include <vector>

using namespace sch;

S_Object::S_Object():stacks_(50),slices_(100),mRot_(1,0,0,0,1,0,0,0,1),trans_(0,0,0)
{
  ++stamp_;
}

S_Object::~S_Object()
{
}

S_Object::S_ObjectType S_Object::getType() const
{
  return S_Object::TS_Object;
}


void S_Object::setOrientation(const Matrix3x3& rotation)
{
  ++stamp_;
  mRot_=rotation;
}


void S_Object::setOrientation(const Quaternion quaternion)
{
  ++stamp_;
  mRot_.Set(quaternion);
}


void S_Object::setOrientation(const Scalar& q0,const Scalar& q1,const Scalar& q2,const Scalar& q3)
{
  ++stamp_;
  mRot_.Set(q0,q1,q2,q3);
}

void S_Object::setOrientation(const Scalar& r00,const Scalar& r01,const Scalar& r02,
                              const Scalar& r10,const Scalar& r11,const Scalar& r12,
                              const Scalar& r20,const Scalar& r21,const Scalar& r22)
{
  ++stamp_;
  mRot_.Set( r00, r01, r02,
             r10, r11, r12,
             r20, r21, r22);
}

void S_Object::setOrientation(const Scalar* const p)
{
  ++stamp_;
  mRot_.Set(p);
}

void S_Object::setOrientation(const Scalar& roll, const Scalar& pitch, const Scalar& yaw)
{
  ++stamp_;
  Matrix3x3 m(roll, pitch, yaw);
  mRot_=m;
}


void S_Object::setOrientation(const Scalar& s, const Vector3& v)
{
  ++stamp_;
  mRot_.Set(s,v);
}


void S_Object::setPosition(const Vector3 &v)
{
  ++stamp_;
  trans_=v;
}

void S_Object::setPosition(const Scalar &x,const Scalar &y, const  Scalar &z)
{
  ++stamp_;
  trans_.Set(x,y,z);
}


void S_Object::setPosition(const Scalar * const p)
{
  ++stamp_;
  trans_.Set(p);
}


void S_Object::addRotation(const Matrix3x3& rotation)
{
  ++stamp_;
  mRot_*=rotation;
  trans_=rotation*trans_;
}


void S_Object::addRotation(const Quaternion quaternion)
{
  ++stamp_;
  Matrix3x3 m(quaternion);
  mRot_=m*mRot_;
  trans_=m*trans_;

}


void S_Object::addRotation(const Scalar& q0,const Scalar& q1,const Scalar& q2,const Scalar& q3)
{
  ++stamp_;
  Matrix3x3 m(q0,q1,q2,q3);
  mRot_=m*mRot_;
  trans_=m*trans_;
}

void S_Object::addRotation(const Scalar& s, const Vector3& v)
{
  ++stamp_;
  Matrix3x3 m(s,v);
  mRot_=m*mRot_;
  trans_=m*trans_;

}

void S_Object::addRotation(const Scalar& r00,const Scalar& r01,const Scalar& r02,
                           const Scalar& r10,const Scalar& r11,const Scalar& r12,
                           const Scalar& r20,const Scalar& r21,const Scalar& r22)
{
  ++stamp_;
  Matrix3x3 m( r00, r01, r02,
               r10, r11, r12,
               r20, r21, r22);
  mRot_=m*mRot_;
  trans_=m*trans_;
}

void S_Object::addRotation(const Scalar* const p)
{
  ++stamp_;
  Matrix3x3 m(p);
  mRot_=m*mRot_;
  trans_=m*trans_;
}

void S_Object::addRotation(const Scalar& roll, const Scalar& pitch, const Scalar& yaw)
{
  ++stamp_;
  Matrix3x3 m(roll, pitch, yaw);
  mRot_=m*mRot_;
  trans_=m*trans_;
}


void S_Object::addTranslation(const Vector3& v)
{
  ++stamp_;
  trans_+=v;
}

void S_Object::addTranslation(const Scalar & x,const Scalar & y,const Scalar & z)
{
  ++stamp_;
  trans_+=Vector3(x,y,z);
}

void S_Object::addTranslation(const Scalar * const p)
{
  ++stamp_;
  trans_+=Vector3(p);
}

void S_Object::addScale(const Scalar & x,const Scalar & y,const Scalar & z)
{
  ++stamp_;
  mRot_(0,0)*=x;
  mRot_(0,1)*=x;
  mRot_(0,2)*=x;
  trans_(0)*=x;
  mRot_(1,0)*=y;
  mRot_(1,1)*=y;
  mRot_(1,2)*=y;
  trans_(1)*=y;
  mRot_(2,0)*=z;
  mRot_(2,1)*=z;
  mRot_(2,2)*=z;
  trans_(2)*=z;
}

void S_Object::setTransformation(const Matrix4x4& t)
{
  ++stamp_;
  setOrientation(t(0,0),t(0,1),t(0,2),
                 t(1,0),t(1,1),t(1,2),
                 t(2,0),t(2,1),t(2,2));
  setPosition(t(0,3),t(1,3),t(2,3));
}

void S_Object::addTransformation(const Matrix4x4& tr)
{
  ++stamp_;
  Matrix4x4 k;
  k(0,0)=mRot_(0,0);
  k(0,1)=mRot_(0,1);
  k(0,2)=mRot_(0,2);
  k(0,3)=trans_(0);
  k(1,0)=mRot_(1,0);
  k(1,1)=mRot_(1,1);
  k(1,2)=mRot_(1,2);
  k(1,3)=trans_(1);
  k(2,0)=mRot_(2,0);
  k(2,1)=mRot_(2,1);
  k(2,2)=mRot_(2,2);
  k(2,3)=trans_(2);
  k(3,3)=1;

  Matrix4x4 t(tr*k);

  setOrientation(t(0,0),t(0,1),t(0,2),
                 t(1,0),t(1,1),t(1,2),
                 t(2,0),t(2,1),t(2,2));
  setPosition(t(0,3),t(1,3),t(2,3));
}

void S_Object::resetTransformation()
{
  ++stamp_;
  setOrientation(1,0,0,
                 0,1,0,
                 0,0,1);
  setPosition(0,0,0);
}

void S_Object::constructFromFile(const std::string &)
{
}

