#include <SCD/S_Object/S_Object.h>

#ifdef WITH_OPENGL
# if defined __APPLE__
#  include <GLUT/glut.h>
# else
#  include <GL/glut.h>
# endif // __APPLE__
#endif // WITH_OPENGL

#include <vector>

using namespace SCD;

const double PI=3.14159265358979323;

S_Object::S_Object():displist_(-1),stacks_(50),slices_(100),mRot_(1,0,0,0,1,0,0,0,1),trans_(0,0,0)
{
	++stamp_;
}

S_Object::~S_Object()
{
}

S_Object::S_ObjectType S_Object::getType() const
{
	return S_Object::TS_Object;
}


void S_Object::setOrientation(const Matrix3x3& rotation)
{
	++stamp_;
	mRot_=rotation;
	
}


void S_Object::setOrientation(const Quaternion quaternion)
{
	++stamp_;
	mRot_.Set(quaternion);
	
	
}


void S_Object::setOrientation(const Scalar& q0,const Scalar& q1,const Scalar& q2,const Scalar& q3)
{
	++stamp_;
	mRot_.Set(q0,q1,q2,q3);
	
	
}

void S_Object::setOrientation(const Scalar& r00,const Scalar& r01,const Scalar& r02,
						   const Scalar& r10,const Scalar& r11,const Scalar& r12,
						   const Scalar& r20,const Scalar& r21,const Scalar& r22)
{
	++stamp_;
	mRot_.Set( r00, r01, r02, 
			  r10, r11, r12, 
			  r20, r21, r22);
	

}

void S_Object::setOrientation(const Scalar* const p)
{
	++stamp_;
	mRot_.Set(p);
	

}

void S_Object::setOrientation(const Scalar& roll, const Scalar& pitch, const Scalar& yaw)
{
	++stamp_;
	Matrix3x3 m(roll, pitch, yaw);
	mRot_=m;
}


void S_Object::setOrientation(const Scalar& s, const Vector3& v)
{
	++stamp_;
	mRot_.Set(s,v);
	
}


void S_Object::setPosition(const Vector3 &v)
{
	++stamp_;
	trans_=v;
	

}

void S_Object::setPosition(const Scalar &x,const Scalar &y, const  Scalar &z)
{
	++stamp_;
	trans_.Set(x,y,z);

	

}


void S_Object::setPosition(const Scalar * const p)
{
	++stamp_;
	trans_.Set(p);

	

}





void S_Object::addRotation(const Matrix3x3& rotation)
{
	++stamp_;
	mRot_*=rotation;
	trans_=rotation*trans_;


}


void S_Object::addRotation(const Quaternion quaternion)
{
	++stamp_;
	Matrix3x3 m(quaternion);
	mRot_=m*mRot_;
	trans_=m*trans_;	
	
}


void S_Object::addRotation(const Scalar& q0,const Scalar& q1,const Scalar& q2,const Scalar& q3)
{
	++stamp_;
	Matrix3x3 m(q0,q1,q2,q3);
	mRot_=m*mRot_;
	trans_=m*trans_;	
}

void S_Object::addRotation(const Scalar& s, const Vector3& v)
{
	++stamp_;
	Matrix3x3 m(s,v);
	mRot_=m*mRot_;
	trans_=m*trans_;
	
}

void S_Object::addRotation(const Scalar& r00,const Scalar& r01,const Scalar& r02,
						   const Scalar& r10,const Scalar& r11,const Scalar& r12,
						   const Scalar& r20,const Scalar& r21,const Scalar& r22)
{
	++stamp_;
	Matrix3x3 m( r00, r01, r02,
				 r10, r11, r12, 
				 r20, r21, r22);
	mRot_=m*mRot_;
	trans_=m*trans_;

	

	
	
}




void S_Object::addRotation(const Scalar* const p)
{

	++stamp_;
	Matrix3x3 m(p);
	mRot_=m*mRot_;
	trans_=m*trans_;
	
}

void S_Object::addRotation(const Scalar& roll, const Scalar& pitch, const Scalar& yaw)
{
	++stamp_;
	Matrix3x3 m(roll, pitch, yaw);
	mRot_=m*mRot_;
	trans_=m*trans_;
	
}


void S_Object::addTranslation(const Vector3& v)
{
	++stamp_;
	trans_+=v;

	
}



void S_Object::addTranslation(const Scalar & x,const Scalar & y,const Scalar & z)
{
	++stamp_;
	trans_+=Vector3(x,y,z);
		
}


void S_Object::addTranslation(const Scalar * const p)
{
	++stamp_;
	trans_+=Vector3(p);
}

void S_Object::addScale(const Scalar & x,const Scalar & y,const Scalar & z)
{
	++stamp_;
	mRot_(0,0)*=x;	mRot_(0,1)*=x;	mRot_(0,2)*=x; trans_(0)*=x;
	mRot_(1,0)*=y;	mRot_(1,1)*=y;	mRot_(1,2)*=y; trans_(1)*=y;
	mRot_(2,0)*=z;	mRot_(2,1)*=z;	mRot_(2,2)*=z; trans_(2)*=z;
		
}

void S_Object::setTransformation(const Matrix4x4& t)
{
	++stamp_;
	setOrientation(t(0,0),t(0,1),t(0,2),
				   t(1,0),t(1,1),t(1,2),
				   t(2,0),t(2,1),t(2,2));
	setPosition(t(0,3),t(1,3),t(2,3));
}

void S_Object::addTransformation(const Matrix4x4& tr)
{
	++stamp_;
	Matrix4x4 k;
	k(0,0)=mRot_(0,0);	k(0,1)=mRot_(0,1);	k(0,2)=mRot_(0,2); k(0,3)=trans_(0);
	k(1,0)=mRot_(1,0);	k(1,1)=mRot_(1,1);	k(1,2)=mRot_(1,2); k(1,3)=trans_(1);
	k(2,0)=mRot_(2,0);	k(2,1)=mRot_(2,1);	k(2,2)=mRot_(2,2); k(2,3)=trans_(2);
															  k(3,3)=1;
	
	Matrix4x4 t(tr*k);

	setOrientation(t(0,0),t(0,1),t(0,2),
				   t(1,0),t(1,1),t(1,2),
				   t(2,0),t(2,1),t(2,2));
	setPosition(t(0,3),t(1,3),t(2,3));

}

void S_Object::resetTransformation()
{
	++stamp_;
	setOrientation(1,0,0,
				   0,1,0,
				   0,0,1);
	setPosition(0,0,0);

}


#ifdef WITH_OPENGL
void S_Object::drawGL()
{

	glPushMatrix();

	double d[16];

	getTransformationMatrix(d);

	glMultMatrixd(d);

	drawGLInLocalCordinates();

	glPopMatrix();
}

void S_Object::drawGLInLocalCordinates()
{
	if (displist_==-1)
	{
		std::vector<Point3> points;
		std::vector<Vector3> normals;
		
		int lastfeature=-1;

		displist_=glGenLists(1);

		points.push_back(l_Support(Vector3(0,0,1),lastfeature));
		normals.push_back(Vector3(0,0,1));

		normals.push_back(Vector3(0,0,-1));
		points.push_back(l_Support(Vector3(0,0,-1),lastfeature));

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

				points.push_back(l_Support(Vector3(c1*c2,c1*s2,s1),lastfeature));

				Vector3 n(c1*c2,c1*s2,s1);

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
#endif //WITH_OPENGL


void S_Object::constructFromFile(const std::string &filename)
{
}

#ifdef WITH_OPENGL
void S_Object::constructFromFileWithGL(const std::string &filename)
{
	constructFromFile(filename);
}
#endif
