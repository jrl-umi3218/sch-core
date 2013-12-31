#include "common.h"

#include <stdlib.h>

#ifdef WITH_OPENGL
# if defined __APPLE__
#  include <GLUT/glut.h>
# else
#  include <GL/glut.h>
# endif // __APPLE__
#endif // WITH_OPENGL

#include <ctime>
#include <math.h>

#include <string>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cwchar>

#include <iostream>
#include <sstream>
#include <ios>
#include <fstream>
#include <vector>

extern std::fstream outfile;

using namespace SCD;

GLfloat light0_ambient[] =  {0.1f, 0.1f, 0.3f, 1.0f};
GLfloat light0_diffuse[] =  {.8f, .8f, 1.0f, 1.0f};
GLfloat light0_position[] = {.5f, .5f, 0.1f, 0.0f};

GLfloat light1_ambient[] =  {0.1f, 0.1f, 0.3f, 1.0f};
GLfloat light1_diffuse[] =  {0.75f, .6f, 0.15f, 1.0f};
GLfloat light1_position[] = {-1.0f, 0.0f, 0.2f, 0.0f},  background[]= {0.2,0.2,0.2};



TestMaterial universe;

void mul_mat_v(const double *mat,const double *vec,double *res)
{

	for (int i=0;i<4;i++)
	{
		res[i]=0;
		for (int j=0;j<4;j++)
		{
			res[i]+=mat[j*4+i]*vec[j];
		}
	}
}

void trans_mat(const double *f,double *g)
{
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
		{
			g[i+j*4]=f[i*4+j];
		}
}

/* keyboard */
struct keyboard_input_t
{
	unsigned char keymap[256];
	int special[256];
	int modifiers;

} keyboard;

/* mouse */
struct mouse_input_t
{
	int buttons[3];
	int x, y;

} mouse;

/* timer */
struct glut_timer_t
{
	double current_time;
	double last_time;

} timer;

/* camera */
struct Vector3d
{
	float x, y, z;

} rot, eye;

Scalar hei,wid;

const Scalar vx[4]={1,0,0,0};
const Scalar vy[4]={0,1,0,0};
const Scalar vz[4]={0,0,1,0};

Scalar nx[4]={1,0,0,0};
Scalar ny[4]={0,1,0,0};
Scalar nz[4]={0,0,1,0};

Scalar matCam[16];

/*
* shutdownApp - application termination
*/
static void
shutdownApp (void)
{
}


/*
* init - application initialisation. Setup keyboard input,
* mouse input, timer, camera and OpenGL.
*/
static void
init (void)
{
	/*
	* application initialization
	*/

	/* init keyboard */
	memset (keyboard.keymap, 0, 256);
	memset (keyboard.special, 0, 256);

	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA| GLUT_DEPTH|GLUT_ALPHA);

	glutInitWindowSize (800, 600);
	glutCreateWindow ("Smooth collision detection");

	/* init mouse */
	mouse.buttons[GLUT_LEFT_BUTTON] = GLUT_UP;
	mouse.buttons[GLUT_MIDDLE_BUTTON] = GLUT_UP;
	mouse.buttons[GLUT_RIGHT_BUTTON] = GLUT_UP;
	mouse.x = 0;
	mouse.y = 0;

	/* init timer */
	timer.current_time = 0;
	timer.last_time = 0;

	/* init camera input */
	rot.x = 0.0f;   eye.x = 0.0f;
	rot.y = 0.0f;   eye.y = 0.0f;
	rot.z = 0.0f;   eye.z = 7.0f;



	/*
	* init OpenGL
	*/




	glEnable (GL_LIGHTING);

	glClearColor (background[0], background[1], background[2], 1.0f);
	glShadeModel (GL_SMOOTH);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_COLOR_MATERIAL);

	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	glShadeModel (GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_ALPHA);

#ifndef LINES_DISPLAY
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
#else
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	//glEnable(GL_LINE_SMOOTH);
#endif

	glEnable(GL_FOG);
	{
		glFogfv (GL_FOG_COLOR, &background[0]);
		glFogi (GL_FOG_MODE, GL_EXP2);

		glFogf (GL_FOG_DENSITY, 0.00025);

		glFogf (GL_FOG_START, 14000.0);
		glFogf (GL_FOG_END, 15000.0);
	}

	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glHint (GL_FOG_HINT, GL_NICEST);

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glMatrixMode( GL_MODELVIEW );

	glLoadIdentity();
	glGetDoublev(GL_MODELVIEW_MATRIX,matCam);

	/*inialize objects*/

	universe.initializeUniverse();
}



/*
* reshape - OpenGL window resizing.  Update the
* viewport and the projection matrix.
*/
static void
reshape (int w, int h)
{
	if (h == 0)
		h = 1;

	hei=h;
	wid=w;

	glViewport (0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (20.0, (GLfloat)w/(GLfloat)h, 0.1, 1000.0);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();

	glutPostRedisplay ();
}


/*
* updateTimer - update the timer
*/
static void
updateTimer (struct glut_timer_t *t)
{
	t->last_time = t->current_time;
	t->current_time = (double)glutGet (GLUT_ELAPSED_TIME) * 0.001f;
}


/*
* handleKeyboard - keyboard input handling
*/
static void
handleKeyboard (struct keyboard_input_t *k)
{
	/*
	* handle here continuous actions when
	* a key is pressed (like moving the camera)
	*/

	/*
	if (k->keymap['yourkey'])
	do_something ();
	*/
}


/*
* display - render the main OpenGL scene
*/
void display (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();

	/* camera rotation */
	glTranslated (-eye.x, -eye.y, -eye.z);
	glMultMatrixd(matCam);

	/* draw utah-teapot */

	//gluLookAt(0,0,0,0,0,-1,0,1,0);
	glColor3d(0.6,0.7,0.6);

//	for (size_t i=0;i<universe.sObj.size();++i)
//		universe.sObj[i]->drawGL();

	Vector3 p=universe.sObj[universe.CurrentObj]->getPosition();
	glDisable (GL_LIGHTING);

	glPushMatrix();

	glTranslated(p[0],p[1],p[2]);


	glBegin(GL_LINES);
	glColor3d(1,0,0);
	glVertex3d(0,0,0);
	glVertex3d(1.5,0,0);

	glColor3d(0,1,0);
	glVertex3d(0,0,0);
	glVertex3d(0,1.5,0);

	glColor3d(0,0,1);
	glVertex3d(0,0,0);
	glVertex3d(0,0,1.5);



	glEnd();

	glPopMatrix();

	glColor3d(1,1,0.2);

	glBegin(GL_LINES);
	for (size_t i=0;i<universe.sObj.size();++i)
	{
		for (size_t j=0;j<i;++j)
		{
			Point3 p1,p2;

			Scalar d = universe.sObj.getWitnessPoints(i,j,p1,p2);

#ifdef DISPLAY_DISTANCE
			std::cout<<d<<' '<<(p1-p2).normsquared()<<' '<<fabs(d)-fabs((p1-p2).normsquared())<<std::endl;
#endif

			glVertex3d(p1[0],p1[1],p1[2]);
			glVertex3d(p2[0],p2[1],p2[2]);

		}
	}
	glEnd();
	glEnable (GL_LIGHTING);
	glutSwapBuffers();
}



/*
* keyPress - key press glut callback function.
* Called when user press a key.
*/



static void
keyPress (unsigned char key, int x, int y)
{
	static int lightOn = 1;

	/* update key state */
	keyboard.keymap[key] = 1;

	/*
	* handle here ponctual actions when
	* a key is pressed (like toggle ligthing)
	*/

	/* escape */

	switch (key)
	{

	case 27:
		exit (0);
		break;

		/* 'l': toggle light */
	case 'l':
		lightOn = !lightOn;
		break;


	case 32:
		universe.CurrentObj=(universe.CurrentObj+1)%universe.sObj.size();
		break;
	case 8:
		universe.CurrentObj=(universe.CurrentObj-1)%universe.sObj.size();
		break;

	case '0':
		universe.RandomTestSupportFunction();
		break;

	case '1':
		universe.TestAnimation();
		break;

	case '2':
		universe.TestPrecision();
		break;

	case '3':
		universe.RandomTestSupportFunctionAllObjects();
		break;

	case '5':
		universe.GeneralTest();
		break;
	}

	if (lightOn)
		glEnable (GL_LIGHTING);
	else
		glDisable (GL_LIGHTING);

	glutPostRedisplay ();
}


/*
* keyUp - key up glut callback function.
* Called when user release a key.
*/
static void
keyUp (unsigned char key, int x, int y)
{
	keyboard.keymap[key] = 0;
}


/*
* specialKeyPress - key press glut callback function.
* Called when user press a special key.
*/
static void
specialKeyPress (int key, int x, int y)
{
	keyboard.special[key] = 1;
}


/*
* specialKeyUp - key up glut callback function.
* Called when user release a special key.
*/
static void
specialKeyUp (int key, int x, int y)
{
	keyboard.special[key] = 0;
}


/*
* mouseMotion - mouse motion glut callback function.
* Called when the user move the mouse. Update the
* camera.
*/
static void
mouseMotion (int x, int y)
{

	if (mouse.buttons[GLUT_RIGHT_BUTTON] == GLUT_DOWN)
	{
		if (keyboard.modifiers & GLUT_ACTIVE_CTRL)
		{

			if (keyboard.modifiers & GLUT_ACTIVE_SHIFT)
			{

				rot.z = (y - mouse.y)+(x - mouse.x);

				double inv[16];

				trans_mat(matCam,inv);
				mul_mat_v(inv,vz,nz);

				glPushMatrix();
				glLoadMatrixd(matCam);

				glRotated (rot.z, nz[0], nz[1], nz[2]);

				glGetDoublev(GL_MODELVIEW_MATRIX,matCam);
				glPopMatrix();


			}
			else
			{
				/* rotation */
				rot.x = (y - mouse.y);
				rot.y = (x - mouse.x);

				double inv[16];

				trans_mat(matCam,inv);
				mul_mat_v(inv,vx,nx);
				mul_mat_v(inv,vy,ny);

				glPushMatrix();

				glLoadMatrixd(matCam);

				glRotated (rot.x, nx[0], nx[1], nx[2]);
				glRotated (rot.y, ny[0], ny[1], ny[2]);

				glGetDoublev(GL_MODELVIEW_MATRIX,matCam);

				glPopMatrix();

			}
		}
		else
		{
			if (keyboard.modifiers & GLUT_ACTIVE_SHIFT)
			{
				rot.z = (y - mouse.y)+(x - mouse.x);

				Vector3 t=universe.sObj[universe.CurrentObj]->getPosition();
				universe.sObj[universe.CurrentObj]->addRotation(rot.z*0.02,Vector3(0,0,1));
				universe.sObj[universe.CurrentObj]->setPosition(t);
			}
			else
			{
				/* rotation */
				rot.x = (y - mouse.y);
				rot.y = (x - mouse.x);

				Vector3 t=universe.sObj[universe.CurrentObj]->getPosition();
				universe.sObj[universe.CurrentObj]->addRotation(rot.x*0.02,Vector3(1,0,0));
				universe.sObj[universe.CurrentObj]->addRotation(rot.y*0.02,Vector3(0,1,0));
				universe.sObj[universe.CurrentObj]->setPosition(t);
			}
		}
	}
	else if (mouse.buttons[GLUT_LEFT_BUTTON] == GLUT_DOWN)
	{
		if (keyboard.modifiers & GLUT_ACTIVE_CTRL)
		{
			/* translation */
			eye.x -= (x - mouse.x) * 0.0097*(eye.z/7);
			eye.y += (y - mouse.y) * 0.0097 *(eye.z/7);
		}
		else
		{
			universe.sObj[universe.CurrentObj]->addTranslation((x - mouse.x) *0.007,-(y - mouse.y)*0.007,0);
		}
	}
	else if (mouse.buttons[GLUT_MIDDLE_BUTTON] == GLUT_DOWN)
	{

		if (keyboard.modifiers & GLUT_ACTIVE_CTRL)
		{
			/* zoom */
			eye.z *= (((x - mouse.x))/wid+((mouse.y-y))/hei)*2+1;

			if (eye.z <0.01)
				eye.z=0.01;
		}
		else
		{
			universe.sObj[universe.CurrentObj]->addTranslation(0,0,-((x - mouse.x)+(mouse.y-y))*0.011);
		}

	}


	mouse.x = x;
	mouse.y = y;


	universe.DoTest();

	glutPostRedisplay ();
}


/*
* mouseButton - mouse button press glut callback function.
* Called when the user press a mouse button. Update mouse
* state and keyboard modifiers.
*/
static void
mouseButton (int button, int state, int x, int y)
{
	/* update key modifiers */
	keyboard.modifiers = glutGetModifiers ();

	/* update mouse state */
	mouse.buttons[button] = state;
	mouse.x = x;
	mouse.y = y;
}


/*
* idleVisible - idle glut callback function.
* Continuously called. Perform background
* processing tasks.
*/
static void
idleVisible (void)
{
	/* update the timer */
	updateTimer (&timer);

	/* handle keyboard input */
	handleKeyboard (&keyboard);
}


/*
* windowStatus - window status glut callback function.
* Called when the status of the window changes.
*/
static void
windowStatus (int state)
{
	/* disable rendering and/or animation when the
	window is not visible */
	if ((state != GLUT_HIDDEN) &&
		(state != GLUT_FULLY_COVERED))
	{
		glutIdleFunc (idleVisible);
	}
	else
	{
		glutIdleFunc (NULL);
	}
}


/*
* main - this is the main programme.
*/
int
main (int argc, char *argv[])
{
	/* initialize glut */
	glutInit (&argc, argv);

	/* create an OpenGL window */


	/* initialize application */
	atexit (shutdownApp);
	init ();

	/* setup glut callback functions */
	glutReshapeFunc (reshape);
	glutDisplayFunc (display);
	glutKeyboardFunc (keyPress);
	glutKeyboardUpFunc (keyUp);
	glutSpecialFunc (specialKeyPress);
	glutSpecialUpFunc (specialKeyUp);
	glutMotionFunc (mouseMotion);
	glutMouseFunc (mouseButton);
	glutWindowStatusFunc (windowStatus);
	glutIdleFunc (idleVisible);

	/* enter the main loop */
	glutMainLoop ();

	return 0;
}
