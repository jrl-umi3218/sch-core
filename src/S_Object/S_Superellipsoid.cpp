#include <SCD/S_Object/S_Superellipsoid.h>
#include <vector>

#ifdef WITH_OPENGL
# if defined __APPLE__
#  include <GLUT/glut.h>
# else
#  include <GL/glut.h>
# endif // __APPLE__
#endif // WITH_OPENGL

const double PI=3.14159265358979323;

using namespace SCD;

inline short sign(Scalar i)
{
	return (i>0)? 1:-1;
}

S_Superellipsoid::S_Superellipsoid(Scalar _a, Scalar _b, Scalar _c, Scalar _epsilon1, Scalar _epsilon2):a_(_a),b_(_b),c_(_c),epsilon1_(_epsilon1),epsilon2_(_epsilon2),
displist_(-1),
_2_e1on2((2-_epsilon1)/2),_2_e2on2((2-_epsilon2)/2),_2on2_e1(2/(2-_epsilon1)),_2on2_e2(2/(2-_epsilon2))
{
	slices_ = 100;
	stacks_ = 50;

	if (epsilon1_>2||epsilon2_>2||
		epsilon1_<0||epsilon2_<0)
	{
		std::cout<<"SUPERELLIPSOIDS EPSILON1 AND EPSILON2 MUST BE BETWEEN 0 AND 2";
		throw;
	}





}

S_Superellipsoid::~S_Superellipsoid(void)
{
}



Point3 S_Superellipsoid::l_Support(const Vector3& v, int& lastFeature)const
{

	Scalar anx,bny,cnz;

	anx=a_*fabs(v[0]);
	bny=b_*fabs(v[1]);
	cnz=c_*fabs(v[2]);

	Scalar tp1,tp2,cp2,sp2,sp2e,cp2e,spe,cpe,
		   tt1,tt2,ct2,st2,st2e,ct2e,ste,cte;

	
	if (anx==0)
	{
		if (bny==0)
		{
			return Point3(0,0,c_*sign(v[2]));
		}
		else
		{
			cp2=0;
			sp2=1;
			cp2e=0;
			sp2e=1;		
			cpe=0;
			spe=1;
			tt1=cnz/bny;
		}
	}
	else
	{
		tp1=bny/anx;
		tp2=pow(tp1,_2on2_e2);
		cp2=1/(tp2+1);

		if (cp2==1)
		{
			sp2=0;
			cp2e=1;
			sp2e=0;		
			cpe=1;
			spe=0;
			tt1=cnz/anx;
		}
		else
		{
			
			sp2=1-cp2;
			sp2e=pow(sp2,_2_e2on2);
			cp2e=sp2e/tp1;
			spe=sp2/sp2e;
			cpe=cp2/cp2e;
			tt1=cnz*sp2e/bny;
		}
	}
	
	
	tt2=pow(tt1,_2on2_e1);
	ct2=1/(tt2+1);

	if (ct2==1)
	{
		return Point3(a_*cpe*sign(v[0]),b_*spe*sign(v[1]),0);
	}
	else
	{
		
		st2=1-ct2;
		st2e=pow(st2,_2_e1on2);
		ct2e=st2e/tt1;
		ste=st2/st2e;
		cte=ct2/ct2e;
		return Point3(a_*cte*cpe*sign(v[0]),
					  b_*cte*spe*sign(v[1]),
					  c_*ste*sign(v[2]));
	}




}

S_Object::S_ObjectType S_Superellipsoid::getType() const
{
	return S_Object::TSphere;
}


#ifdef WITH_OPENGL
void S_Superellipsoid::drawGLInLocalCordinates()
{

	if (displist_==-1)
	{
		std::vector<Point3> points;
		std::vector<Vector3> normals;

		displist_=glGenLists(1);

		points.push_back(Point3(0,0,c_));
		normals.push_back(Vector3(0,0,1));

		normals.push_back(Vector3(0,0,-1));
		points.push_back(Point3(0,0,-c_));

		Scalar c2,c1,s1,s2;

		Scalar longit=0;

		double p1=PI*2/slices_;
		double p2=PI/(stacks_-1);


		for (int i=0;i<slices_;i++)
		{
			Scalar latt=PI/2-p2;
			for (int j=0;j<stacks_-2;j++)
			{
				c1=cos(latt);
				c2=cos(longit);
				s1=sin(latt);
				s2=sin(longit);

				points.push_back(Point3(a_*pow(fabs(c1),epsilon1_)*pow(fabs(c2),epsilon2_)*sign(c1)*sign(c2),
					b_*pow(fabs(c1),epsilon1_)*pow(fabs(s2),epsilon2_)*sign(s2)*sign(c1),
					c_*pow(fabs(s1),epsilon1_)*sign(s1)));


				Vector3 n((1/a_)*pow(fabs(c1),2-epsilon1_)*pow(fabs(c2),2-epsilon2_)*sign(c1)*sign(c2),
					(1/b_)*pow(fabs(c1),2-epsilon1_)*pow(fabs(s2),2-epsilon2_)*sign(s2)*sign(c1),
					(1/c_)*pow(fabs(s1),2-epsilon1_)*sign(s1));
				
				n.normalize();

				normals.push_back(n);

				latt-=p2;
			}
			longit+=p1;

		}






		glNewList(displist_,GL_COMPILE);
		glBegin(GL_TRIANGLES);

		for (int i=0;i<slices_;i++)
		{

			glNormal3d(normals[0][0],normals[0][1],normals[0][2]);
			glVertex3d(points[0][0],points[0][1],points[0][2]);


			glNormal3d(normals[2+(i*(stacks_-2))][0],normals[2+(i*(stacks_-2))][1],normals[2+(i*(stacks_-2))][2]);
			glVertex3d(points[2+(i*(stacks_-2))][0],points[2+(i*(stacks_-2))][1],points[2+(i*(stacks_-2))][2]);


			glNormal3d(normals[2+(((i+1)%(slices_))*(stacks_-2))][0],normals[2+(((i+1)%(slices_))*(stacks_-2))][1],normals[2+(((i+1)%(slices_))*(stacks_-2))][2]);
			glVertex3d(points[2+(((i+1)%(slices_))*(stacks_-2))][0],points[2+(((i+1)%(slices_))*(stacks_-2))][1],points[2+(((i+1)%(slices_))*(stacks_-2))][2]);







			glNormal3d(normals[1][0],normals[1][1],normals[1][2]);
			glVertex3d(points[1][0],points[1][1],points[1][2]);

			glNormal3d(normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))][0],normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))][1],normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))][2]);
			glVertex3d(points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))][0],points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))][1],points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))][2]);

			glNormal3d(normals[stacks_-1+(i*(stacks_-2))][0],normals[stacks_-1+(i*(stacks_-2))][1],normals[stacks_-1+(i*(stacks_-2))][2]);
			glVertex3d(points[stacks_-1+(i*(stacks_-2))][0],points[stacks_-1+(i*(stacks_-2))][1],points[stacks_-1+(i*(stacks_-2))][2]);






		}

		for (int i=0;i<slices_;i++)
		{
			for (int j=0;j<stacks_-3;j++)
			{
				glNormal3d(normals[2+(i*(stacks_-2))+j][0],normals[2+(i*(stacks_-2))+j][1],normals[2+(i*(stacks_-2))+j][2]);
				glVertex3d(points[2+(i*(stacks_-2))+j][0],points[2+(i*(stacks_-2))+j][1],points[2+(i*(stacks_-2))+j][2]);

				glNormal3d(normals[2+(i*(stacks_-2))+j+1][0],normals[2+(i*(stacks_-2))+j+1][1],normals[2+(i*(stacks_-2))+j+1][2]);
				glVertex3d(points[2+(i*(stacks_-2))+j+1][0],points[2+(i*(stacks_-2))+j+1][1],points[2+(i*(stacks_-2))+j+1][2]);

				glNormal3d(normals[2+(((i+1)%(slices_))*(stacks_-2))+j][0],normals[2+(((i+1)%(slices_))*(stacks_-2))+j][1],normals[2+(((i+1)%(slices_))*(stacks_-2))+j][2]);
				glVertex3d(points[2+(((i+1)%(slices_))*(stacks_-2))+j][0],points[2+(((i+1)%(slices_))*(stacks_-2))+j][1],points[2+(((i+1)%(slices_))*(stacks_-2))+j][2]);


				glNormal3d(normals[stacks_-1+(i*(stacks_-2))-j][0],normals[stacks_-1+(i*(stacks_-2))-j][1],normals[stacks_-1+(i*(stacks_-2))-j][2]);
				glVertex3d(points[stacks_-1+(i*(stacks_-2))-j][0],points[stacks_-1+(i*(stacks_-2))-j][1],points[stacks_-1+(i*(stacks_-2))-j][2]);

				glNormal3d(normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j][0],normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j][1],normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j][2]);
				glVertex3d(points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j][0],points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j][1],points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j][2]);

				glNormal3d(normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j-1][0],normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j-1][1],normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j-1][2]);
				glVertex3d(points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j-1][0],points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j-1][1],points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j-1][2]);




			}


		}


		glEnd();




		glEndList();	


	}

	glCallList(displist_);


}
#endif // WITH_OPENGL
