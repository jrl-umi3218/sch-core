#include "CD_Pair.h"
#include "CD_simplex.h"
#include "CD_simplexEnhanced.h"
#include <gl\glut.h>
#include <iostream>

//#define SHOW_LAST_SIMLPEX

inline Vector3 LinearSystem(Matrix3x3& A, Vector3& y)
{
	Matrix3x3 B;
	A.Inversion(B);
	return (B*y);
}




CD_Pair::CD_Pair(S_Object *obj1, S_Object *obj2):sObj1(obj1),sObj2(obj2),lastDirection(1.0,0.0,0.0),
lastFeature1(-1),lastFeature2(-1),distance(0),stamp1(sObj1->CheckStamp()),stamp2(sObj2->CheckStamp()), 
precision(1e-6),s1(Point3()),s2(Point3()),s(Point3()),WitPointsAreComputed(false)
{	
	--stamp1;
	--stamp2;

}

CD_Pair::~CD_Pair(void)
{
}

Scalar CD_Pair::GetDistance()
{
	if ((stamp1==sObj1->CheckStamp())&&(stamp2==sObj2->CheckStamp()))
	{
		return distance;
	}
	else
	{
		stamp1=sObj1->CheckStamp();
		stamp2=sObj2->CheckStamp();
		return GJK();
	}

}



Scalar CD_Pair::ReComputeClosestPoints(Point3& _p1,Point3& _p2)
{
	stamp1=sObj1->CheckStamp();
	stamp2=sObj2->CheckStamp();
	GJK();
	WitPoints(_p1,_p2);
	return distance;
	
}


void CD_Pair::SetRelativePrecision(Scalar s)
{
	precision=s*s;
}


Scalar CD_Pair::GetClosestPoints(Point3 &_p1, Point3 &_p2)
{
	if ((stamp1==sObj1->CheckStamp())&&(stamp2==sObj2->CheckStamp()))
	{
		if (WitPointsAreComputed)
		{
			WitPointsAreComputed=true;
			WitPoints(p1,p2);
		}
		_p1=p1;
		_p2=p2;
		return distance;
	}
	else
	{
		

		WitPointsAreComputed=true;
		stamp1=sObj1->CheckStamp();
		stamp2=sObj2->CheckStamp();
		GJK();
		WitPoints(_p1,_p2);
		return distance;

	}

}




Scalar CD_Pair::GJK()
{
	Vector3& v=lastDirection;

	WitPointsAreComputed=false;

		
	int& lf1=lastFeature1;
	int& lf2=lastFeature2;


	Point3 sup1=sObj1->Support(v,lf1);
	Point3 sup2=sObj2->Support(-v,lf2);

	Point3 sup=sup1-sup2;

	s1=sup1;
	s2=sup2;
	s=sup;

	CD_SimplexEnhanced sp(sup);

	
	Scalar dp;

	char cntIrregul=0;


	CD_SimplexKeptPoints k;

	projectionComputed_=false;
	
	bool cont;

	if (v.IsZero())
	{
		v.Set(1,0,0);
		return 0;
	}
	else
	{
		cont=true;
	}
	
		
	Point3 proj;

	Vector3 S01;
	Vector3 S02;

	Scalar a1,a2,a3,a4,a5,a6,det;


	while (cont)
	{

		switch (s.getType())
		{

		case CD_Simplex::triangle:
			{
				S01=s[1]-s[2];
				S02=s[0]-s[2];

				a1=S01*s[0],a2=S01*s[1],a3=S01*s[2],a4=S02*s[0],a5=S02*s[1],a6=S02*s[2];
				
				
				lambda0_=a2*a6-a3*a5;
				lambda1_=a3*a4-a1*a6;
				lambda2_=a1*a5-a2*a4;
				det=1/(lambda0_+lambda1_+lambda2_);
				
				lambda0_*=det;
				lambda1_*=det;
				lambda2_*=det;

				proj=s[0]*lambda0_+s[1]*lambda1_+s[2]*lambda2_;
				
				v=-proj;

				break;
			
			}

		case CD_Simplex::segment:
			{

			
				S01=s[1]-s[0];
	
				lambda1_=-(S01*s[0]);
				lambda0_=S01*s[1];

				det=1/(lambda0_+lambda1_);

				lambda0_*=det;
				lambda1_*=det;

				proj=s[0]*lambda0_+s[1]*lambda1_;
				
				
				v=-proj;

				break;

			}
		default:
			{
				proj=s[0];
				
				v=-proj;
			}

		}

		if ((v.IsZero())||((dp=proj.normsquared())>=distance)&&(++cntIrregul>200))
		{
			cont=false;
		}
		else
		{
			distance=dp;



			sup1=sObj1->Support(v,lf1);
			sup2=sObj2->Support(-v,lf2);

			sup=sup1-sup2;



			if ((distance-proj*sup)<(precision*distance))
			{
				cont=false;
				projectionComputed_=true;

			}
			else
			{

				sp+=sup;
				sp.updateVectors();


				if (sp.IsAffinelyDependent())
				{
					cont=false;
				}
				else
				{

					sp=sp.GetClosestSubSimplexGJK(k);

					if (sp.getType()==CD_Simplex::tetrahedron)
						cont=false;
					else
					{

						s1+=sup1;
						s2+=sup2;
						s=sp;

						s1.Filter(k);
						s2.Filter(k);

						
					}
				}
			}
		}
	}

	
	
	if (sp.getType()==CD_Simplex::tetrahedron)//origin is inside the tetrahedron
	{		
			return distance=-1;
	}
	else
		return distance;

	


	



	
}

void CD_Pair::WitPoints(Point3 &_p1, Point3 &_p2)
{
	Point3 proj;
	Vector3& v=lastDirection;
	
	if (distance==-1)
		return;


	switch (s.getType())
	{
	
	case CD_Simplex::triangle:
		{

			{
				if (!projectionComputed_)
				{
					Vector3 S01(s[1]-s[2]), S02(s[0]-s[2]);

					Scalar a1=S01*s[0],a2=S01*s[1],a3=S01*s[2],a4=S02*s[0],a5=S02*s[1],a6=S02*s[2];


					lambda0_=a2*a6-a3*a5;
					lambda1_=a3*a4-a1*a6;
					lambda2_=a1*a5-a2*a4;
					Scalar det=1/(lambda0_+lambda1_+lambda2_);

					lambda0_*=det;
					lambda1_*=det;
					lambda2_*=det;

					proj=s[0]*lambda0_+s[1]*lambda1_+s[2]*lambda2_;

					v=-proj;

				}

				p1=_p1=s1[0]*lambda0_+s1[1]*lambda1_+s1[2]*lambda2_;
				p2=_p2=s2[0]*lambda0_+s2[1]*lambda1_+s2[2]*lambda2_;			

			}
		

			

			


			
#ifdef SHOW_LAST_SIMLPEX
			glDisable(GL_DEPTH_TEST);
			glColor4d(0,0.5,1,0.5);
			glBegin(GL_TRIANGLES);
			glVertex3d(s1[0][0],s1[0][1],s1[0][2]);
			glVertex3d(s1[1][0],s1[1][1],s1[1][2]);
			glVertex3d(s1[2][0],s1[2][1],s1[2][2]);

			glVertex3d(s2[0][0],s2[0][1],s2[0][2]);
			glVertex3d(s2[1][0],s2[1][1],s2[1][2]);
			glVertex3d(s2[2][0],s2[2][1],s2[2][2]);

		
			glEnd();

			glEnable(GL_DEPTH_TEST);
#endif

			return;
			
		}
		
	case CD_Simplex::segment:
		{
			if (!projectionComputed_)
			{
				
			
				Vector3 S01(s[1]-s[0]);
	
				lambda1_=-(S01*s[0]);
				lambda0_=S01*s[1];

				Scalar det=1/(lambda0_+lambda1_);

				lambda0_*=det;
				lambda1_*=det;

				proj=s[0]*lambda0_+s[1]*lambda1_;
				
				
				v=-proj;

				
			}

			p1=_p1=s1[0]*lambda0_+s1[1]*lambda1_;
			p2=_p2=s2[0]*lambda0_+s2[1]*lambda1_;



#ifdef SHOW_LAST_SIMLPEX
			
			glDisable(GL_DEPTH_TEST);
			glColor4d(0,0.5,1,0.5);
			glBegin(GL_LINES);
			glVertex3d(s1[0][0],s1[0][1],s1[0][2]);
			glVertex3d(s1[1][0],s1[1][1],s1[1][2]);
		

			glVertex3d(s2[0][0],s2[0][1],s2[0][2]);
			glVertex3d(s2[1][0],s2[1][1],s2[1][2]);
			
			glEnd();

			glEnable(GL_DEPTH_TEST);


#endif
			return ;
		}
	default:
		{
			p1=_p1=s1[0];
			p2=_p2=s2[0];

			return ;
		}
		
	
		

	}
}