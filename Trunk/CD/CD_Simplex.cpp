#include "CD_Simplex.h"


using namespace SCD;

const Scalar CD_Simplex::zero_ =__ZERO;
const Scalar CD_Simplex::zero2_=__ZERO*__ZERO;
const Scalar CD_Simplex::zero3_=__ZERO*__ZERO*__ZERO;
const Scalar CD_Simplex::zero4_=__ZERO*__ZERO*__ZERO*__ZERO;


	/*! 
	 *\brief gets the closest point from the origin to a conter-clocckwise triangle abc,
	 * A is the last inserted vertice
	 * we ae supposed to know that the origin is tilted up (in the direction of AB^AC)
	 */
	
CD_Simplex::~CD_Simplex(void)
{
}


