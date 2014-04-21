#include <limits>

#include <sch/CD/CD_Simplex.h>

using namespace sch;

typedef std::numeric_limits< Scalar > dl;

const Scalar CD_Simplex::zero_ =pow(double(10),-(dl::digits10));
const Scalar CD_Simplex::zero2_=zero_*zero_;
const Scalar CD_Simplex::zero3_=zero2_*zero_;
const Scalar CD_Simplex::zero4_=zero2_*zero2_;

/*!
 *\brief gets the closest point from the origin to a conter-clocckwise triangle abc,
 * A is the last inserted vertice
 * we ae supposed to know that the origin is tilted up (in the direction of AB^AC)
 */
CD_Simplex::~CD_Simplex(void)
{
}

