#include "CD_Pair.h"
#include "CD_simplex.h"
#include "CD_simplexEnhanced.h"
#include <gl\glut.h>
#include <iostream>

//#define SHOW_LAST_SIMLPEX
//#define COUNTER
//#define SAFE_VERSION
#define PENETRATION_DEPTH

#define _EPSILON_ 1e-24
#define _PRECISION_ 1e-6


using namespace SCD;

inline Vector3 LinearSystem(Matrix3x3& A, Vector3& y)
{
	Matrix3x3 B;
	A.Inversion(B);
	return (B*y);
}




CD_Pair::CD_Pair(S_Object *obj1, S_Object *obj2):sObj1_(obj1),sObj2_(obj2),lastDirection_(1.0,0.0,0.0),
lastFeature1_(-1),lastFeature2_(-1),distance_(0),stamp1_(sObj1_->checkStamp()),stamp2_(sObj2_->checkStamp()), 
precision_(_PRECISION_),epsilon_(_EPSILON_),s1_(Point3()),s2_(Point3()),s_(Point3()),witPointsAreComputed_(false),depthPair(obj1,obj2)
{	
	--stamp1_;
	--stamp2_;

	depthPair.setRelativePrecision(_PRECISION_);
	depthPair.setEpsilon(_EPSILON_);



}

CD_Pair::~CD_Pair(void)
{
}

Scalar CD_Pair::getDistance()
{
	if ((stamp1_==sObj1_->checkStamp())&&(stamp2_==sObj2_->checkStamp()))
	{
		return distance_;
	}
	else
	{
		stamp1_=sObj1_->checkStamp();
		stamp2_=sObj2_->checkStamp();
		return GJK();
	}

}



Scalar CD_Pair::reComputeClosestPoints(Point3& p1,Point3& p2)
{
	stamp1_=sObj1_->checkStamp();
	stamp2_=sObj2_->checkStamp();
	GJK();
	witPoints(p1,p2);
	return distance_;
	
}


void CD_Pair::setRelativePrecision(Scalar s)
{
	precision_=s*s;
	depthPair.setRelativePrecision(s*s);
}


void CD_Pair::setEpsilon(Scalar s)
{
	epsilon_=s;
	depthPair.setEpsilon(s);
}

Scalar CD_Pair::getClosestPoints(Point3 &p1, Point3 &p2)
{
	if ((stamp1_==sObj1_->checkStamp())&&(stamp2_==sObj2_->checkStamp()))
	{
		if (!witPointsAreComputed_)
		{
			witPointsAreComputed_=true;
			witPoints(p1,p2);
		}
		p1=p1_;
		p2=p2_;
		return distance_;
	}
	else
	{
		

		witPointsAreComputed_=true;
		stamp1_=sObj1_->checkStamp();
		stamp2_=sObj2_->checkStamp();
		GJK();
		witPoints(p1,p2);
		return distance_;

	}

}




Scalar CD_Pair::GJK()
{

	Vector3& v=lastDirection_;

	witPointsAreComputed_=false;

		
	int& lf1=lastFeature1_;
	int& lf2=lastFeature2_;


	Point3 sup1=sObj1_->support(v,lf1);
	Point3 sup2=sObj2_->support(-v,lf2);

	Point3 sup(sup1);
	
	sup-=sup2;

	s1_=sup1;
	s2_=sup2;
	s_=sup;

	CD_SimplexEnhanced sp(sup);

	CD_SimplexKeptPoints k;

	projectionComputed_=false;
	
	bool cont=true;

	
	
		
	Point3 proj;

	Vector3 S01;
	Vector3 S02;

	Scalar a1,a2,a3,a4,a5,a6;


#ifdef COUNTER

	int	cnt=0;
#endif 


	while (cont)
	{

#ifdef COUNTER

		cnt++;
#endif 

		switch (s_.getType())
		{

		case CD_Triangle:
			{
				S01=s_[1];
				S01-=s_[2];
				S02=s_[0];
				S02-=s_[2];

				a1=S01*s_[0],a2=S01*s_[1],a3=S01*s_[2],a4=S02*s_[0],a5=S02*s_[1],a6=S02*s_[2];
				
				
				lambda0_=a2*a6-a3*a5;
				lambda1_=a3*a4-a1*a6;
				lambda2_=a1*a5-a2*a4;
				det_=1/(lambda0_+lambda1_+lambda2_);
				
				lambda0_*=det_;
				lambda1_*=det_;
				lambda2_*=det_;

				proj=s_[0]*lambda0_+s_[1]*lambda1_+s_[2]*lambda2_;
				
				v=-proj;

				break;
			
			}

		case CD_Segment:
			{

			
				S01=s_[1];
				S01-=s_[0];
	
				lambda0_=S01*s_[1];
				lambda1_=-(S01*s_[0]);
				

				det_=1/(lambda0_+lambda1_);

				lambda0_*=det_;
				lambda1_*=det_;

				proj=s_[0]*lambda0_+s_[1]*lambda1_;
				
				
				v=-proj;

				break;

			}
		default:
			{
				proj=s_[0];
				
				v=-proj;
			}

		}
		if ((distance_=v.normsquared())<=sp.farthestPointDistance()*epsilon_)//v is considered zero
		{
			collision_=true;
			cont=false;
		}
		else
		{
			sup1=sObj1_->support(v,lf1);
			sup2=sObj2_->support(-v,lf2);

			sup=sup1;
			sup-=sup2;



			if ((distance_-proj*sup)<(precision_*distance_))
			{
				collision_=false;
				cont=false;
				projectionComputed_=true;

			}
			else
			{

				sp+=sup;
				
				sp.updateVectors();

#ifndef SAFE_VERSION
				if (sp.isAffinelyDependent())
				{
					cont=false;
					collision_=false;
					projectionComputed_=true;
				}
				else
#endif
				{

					sp.getClosestSubSimplexGJK(k);
					sp.filter(k);
					s1_+=sup1;
					s2_+=sup2;
					
					if (sp.getType()==CD_Tetrahedron)
					{
						cont=false;
						s1_+=sup1;
						s2_+=sup2;
						collision_=true;

					}	
					else
					{
						
						s_=sp;
						s1_.filter(k);
						s2_.filter(k);

						
					}
				}
			}
		}
	}

#ifdef COUNTER

	std::cout<<"F "<<cnt<<" ; ";
#endif 
#ifdef PENETRATION_DEPTH	
	if (collision_)//Objects are in collision
	{		
		distance_=-depthPair.getPenetrationDepth(v,p1_,p2_,sp,s1_,s2_);
		if (distance_>=0)
		{
			collision_=false;
			
		}
	}
#endif

	return distance_;

	


}

void CD_Pair::setVector(const Vector3 &v)
{
	lastDirection_=v;
}



void CD_Pair::witPoints(Point3 &p1, Point3 &p2)
{
	Point3 proj;
	Vector3& v=lastDirection_;
	
	if (collision_)
	{		
		p1=p1_;
		p2=p2_;
		return;
		
	}		

	switch (s_.getType())
	{
	
	case CD_Triangle:
		{

			{
				if (!projectionComputed_)
				{
					Vector3 S01(s_[1]-s_[2]), S02(s_[0]-s_[2]);

					Scalar a1=S01*s_[0],a2=S01*s_[1],a3=S01*s_[2],a4=S02*s_[0],a5=S02*s_[1],a6=S02*s_[2];


					lambda0_=a2*a6-a3*a5;
					lambda1_=a3*a4-a1*a6;
					lambda2_=a1*a5-a2*a4;
					det_=1/(lambda0_+lambda1_+lambda2_);

					lambda0_*=det_;
					lambda1_*=det_;
					lambda2_*=det_;

					proj=s_[0]*lambda0_+s_[1]*lambda1_+s_[2]*lambda2_;

					v=-proj;

				}

				

				p1_=p1=s1_[0]*lambda0_+s1_[1]*lambda1_+s1_[2]*lambda2_;
				p2_=p2=s2_[0]*lambda0_+s2_[1]*lambda1_+s2_[2]*lambda2_;

			

			}
		

			

			


			
#ifdef SHOW_LAST_SIMLPEX
			glDisable(GL_DEPTH_TEST);
			glColor4d(0,0.5,1,0.5);
			glBegin(GL_TRIANGLES);
			glVertex3d(s1_[0][0],s1_[0][1],s1_[0][2]);
			glVertex3d(s1_[1][0],s1_[1][1],s1_[1][2]);
			glVertex3d(s1_[2][0],s1_[2][1],s1_[2][2]);

			glVertex3d(s2_[0][0],s2_[0][1],s2_[0][2]);
			glVertex3d(s2_[1][0],s2_[1][1],s2_[1][2]);
			glVertex3d(s2_[2][0],s2_[2][1],s2_[2][2]);

		
			glEnd();

			glEnable(GL_DEPTH_TEST);
#endif

			return;
			
		}
		
	case CD_Segment:
		{
			if (!projectionComputed_)
			{
				
			
				Vector3 S01(s_[1]-s_[0]);
	
				lambda1_=-(S01*s_[0]);
				lambda0_=S01*s_[1];

				det_=1/(lambda0_+lambda1_);

				lambda0_*=det_;
				lambda1_*=det_;

				proj=s_[0]*lambda0_+s_[1]*lambda1_;
				
				
				v=-proj;

				
			}

			p1_=p1=s1_[0]*lambda0_+s1_[1]*lambda1_;
			p2_=p2=s2_[0]*lambda0_+s2_[1]*lambda1_;



#ifdef SHOW_LAST_SIMLPEX
			
			glDisable(GL_DEPTH_TEST);
			glColor4d(0,0.5,1,0.5);
			glBegin(GL_LINES);
			glVertex3d(s1_[0][0],s1_[0][1],s1_[0][2]);
			glVertex3d(s1_[1][0],s1_[1][1],s1_[1][2]);
		

			glVertex3d(s2_[0][0],s2_[0][1],s2_[0][2]);
			glVertex3d(s2_[1][0],s2_[1][1],s2_[1][2]);
			
			glEnd();

			glEnable(GL_DEPTH_TEST);


#endif
			return ;
		}
	default:
		{
			p1_=p1=s1_[0];
			p2_=p2=s2_[0]; 

			return ;
		}
		
	
		

	}
}


#undef SHOW_LAST_SIMLPEX
#undef COUNTER