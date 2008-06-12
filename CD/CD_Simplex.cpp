#include "CD_Simplex.h"

const Scalar CD_Simplex::zero =__ZERO;
const Scalar CD_Simplex::zero2=__ZERO*__ZERO;
const Scalar CD_Simplex::zero3=__ZERO*__ZERO*__ZERO;
const Scalar CD_Simplex::zero4=__ZERO*__ZERO*__ZERO*__ZERO;


inline char sign(Scalar i)
{
	return (i>0)? 1:-1;
}

	/*! 
	 *\brief gets the closest point from the origin to a conter-clocckwise triangle abc,
	 * A is the last inserted vertice
	 * we ae supposed to know that the origin is tilted up (in the direction of AB^AC)
	 */
	
inline CD_Simplex GetClosestSubSimplexCCKWTriangle(const Vector3& AB,const Vector3& AC,const Vector3& ABC,const Vector3& AO,const Point3& A,const Point3& B,const Point3& C, CD_SimplexKeptPoints &k,unsigned char bA,unsigned char bB,unsigned char bC)
{
	if ((ABC^AC)*AO>=0)
	{
		if (AC*AO>=0)
		{
			k.Reset();
			k.b1=bC;
			k.b2=bA;
			return CD_Simplex(C,A);
		}
		else
		{
			if (AB*AO>=0)
			{
				k.Reset();
				k.b1=bA;
				k.b2=bB;
				return CD_Simplex(A,B);

			}
			else
			{
				k.Reset();
				k.b1=bA;			
				return CD_Simplex(A);
			}
		}
	}
	else
	{
		if ((AB^ABC)*AO>=0)
		{
			if (AB*AO>=0)
			{
				k.Reset();
				k.b1=bA;
				k.b2=bB;
				return CD_Simplex(A,B);

			}
			else
			{
				k.Reset();
				k.b1=bA;	
				return CD_Simplex(A);
			}
		}
		else
		{
			k.Reset();
			k.b1=bB;
			k.b2=bC;
			k.b3=bA;
			return CD_Simplex(B,C,A);
		}
	}

}





CD_Simplex::~CD_Simplex(void)
{
}


CD_Simplex CD_Simplex::GetClosestSubSimplex(const Point3& p,Vector3& v) const
{
	return *this;
	

}

CD_Simplex CD_Simplex::GetClosestSubSimplexGJK(CD_SimplexKeptPoints &k) const
{
	switch (type)
	{
	
	case (segment):
		{
			Vector3 AO(-S2);
			
			if (ab_*AO>=0)
			{
				k.Reset();
				k.b1=0;
				k.b2=1;
				return *this;
			}
			else
			{
				k.Reset();
				k.b1=1;
				return CD_Simplex(S2);
			}
		}
	case (triangle):
		{
			Vector3 AO(-S3);
			Vector3 ABC(ab_^ac_);
			if ((ABC^ac_)*AO>=0)
			{
				if (ac_*AO>=0)
				{
					k.Reset();
					k.b1=1;
					k.b2=2;
					return CD_Simplex(S2,S3);
				}
				else
				{
					if (ab_*AO>=0)
					{
						k.Reset();
						k.b1=2;
						k.b2=0;
						return CD_Simplex(S3,S1);

					}
					else
					{
						k.Reset();
						k.b1=2;
						return CD_Simplex(S3);
					}
				}
			}
			else
			{
				if ((ab_^ABC)*AO>=0)
				{
					if (ab_*AO>=0)
					{
						k.Reset();
						k.b1=2;
						k.b2=0;
						return CD_Simplex(S3,S1);

					}
					else
					{
						k.Reset();
						k.b1=2;
						return CD_Simplex(S3);
					}
				}
				else
				{
					if (ABC*AO>=0)
					{
						k.Reset();
						k.b1=0;
						k.b2=1;
						k.b3=2;
						return CD_Simplex(S1,S2,S3);
					}
					else
					{
						k.Reset();
						k.b1=1;
						k.b2=0;
						k.b3=2;
						return CD_Simplex(S2,S1,S3);
					}
				}


			}

		}	
	case (tetrahedron):
		{

			Vector3 AO(-S4);
			Vector3 ABC(ab_^ac_),ACD(ac_^ad_),ADB(ad_^ab_);
			Scalar d_abc(ABC*AO),d_acd(ACD*AO),d_adb(ADB*AO);
			d_abc=(d_abc*d_abc)/ABC.normsquared()*sign(d_abc);
			d_acd=(d_acd*d_acd)/ACD.normsquared()*sign(d_acd);
			d_adb=(d_adb*d_adb)/ADB.normsquared()*sign(d_adb);


			if (d_abc>d_acd)
			{
				if (d_abc>d_adb)
				{
					if (d_abc>=0)
						return GetClosestSubSimplexCCKWTriangle(ab_,ac_,ABC,AO,S4,S1,S2,k,3,0,1);
					else
						return *this;
				}
				else
				{
					if (d_adb>=0)
						return GetClosestSubSimplexCCKWTriangle(ad_,ab_,ADB,AO,S4,S3,S1,k,3,2,0);
					else
						return *this;
				}
			}
			else
			{
				if (d_acd>d_adb)
				{
					if (d_acd>=0)
						return GetClosestSubSimplexCCKWTriangle(ac_,ad_,ACD,AO,S4,S2,S3,k,3,1,2);
					else
						return *this;

				}
				else
				{
					if (d_adb>=0)
						return GetClosestSubSimplexCCKWTriangle(ad_,ab_,ADB,AO,S4,S3,S1,k,3,2,0);
					else
						return *this;

				}
			}
		}
	
	default:
		{
			k.Reset();
			k.b1=0;
			return *this;
		}
	}

	return *this;

	


}


