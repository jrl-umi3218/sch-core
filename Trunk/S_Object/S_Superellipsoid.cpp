#include "S_Superellipsoid.h"
#include <vector>
#include <gl\glut.h>

const double PI=3.14159265358979323;

using namespace SCD;

inline short sign(Scalar i)
{
	return (i>0)? 1:-1;
}

S_Superellipsoid::S_Superellipsoid(Scalar _a, Scalar _b, Scalar _c, Scalar _epsilon1, Scalar _epsilon2):a_(_a),b_(_b),c_(_c),epsilon1_(_epsilon1),epsilon2_(_epsilon2),slices_(100),stacks_(50), displist_(-1)
{





}

S_Superellipsoid::~S_Superellipsoid(void)
{
}



Point3 S_Superellipsoid::n_Support(const Vector3& v, int& lastFeature)const
{
	Scalar N,D,teta,phi,cp;
	
	if (v[0]==0)
	{
		phi = PI/2.0;
		cp=0;
		N = v[2]*c_;
		D = v[1]*b_;
		teta = atan(pow(fabs(N/D), (1/(2-epsilon1_))));

	}
	else
	{

		
		N = v[1]*b_;
		D = v[0]*a_;
		phi = atan(pow(fabs(N/D), (1/(2-epsilon2_))));
		//D = N / power(abs(sin(v)),2-e(2));

		cp = fabs(cos(phi));

		D /=  pow(cp,2-epsilon2_);

		N = v[2]*c_;

		teta = atan(pow(fabs(N/D), (1/(2-epsilon1_))));
	}

	// Computing the support point

	Scalar st,sp,ct,sx,sy,sz,ctep;
	
	st = fabs(sin(teta));
	ct = fabs(cos(teta));
	
	sp = fabs(sin(phi));


	sx = sign(v[0]);
	sy = sign(v[1]);
	sz = sign(v[2]);

	ctep=pow(ct,epsilon1_);

	return Point3( a_ * sx * ctep * pow(cp,epsilon2_),
				   b_ * sy * ctep * pow(sp,epsilon2_),
				   c_ * sz * pow(st,epsilon1_));

}

S_Object::S_ObjectType S_Superellipsoid::getType() const
{
	return S_Object::TSphere;
}


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