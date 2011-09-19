#include <SCD/S_Object/S_Sphere.h>

#ifdef WITH_OPENGL
# if defined __APPLE__
#  include <GLUT/glut.h>
# else
#  include <GL/glut.h>
# endif // __APPLE__
#endif // WITH_OPENGL

using namespace SCD;
S_Sphere::S_Sphere(const Scalar& Rad): radius_(Rad),slices_(100),stacks_(50)
{
}

S_Sphere::~S_Sphere(void)
{
}


Point3 S_Sphere::l_Support(const Vector3& v, int& lastFeature)const
{
	return v*radius_;
}


S_Object::S_ObjectType S_Sphere::getType() const
{
	return S_Object::TSphere;
}

#ifdef WITH_OPENGL
void S_Sphere::drawGLInLocalCordinates()
{
	glutSolidSphere(radius_,100,50);
	
}
#endif
