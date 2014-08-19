

#ifndef sch_TYPES
#define sch_TYPES

#include <iostream>
#include <cmath>
#include <cfloat>
#include <cassert>

#include <Eigen/Core>
#include <Eigen/Geometry>

//#include <sch/Matrix/QuaternionT.h>

#ifdef sch_FADIFF
#include "fadiff.h"
#endif

namespace sch
{
  typedef  double  Scalar;
  typedef  Eigen::Matrix<Scalar, 3, 1> Vector3;
  typedef  Eigen::Matrix<Scalar, 4, 1> Vector4;
  typedef  Vector3 Point3;
  typedef  Eigen::Matrix<Scalar, 3, 3> Matrix3x3;
  typedef  Eigen::Quaternion<Scalar> Quaternion;
  typedef  Eigen::Matrix<Scalar, 4, 4> Matrix4x4;

  static const Scalar infinity = DBL_MAX;


  /*!Euler
   * ROLL PITCH YAW - AROUND X, Y THEN Z */
  inline void eulerToRotation(Matrix3x3& m, const Scalar &roll, const Scalar &pitch, const Scalar &yaw)
  {
    Scalar cy(cos(yaw));
    Scalar sy(sin(yaw));
    Scalar cp(cos(pitch));
    Scalar sp(sin(pitch));
    Scalar cr(cos(roll));
    Scalar sr(sin(roll));

    Scalar sysp = sy * sp;
    Scalar cysp = cy * sp;
    Scalar sysr = sy * sr;
    Scalar sycr = sy * cr;

    m <<
    cy*cp, cysp*sr-sycr,   cysp*cr+sysr,
    sy*cp, sysp*sr+cy*cr,  sysp*cr-cy*sr,
     -sp ,         cp*sr,          cp*cr;
  }
  inline Matrix3x3 eulerToRotation(const Scalar &roll, const Scalar &pitch, const Scalar &yaw)
  {
    Matrix3x3 m;
    eulerToRotation(m, roll, pitch, yaw);
    return m;
  }

  /*! angle axis*/
  inline void angleAxisToRotation (Matrix3x3& m, const Scalar &angle,const Vector3  &axis)
  {
    Scalar sin_a = sin(angle / 2),
      cos_a = cos(angle / 2);

    Scalar q0 = axis[0] * sin_a;
    Scalar q1 = axis[1] * sin_a;
    Scalar q2 = axis[2] * sin_a;
    Scalar q3 = cos_a;

    Scalar d = q0*q0+q1*q1+q2*q2+q3*q3;

    assert(d != Scalar(0.0));
    Scalar s = Scalar(2.0) / d;
    Scalar xs = q0 * s,   ys = q1 * s,   zs = q2 * s;
    Scalar wx = q3 * xs,  wy = q3 * ys,  wz = q3 * zs;
    Scalar xx = q0 * xs,  xy = q0 * ys,  xz = q0 * zs;
    Scalar yy = q1 * ys,  yz = q1 * zs,  zz = q2 * zs;

    m <<
    (Scalar(1.0) - (yy + zz)), xy - wz,  xz + wy,
    xy + wz,  (Scalar(1.0) - (xx + zz)), yz - wx,
    xz - wy, yz + wx,  (Scalar(1.0) - (xx + yy));
  }

  inline Matrix3x3 angleAxisToRotation (const Scalar &angle,const Vector3  &axis)
  {
    Matrix3x3 m;
    angleAxisToRotation(m, angle, axis);
    return m;
  }

  /*! quatrenion*/
  inline void quaternionToRotation (Matrix3x3& m,
      const Scalar &q0,const Scalar &q1,const Scalar &q2,const Scalar &q3)
  {
    Scalar d = q0*q0+q1*q1+q2*q2+q3*q3;
    assert(d != Scalar(0.0));
    Scalar s = Scalar(2.0) / d;
    Scalar xs = q0 * s,   ys = q1 * s,   zs = q2 * s;
    Scalar wx = q3 * xs,  wy = q3 * ys,  wz = q3 * zs;
    Scalar xx = q0 * xs,  xy = q0 * ys,  xz = q0 * zs;
    Scalar yy = q1 * ys,  yz = q1 * zs,  zz = q2 * zs;

    m <<
    Scalar(1.0) - (yy + zz),
    xy - wz,
    xz + wy,
    xy + wz,
    Scalar(1.0) - (xx + zz),
    yz - wx,
    xz - wy,
    yz + wx,
    Scalar(1.0) - (xx + yy);
  }

  inline Matrix3x3 quaternionToRotation (
      const Scalar &q0,const Scalar &q1,const Scalar &q2,const Scalar &q3)
  {
    Matrix3x3 m;
    quaternionToRotation (m, q0, q1, q2, q3);
    return m;
  }
}

#endif
