#include "S_Box.h"
#include <GL/glut.h>

inline short sign(Scalar i)
{
	return (i>0)? 1:(i<0)?-1:0;
}

S_Box::S_Box(Scalar _a,Scalar _b,Scalar _c):a(fabs(_a/2)),b(fabs(_b/2)),c(fabs(_c/2))
{

}

S_Box::~S_Box(void)
{
}

Point3  S_Box::N_Support(const Vector3& v, int& lastFeature)const
{
	return Point3(sign(v[0])*a,sign(v[1])*b,sign(v[2])*c);
	
}

S_Object::S_ObjectType S_Box::S_GetType() const
{
	return S_Object::TBox;
}

void S_Box::DrawGL() const
{


	
	glPushMatrix();
	
	double d[16];

	GetTransformationMatrix(d);

	glMultMatrixd(d);

	Point3 x(a,b,c), n(-a,-b,-c);

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