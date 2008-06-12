#include "S_Superellipsoid.h"
#include <vector>
#include <gl\glut.h>

const double PI=3.14159265358979323;

inline short sign(Scalar i)
{
	return (i>0)? 1:-1;
}

S_Superellipsoid::S_Superellipsoid(Scalar _a, Scalar _b, Scalar _c, Scalar _epsilon1, Scalar _epsilon2):a(_a),b(_b),c(_c),epsilon1(_epsilon1),epsilon2(_epsilon2),slices(100),stacks(50)
{
	std::vector<Point3> points;
	std::vector<Vector3> normals;

	displist=glGenLists(1);

	points.push_back(Point3(0,0,c));
	normals.push_back(Vector3(0,0,1));

	normals.push_back(Vector3(0,0,-1));
	points.push_back(Point3(0,0,-c));

	Scalar c2,c1,s1,s2;

	Scalar longit=0;

	double p1=PI*2/slices;
	double p2=PI/(stacks-1);


	for (int i=0;i<slices;i++)
	{
		Scalar latt=PI/2-p2;
		for (int j=0;j<stacks-2;j++)
		{
			c1=cos(latt);
			c2=cos(longit);
			s1=sin(latt);
			s2=sin(longit);

			points.push_back(Point3(a*pow(fabs(c1),epsilon1)*pow(fabs(c2),epsilon2)*sign(c1)*sign(c2),
									b*pow(fabs(c1),epsilon1)*pow(fabs(s2),epsilon2)*sign(s2)*sign(c1),
									c*pow(fabs(s1),epsilon1)*sign(s1)));
			

			Vector3 n((1/a)*pow(fabs(c1),2-epsilon1)*pow(fabs(c2),2-epsilon2)*sign(c1)*sign(c2),
					  (1/b)*pow(fabs(c1),2-epsilon1)*pow(fabs(s2),2-epsilon2)*sign(s2)*sign(c1),
					  (1/c)*pow(fabs(s1),2-epsilon1)*sign(s1));

			n.normalize();

			normals.push_back(n);
			
			latt-=p2;
		}
		longit+=p1;

	}



	


	glNewList(displist,GL_COMPILE);
	glBegin(GL_TRIANGLES);
	
	for (int i=0;i<slices;i++)
	{
		
		glNormal3d(normals[0][0],normals[0][1],normals[0][2]);
		glVertex3d(points[0][0],points[0][1],points[0][2]);

		
		glNormal3d(normals[2+(i*(stacks-2))][0],normals[2+(i*(stacks-2))][1],normals[2+(i*(stacks-2))][2]);
		glVertex3d(points[2+(i*(stacks-2))][0],points[2+(i*(stacks-2))][1],points[2+(i*(stacks-2))][2]);


		glNormal3d(normals[2+(((i+1)%(slices))*(stacks-2))][0],normals[2+(((i+1)%(slices))*(stacks-2))][1],normals[2+(((i+1)%(slices))*(stacks-2))][2]);
		glVertex3d(points[2+(((i+1)%(slices))*(stacks-2))][0],points[2+(((i+1)%(slices))*(stacks-2))][1],points[2+(((i+1)%(slices))*(stacks-2))][2]);



		


		
		glNormal3d(normals[1][0],normals[1][1],normals[1][2]);
		glVertex3d(points[1][0],points[1][1],points[1][2]);

		glNormal3d(normals[stacks-1+(((i+1)%(slices))*(stacks-2))][0],normals[stacks-1+(((i+1)%(slices))*(stacks-2))][1],normals[stacks-1+(((i+1)%(slices))*(stacks-2))][2]);
		glVertex3d(points[stacks-1+(((i+1)%(slices))*(stacks-2))][0],points[stacks-1+(((i+1)%(slices))*(stacks-2))][1],points[stacks-1+(((i+1)%(slices))*(stacks-2))][2]);

		glNormal3d(normals[stacks-1+(i*(stacks-2))][0],normals[stacks-1+(i*(stacks-2))][1],normals[stacks-1+(i*(stacks-2))][2]);
		glVertex3d(points[stacks-1+(i*(stacks-2))][0],points[stacks-1+(i*(stacks-2))][1],points[stacks-1+(i*(stacks-2))][2]);






	}

	for (int i=0;i<slices;i++)
	{
		for (int j=0;j<stacks-3;j++)
		{
			glNormal3d(normals[2+(i*(stacks-2))+j][0],normals[2+(i*(stacks-2))+j][1],normals[2+(i*(stacks-2))+j][2]);
			glVertex3d(points[2+(i*(stacks-2))+j][0],points[2+(i*(stacks-2))+j][1],points[2+(i*(stacks-2))+j][2]);

			glNormal3d(normals[2+(i*(stacks-2))+j+1][0],normals[2+(i*(stacks-2))+j+1][1],normals[2+(i*(stacks-2))+j+1][2]);
			glVertex3d(points[2+(i*(stacks-2))+j+1][0],points[2+(i*(stacks-2))+j+1][1],points[2+(i*(stacks-2))+j+1][2]);

			glNormal3d(normals[2+(((i+1)%(slices))*(stacks-2))+j][0],normals[2+(((i+1)%(slices))*(stacks-2))+j][1],normals[2+(((i+1)%(slices))*(stacks-2))+j][2]);
			glVertex3d(points[2+(((i+1)%(slices))*(stacks-2))+j][0],points[2+(((i+1)%(slices))*(stacks-2))+j][1],points[2+(((i+1)%(slices))*(stacks-2))+j][2]);

			
			glNormal3d(normals[stacks-1+(i*(stacks-2))-j][0],normals[stacks-1+(i*(stacks-2))-j][1],normals[stacks-1+(i*(stacks-2))-j][2]);
			glVertex3d(points[stacks-1+(i*(stacks-2))-j][0],points[stacks-1+(i*(stacks-2))-j][1],points[stacks-1+(i*(stacks-2))-j][2]);

			glNormal3d(normals[stacks-1+(((i+1)%(slices))*(stacks-2))-j][0],normals[stacks-1+(((i+1)%(slices))*(stacks-2))-j][1],normals[stacks-1+(((i+1)%(slices))*(stacks-2))-j][2]);
			glVertex3d(points[stacks-1+(((i+1)%(slices))*(stacks-2))-j][0],points[stacks-1+(((i+1)%(slices))*(stacks-2))-j][1],points[stacks-1+(((i+1)%(slices))*(stacks-2))-j][2]);

			glNormal3d(normals[stacks-1+(((i+1)%(slices))*(stacks-2))-j-1][0],normals[stacks-1+(((i+1)%(slices))*(stacks-2))-j-1][1],normals[stacks-1+(((i+1)%(slices))*(stacks-2))-j-1][2]);
			glVertex3d(points[stacks-1+(((i+1)%(slices))*(stacks-2))-j-1][0],points[stacks-1+(((i+1)%(slices))*(stacks-2))-j-1][1],points[stacks-1+(((i+1)%(slices))*(stacks-2))-j-1][2]);


		

		}


	}


	glEnd();

	
	

	glEndList();




}

S_Superellipsoid::~S_Superellipsoid(void)
{
}



Point3 S_Superellipsoid::N_Support(const Vector3& v, int& lastFeature)const
{
	return v;
}

S_Object::S_ObjectType S_Superellipsoid::S_GetType() const
{
	return S_Object::TSphere;
}

void S_Superellipsoid::DrawGL() const
{
	glPushMatrix();
	
	double d[16];

	GetTransformationMatrix(d);

	glMultMatrixd(d);

	glCallList(displist);
	
	glPopMatrix();


}