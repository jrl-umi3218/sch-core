

#ifndef sch_TYPES
#define sch_TYPES

#include <iostream>
#include <cmath>
#include <cfloat>
#include <cassert>

#include <sch/Matrix/SmallMatrix3x3T.h>
#include <sch/Matrix/SmallVector3T.h>


#include <sch/Matrix/SmallVector4T.h>
#include <sch/Matrix/SmallMatrix4x4T.h>
#include <sch/Matrix/QuaternionT.h>




#ifdef sch_FADIFF
#include "fadiff.h"
#endif

namespace sch
{
  typedef  double  Scalar;
  typedef  CD_Matrix::Vector3T<Scalar,false> Vector3;
  typedef  CD_Matrix::Vector4T<Scalar> Vector4;
  typedef  Vector3 Point3;
  typedef  CD_Matrix::Matrix3x3T<Scalar> Matrix3x3;
  typedef  CD_Matrix::QuaternionT<Scalar> Quaternion;
  typedef  CD_Matrix::Matrix4x4T<Scalar> Matrix4x4;
  typedef  CD_Matrix::Vector3T<Scalar,true> Vector3NormOptimized;

  static const Scalar infinity = DBL_MAX;
}

#endif
