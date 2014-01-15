

#ifndef SCD_TYPES
#define SCD_TYPES

#include <iostream>
#include <cmath>
#include <cfloat>
#include <cassert>

#include <SCD/Matrix/SmallMatrix3x3T.h>
#include <SCD/Matrix/SmallVector3T.h>


#include <SCD/Matrix/SmallVector4T.h>
#include <SCD/Matrix/SmallMatrix4x4T.h>
#include <SCD/Matrix/QuaternionT.h>




#ifdef SCD_FADIFF
#include "fadiff.h"
#endif

namespace SCD
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
