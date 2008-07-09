#include "S_Box.h"
#include <GL/glut.h>

inline short sign(Scalar i)
{
	return (i>0)? 1:-1;
}

S_Box::S_Box(Scalar _a,Scalar _b,Scalar _c):a_(fabs(_a/2)),b_(fabs(_b/2)),c_(fabs(_c/2))
{

}

S_Box::~S_Box(void)
{
}

Point3  S_Box::n_Support(const Vector3& v, int& lastFeature)const
{
	return Point3(sign(v[0])*a_,sign(v[1])*b_,sign(v[2])*c_);
	
}

S_Object::S_ObjectType S_Box::getType() const
{
	return S_Object::TBox;
}

void S_Box::drawGL() const
{


	
	glPushMatrix();
	
	double d[16];

	getTransformationMatrix(d);

	glMultMatrixd(d);

	Point3 x(a_,b_,c_), n(-a_,-b_,-c_);

	glBegin(GL_QUADS);
 
	glNormal3d(0,0,1);
    glVertex3d(n[0],x[1],x[2]);
    glVertex3d(n[0],n[1],x[2]);
    glVertex3d(x[0],n[1],x[2]);
    glVertex3d(x[0],x[1],x[2]);
     
    glNormal3d(0,0,-1);
    glVertex3d(x[0],x[1],n[2]);
    glVertex3d(x[0],n[1],n[2]);
    glVertex3d(n[0],n[1],n[2]);
    glVertex3d(n[0],x[1],n[2]);
  
    glNormal3d(1,0,0);
    glVertex3d(x[0],x[1],x[2]);
    glVertex3d(x[0],n[1],x[2]);
    glVertex3d(x[0],n[1],n[2]);
    glVertex3d(x[0],x[1],n[2]);
 
    glNormal3d(-1,0,0);
    glVertex3d(n[0],x[1],n[2]);
    glVertex3d(n[0],n[1],n[2]);
    glVertex3d(n[0],n[1],x[2]);
    glVertex3d(n[0],x[1],x[2]);
    
    glNormal3d(0,1,0);
    glVertex3d(n[0],x[1],n[2]);
    glVertex3d(n[0],x[1],x[2]);
    glVertex3d(x[0],x[1],x[2]);
    glVertex3d(x[0],x[1],n[2]);  

    glNormal3d(0,-1,0);
    glVertex3d(x[0],n[1],n[2]);
    glVertex3d(x[0],n[1],x[2]);
    glVertex3d(n[0],n[1],x[2]);
    glVertex3d(n[0],n[1],n[2]);
      
    glEnd();

	glPopMatrix();

	

}