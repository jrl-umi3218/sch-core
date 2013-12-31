#include "STPBV_gl.h"
#include <SCD/STP-BV/STP_BV.h>

#if defined __APPLE__
# include <GLUT/glut.h>
#else
# include <GL/glut.h>
#endif // __APPLE__

using namespace SCD;

STP_BV_GL::STP_BV_GL(STP_BV * obj)
: S_Object_GL(obj)
, stpbv_(obj)
{
	computeDisplayList();
}

void STP_BV_GL::drawGLInLocalCordinates() const
{
	for(unsigned i =0; i< displayList_.size(); ++i)
	{
		glPushMatrix();
		glCallList(displayList_[i]);
		glPopMatrix();
	}
}

void STP_BV_GL::computeDisplayList()
{
	const std::vector<Geometry> & geometries = stpbv_->getGeometries();
	for(unsigned i = 0; i<geometries.size(); ++i)
	{
		const Geometry & geom = geometries[i];

		GLuint listID = glGenLists(1);
		glNewList(listID, GL_COMPILE);

		glPushMatrix();
		glColor3f(geom.color[0], geom.color[1], geom.color[2]);
		glTranslatef(geom.center[0], geom.center[1], geom.center[2]);
		switch(geom.type)
		{
		case(Geometry::LINE):
		{
			glBegin(GL_LINES);
			for(unsigned j=0; j<geom.vertex.size(); ++j)
			{
//				glVertex3f(geom.vertex[j][0], geom.vertex[j][1], geom.vertex[j][2]);
//				std::cout << geom.vertex[j] << std::endl;
			}
			glEnd();
			break;
		}
		case(Geometry::TRIANGLE):
		{
			glBegin(GL_TRIANGLES);
			if(geom.vertex.size() == geom.normal.size())
			{
				for(unsigned j=0; j<geom.vertex.size(); ++j)
				{
					glNormal3f(geom.normal[j][0], geom.normal[j][1], geom.normal[j][2]);
					glVertex3f(geom.vertex[j][0], geom.vertex[j][1], geom.vertex[j][2]);
				}
			}
			else if(geom.vertex.size() == geom.normal.size() *3)
			{
				for(unsigned j=0; j<geom.normal.size(); ++j)
				{
					glNormal3f(geom.normal[j][0], geom.normal[j][1], geom.normal[j][2]);
					for(unsigned k=0; k<3; ++k)
						glVertex3f(geom.vertex[3*j+k][0], geom.vertex[3*j+k][1], geom.vertex[3*j+k][2]);
				}
			}
			else if(geom.normal.size() == 0)
			{
				for(unsigned j=0; j<geom.vertex.size(); ++j)
				{
					glVertex3f(geom.vertex[j][0], geom.vertex[j][1], geom.vertex[j][2]);
				}
			}
			else
			{
			}
			glEnd();
			break;
		}
		case(Geometry::SPHERE):
		{
			glutSolidSphere(geom.radius, 20, 20);
			break;
		}
		}
		glPopMatrix();
		glEndList();
		displayList_.push_back(listID);
	}
}
