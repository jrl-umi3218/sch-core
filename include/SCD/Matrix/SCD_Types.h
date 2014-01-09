

#ifndef SCD_TYPES
#define SCD_TYPES

#include <SCD/Matrix/SmallVector3Mod.h>
#include <SCD/Matrix/SmallVector4Default.h>
#include <SCD/Matrix/SmallMatrix3x3Mod.h>
#include <SCD/Matrix/SmallMatrix4x4Default.h>
#include <SCD/Matrix/QuaternionM.h>
#include <cfloat>

#ifdef SCD_FADIFF
#include "fadiff.h"
#endif

namespace SCD
{
	typedef  double  Scalar;
	typedef  MAL_Default::Vector3Mod<Scalar> Vector3;
	typedef  MAL_Default::Vector4D<Scalar> Vector4;
	typedef  Vector3 Point3;
	typedef  MAL_Default::Matrix3x3Mod<Scalar> Matrix3x3;
	typedef  MAL_Default::QuaternionM<Scalar> Quaternion;
	typedef  MAL_Default::Matrix4x4D<Scalar> Matrix4x4;

    static const Scalar infinity = DBL_MAX;
}

#endif
