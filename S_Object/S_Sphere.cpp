

#include "S_Sphere.h"
#include <GL/glut.h>


S_Sphere::S_Sphere(const Scalar& Rad): radius(Rad),slices(100),stacks(50)
{
}

S_Sphere::~S_Sphere(void)
{
}


Point3 S_Sphere::N_Support(const Vector3& v, int& lastFeature)const
{
	return v*radius;
}

S_Object::S_ObjectType S_Sphere::S_GetType() const
{
	return S_Object::TSphere;
}

void S_Sphere::DrawGL() const
{
	glPushMatrix();
	
	double d[16];

	GetTransformationMatrix(d);

	glMultMatrixd(d);

	glutSolidSphere(radius,100,50);
	
	glPopMatrix();


}

