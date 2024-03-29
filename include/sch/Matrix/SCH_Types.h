

#ifndef sch_TYPES
#define sch_TYPES

#include <cassert>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <limits>
#include <sch/Matrix/QuaternionT.h>
#include <sch/Matrix/SmallMatrix3x3T.h>
#include <sch/Matrix/SmallMatrix4x4T.h>
#include <sch/Matrix/SmallVector3T.h>
#include <sch/Matrix/SmallVector4T.h>

#ifdef sch_FADIFF
#  include "fadiff.h"
#endif

namespace sch
{
typedef double Scalar;
typedef CD_Matrix::Vector3T<Scalar, false> Vector3;
typedef CD_Matrix::Vector4T<Scalar> Vector4;
typedef Vector3 Point3;
typedef CD_Matrix::Matrix3x3T<Scalar> Matrix3x3;
typedef CD_Matrix::QuaternionT<Scalar> Quaternion;
typedef CD_Matrix::Matrix4x4T<Scalar> Matrix4x4;
typedef CD_Matrix::Vector3T<Scalar, true> Vector3NormOptimized;

static const Scalar infinity = std::numeric_limits<Scalar>::max();
static const Scalar epsilon = std::numeric_limits<Scalar>::epsilon();
static const Scalar epsilon10 = std::numeric_limits<Scalar>::epsilon() * 10;
static const Scalar defaultPrecision = 1e-6;
static const Scalar pi = 3.141592653589793238462643383279502884;
} // namespace sch

#endif
