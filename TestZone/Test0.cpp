#ifdef __TEST_0__


#include "includes.h"



#include <iostream>
#include <sstream>
#include <ios>
#include <fstream>
#include <vector>

#include <GL/glut.h>
#include <time.h>
#include <string>



/*************************
void main()
{
	int i;


	S_Box s2(22, 20, 3);
	S_Box s1(24, 23, 5);

	s1.SetPosition(24,0,0);

	s2.SetPosition(0,0,0);

	CD_Pair p(&s1,&s2);
	
	Point3 a,b;
	
	Scalar d,dp;
	
	d=p.GetClosestPoints(a,b);

	
	

	std::cin>>i;
}
***************************/


#define DISP_FILL
//#define DISP_LINE
#define DISPLAY_BV
//#define DISPLAY_VVR
#define DISPLAY_TEST
#define DO_TEST
//#define OUTPUT_FILE
//#define FARTHESTNEIGHBOUR
//#define NAIVE
#define STATISTICS




const Scalar SPACE_SIZE = 0.1f;  // Size of the space 
const Scalar SIZE_RATIO = 1.0e-0;  // Difference in size 
const Scalar ROTSTEPK   = 3.0f;  // Displacement of camera in degrees
const Scalar TRANSSTEPK = 0.005f;
const Scalar ROTSTEPM   = 0.3f;  // Displacement of camera in degrees
const Scalar TRANSSTEPM = 0.003f;

const Scalar INCR_TRANS = 0.0025f;
const Scalar INCR_ROT = 0.01f;


const Vector3 globalX(1,0,0);
const Vector3 globalY(0,1,0);
const Vector3 globalZ(0,0,1);

const double AnimationSpeed=0.0030;
const double AnimationScale=2;
const long AnimationBegin=0;
const long RandomTestEnd=430000000;
const long AnimationEnd=10000;
const double AngleSteps=360;
const double PI=3.1415926535897932384626;




Vector3 camAxeX(1,0,0);
Vector3 camAxeY(0,1,0);
Vector3 camAxeZ(0,0,1);



bool cameraMode = false;

#ifdef SCALING_ON

const Scalar SCALE_BOTTOM = 0.5f; // Lowest scale factor
const Scalar SCALE_RANGE  = 2.0f; // Range for scaling 
									 //	[SCALE_BOTTOM, SCALE_BOTTOM + SCALE_RANGE ]
#endif

enum transformationType
{
	LOCAL_TRANSLATION_X,
	LOCAL_TRANSLATION_Y,
	LOCAL_TRANSLATION_Z,
	LOCAL_TRANSLATION_XY,
	LOCAL_TRANSLATION_YZ,
	LOCAL_TRANSLATION_ZX,
	GLOBAL_TRANSLATION_X,
	GLOBAL_TRANSLATION_Y,
	GLOBAL_TRANSLATION_Z,
	GLOBAL_TRANSLATION_XY,
	GLOBAL_TRANSLATION_YZ,
	GLOBAL_TRANSLATION_ZX,
	CAM_TRANSLATION_X,
	CAM_TRANSLATION_Y,
	CAM_TRANSLATION_Z,
	CAM_TRANSLATION_XY,
	CAM_TRANSLATION_YZ,
	CAM_TRANSLATION_ZX,
	LOCAL_ROTATION_X,
	LOCAL_ROTATION_Y,
	LOCAL_ROTATION_Z,
	LOCAL_ROTATION_XY,
	LOCAL_ROTATION_YZ,
	LOCAL_ROTATION_ZX,
	GLOBAL_ROTATION_X,
	GLOBAL_ROTATION_Y,
	GLOBAL_ROTATION_Z,
	GLOBAL_ROTATION_XY,
	GLOBAL_ROTATION_YZ,
	GLOBAL_ROTATION_ZX,
	CAM_ROTATION_X,
	CAM_ROTATION_Y,
	CAM_ROTATION_Z,
	CAM_ROTATION_XY,
	CAM_ROTATION_YZ,
	CAM_ROTATION_ZX,
	NONE
};


void multMatVect(double m[16], const Vector3& v, Vector3& out)
{
	out[0] = m[0]*v[0] + m[4]*v[1] + m[8]*v[2];
	out[1] = m[1]*v[0] + m[5]*v[1] + m[9]*v[2];
	out[2] = m[2]*v[0] + m[6]*v[1] + m[10]*v[2];
}



float ReciprocalSqrt( float x ) { 
	long i; 
	float y, r; 
	y = x * 0.5f; 
	i = *(long *)( &x ); 
	i = 0x5f3759df - ( i >> 1 ); 
	r = *(float *)( &i ); 
	r = r * ( 1.5f - r * r * y ); 
	return r; 
} 
void ConvertJointMatsToJointQuats(const double* m, Quaternion& q, Vector3& t) 
{ 
	if ( m[0 * 4 + 0] + m[1 * 4 + 1] + m[2 * 4 + 2] > 0.0 ) { 
		float t = + m[0 * 4 + 0] + m[1 * 4 + 1] + m[2 * 4 + 2] + 1.0; 
		float s = ReciprocalSqrt( t ) * 0.5; 
		q[3] = s * t; 
		q[2] = ( m[1 * 4 + 0] - m[0 * 4 + 1] ) * s; 
		q[1] = ( m[0 * 4 + 2] - m[2 * 4 + 0] ) * s; 
		q[0] = ( m[2 * 4 + 1] - m[1 * 4 + 2] ) * s; 
	} else if ( m[0 * 4 + 0] > m[1 * 4 + 1] && m[0 * 4 + 0] > m[2 * 4 + 2] ) { 
		float t = + m[0 * 4 + 0] - m[1 * 4 + 1] - m[2 * 4 + 2] + 1.0; 
		float s = ReciprocalSqrt( t ) * 0.5f; 
		q[0] = s * t; 
		q[1] = ( m[1 * 4 + 0] + m[0 * 4 + 1] ) * s;  

		q[2] = ( m[0 * 4 + 2] + m[2 * 4 + 0] ) * s; 
		q[3] = ( m[2 * 4 + 1] - m[1 * 4 + 2] ) * s; 
	} else if ( m[1 * 4 + 1] > m[2 * 4 + 2] ) { 
		float t = - m[0 * 4 + 0] + m[1 * 4 + 1] - m[2 * 4 + 2] + 1.0; 
		float s = ReciprocalSqrt( t ) * 0.5; 
		q[1] = s * t; 
		q[0] = ( m[1 * 4 + 0] + m[0 * 4 + 1] ) * s; 
		q[3] = ( m[0 * 4 + 2] - m[2 * 4 + 0] ) * s; 
		q[2] = ( m[2 * 4 + 1] + m[1 * 4 + 2] ) * s; 
	} else { 
		float t = - m[0 * 4 + 0] - m[1 * 4 + 1] + m[2 * 4 + 2] + 1.0; 
		float s = ReciprocalSqrt( t ) * 0.5; 
		q[2] = s * t; 
		q[3] = ( m[1 * 4 + 0] - m[0 * 4 + 1] ) * s; 
		q[0] = ( m[0 * 4 + 2] + m[2 * 4 + 0] ) * s; 
		q[1] = ( m[2 * 4 + 1] + m[1 * 4 + 2] ) * s; 
	} 
	t[0] = m[3 * 4 + 0]; 
	t[1] = m[3 * 4 + 1]; 
	t[2] = m[3 * 4 + 2]; 
}  


typedef struct s_DisplayObject
{


	S_Object * _obj;

	Vector3 position;
	Quaternion orientation;

	Vector3 oldPosition;
	Quaternion oldOrientation;

	Vector3 additionalPosition;
	Quaternion additionalOrientation;

	Vector3 localX;
	Vector3 localY;
	Vector3 localZ;

	double tr1;
	double tr2;

	int transType;


	void resetAdditionalTransformation(void)
	{
		tr1 = tr2 = 0;
	}

	void turnAroundLocalX(double angle)
	{
	}

	void turnAroundLocalY(double angle)
	{
	}

	void turnAroundLocalZ(double angle)
	{
	}

	void turnAroundGlobalX(double angle)
	{
	}

	void turnAroundGlobalY(double angle)
	{
	}

	void turnAroundGlobalZ(double angle)
	{
	}

	void moveAlongLocalX(double dist)
	{
	}

	void moveAlongLocalY(double dist)
	{
	}

	void moveAlongLocalZ(double dist)
	{
	}

	void moveAlongGlobalX(double dist)
	{
	}

	void moveAlongGlobalY(double dist)
	{
	}

	void moveAlongGlobalZ(double dist)
	{
	}

	void getTransfo(Vector3& t, Quaternion& r)
	{
		t = oldPosition;
		r = oldOrientation;
	}

	void computeTransformation(void)
	{
		bool trans;
		bool twoTrans;
		const Vector3* axe;
		const Vector3* axe2;
		switch (transType)
		{
		case LOCAL_TRANSLATION_X:
			trans = true;
			twoTrans = false;
			axe = &localX;
			break;
		case LOCAL_TRANSLATION_Y:
			trans = true;
			twoTrans = false;
			axe = &localY;
			break;
		case LOCAL_TRANSLATION_Z:
			trans = true;
			twoTrans = false;
			axe = &localZ;
			break;
		case LOCAL_TRANSLATION_XY:
			trans = true;
			twoTrans = true;
			axe = &localX;
			axe2 = &localY;
			break;
		case LOCAL_TRANSLATION_YZ:
			trans = true;
			twoTrans = true;
			axe = &localY;
			axe2 = &localZ;
			break;
		case LOCAL_TRANSLATION_ZX:
			trans = true;
			twoTrans = true;
			axe = &localZ;
			axe2 = &localX;
			break;
		case GLOBAL_TRANSLATION_X:
			trans = true;
			twoTrans = false;
			axe = &globalX;
			break;
		case GLOBAL_TRANSLATION_Y:
			trans = true;
			twoTrans = false;
			axe = &globalY;
			break;
		case GLOBAL_TRANSLATION_Z:
			trans = true;
			twoTrans = false;
			axe = &globalZ;
			break;
		case GLOBAL_TRANSLATION_XY:
			trans = true;
			twoTrans = true;
			axe = &globalX;
			axe2 = &globalY;
			break;
		case GLOBAL_TRANSLATION_YZ:
			trans = true;
			twoTrans = true;
			axe = &globalY;
			axe2 = &globalZ;
			break;
		case GLOBAL_TRANSLATION_ZX:
			trans = true;
			twoTrans = true;
			axe = &globalZ;
			axe2 = &globalX;
			break;
		case CAM_TRANSLATION_X:
			trans = true;
			twoTrans = false;
			axe = &camAxeX;
			break;
		case CAM_TRANSLATION_Y:
			trans = true;
			twoTrans = false;
			axe = &camAxeY;
			break;
		case CAM_TRANSLATION_Z:
			trans = true;
			twoTrans = false;
			axe = &camAxeZ;
			break;
		case CAM_TRANSLATION_XY:
			trans = true;
			twoTrans = true;
			axe = &camAxeX;
			axe2 = &camAxeY;
			break;
		case CAM_TRANSLATION_YZ:
			trans = true;
			twoTrans = true;
			axe = &camAxeY;
			axe2 = &camAxeZ;
			break;
		case CAM_TRANSLATION_ZX:
			trans = true;
			twoTrans = true;
			axe = &camAxeZ;
			axe2 = &camAxeX;
			break;
		case LOCAL_ROTATION_X:
			trans = false;
			twoTrans = false;
			axe = &localX;
			break;
		case LOCAL_ROTATION_Y:
			trans = false;
			twoTrans = false;
			axe = &localY;
			break;
		case LOCAL_ROTATION_Z:
			trans = false;
			twoTrans = false;
			axe = &localZ;
			break;
		case LOCAL_ROTATION_XY:
			trans = false;
			twoTrans = true;
			axe = &localX;
			axe2 = &localY;
			break;
		case LOCAL_ROTATION_YZ:
			trans = false;
			twoTrans = true;
			axe = &localY;
			axe2 = &localZ;
			break;
		case LOCAL_ROTATION_ZX:
			trans = false;
			twoTrans = true;
			axe = &localZ;
			axe2 = &localX;
			break;
		case GLOBAL_ROTATION_X:
			trans = false;
			twoTrans = false;
			axe = &globalX;
			break;
		case GLOBAL_ROTATION_Y:
			trans = false;
			twoTrans = false;
			axe = &globalY;
			break;
		case GLOBAL_ROTATION_Z:
			trans = false;
			twoTrans = false;
			axe = &globalZ;
			break;
		case GLOBAL_ROTATION_XY:
			trans = false;
			twoTrans = true;
			axe = &globalX;
			axe2 = &globalY;
			break;
		case GLOBAL_ROTATION_YZ:
			trans = false;
			twoTrans = true;
			axe = &globalX;
			axe2 = &globalY;
			break;
		case GLOBAL_ROTATION_ZX:
			trans = false;
			twoTrans = true;
			axe = &globalX;
			axe2 = &globalY;
			break;
		case CAM_ROTATION_X:
			trans = false;
			twoTrans = false;
			axe = &camAxeX;
			break;
		case CAM_ROTATION_Y:
			trans = false;
			twoTrans = false;
			axe = &camAxeY;
			break;
		case CAM_ROTATION_Z:
			trans = false;
			twoTrans = false;
			axe = &camAxeZ;
			break;
		case CAM_ROTATION_XY:
			trans = false;
			twoTrans = true;
			axe = &camAxeX;
			axe2 = &camAxeY;
			break;
		case CAM_ROTATION_YZ:
			trans = false;
			twoTrans = true;
			axe = &camAxeY;
			axe2 = &camAxeZ;
			break;
		case CAM_ROTATION_ZX:
			trans = false;
			twoTrans = true;
			axe = &camAxeZ;
			axe2 = &camAxeX;
			break;
		case NONE:
			return;
		}

		std::cout << tr1 << std::endl;
		std::cout << tr2 << std::endl;

		if (trans)
		{
			position = oldPosition +   *axe * tr1;
			if (twoTrans)
				position = position + *axe2 * tr2 ;
		}
		else
		{
			
				orientation = Quaternion(*axe2, tr2)*Quaternion(*axe, tr1);
				double m[16];
				getInvMatrix(m);

				orientation = oldOrientation * Quaternion(*axe, -tr1);
				if (twoTrans)
					orientation = orientation * Quaternion(*axe2, -tr2);

				Vector3 vr = oldPosition;
				multMatVect(m, vr, position);
				
				std::cout << position;
			
		}
		if (_obj)
		{
			_obj->AddTranslation(position);
			_obj->AddRotation(orientation);
		}
	}

	void getMatrix(double* mat)
	{
		mat[0] = 1 - 2 * orientation[1] * orientation[1] - 2 * orientation[2] * orientation[2];
		mat[5] = 1 - 2 * orientation[0] * orientation[0] - 2 * orientation[2] * orientation[2];
		mat[10] = 1 - 2 * orientation[1] * orientation[1] - 2 * orientation[0] * orientation[0];
		mat[1] = 2 * orientation[0] * orientation[1] + 2 * orientation[2] * orientation[3];
		mat[4] = 2 * orientation[0] * orientation[1] - 2 * orientation[2] * orientation[3];
		mat[2] = 2 * orientation[0] * orientation[2] - 2 * orientation[1] * orientation[3];
		mat[8] = 2 * orientation[0] * orientation[2] + 2 * orientation[1] * orientation[3];
		mat[6] = 2 * orientation[1] * orientation[2] + 2 * orientation[0] * orientation[3];
		mat[9] = 2 * orientation[1] * orientation[2] - 2 * orientation[2] * orientation[3];
		mat[3] = mat[7] = mat[11] = 0.0;
		mat[12] = position[0];
		mat[13] = position[1];
		mat[14] = position[2];
		mat[15] = 1.0;
	}

	void getInvMatrix(double* mat)
	{
		mat[0] = 1 - 2 * orientation[1] * orientation[1] - 2 * orientation[2] * orientation[2];
		mat[5] = 1 - 2 * orientation[0] * orientation[0] - 2 * orientation[2] * orientation[2];
		mat[10] = 1 - 2 * orientation[1] * orientation[1] - 2 * orientation[0] * orientation[0];
		mat[4] = 2 * orientation[0] * orientation[1] + 2 * orientation[2] * orientation[3];
		mat[1] = 2 * orientation[0] * orientation[1] - 2 * orientation[2] * orientation[3];
		mat[8] = 2 * orientation[0] * orientation[2] - 2 * orientation[1] * orientation[3];
		mat[2] = 2 * orientation[0] * orientation[2] + 2 * orientation[1] * orientation[3];
		mat[9] = 2 * orientation[1] * orientation[2] + 2 * orientation[0] * orientation[3];
		mat[6] = 2 * orientation[1] * orientation[2] - 2 * orientation[0] * orientation[3];
		mat[3] = mat[7] = mat[11] = 0.0;
		mat[12] = -(mat[0] * position[0] + mat[4]*position[1] + mat[8]*position[2]);
		mat[13] = -(mat[1] * position[0] + mat[5]*position[1] + mat[9]*position[2]);
		mat[14] = -(mat[2] * position[0] + mat[6]*position[1] + mat[10]*position[2]);
		mat[15] = 1.0;
	}

	void updateAxis(void)
	{
		
	}

	void collapseTransformation(void)
	{
		computeTransformation();
		resetAdditionalTransformation();
		oldOrientation = orientation;
		oldPosition = position;
		updateAxis();
	}

	void drawLocalAxes(void)
	{
		Vector3 o(0,0,0);
		glColor3d(2.5,0,0);
		glBegin(GL_LINES);
			glVertex3d(o[0],o[1],o[2]);
			glVertex3d(localX[0],localX[1],localX[2]);
		glEnd();
		glColor3d(0,2.5,0);
		glBegin(GL_LINES);
			glVertex3d(o[0],o[1],o[2]);
			glVertex3d(localY[0],localY[1],localY[2]);
		glEnd();
		glColor3d(0,0,2.5);
		glBegin(GL_LINES);
			glVertex3d(o[0],o[1],o[2]);
			glVertex3d(localZ[0],localZ[1],localZ[2]);
		glEnd();
	}

	void drawCamAxes(void)
	{
		Vector3 o(0,0,0);
		glColor3d(0.5,0,0);
		glBegin(GL_LINES);
			glVertex3d(o[0],o[1],o[2]);
			glVertex3d(camAxeX[0],camAxeX[1],camAxeX[2]);
		glEnd();
		glColor3d(0,0.5,0);
		glBegin(GL_LINES);
			glVertex3d(o[0],o[1],o[2]);
			glVertex3d(camAxeY[0],camAxeY[1],camAxeY[2]);
		glEnd();
		glColor3d(0,0,0.5);
		glBegin(GL_LINES);
			glVertex3d(o[0],o[1],o[2]);
			glVertex3d(camAxeZ[0],camAxeZ[1],camAxeZ[2]);
		glEnd();
	}

	void drawGlobalAxes(void)
	{
		Vector3 o(0,0,0);
		glColor3d(1,0,0);
		glBegin(GL_LINES);
			glVertex3d(o[0],o[1],o[2]);
			glVertex3d(globalX[0],globalX[1],globalX[2]);
		glEnd();
		glColor3d(0,1,0);
		glBegin(GL_LINES);
			glVertex3d(o[0],o[1],o[2]);
			glVertex3d(globalY[0],globalY[1],globalY[2]);
		glEnd();
		glColor3d(0,0,1);
		glBegin(GL_LINES);
			glVertex3d(o[0],o[1],o[2]);
			glVertex3d(globalZ[0],globalZ[1],globalZ[2]);
		glEnd();
	}

	void drawAxes(bool local, bool cam)
	{
		if (local)
			drawLocalAxes();
		else if (cam)
			drawCamAxes();
		else
			drawGlobalAxes();
	}

} DisplayObject;

Vector3 pos, posc;
Quaternion orn, ornc;
#ifdef SCALING_ON
Vector3 scl1, scl2;
#endif

std::vector<DisplayObject> dobj;

DisplayObject cam;
int currentObj=0;
int currentObjId = 1;

std::vector <std::vector <Point3> > cp;
Point3  source, target, spot, normal;
Scalar param;
bool   intersection;
Vector3 separation;


bool activeAlt = false;
bool activeShift = false;
bool activeCtrl = false;

const void *hit_client;

//camera parameters
Point3 campos;
Point3 camref;
Vector3 camx, camz;
Scalar distance = 3.0f; 
Scalar ele, azi = 0.0f;
double rCam;

void initGL()
{
	GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    /*	light_position is NOT default value	*/
    GLfloat light_position0[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    GLfloat light_position1[] = { -1.0f, -1.0f, -1.0f, 0.0f };
  
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
  
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
  

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
  
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

	glEnable(GL_COLOR_MATERIAL);
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (float)w/(float)h, 0.01f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
}

void updateCameraAxes(double m[16])
{
//	camAxeX = Vector3(m[0],m[1],m[2]);
	camAxeZ = -Vector3(m[4],m[5],m[6]);
//	camAxeY = Vector3(m[8],m[9],m[10]);
	camAxeY = camref- campos;
	camAxeY /= camAxeY.norm();
	camAxeX = camAxeY^camAxeZ;
	camAxeX /= camAxeX.norm();
	camAxeZ = camAxeX^camAxeY;
}

void updateCameraRef(void)
{
	double m[16];
	dobj[currentObj].getMatrix(m);
	camref[0] = m[12];
	camref[1] = m[13];
	camref[2] = m[14];

	Vector3 v = campos - camref;
	rCam = v.norm();
}

void initCamera()
{
#ifdef DISPLAY_BV
	campos = Point3(0.25, -2.0, 1.25);
#endif
#ifdef DISPLAY_VVR
	campos = Point3(0.0, -3.00, 1.0);
#endif
	camz = Vector3(0.0, 0.0, 1.0);
	camx = Vector3(1.0, 0.0, 0.0);


	cam._obj = 0x0;
}

void initScene()
{
		
	
	cam.position = posc;
	cam.oldPosition = posc;
	cam.orientation = ornc;
	cam.oldOrientation = ornc;
	cam._referenceObject = &dobj[0];
	cam.updateAxis();

	initCamera();

	

	
	DisplayObject dispo
	dobj.push_back(dispo);
	dobj.push_back(dispo);


	dobj[0]._obj=new S_Box(5,1.3,1.6);
	dobj[0]._obj=new S_Box(1,2.2,0.6);



	for (i=0;i<dobj.size();i++)
	{
		std::vector <Point3> v;
		for (int j=0;j<dobj.size();j++)
		{
			Point3 c(0,0,0);
			v.push_back(c);
			
		}
		cp.push_back(v);
	}

	posc = Vector3(0.25, -2.0, 1.25);
	orn = Quaternion(0.0, 0.0, 0.0, 1.0);
	ornc = Quaternion(0.0, 0.0, 0.0, 1.0);


	for (i=0;i<dobj.size();i++)
	{
		dobj[i].oldPosition[0]=dobj[i].position[0] =1+i%5;
		dobj[i].oldPosition[1]=dobj[i].position[1] =i%6*(5.0/6);
		dobj[i].oldPosition[2]=dobj[i].position[2] =i%7*(5.0/7);
		dobj[i].oldPosition = pos;
		dobj[i]._obj->setOrientation(orn);
		dobj[i].orientation = orn;
		dobj[i].oldOrientation = orn;
		dobj[i]._referenceObject = &dobj[i];
		dobj[i].updateAxis();
		dobj[i].resetAdditionalTransformation();
		dobj[i].transType=NONE;

	}

	
	for (i=0;i<dobj.size();i++)
	{
		Vector3 v(dobj[i].position[0],dobj[i].position[1],dobj[i].position[2]);
		dobj[i]._obj->setPosition(v);
	
	}
	

	currentObj = 0;
}

Point3 resupport;
double matCam[16];

void display()
{
	double matrix[16];

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glLoadIdentity();

	gluLookAt(campos[0], campos[1]-3, campos[2], camref[0]+6, camref[1]+7, camref[2]+2, camAxeZ[0], camAxeZ[1], camAxeZ[2]);
	glGetDoublev(GL_MODELVIEW_MATRIX, matCam);


	dobj[currentObj].getMatrix(matrix);
	glPushMatrix();
	glTranslated(matrix[12], matrix[13], matrix[14]);
	dobj[currentObj].drawAxes(activeAlt, activeCtrl);
	glPopMatrix();

#ifdef DISPLAY_BV
	
	
#ifdef DISP_FILL
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
#endif

#ifdef DISP_LINE
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
#endif

	glDisable(GL_CULL_FACE);

	for (int i=0;i<dobj.size();i++)
	{
		dobj[i].getMatrix(matrix);
		glPushMatrix();
		//glMultMatrixd(matrix);
		glLoadIdentity();
		dobj[i]._obj->DrawGL();
		glPopMatrix();
	}

	glEnable(GL_LINE_SMOOTH );

	
	
	
	
	
	
	



    glColor3f(1.0f, 1.0f, 0.0f);
#ifdef COMMON_POINT
    if (intersection) {
        glPointSize(5);
        glBegin(GL_POINTS);
        glVertex3d(cp1[0], cp1[1], cp1[2]);
        glEnd();
        glPointSize(1);
    }
    else
#endif 
    {
       
		for (i=0;i<dobj.size();i++)
		{
			for (int j=0;j<i;j++)
			{ 
				glBegin(GL_LINES);
				glVertex3dv(cp[i][j]);
				glVertex3dv(cp[j][i]);
				glEnd();
				
			}
			
		}
		
        
	}
	
	glColor3f(1.0f, 0.0f, 0.0f);

	
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
#endif
#ifdef DISPLAY_VVR
	
	for (int i=0; i<dobj.size();i++)
	{
		dobj[i].getMatrix(matrix);
		glPushMatrix();
		glMultMatrixd(matrix);
		dobj[i].obj.GLdisplayVVR();
		glPopMatrix();
	}



	glPopMatrix();

#endif



    glFlush();
    glutSwapBuffers();
}


float getClosestPair(DT_Object* object1, DT_Object* object2, Point3& point1, Point3& point2)
{

    
    Scalar result = closest_points(*object1, *object2, point1, point2);


    return sqrt(result);
}

DT_Bool getPenetrationDepth(DT_Object* object1, DT_Object* object2, Point3& point1, Point3& point2)
{
	Vector3 v(Scalar(0.0), Scalar(0.0), Scalar(0.0)); 

    
    bool result = penetration_depth(*object1, *object2, v, point1, point2);


    return result;
}

DT_Bool getCommonPoint(DT_Object* object1, DT_Object* object2, Point3& point)
{
	Vector3  v(Scalar(0.0), Scalar(0.0), Scalar(0.0)); 
    Point3   p1, p2;
    
    bool result = common_point(*object1, *object2, v, point, p2);


    return result;
}

void* rayCast(DT_Scene* scene, void *ignore_client,
				const DT_Vector3 source, const DT_Vector3 target,
				DT_Scalar max_param, DT_Scalar *param, DT_Vector3 normal)
{
	DT_Scalar  lambda = max_param;

	void *client_object = scene->rayCast(ignore_client, source, target, lambda, normal);
   
	if (client_object)
	{
		*param = lambda;
	}
	return client_object;
}

void doTest() 
{



	for (int i=0;i<dobj.size();i++)
	{
		dobj[i].computeTransformation();
		
	}


	for (i=0;i<dobj.size();i++)
		{
			for (int j=0;j<i;j++)
			{ 
				getClosestPair(dobj[i]._obj, dobj[j]._obj, cp[i][j], cp[j][i]);
	
				
			}
			
		}



    display();
}

void RandomTestSupportFunction()
{
	Vector3 position;
	Quaternion orientation;

	Vector3 axe;
	double angle;
	
	position[0] =position[1] =	position[2] =0;



	axe[0] =  0;
	axe[1] = 0;
	axe[2] =  1;


	angle=0;

	orientation = Quaternion(axe, angle);


	for (int i=0;i<dobj.size();i++)
	{
		
		dobj[i].position=position;
		dobj[i].orientation=orientation;
		dobj[i]._obj->setPosition(position);
		dobj[i]._obj->setOrientation(orientation);
		

	}

	

	

	clock_t begin, end;

	begin=clock();

#ifdef OUTPUT_FILE

	std::fstream outfile;

	outfile.open("c:/mehdi/angletestresult.txt",std::ios_base::out|std::ios_base::trunc);
	outfile.precision(18);
#endif	

	//	std::vector<DT_Convex&> dtc;
	std::vector<const STP_Object*> stp;

	for (int i=0;i<dobj.size();i++)
	{

		DT_Transform ta(dobj[i]._obj->m_xform  , (const DT_Convex&)dobj[i]._obj->m_shape );
		const DT_Convex& dtci=static_cast<const DT_Convex&>(ta);
		//dtc.push_back(dtci);

		const void* ptr=&dtci;
		const DT_Transform* mtc=(const DT_Transform*)ptr;

		const STP_Object* stpi=(const STP_Object*)&mtc->m_child;
		stp.push_back(stpi);		

	}



	srand(time(NULL)); 
	for (long j=0;j<RandomTestEnd;j++)
	{
		
		double a = (rand()/double(RAND_MAX)) ;
		double b = (rand()/double(RAND_MAX)) ;
		double c = (rand()/double(RAND_MAX)) ;
		double d = (rand()/double(RAND_MAX)) ;

		

		


		Vector3 v(sqrt(-2*log(a))*cos(2*PI*b),sqrt(-2*log(b))*cos(2*PI*a),sqrt(-2*log(c))*cos(2*PI*d));

#ifdef DO_TEST

		for (int i=0;i<dobj.size();i++)
		{
			cp[i][i]=stp[i]->support(v);
		}


#ifdef FARTHESTNEIGHBOUR
		cp1=stp1->supportFarthestNeighbour(v);
		cp2=stp2->supportFarthestNeighbour(v);
#endif

#ifdef NAIVE
		cp1=stp1->supportNaive(v);
		cp2=stp2->supportNaive(v);
#endif


		//			((const DT_Convex)(dobj1._obj->m_shape)).support(v);

#ifdef OUTPUT_FILE
		for (int i=0;i<dobj.size();i++)
		{
			outfile<<cp[i][i]<<"  ";
		}
		outfile<<std::endl;

#endif

#endif





	}

#ifdef OUTPUT_FILE
	outfile.close();
#endif

	end=clock();

	std::cout << ((double)(end- begin) / CLOCKS_PER_SEC) <<  std::endl;

	

	



	
}





void TestSupportFunction()
{
	Vector3 position;
	Quaternion orientation;

	Vector3 axe;
	double angle;
	
	position[0] =position[1] =	position[2] =0;



	axe[0] =  0;
	axe[1] = 0;
	axe[2] =  1;


	angle=0;

	orientation = Quaternion(axe, angle);


	for (int i=0;i<dobj.size();i++)
	{
		
		dobj[i].position=position;
		dobj[i].orientation=orientation;
		dobj[i]._obj->setPosition(position);
		dobj[i]._obj->setOrientation(orientation);
		

	}

	

	

	clock_t begin, end;

	begin=clock();

#ifdef OUTPUT_FILE

	std::fstream outfile;

	outfile.open("c:/mehdi/angletestresult.txt",std::ios_base::out|std::ios_base::trunc);
	outfile.precision(18);
#endif	

//	std::vector<DT_Convex&> dtc;
	std::vector<const STP_Object*> stp;

	for (int i=0;i<dobj.size();i++)
	{
		
		DT_Transform ta(dobj[i]._obj->m_xform  , (const DT_Convex&)dobj[i]._obj->m_shape );
		const DT_Convex& dtci=static_cast<const DT_Convex&>(ta);
		//dtc.push_back(dtci);
		
		const void* ptr=&dtci;
		const DT_Transform* mtc=(const DT_Transform*)ptr;

		const STP_Object* stpi=(const STP_Object*)&mtc->m_child;
		stp.push_back(stpi);		

	}




	for (long j=-AngleSteps/4;j<=AngleSteps/4;j++)
	{
		Scalar b(j/AngleSteps*2*PI);
		for (long i=-AngleSteps/2; i<AngleSteps/2; i++)
		{
			
			Scalar a(i/AngleSteps*2*PI);



			Vector3 v(cos(a)*cos(b),sin(a)*cos(b),sin(b));
		
#ifdef DO_TEST

			for (int i=0;i<dobj.size();i++)
			{
				cp[i][i]=stp[i]->support(v);
			}


#ifdef FARTHESTNEIGHBOUR
			cp1=stp1->supportFarthestNeighbour(v);
			cp2=stp2->supportFarthestNeighbour(v);
#endif

#ifdef NAIVE
			cp1=stp1->supportNaive(v);
			cp2=stp2->supportNaive(v);
#endif


			//			((const DT_Convex)(dobj1._obj->m_shape)).support(v);

#ifdef OUTPUT_FILE
			for (int i=0;i<dobj.size();i++)
			{
				outfile<<cp[i][i]<<"  ";
			}
			outfile<<std::endl;
		
#endif

#endif



		}

	}

#ifdef OUTPUT_FILE
	outfile.close();
#endif

	end=clock();

	std::cout << ((double)(end- begin) / CLOCKS_PER_SEC) <<  std::endl;

	

	



	
}



void TestAnimation()
{
	Vector3 position;
	Quaternion orientation;

	Vector3 axe;
	double angle;
	
	position[0] =position[1] =	position[2] =3;



	axe[0] =  0;
	axe[1] = 0;
	axe[2] =  1;


	angle=0;

	orientation = Quaternion(axe, angle);


	for (int i=0;i<dobj.size();i++)
	{
		position[0] =dobj[i].oldPosition[0]=dobj[i].position[0] =1+i%5;
		position[1] =dobj[i].oldPosition[1]=dobj[i].position[1] =i%6*(5.0/6);
		position[2] =dobj[i].oldPosition[2]=dobj[i].position[2] =i%7*(5.0/7);
		//dobj[i].position=position;
		dobj[i].orientation=orientation;
		dobj[i]._obj->setPosition(position);
		dobj[i]._obj->setOrientation(orientation);
		

	}

	

	


#ifdef DO_TEST

	
	for (i=0;i<dobj.size();i++)
		{
			for (int j=0;j<i;j++)
			{ 
				getClosestPair(dobj[i]._obj, dobj[j]._obj, cp[i][j], cp[j][i]);
	
				
			}
			
		}

#endif

#ifdef DISPLAY_TEST
	display();
#endif

	clock_t begin, end;

	begin=clock();

#ifdef OUTPUT_FILE

	std::fstream outfile;

	

	outfile.open("c:/mehdi/animationtestresult.txt",std::ios_base::out|std::ios_base::trunc);
	
	outfile.precision(18);

#endif	








	for (long i=AnimationBegin; i<AnimationEnd; i++)
	{
		
		for (int j=0;j<dobj.size();j++)
		{
			position[0] =dobj[j].oldPosition[0]+AnimationScale*sin((20*(j%3+1)+2*j)*sin(0.2*AnimationSpeed*i));
			position[1] =dobj[j].oldPosition[1]+AnimationScale*sin((71-140*(j%2-1)+2*j)*sin(0.15*AnimationSpeed*i));
			position[2] =dobj[j].oldPosition[2]+AnimationScale*sin((20+((j*5)%7)*5+3*j)*sin(0.2*AnimationSpeed*i));


			axe[0] =  sin((42+j)*sin(0.2*AnimationSpeed*i));
			axe[1] =  sin((-43-j)*sin(0.2*AnimationSpeed*i));
			axe[2] =  cos((83+j)*sin(0.1*AnimationSpeed*i));


			angle=4*sin((97-j)*sin(0.2*sin(0.5*AnimationSpeed*i)));

			orientation =Quaternion(axe, angle);

			dobj[j].position=position;
			dobj[j].orientation=orientation;



			dobj[j]._obj->setPosition(position);
			dobj[j]._obj->setOrientation(orientation);

		}

		
		


	

		
		
#ifdef DO_TEST
		for (int k=0;k<dobj.size();k++)
		{
			for (int j=0;j<k;j++)
			{ 
				getClosestPair(dobj[k]._obj, dobj[j]._obj, cp[k][j], cp[j][k]);
	
			}
			
		}

#ifdef OUTPUT_FILE
		for (int k=0;k<dobj.size();k++)
		{
			for (int j=0;j<k;j++)
			{ 
				outfile<<i<<"-"<<j<<":"<<(cp[k][j]-cp[j][k]).norm()<<" "<<std::endl;
	
			
			}
			
			
		}
		outfile<<std::endl;
		
#endif

#endif


		


#ifdef DISPLAY_TEST
		display();
#endif





	}

#ifdef OUTPUT_FILE
	outfile.close();
#endif

	end=clock();

	std::cout << ((double)(end- begin) / CLOCKS_PER_SEC) << " : " << ((double)(end - begin) / CLOCKS_PER_SEC)/(AnimationEnd-AnimationBegin) << std::endl;

	
	



	
}

void move_up()
{ 
	pos[2] += 0.01f; 
	doTest(); 
} 
void move_down()
{ 
	pos[2] -= 0.01f;
	doTest();  
} 
void move_front()
{ 
	pos[1] -= 0.01f; 
	doTest(); 
} 
void move_back()
{ 
	pos[1] += 0.01f;
	doTest();  
} 
void move_right()
{ 
	pos[0] += 0.01f; 
	doTest(); 
} 
void move_left()
{ 
	pos[0] -= 0.01f; 
	doTest(); 
} 

void turn_up()
{ 
	orn[2] += 0.01f; 
	doTest(); 
} 
void turn_down()
{ 
	orn[2] -= 0.01f;
	doTest();  
} 
void turn_front()
{ 
	orn[1] -= 0.01f; 
	doTest(); 
} 
void turn_back()
{ 
	orn[1] += 0.01f;
	doTest();  
} 
void turn_right()
{ 
	orn[0] += 0.01f; 
	doTest(); 
} 
void turn_left()
{ 
	orn[0] -= 0.01f; 
	doTest(); 
} 

void setCamera() 
{
    glLoadIdentity();

	gluLookAt(campos[0], campos[1], campos[2], (camz.cross(camx))[0] + campos[0], (camz.cross(camx))[1] + campos[1], (camz.cross(camx))[2] + campos[2], camz[0], camz[1], camz[2]);
	display();
}

void stepLeft(Scalar step)
{ 
	campos -= step * camx;
	setCamera(); 
}
void stepRight(Scalar step)
{ 
	campos += step * camx;
	setCamera(); 
}

void stepUp(Scalar step)
{
	campos += step * camz;
	setCamera();
}
void stepDown(Scalar step)
{
	campos -= step * camz;
	setCamera();
}

void zoomIn(Scalar step)
{ 
	campos += step * camz.cross(camx);
	setCamera(); 
}
void zoomOut(Scalar step) 
{ 
	campos -= step * camz.cross(camx);
	setCamera(); 
}

void switchObject(void)
{
	currentObj = (currentObj+1)%dobj.size();
}


void switchObjectReverse(void)
{
	currentObj = (currentObj+dobj.size()-1)%dobj.size();
}


void lookLeft(Scalar step)
{
	float matrix[16];
	glPushMatrix();
	glLoadIdentity();
	glRotatef(step, camz[0], camz[1], camz[2]);
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glPopMatrix();

	Vector3 tmp = camx;
	camx[0] = matrix[0] * tmp[0] + matrix[4] * tmp[1] + matrix[8] * tmp[2];
	camx[1] = matrix[1] * tmp[0] + matrix[5] * tmp[1] + matrix[9] * tmp[2];
	camx[2] = matrix[2] * tmp[0] + matrix[6] * tmp[1] + matrix[10] * tmp[2];

	setCamera();
}

void lookRight(Scalar step)
{
	float matrix[16];
	glPushMatrix();
	glLoadIdentity();
	glRotatef(-step, camz[0], camz[1], camz[2]);
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glPopMatrix();

	Vector3 tmp = camx;
	camx[0] = matrix[0] * tmp[0] + matrix[4] * tmp[1] + matrix[8] * tmp[2];
	camx[1] = matrix[1] * tmp[0] + matrix[5] * tmp[1] + matrix[9] * tmp[2];
	camx[2] = matrix[2] * tmp[0] + matrix[6] * tmp[1] + matrix[10] * tmp[2];
	
	setCamera();
}

void lookUp(Scalar step)
{
	float matrix[16];
	glPushMatrix();
	glLoadIdentity();
	glRotatef(step, camx[0], camx[1], camx[2]);
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glPopMatrix();

	Vector3 tmp = camz;
	camz[0] = matrix[0] * tmp[0] + matrix[4] * tmp[1] + matrix[8] * tmp[2];
	camz[1] = matrix[1] * tmp[0] + matrix[5] * tmp[1] + matrix[9] * tmp[2];
	camz[2] = matrix[2] * tmp[0] + matrix[6] * tmp[1] + matrix[10] * tmp[2];
	
	setCamera();
}

void lookDown(Scalar step)
{
	float matrix[16];
	glPushMatrix();
	glLoadIdentity();
	glRotatef(-step, camx[0], camx[1], camx[2]);
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glPopMatrix();

	Vector3 tmp = camz;
	camz[0] = matrix[0] * tmp[0] + matrix[4] * tmp[1] + matrix[8] * tmp[2];
	camz[1] = matrix[1] * tmp[0] + matrix[5] * tmp[1] + matrix[9] * tmp[2];
	camz[2] = matrix[2] * tmp[0] + matrix[6] * tmp[1] + matrix[10] * tmp[2];
	
	setCamera();
}

void myKeyboard(unsigned char key, int x, int y)
{
    switch (key) 
	{
	case 32:
		switchObject();
		display();
		break;
	case 8:
		switchObjectReverse();
		display();
		break;
    case 'z': 
		zoomIn(TRANSSTEPK); 
		break;
    case 'x': 
		zoomOut(TRANSSTEPK); 
		break;
	case 'w': 
		move_up(); 
		break;
    case 's': 
		move_down(); 
		break;
	case 'a': 
		move_left(); 
		break;
    case 'd': 
		move_right(); 
		break;  
	case 'e':
		move_back();
		break;
	case 'f':
		move_front();
		break;
	case 'p': 
		turn_up(); 
		break;
    case ';': 
		turn_down(); 
		break;
	case 'l': 
		turn_left(); 
		break;
    case '\'': 
		turn_right(); 
		break;  
	case '[':
		turn_back();
		break;
	case ']':
		turn_front();
		break;
	case 'u':
		lookUp(ROTSTEPK);
		break;
	case'j':
		lookDown(ROTSTEPK);
		break;
	case 'h':
		lookLeft(ROTSTEPK);
		break;
	case 'k':
		lookRight(ROTSTEPK);
		break;
	case 'c':
		cameraMode = !cameraMode;
		updateCameraAxes(matCam);
		break;
	/*case 'i':
		toggleIdle(); 
		break;
    case ' ':
		newPlacements();
		break;*/
    default:
        break;
    }

	int m = glutGetModifiers();
	activeAlt = m & GLUT_ACTIVE_ALT;
	activeCtrl = m & GLUT_ACTIVE_CTRL;

	display();
}

void mySpecial(int key, int x, int y)
{
    switch (key) 
	{
    case GLUT_KEY_LEFT: 
		stepLeft(TRANSSTEPK); 
		break;
    case GLUT_KEY_RIGHT: 
		stepRight(TRANSSTEPK); 
		break;
    case GLUT_KEY_UP:
		zoomIn(TRANSSTEPK); 
		break;
    case GLUT_KEY_DOWN:
		zoomOut(TRANSSTEPK); 
		break;
    case GLUT_KEY_PAGE_UP:
		stepUp(TRANSSTEPK);
		break;
    case GLUT_KEY_PAGE_DOWN:
		stepDown(TRANSSTEPK);
		break;
    case GLUT_KEY_HOME:
		initCamera();
		setCamera();
		break;
    default:
        break;
    }
}

float previousX;
float previousY;
float prevX;
float prevY;
bool turn = false;
bool move = false;
bool forward = false;

void mouseDown(int button, int state, int x, int y)
{
	if( (button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) )
	{
		turn = true;
		move = false;
		forward = false;
		previousX = x;
		previousY = y;
	}
	else if ( (button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN) )
	{
		move = true;
		turn = false;
		forward = false;
		previousX = x;
		previousY = y;
	}
	else 
	{
		turn = false;
		move = false;
		forward = false;
	}
}

void mouseClic(int button, int state, int x, int y)
{
	if( (button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) )
	{
		turn = true;
		move = false;
		prevX = previousX = x;
		prevY = previousY = y;
	}
	else if ( (button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN) )
	{
		move = true;
		turn = false;
		prevX = previousX = x;
		prevY = previousY = y;
	}
	else 
	{
		turn = false;
		move = false;
		dobj[currentObj].collapseTransformation();
		display();
		if (cameraMode)
			updateCameraAxes(matCam);
	}

	int m = glutGetModifiers();
	activeAlt = m & GLUT_ACTIVE_ALT;
	activeShift = m & GLUT_ACTIVE_SHIFT;
	activeCtrl = m & GLUT_ACTIVE_CTRL;

//	std::cout << activeAlt << std::endl;
}



void mouseMotion(int x, int y)
{
	float dx = x - previousX;
	float dy = y - previousY;

	std::cout << dx << "    " << dy << std::endl;

	if(turn)
	{
		if(dx > 0.0)
			dobj[currentObj].tr1 = INCR_ROT * dx;
		else if(dx < 0.0)
			dobj[currentObj].tr1 = INCR_ROT * dx;

		if(dy > 0.0)
			dobj[currentObj].tr2 = INCR_ROT * dy;
		else if(dy < 0.0)
			dobj[currentObj].tr2 = INCR_ROT * dy;
		if (!activeAlt)
		{
			if (activeShift)
				dobj[currentObj].transType = GLOBAL_ROTATION_YZ;
			else if (activeCtrl)
				dobj[currentObj].transType = GLOBAL_ROTATION_ZX;
			else
				dobj[currentObj].transType = GLOBAL_ROTATION_XY;
		}
		else
		{
			if (activeShift)
				dobj[currentObj].transType = LOCAL_ROTATION_YZ;
			else if (activeCtrl)
				dobj[currentObj].transType = LOCAL_ROTATION_ZX;
			else
				dobj[currentObj].transType = LOCAL_ROTATION_XY;
		}
	}
	else if(move)
	{
		if(dx > 0.0)
			dobj[currentObj].tr1 = INCR_TRANS * dx;
		else if(dx < 0.0)
			dobj[currentObj].tr1 = INCR_TRANS * dx;

		if(dy > 0.0)
			dobj[currentObj].tr2 = -INCR_TRANS * dy;
		else if(dy < 0.0)
			dobj[currentObj].tr2 = -INCR_TRANS * dy;
		if (!activeAlt)
		{
			if (activeShift)
				dobj[currentObj].transType = GLOBAL_TRANSLATION_YZ;
			else if (activeCtrl)
				dobj[currentObj].transType = GLOBAL_TRANSLATION_ZX;
			else
				dobj[currentObj].transType = GLOBAL_TRANSLATION_XY;
		}
		else
		{
			if (activeShift)
				dobj[currentObj].transType = LOCAL_TRANSLATION_YZ;
			else if (activeCtrl)
				dobj[currentObj].transType = LOCAL_TRANSLATION_ZX;
			else
				dobj[currentObj].transType = LOCAL_TRANSLATION_XY;
		}
	}

	doTest();
}

void mouseMotion3mode(int x, int y)
{
	double dx = x - previousX;
	double dy = y - previousY;
	double dpx = x - prevX;
	double dpy = y - prevY;

//	std::cout << dx << "    " << dy << std::endl;
	if (cameraMode)
	{
		if (turn)
		{
			if (activeShift)
			{
			}
			else
			{
				campos = camref + rCam * (
							  cos(INCR_ROT*dx)*sin(INCR_ROT*dy) * -camAxeY
							+ sin(INCR_ROT*dx)*sin(INCR_ROT*dy) * camAxeX
							+ cos(INCR_ROT*dy) * camAxeZ);
			}
		}
		else if (move)
		{
			if (activeShift)
			{
				camref += INCR_TRANS*(dpy)*camAxeZ;
			}
			else
			{
				camref += INCR_TRANS*(dpx*camAxeX + dpy*camAxeY);
				campos += INCR_TRANS*(dpx*camAxeX + dpy*camAxeY);
			}
		}
	}
	else 
	{
		if(turn)
		{
			if(dx > 0.0)
				dobj[currentObj].tr1 = INCR_ROT * dx;
			else if(dx < 0.0)
				dobj[currentObj].tr1 = INCR_ROT * dx;

			if(dy > 0.0)
				dobj[currentObj].tr2 = INCR_ROT * dy;
			else if(dy < 0.0)
				dobj[currentObj].tr2 = INCR_ROT * dy;
			if (activeAlt)
			{
				if (activeShift)
				{
					dobj[currentObj].transType = LOCAL_ROTATION_Z;
					dobj[currentObj].tr1 +=  dobj[currentObj].tr2;
				}
				else
					dobj[currentObj].transType = LOCAL_ROTATION_XY;
			}
			else if (activeCtrl)
			{
				if (activeShift)
				{
					dobj[currentObj].transType = CAM_ROTATION_Z;
					dobj[currentObj].tr1 +=  dobj[currentObj].tr2;
				}
				else
					dobj[currentObj].transType = CAM_ROTATION_XY;
			}
			else
			{
				if (activeShift)
				{
					dobj[currentObj].transType = GLOBAL_ROTATION_Z;
					dobj[currentObj].tr1 +=  dobj[currentObj].tr2;
				}
				else
					dobj[currentObj].transType = GLOBAL_ROTATION_XY;
			}
		}
		else if(move)
		{
			if(dx > 0.0)
				dobj[currentObj].tr1 = INCR_TRANS * dx;
			else if(dx < 0.0)
				dobj[currentObj].tr1 = INCR_TRANS * dx;

			if(dy > 0.0)
				dobj[currentObj].tr2 = -INCR_TRANS * dy;
			else if(dy < 0.0)
				dobj[currentObj].tr2 = -INCR_TRANS * dy;
			if (activeAlt)
			{
				if (activeShift)
				{
					dobj[currentObj].transType = LOCAL_TRANSLATION_Z;
					dobj[currentObj].tr1 += dobj[currentObj].tr2;
				}
				else
					dobj[currentObj].transType = LOCAL_TRANSLATION_XY;
			}
			else if (activeCtrl)
			{
				if (activeShift)
				{
					dobj[currentObj].transType = CAM_TRANSLATION_Z;
					dobj[currentObj].tr1 +=  dobj[currentObj].tr2;
				}
				else
					dobj[currentObj].transType = CAM_TRANSLATION_XY;
			}
			else
			{
				if (activeShift)
				{
					dobj[currentObj].transType = GLOBAL_TRANSLATION_Z;
					dobj[currentObj].tr1 +=  dobj[currentObj].tr2;
				}
				else
					dobj[currentObj].transType = GLOBAL_TRANSLATION_XY;
			}
		}
	}

	prevX = x;
	prevY = y;

	doTest();
}


void goodbye( void)
{
    std::cout << "goodbye ..." << std::endl;
    exit(0);
}

void menu(int choice)
{

    static int fullScreen = 0;
    static int px, py, sx, sy;
 
    switch(choice) {
    case 1:
        if (fullScreen==1) {
            glutPositionWindow(px, py);
            glutReshapeWindow(sx, sy);
            glutChangeToMenuEntry(1, "Full Screen", 1);
            fullScreen=0;
        } 
		else {
            px = glutGet((GLenum)GLUT_WINDOW_X);
            py = glutGet((GLenum)GLUT_WINDOW_Y);
            sx = glutGet((GLenum)GLUT_WINDOW_WIDTH);
            sy = glutGet((GLenum)GLUT_WINDOW_HEIGHT);
            glutFullScreen();
            glutChangeToMenuEntry(1, "Close Full Screen", 1);
            fullScreen = 1;
        }
        break;
    /*case 2:
        toggleIdle();
        break;*/
    case 3:
		TestAnimation();
		break; 

	case 4:
		TestSupportFunction();
        break;
	case 5:
		RandomTestSupportFunction();
		break;
	case 6:
		goodbye();
        break;
		
    default:
        break;
    }
}

void createMenu()
{
    glutCreateMenu(menu);
    glutAddMenuEntry("Full Screen", 1);
    //glutAddMenuEntry("Toggle Idle (Start/Stop)", 2);
    glutAddMenuEntry("Animation", 3);
	glutAddMenuEntry("Support test", 4);
	glutAddMenuEntry("Random support test", 5);
	glutAddMenuEntry("Quit", 6);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
}



int main(int argc, char** argv)
{
	mpfr::Library.setPrecision(PRECISION);

	

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("TestGL");

    initGL();
	initScene();
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecial);
    glutReshapeFunc(myReshape);
	glutMouseFunc(mouseClic);
	glutMotionFunc(mouseMotion3mode);
    createMenu();
	
    glutIdleFunc(0);
	doTest();
	setCamera();
    glutDisplayFunc(display);
	doTest();
    glutMainLoop();

	if(scene)
		delete scene;
	for (int i=0;i<dobj.size();i++)
		delete dobj[i]._obj;

    return 0;
}
#endif