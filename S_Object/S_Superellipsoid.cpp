#include "S_Superellipsoid.h"
#include <vector>
#include <gl\glut.h>

const double PI=3.14159265358979323;

inline short sign(Scalar i)
{
	return (i>0)? 1:-1;
}

S_Superellipsoid::S_Superellipsoid(Scalar _a, Scalar _b, Scalar _c, Scalar _epsilon1, Scalar _epsilon2):a_(_a),b_(_b),c_(_c),epsilon1_(_epsilon1),epsilon2_(_epsilon2),slices_(100),stacks_(50)
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

S_Superellipsoid::~S_Superellipsoid(void)
{
}



Point3 S_Superellipsoid::n_Support(const Vector3& v, int& lastFeature)const
{
	return v;
}

S_Object::S_ObjectType S_Superellipsoid::getType() const
{
	return S_Object::TSphere;
}

void S_Superellipsoid::drawGL() const
{
	glPushMatrix();
	
	double d[16];

	getTransformationMatrix(d);

	glMultMatrixd(d);

	glCallList(displist_);
	
	glPopMatrix();


}