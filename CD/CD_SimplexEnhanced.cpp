#include "CD_SimplexEnhanced.h"

inline char sign(Scalar i)
{
	return (i>0)? 1:-1;
}


inline CD_SimplexEnhanced GetClosestSubSimplexCCKWTriangle(const Vector3& AB,const Vector3& AC,const Vector3& ABC,const Vector3& AO,const Point3& A,const Point3& B,const Point3& C, Scalar normA,Scalar normB,Scalar normC, CD_SimplexKeptPoints &k,unsigned char bA,unsigned char bB,unsigned char bC)
{
	if ((ABC^AC)*AO>=0)
	{
		if (AC*AO>=0)
		{
			k.reset();
			k.b1=bC;
			k.b2=bA;
			return CD_SimplexEnhanced(C,A,normC,normA);
		}
		else
		{
			if (AB*AO>=0)
			{
				k.reset();
				k.b1=bA;
				k.b2=bB;
				return CD_SimplexEnhanced(A,B,normA,normB);

			}
			else
			{
				k.reset();
				k.b1=bA;			
				return CD_SimplexEnhanced(A,normA);
			}
		}
	}
	else
	{
		if ((AB^ABC)*AO>=0)
		{
			if (AB*AO>=0)
			{
				k.reset();
				k.b1=bA;
				k.b2=bB;
				return CD_SimplexEnhanced(A,B,normA,normB);

			}
			else
			{
				k.reset();
				k.b1=bA;	
				return CD_SimplexEnhanced(A,normA);
			}
		}
		else
		{
			k.reset();
			k.b1=bB;
			k.b2=bC;
			k.b3=bA;
			return CD_SimplexEnhanced(B,C,A,normB,normC,normA);
		}
	}

}






CD_SimplexEnhanced::~CD_SimplexEnhanced(void)
{
}


CD_SimplexEnhanced CD_SimplexEnhanced::GetClosestSubSimplexGJK(CD_SimplexKeptPoints &k) const
{
	switch (type)
	{
	
	case (segment):
		{
			Vector3 AO(-S2);
			
			if (ab_*AO>=0)
			{
				k.reset();
				k.b1=0;
				k.b2=1;
				return *this;
			}
			else
			{
				k.reset();
				k.b1=1;
				return CD_SimplexEnhanced(S2,norm2_);
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
					k.reset();
					k.b1=1;
					k.b2=2;
					return CD_SimplexEnhanced(S2,S3,norm2_,norm3_);
				}
				else
				{
					if (ab_*AO>=0)
					{
						k.reset();
						k.b1=2;
						k.b2=0;
						return CD_SimplexEnhanced(S3,S1,norm3_,norm1_);

					}
					else
					{
						k.reset();
						k.b1=2;
						return CD_SimplexEnhanced(S3,norm3_);
					}
				}
			}
			else
			{
				if ((ab_^ABC)*AO>=0)
				{
					if (ab_*AO>=0)
					{
						k.reset();
						k.b1=2;
						k.b2=0;
						return CD_SimplexEnhanced(S3,S1,norm3_,norm1_);

					}
					else
					{
						k.reset();
						k.b1=2;
						return CD_SimplexEnhanced(S3,norm3_);
					}
				}
				else
				{
					if (ABC*AO>=0)
					{
						k.reset();
						k.b1=0;
						k.b2=1;
						k.b3=2;
						return CD_SimplexEnhanced(S1,S2,S3,norm1_,norm2_,norm3_);
					}
					else
					{
						k.reset();
						k.b1=1;
						k.b2=0;
						k.b3=2;
						return CD_SimplexEnhanced(S2,S1,S3,norm2_,norm1_,norm3_);
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
						return GetClosestSubSimplexCCKWTriangle(ab_,ac_,ABC,AO,S4,S1,S2,norm4_,norm1_,norm2_,k,3,0,1);
					else
						return *this;
				}
				else
				{
					if (d_adb>=0)
						return GetClosestSubSimplexCCKWTriangle(ad_,ab_,ADB,AO,S4,S3,S1,norm4_,norm3_,norm1_,k,3,2,0);
					else
						return *this;
				}
			}
			else
			{
				if (d_acd>d_adb)
				{
					if (d_acd>=0)
						return GetClosestSubSimplexCCKWTriangle(ac_,ad_,ACD,AO,S4,S2,S3,norm4_,norm2_,norm3_,k,3,1,2);
					else
						return *this;

				}
				else
				{
					if (d_adb>=0)
						return GetClosestSubSimplexCCKWTriangle(ad_,ab_,ADB,AO,S4,S3,S1,norm4_,norm3_,norm1_,k,3,2,0);
					else
						return *this;

				}
			}
		}
	
	default:
		{
			k.reset();
			k.b1=0;
			return *this;
		}
	}

	return *this;

	


}


