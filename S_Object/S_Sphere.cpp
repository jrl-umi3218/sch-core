

#include "S_Sphere.h"
#include <GL/glut.h>


S_Sphere::S_Sphere(const Scalar& Rad): radius_(Rad),slices_(100),stacks_(50)
{
}

S_Sphere::~S_Sphere(void)
{
}


Point3 S_Sphere::n_Support(const Vector3& v, int& lastFeature)const
{
	return v*radius_;
}

S_Object::S_ObjectType S_Sphere::getType() const
{
	return S_Object::TSphere;
}

void S_Sphere::drawGL() const
{
	glPushMatrix();
	
	double d[16];

	getTransformationMatrix(d);

	glMultMatrixd(d);

	glutSolidSphere(radius_,100,50);
	
	glPopMatrix();


}

