

#ifndef SCD_TYPES
#define SCD_TYPES

#include "SmallVector3mod.h"
#include "SmallVector4Default.h"
#include "SmallMatrix3x3mod.h"
#include "SmallMatrix4x4Default.h"
#include "QuaternionM.h"
#include <cfloat>


typedef  double  Scalar;
typedef  MAL_Default::Vector3Mod<Scalar> Vector3;
typedef  MAL_Default::Vector4D<Scalar> Vector4;
typedef  Vector3 Point3;
typedef  MAL_Default::Matrix3x3Mod<Scalar> Matrix3x3;
typedef  MAL_Default::QuaternionM<Scalar> Quaternion;
typedef  MAL_Default::Matrix4x4D<Scalar> Matrix4x4;

const Scalar INFINITY(DBL_MAX);






#endif