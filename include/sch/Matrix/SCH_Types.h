

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
}

#endif
