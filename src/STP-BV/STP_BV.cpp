
/*! \file STP_Feature.cpp
\brief definition of the STP_BV class, 
the Triangle and SphereApproxim structures and the PointsComparator functor
\author Cochet-Grasset Amelie
\date 2007
*/


#include <SCD/STP-BV/STP_BV.h>
#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <exception>






#include <SCD/STP-BV/STP_SmallSphere.h>
#include <SCD/STP-BV/STP_BigSphere.h>
#include <SCD/STP-BV/STP_Torus.h>

const double PI=3.141592653589793238462643383279502884197;


#define REMEMBER_LAST_FEATURE

//#define NAIVESUPPORT
//#define FARTHESTSUPPORT
//#define FARTHESTSUPPORTPRIME
//#define FIRSTSUPPORT
//#define FIRSTSUPPORTPRIME
#define HYBRIDSUPPORT
//#define TREESUPPORT

#define SUPPORT_DEBUG

//#define COUNTER

//#define writecout
//#define writeos
//#define writeos1
//#define writeos2
//#define writeos3
//#define writeos4
//#define writeos5
//#define writeos6

#ifdef writeos
std::ofstream os("debugSortVertices_testGL.txt"); //DEBUG
#endif
#ifdef writeos1
std::ofstream os1("debugData.txt"); //DEBUG
#endif
#ifdef writeos2
std::ofstream os2("debugBoucleComputeSurface_testGL.txt"); //DEBUG
#endif
#ifdef writeos3
std::ofstream os3("debugTriInter_testGL.txt"); //DEBUG
#endif
#ifdef writeos4
std::ofstream os4("debugCompleteBVData_testGL.txt"); //DEBUG
#endif
#ifdef writeos5
std::ofstream os5("debugDecoupagesEffectuesCube.txt");
bool okos5 = false;
#endif
#ifdef writeos6
std::ofstream os6("debugSortList.txt");
#endif


using namespace SCD;

s_Triangle::s_Triangle(const Point3& vertex1, const Point3& vertex2, const Point3& vertex3):
m_vertex1(vertex1), m_vertex2(vertex2), m_vertex3(vertex3)
{
}

s_SphereApproxim::s_SphereApproxim(std::vector<Point3>& vertices, int step, const Point3& sphereCenter, double sphereRadius):
m_vertices(vertices), m_step(step), m_sphereCenter(sphereCenter), m_sphereRadius(sphereRadius)
{
}

void s_SphereApproxim::operator ()(const Triangle& vertices, const int& currentStep) const 
{
	if(currentStep < m_step/2)
	{
		Triangle t;
		t.m_vertex1 = vertices.m_vertex1;
		t.m_vertex1 += vertices.m_vertex2;
		t.m_vertex1 /= 2.0;
		t.m_vertex2 = vertices.m_vertex2;
		t.m_vertex2 += vertices.m_vertex3;
		t.m_vertex2 /= 2.0;
		t.m_vertex3 = vertices.m_vertex3;
		t.m_vertex3 += vertices.m_vertex1;
		t.m_vertex3 /= 2.0;
		(*this)( Triangle(vertices.m_vertex1, t.m_vertex1, t.m_vertex3), currentStep + 1 );
		(*this)( Triangle(t.m_vertex1, vertices.m_vertex2, t.m_vertex2), currentStep + 1 );
		(*this)( Triangle(t.m_vertex1, t.m_vertex2, t.m_vertex3), currentStep + 1 );
		(*this)( Triangle(t.m_vertex3, t.m_vertex2, vertices.m_vertex3), currentStep + 1 );
	}
	else
	{
		Point3 v = vertices.m_vertex1;
		v -= m_sphereCenter;
		v.normalize();
		v *= m_sphereRadius;
		m_vertices.push_back(v);
		v = vertices.m_vertex2;
		v -= m_sphereCenter;
		v.normalize();
		v *= m_sphereRadius;
		m_vertices.push_back(v);
		v = vertices.m_vertex3; 
		v -= m_sphereCenter;
		v.normalize();
		v *= m_sphereRadius;
		m_vertices.push_back(v);
	}
}

s_PointsComparator::s_PointsComparator()
{
}

void s_PointsComparator::setData(const Point3& axis, const std::vector<Point3>& points)
{
	m_axis = axis;
	m_points = points;
}

bool s_PointsComparator::operator ()(unsigned int id1, unsigned int id2) const
{
	if(id1 >= m_points.size() || id2 >= m_points.size())
		return false;

	if((m_points[id1]^m_points[id2])*m_axis > Scalar(0))
		return true;
	return false;
}

STP_BV::STP_BV():m_fastPatches(NULL),m_lastPatches(NULL),drawnGL_(false)
{

}

STP_BV::STP_BV(const STP_BV & bv):m_fastPatches(NULL),m_lastPatches(NULL),drawnGL_(bv.drawnGL_)
{
	for (size_t i=0;i<bv.m_patches.size();i++)
	{
		m_patches.push_back(bv.m_patches[i]->clone());
	}
	updateFastPatches();
}

STP_BV::~STP_BV()
{
	for (size_t i=0;i<m_patches.size();i++)
	{
		delete m_patches[i];
	}
	if (m_fastPatches!=NULL)
		delete[] m_fastPatches;
}


STP_BV & STP_BV::operator =(const STP_BV & bv)
{
	if (&bv!=this)
	{
		drawnGL_=bv.drawnGL_;
		m_patches.clear();
		for (size_t i=0;i<bv.m_patches.size();i++)
		{
			m_patches.push_back(bv.m_patches[i]->clone());
		}
		updateFastPatches();
	}
	return *this;
}

void STP_BV::computeArcPointsBetween(const Point3& p1, const Point3& p2, 
									 const Point3& center, double radius, int step, 
									 std::vector<Point3>* res) const
{


	Vector3 v1=p1-center, v2p=p2-center;

	double k=v1.norm();
	k=v2p.norm();

	k=(v2p.norm()+k)/2;


	v1.normalize();
	v2p.normalize();


	double angle=acos(v1*v2p)/(step);






	Vector3 v3=v1^v2p;

	v3.normalize();

	Vector3 v2=v3^v1;

	Matrix3x3 m(v1[0],v2[0],v3[0],
		v1[1],v2[1],v3[1],
		v1[2],v2[2],v3[2]);



	res->push_back(p1);

	double a=angle;
	for (int i=1;i<step;i++)
	{
		Point3 tmp((const double)cos(a),(const double)(sin(a)),(const double)0);
		tmp=(m*tmp)*k+center;
		res->push_back(tmp);
		a+=angle;

	}
	res->push_back(p2);



}

void STP_BV::computeConePointsBetween(const Point3& p1, const Point3& p2, 
									  double cosangle, Vector3 axis, int step, 
									  std::vector<Point3>* res)
{
	//axis.normalize(); //we're supposed to use already normalized axes in this programm

	double matrix[16]; // this will be passed to OpenGL functions so it has to be a double
	Point3 tmp1, tmp2;
	Point3 startp = p1 - axis*(p1*axis);
	Point3 endp = p2 -  axis* (p2*axis);
	startp.normalize();
	endp.normalize();
	double angle = startp[0] * endp[0] + startp[1] * endp[1] + startp[2] * endp[2];
	angle = acos(angle) * 180.0 / 3.14159265;
	angle /= step;

	res->push_back(p1);

	glPushMatrix();
	glLoadIdentity();
	glRotatef(angle, axis[0], axis[1], axis[2]);
	glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
	glPopMatrix();
	for(int i = 0 ; i < step - 1; ++i)
	{
		tmp1 = (*res)[i];
		tmp2[0] = matrix[0] * tmp1[0] + matrix[4] * tmp1[1] + matrix[8] * tmp1[2];
		tmp2[1] = matrix[1] * tmp1[0] + matrix[5] * tmp1[1] + matrix[9] * tmp1[2];
		tmp2[2] = matrix[2] * tmp1[0] + matrix[6] * tmp1[1] + matrix[10] * tmp1[2];
		res->push_back(tmp2);
	}
	res->push_back(p2);
}

Point3 STP_BV::computeLinesCommonPoint(const Point3& l1p1, const Point3& l1p2, 
									   const Point3& l2p1, const Point3& l2p2) const
{
	Vector3 v1, v2;
	v1 = l1p1 - l1p2;
	v2 = l2p1 - l2p2;

	double t;
	if( fabs(v2[0] * v1[1] - v1[0] * v2[1]) > 1e-8 )
	{
		t = (v2[0] * (l2p1[1] - l1p1[1]) + v2[1] * (l1p1[0] - l2p1[0])) / (v2[0] * v1[1] - v1[0] * v2[1]);
	}
	else if( fabs(v2[1] * v1[2] - v2[2] * v1[1])>1e-8 )
	{
		t = (v2[1] * (l2p1[2] - l1p1[2]) + v2[2] * (l1p1[1] - l2p1[1])) / (v2[1] * v1[2] - v2[2] * v1[1]);
	}
	else
	{
		t = (v2[2] * (l2p1[0] - l1p1[0]) + v2[0] * (l1p1[2] - l2p1[2])) / (v2[2] * v1[0] - v2[0] * v1[2]);
	}

	//Point3 res;
	return Point3(l1p1[0] + t * v1[0], l1p1[1] + t * v1[1], l1p1[2] + t * v1[2]);

	//return res;
}

void STP_BV::constructFromFile(const std::string& filename)
{
	std::ifstream is;
	int i, j;
	int ssnum, bsnum, tnum;
	int ssvvrnum;
	int outerSTP;
	Scalar cRadius, sRadius, cosangle;
	Scalar center[3];
	Scalar axis[3];
	std::vector<STP_VVR> ssvvr;
	STP_VVR dvvr[4];
	std::vector<Point3> patchesCenter;

	std::cout << std::endl << "START OBJECT CREATION" << std::endl;
#ifdef writeos2
	os2 << "DEBUT CREATION OBJET" << std::endl;
#endif
	is.open(filename.c_str());
	if(!is.is_open())
	{
		std::cout << "EXCEPTION : pas reussi a ouvrir le fichier" << std::endl;
		throw std::exception();
	}

	//small spheres
	STP_SmallSphere* ss;
	double _r,_R;
	is >>_r>>_R>> ssnum;
	if(ssnum <= 0)
	{
		std::cout << "EXCEPTION : the given source file doesn't contain any small spheres." << std::endl;
		throw std::exception();
	}
	for(i = 0 ; i < ssnum ; ++i)
	{
		is >> sRadius >> center[0] >> center[1] >> center[2];
		ss = new STP_SmallSphere(sRadius, Point3(center[0], center[1], center[2]));
		patchesCenter.push_back(Point3(center[0], center[1], center[2]));

		is >> ssvvrnum;
		ssvvr.resize(ssvvrnum);
		for(j = 0 ; j < ssvvrnum ; ++j)
		{
			is >> outerSTP >> cosangle >> axis[0] >> axis[1] >> axis[2];
			ssvvr[j].m_cosangle = cosangle;
			ssvvr[j].m_axis = Vector3(axis[0], axis[1], axis[2]);
			ssvvr[j].m_outerSTP = outerSTP;
			ssvvr[j].m_displayList;

		}
		ss->setVVR(ssvvr);

		addPatch(ss);
	}

	//big spheres
	Triangle vertices;
	STP_BigSphere* bigs;
	Vector3 normal;
	is >> bsnum;
	if(bsnum <= 0)
	{
		std::cout << "EXCEPTION : the given source file doesn't contain any big spheres." << std::endl;
		throw std::exception();
	}
	for(i = 0 ; i < bsnum ; ++i)
	{
		is >> sRadius >> center[0] >> center[1] >> center[2];
		bigs = new STP_BigSphere(sRadius, Point3(center[0], center[1], center[2]));
		patchesCenter.push_back(Point3(center[0], center[1], center[2]));

		//get the vertices
		is >> center[0] >> center[1] >> center[2];
		vertices.m_vertex1 = Point3(center[0], center[1], center[2]);
		is >> center[0] >> center[1] >> center[2];
		vertices.m_vertex2 = Point3(center[0], center[1], center[2]);
		is >> center[0] >> center[1] >> center[2];
		vertices.m_vertex3 = Point3(center[0], center[1], center[2]);

		//get the VVR info
		for(j = 0 ; j < 3 ; ++j)
		{
			is >> outerSTP >> axis[0] >> axis[1] >> axis[2];
			dvvr[j].m_cosangle = 0.0;
			dvvr[j].m_axis.Set(axis[0], axis[1], axis[2]);
			dvvr[j].m_outerSTP = outerSTP;
			dvvr[j].m_displayList=0;
		}
		bigs->setVVR(dvvr);

		addPatch(bigs);
	}

	//torus
	STP_Torus* t = NULL;
	bool isRealTorus;
	int torusCount = 0;
	//toruslinkedBV relatedBV;
	Point3 arcCenter;
	Point3 p1, p2, p3, p4;
	std::vector<Point3> computedPoints;
	std::vector<Point3> firstArc;
	std::vector<Point3> lastArc;

	is >> tnum;
	if(tnum <= 0)
	{
		std::cout << "EXCEPTION : the given source file doesn't contain any toruses." << std::endl;
		throw std::exception();
	}

	for(i = 0 ; i < tnum ; ++i)
	{
		is >> isRealTorus;
		if(isRealTorus)
			++torusCount;
		is >> cRadius >> sRadius;
		is >> center[0] >> center[1] >> center[2];
		is >> axis[0] >> axis[1] >> axis[2];
		if(isRealTorus)
			t = new STP_Torus(Vector3(axis[0], axis[1], axis[2]), Point3(center[0], center[1], center[2]), Scalar(cRadius), Scalar(sRadius));

		is >> outerSTP >> cosangle >> axis[0] >> axis[1] >> axis[2];
		dvvr[0].m_cosangle = cosangle;
		dvvr[0].m_axis.Set(axis[0], axis[1], axis[2]);
		dvvr[0].m_outerSTP = outerSTP;
		is >> outerSTP >> cosangle >> axis[0] >> axis[1] >> axis[2];
		dvvr[1].m_cosangle = cosangle;
		dvvr[1].m_axis.Set(axis[0], axis[1], axis[2]);
		dvvr[1].m_outerSTP = outerSTP;
		is >> outerSTP >> axis[0] >> axis[1] >> axis[2];
		dvvr[2].m_cosangle = 0.0;
		dvvr[2].m_axis.Set(axis[0], axis[1], axis[2]);
		dvvr[2].m_outerSTP = outerSTP;
		is >> outerSTP >> axis[0] >> axis[1] >> axis[2];
		dvvr[3].m_cosangle = 0.0;
		dvvr[3].m_axis.Set(axis[0], axis[1], axis[2]);
		dvvr[3].m_outerSTP = outerSTP;




		if(isRealTorus)
		{

			//save the data
			t->setVVR(dvvr);

			addPatch(t);
		}
	}

	is.close();
	updateFastPatches();


	/*os1 << std::endl << std::endl << "--- APRES CREATION DE TOUTES LES DONNEES ---" << std::endl; //DEBUG
	for(std::map<int, STP_STBVData>::iterator itmp = bvlist.begin() ; itmp != bvlist.end() ; ++itmp) //DEBUG
	{ //DEBUG
	os1 << std::endl << "BV " << itmp->second.m_BVID << std::endl; //DEBUG
	int j = 0; //DEBUG
	for(std::vector<STP_VVR>::iterator itmp2 = itmp->second.m_VVRlimits.begin() ; itmp2 != itmp->second.m_VVRlimits.end() ; ++itmp2) //DEBUG
	{ //DEBUG
	os1 << "axe " << j << " - cos : " << itmp2->m_cosangle; //DEBUG
	os1 << " ; outBV : " << itmp2->m_outerSTP << std::endl; //DEBUG
	os1 << itmp2->m_axis.dot(itmp->second.m_points[j]) << std::endl; //DEBUG
	os1 << itmp2->m_axis.dot(itmp->second.m_points[(j + 1)%(itmp->second.m_points.size())]) << std::endl; //DEBUG
	++j;
	} //DEBUG
	os1 << "points : " << std::endl; //DEBUG
	for(j = 0 ; j < itmp->second.m_points.size() ; ++j) //DEBUG
	{ //DEBUG
	os1 << "p" << j << " : " << itmp->second.m_points[j][0] << ", " << itmp->second.m_points[j][1] << ", " <<itmp->second.m_points[j][2] << std::endl; //DEBUG
	} //DEBUG
	} //DEBUG*/

#ifdef writeos1
	os1.close(); //DEBUG
#endif
#ifdef writeos2
	os2 << "FIN CREATION OBJET" << std::endl << std::endl << std::endl; //DEBUG
	os2.close(); //DEBUG
#endif
#ifdef writeos3
	os3.close(); //DEBUG
#endif
#ifdef writeos4
	os4.close(); //DEBUG
#endif
#ifdef writeos5
	os5.close(); //DEBUG
#endif
#ifdef writeos6
	os6.close(); //DEBUG
#endif
#ifdef writeos
	os.close(); //DEBUG
#endif
	std::cout << "OBJECT CREATED" << std::endl << std::endl << std::endl;
}






void STP_BV::constructFromFileWithGL(const std::string& filename)
{

	drawnGL_=true;
	std::ifstream is;
	int ssnum, bsnum, tnum;
	int ssvvrnum;
	int listID;
	int outerSTP;
	Scalar cRadius, sRadius, cosangle;
	Scalar center[3];
	Scalar axis[3];
	std::vector<STP_VVR> ssvvr;
	STP_VVR dvvr[4];
	int step = 7;
	int anglestep = 20;
	std::vector<Point3> patchesCenter;

	std::cout << std::endl << "START OBJECT CREATION" << std::endl;
#ifdef writeos2
	os2 << "DEBUT CREATION OBJET" << std::endl;
#endif
	is.open(filename.c_str());
	if(!is.is_open())
	{
		std::cout << "EXCEPTION : pas reussi a ouvrir le fichier" << std::endl;
		throw std::exception();
	}

	//small spheres
	STP_SmallSphere* ss;
	double _r,_R;
	is >>_r>>_R>> ssnum;
	if(ssnum <= 0)
	{
		std::cout << "EXCEPTION : the given source file doesn't contain any small spheres." << std::endl;
		throw std::exception();
	}
	for(int i = 0 ; i < ssnum ; ++i)
	{
		is >> sRadius >> center[0] >> center[1] >> center[2];
		ss = new STP_SmallSphere(sRadius, Point3(center[0], center[1], center[2]));
		patchesCenter.push_back(Point3(center[0], center[1], center[2]));

		is >> ssvvrnum;
		ssvvr.resize(ssvvrnum);
		for(int j = 0 ; j < ssvvrnum ; ++j)
		{
			is >> outerSTP >> cosangle >> axis[0] >> axis[1] >> axis[2];
			ssvvr[j].m_cosangle = cosangle;
			ssvvr[j].m_axis = Vector3(axis[0], axis[1], axis[2]);
			ssvvr[j].m_outerSTP = outerSTP;
			ssvvr[j].m_displayList;

		}
		ss->setVVR(ssvvr);

		addPatch(ss);
	}

	//big spheres
	Triangle vertices;
	STP_BigSphere* bigs;
	Vector3 normal;
	is >> bsnum;
	if(bsnum <= 0)
	{
		std::cout << "EXCEPTION : the given source file doesn't contain any big spheres." << std::endl;
		throw std::exception();
	}
	for(int i = 0 ; i < bsnum ; ++i)
	{
		is >> sRadius >> center[0] >> center[1] >> center[2];
		bigs = new STP_BigSphere(sRadius, Point3(center[0], center[1], center[2]));
		patchesCenter.push_back(Point3(center[0], center[1], center[2]));

		//get the vertices
		is >> center[0] >> center[1] >> center[2];
		vertices.m_vertex1 = Point3(center[0], center[1], center[2]);
		is >> center[0] >> center[1] >> center[2];
		vertices.m_vertex2 = Point3(center[0], center[1], center[2]);
		is >> center[0] >> center[1] >> center[2];
		vertices.m_vertex3 = Point3(center[0], center[1], center[2]);

		//create the BV displayList
		std::vector<Point3> spherePoints;
		SphereApproxim f(spherePoints, step, bigs->getCenter(), sRadius);
		f(vertices, 0);
		listID = glGenLists(1);
		glNewList(listID, GL_COMPILE);
		glColor3f(1, 0.9, 0.9);
		glTranslatef(bigs->getCenter()[0], bigs->getCenter()[1], bigs->getCenter()[2]);
		glBegin(GL_TRIANGLES);
		for(std::vector<Point3>::const_iterator it = spherePoints.begin() ; it != spherePoints.end() ; ++it)
		{
			normal = (*it) - bigs->getCenter();
			normal.normalize();
			glNormal3d(normal[0], normal[1], normal[2]);
			glVertex3d((*it)[0], (*it)[1], (*it)[2]);
		}
		glEnd();
		glEndList();
		bigs->setDisplayList(listID);

		//get the VVR info
		for(int j = 0 ; j < 3 ; ++j)
		{
			is >> outerSTP >> axis[0] >> axis[1] >> axis[2];
			dvvr[j].m_cosangle = 0.0;
			dvvr[j].m_axis.Set(axis[0], axis[1], axis[2]);
			dvvr[j].m_outerSTP = outerSTP;
			dvvr[j].m_displayList=0;
		}
		bigs->setVVR(dvvr);

		addPatch(bigs);
	}

	//torus
	STP_Torus* t = NULL;
	bool isRealTorus;
	int torusCount = 0;
	double r;
	//toruslinkedBV relatedBV;
	Point3 arcCenter;
	Point3 p1, p2, p3, p4;
	std::vector<Point3> computedPoints;
	std::vector<Point3> firstArc;
	std::vector<Point3> lastArc;

	is >> tnum;
	if(tnum <= 0)
	{
		std::cout << "EXCEPTION : the given source file doesn't contain any toruses." << std::endl;
		throw std::exception();
	}

	for(int i = 0 ; i < tnum ; ++i)
	{
		is >> isRealTorus;
		if(isRealTorus)
			++torusCount;
		is >> cRadius >> sRadius;
		is >> center[0] >> center[1] >> center[2];
		is >> axis[0] >> axis[1] >> axis[2];
		if(isRealTorus)
			t = new STP_Torus(Vector3(axis[0], axis[1], axis[2]), Point3(center[0], center[1], center[2]), Scalar(cRadius), Scalar(sRadius));

		is >> outerSTP >> cosangle >> axis[0] >> axis[1] >> axis[2];
		dvvr[0].m_cosangle = cosangle;
		dvvr[0].m_axis.Set(axis[0], axis[1], axis[2]);
		dvvr[0].m_outerSTP = outerSTP;
		is >> outerSTP >> cosangle >> axis[0] >> axis[1] >> axis[2];
		dvvr[1].m_cosangle = cosangle;
		dvvr[1].m_axis.Set(axis[0], axis[1], axis[2]);
		dvvr[1].m_outerSTP = outerSTP;
		is >> outerSTP >> axis[0] >> axis[1] >> axis[2];
		dvvr[2].m_cosangle = 0.0;
		dvvr[2].m_axis.Set(axis[0], axis[1], axis[2]);
		dvvr[2].m_outerSTP = outerSTP;
		is >> outerSTP >> axis[0] >> axis[1] >> axis[2];
		dvvr[3].m_cosangle = 0.0;
		dvvr[3].m_axis.Set(axis[0], axis[1], axis[2]);
		dvvr[3].m_outerSTP = outerSTP;

		if(isRealTorus)
		{
			//get the torus displayLists IDs
			listID = glGenLists(5);
		}

		//torus-small sphere VVR (real cones)
		if(isRealTorus)
			computedPoints.clear();
		p1 = patchesCenter[dvvr[0].m_outerSTP] - patchesCenter[dvvr[2].m_outerSTP];
		p1.normalize();
		p2 = patchesCenter[dvvr[0].m_outerSTP] - patchesCenter[dvvr[3].m_outerSTP];
		p2.normalize();
		if(isRealTorus)
		{
			if(  (p1^p2)*dvvr[0].m_axis < 0.0)
				computeConePointsBetween(p2, p1, dvvr[0].m_cosangle, dvvr[0].m_axis, anglestep, &computedPoints);
			else
				computeConePointsBetween(p1, p2, dvvr[0].m_cosangle, dvvr[0].m_axis, anglestep, &computedPoints);
			glNewList(listID, GL_COMPILE);
			glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.5 * dvvr[0].m_axis[0], 0.5 * dvvr[0].m_axis[1], 0.5 * dvvr[0].m_axis[2]);
			glEnd();
			glColor3f(0.74 + i * 0.04, 0.85, 0.95);
			glBegin(GL_TRIANGLES);
			for(size_t j = 0 ; j < computedPoints.size() - 1 ; ++j)
			{
				glVertex3f(computedPoints[j][0], computedPoints[j][1], computedPoints[j][2]);
				glVertex3f(0.0, 0.0, 0.0);
				glVertex3f(computedPoints[j+1][0], computedPoints[j+1][1], computedPoints[j+1][2]);
			}
			glEnd();
			glEndList();
			dvvr[0].m_displayList = listID;
		}

		//torus-small sphere VVR (real cones)
		if(isRealTorus)
			computedPoints.clear();
		p1 = patchesCenter[dvvr[1].m_outerSTP] - patchesCenter[dvvr[3].m_outerSTP];
		p1.normalize();
		p2 = patchesCenter[dvvr[1].m_outerSTP] - patchesCenter[dvvr[2].m_outerSTP];
		p2.normalize();
		if(isRealTorus)
		{
			if( ( p1^p2)*dvvr[1].m_axis < 0.0)
				computeConePointsBetween(p2, p1, dvvr[1].m_cosangle, dvvr[1].m_axis, anglestep, &computedPoints);
			else
				computeConePointsBetween(p1, p2, dvvr[1].m_cosangle, dvvr[1].m_axis, anglestep, &computedPoints);
			glNewList(listID + 1, GL_COMPILE);
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.5 * dvvr[1].m_axis[0], 0.5 * dvvr[1].m_axis[1], 0.5 * dvvr[1].m_axis[2]);
			glEnd();
			glColor3f(0.45 + i * 0.04, 0.84, 0.4);
			glBegin(GL_TRIANGLES);
			for(size_t j = 0 ; j < computedPoints.size() - 1 ; ++j)
			{
				normal=computedPoints[j]^computedPoints[j+1];

				normal.normalize();

				glNormal3f(normal[0],normal[1],normal[2]);
				glVertex3f(computedPoints[j][0], computedPoints[j][1], computedPoints[j][2]);
				glVertex3f(0.0, 0.0, 0.0);
				glVertex3f(computedPoints[j+1][0], computedPoints[j+1][1], computedPoints[j+1][2]);
			}
			glEnd();
			glEndList();
			dvvr[1].m_displayList = listID + 1;
		}

		//torus-big sphere VVR (plane)
		if(isRealTorus)
			computedPoints.clear();
		p1 = patchesCenter[dvvr[0].m_outerSTP] - patchesCenter[dvvr[2].m_outerSTP];
		p1.normalize();
		p2 = patchesCenter[dvvr[1].m_outerSTP] - patchesCenter[dvvr[2].m_outerSTP];
		p2.normalize();
		if(isRealTorus)
		{
			computeArcPointsBetween(p2, p1, Point3(0.0, 0.0, 0.0), 1.00, step, &computedPoints);
			//create and register the displayList
			glNewList(listID + 2, GL_COMPILE);
			glColor3f(1.0, 0.59, 0.0);
			glBegin(GL_TRIANGLES);
			for(size_t j = 0 ; j < computedPoints.size() - 1 ; ++j)
			{




				normal=computedPoints[j]^computedPoints[j+1];
				normal.normalize();

				glNormal3f(normal[0],normal[1],normal[2]);
				glVertex3f(computedPoints[j][0], computedPoints[j][1], computedPoints[j][2]);
				glVertex3f(0.0, 0.0, 0.0);
				glVertex3f(computedPoints[j+1][0], computedPoints[j+1][1], computedPoints[j+1][2]);
			}
			glEnd();
			glEndList();
			dvvr[2].m_displayList = listID + 2;
		}

		//torus-big sphere VVR (plane)
		if(isRealTorus)
			computedPoints.clear();
		p1 = patchesCenter[dvvr[0].m_outerSTP] - patchesCenter[dvvr[3].m_outerSTP];
		p1.normalize();
		p2 = patchesCenter[dvvr[1].m_outerSTP] - patchesCenter[dvvr[3].m_outerSTP];
		p2.normalize();
		if(isRealTorus)
		{
			computeArcPointsBetween(p1,p2, Point3(0.0, 0.0, 0.0), 1.00, step, &computedPoints);
			//create and register the displayList
			glNewList(listID + 3, GL_COMPILE);
			glColor3f(1.0, 1.0, 0.3);
			glBegin(GL_TRIANGLES);
			for(size_t j = 0 ; j < computedPoints.size() - 1 ; ++j)
			{


				normal=computedPoints[j]^computedPoints[j+1];
				normal.normalize();

				glNormal3f(normal[0],normal[1],normal[2]);
				glVertex3f(computedPoints[j][0], computedPoints[j][1], computedPoints[j][2]);
				glVertex3f(0.0, 0.0, 0.0);
				glVertex3f(computedPoints[j+1][0], computedPoints[j+1][1], computedPoints[j+1][2]);
			}
			glEnd();
			glEndList();
			dvvr[3].m_displayList = listID + 3;
		}

		if(isRealTorus)
		{
			//get the data for the torus displayList
			p1 = patchesCenter[dvvr[0].m_outerSTP] - patchesCenter[dvvr[2].m_outerSTP];
			p1.normalize();
			p1 *= sRadius;
			p1 += patchesCenter[dvvr[2].m_outerSTP];
			p2 = patchesCenter[dvvr[1].m_outerSTP] - patchesCenter[dvvr[2].m_outerSTP];
			p2.normalize();
			p2 *= sRadius;
			p2 += patchesCenter[dvvr[2].m_outerSTP];
			p3 = patchesCenter[dvvr[1].m_outerSTP] - patchesCenter[dvvr[3].m_outerSTP];
			p3.normalize();
			p3 *= sRadius;
			p3 += patchesCenter[dvvr[3].m_outerSTP];
			p4 = patchesCenter[dvvr[0].m_outerSTP] - patchesCenter[dvvr[3].m_outerSTP];
			p4.normalize();
			p4 *= sRadius;
			p4 += patchesCenter[dvvr[3].m_outerSTP];

			firstArc.clear();
			lastArc.clear();
			computedPoints.clear();
			computeArcPointsBetween(p1, p2, patchesCenter[dvvr[2].m_outerSTP], sRadius, step, &firstArc);
			computeArcPointsBetween(p4, p3, patchesCenter[dvvr[3].m_outerSTP], sRadius, step, &lastArc);
			r = sRadius - (patchesCenter[dvvr[0].m_outerSTP] - patchesCenter[dvvr[2].m_outerSTP]).norm();
			computeArcPointsBetween(p1, p4, patchesCenter[dvvr[0].m_outerSTP], r, step, &computedPoints);
			for(int j = 1 ; j < step ; ++j)
			{


				arcCenter = computeLinesCommonPoint(patchesCenter[dvvr[0].m_outerSTP], 
					patchesCenter[dvvr[1].m_outerSTP],
					patchesCenter[dvvr[2].m_outerSTP],
					firstArc[j]);
				r = sRadius - (arcCenter - patchesCenter[dvvr[2].m_outerSTP]).norm();
				computeArcPointsBetween(firstArc[j], lastArc[j], arcCenter, r, step, &computedPoints);
			}
			r = sRadius - (patchesCenter[dvvr[1].m_outerSTP] - patchesCenter[dvvr[2].m_outerSTP]).norm();
			computeArcPointsBetween(p2, p3, patchesCenter[dvvr[1].m_outerSTP], r, step, &computedPoints);

			//create the torus displayList
			glNewList(listID + 4, GL_COMPILE);
			glColor3f(1, .5, .5);
			glBegin(GL_TRIANGLES);
			for(int j = 0 ; j < step ; ++j)
			{
				for(int k = 0 ; k < step ; ++k)
				{   
					normal = computedPoints[j * (step + 1) + k] - computeLinesCommonPoint(patchesCenter[dvvr[0].m_outerSTP], 
						patchesCenter[dvvr[1].m_outerSTP],
						patchesCenter[dvvr[2].m_outerSTP],
						firstArc[j]);
					normal.normalize();
					glNormal3d(normal[0], normal[1], normal[2]);
					glVertex3f(computedPoints[j * (step + 1) + k][0], computedPoints[j * (step + 1) + k][1], computedPoints[j * (step + 1) + k][2]);

					normal = computedPoints[(j+1) * (step + 1) + k] - computeLinesCommonPoint(patchesCenter[dvvr[0].m_outerSTP], 
						patchesCenter[dvvr[1].m_outerSTP],
						patchesCenter[dvvr[2].m_outerSTP],
						firstArc[j+1]);
					normal.normalize();
					glNormal3d(normal[0], normal[1], normal[2]);
					glVertex3f(computedPoints[(j+1) * (step + 1) + k][0], computedPoints[(j+1) * (step + 1) + k][1], computedPoints[(j+1) * (step + 1) + k][2]);

					normal = computedPoints[(j+1) * (step + 1) + k+1] - computeLinesCommonPoint(patchesCenter[dvvr[0].m_outerSTP], 
						patchesCenter[dvvr[1].m_outerSTP],
						patchesCenter[dvvr[2].m_outerSTP],
						firstArc[j+1]);
					normal.normalize();
					glNormal3d(normal[0], normal[1], normal[2]);
					glVertex3f(computedPoints[(j+1) * (step + 1) + k+1][0], computedPoints[(j+1) * (step + 1) + k+1][1], computedPoints[(j+1) * (step + 1) + k+1][2]);

					normal = computedPoints[(j+1) * (step + 1) + k+1] - computeLinesCommonPoint(patchesCenter[dvvr[0].m_outerSTP], 
						patchesCenter[dvvr[1].m_outerSTP],
						patchesCenter[dvvr[2].m_outerSTP],
						firstArc[j+1]);
					normal.normalize();
					glNormal3d(normal[0], normal[1], normal[2]);
					glVertex3f(computedPoints[(j+1) * (step + 1) + k+1][0], computedPoints[(j+1) * (step + 1) + k+1][1], computedPoints[(j+1) * (step + 1) + k+1][2]);

					normal = computedPoints[(j) * (step + 1) + k+1] - computeLinesCommonPoint(patchesCenter[dvvr[0].m_outerSTP], 
						patchesCenter[dvvr[1].m_outerSTP],
						patchesCenter[dvvr[2].m_outerSTP],
						firstArc[j]);
					normal.normalize();
					glNormal3d(normal[0], normal[1], normal[2]);
					glVertex3f(computedPoints[j * (step + 1) + k+1][0], computedPoints[j * (step + 1) + k+1][1], computedPoints[j * (step + 1) + k+1][2]);

					normal = computedPoints[j * (step + 1) + k] - computeLinesCommonPoint(patchesCenter[dvvr[0].m_outerSTP], 
						patchesCenter[dvvr[1].m_outerSTP],
						patchesCenter[dvvr[2].m_outerSTP],
						firstArc[j]);
					normal.normalize();
					glNormal3d(normal[0], normal[1], normal[2]);
					glVertex3f(computedPoints[j * (step + 1) + k][0], computedPoints[j * (step + 1) + k][1], computedPoints[j * (step + 1) + k][2]);
				}
			}
			glEnd();
		
			glEndList();
			t->setDisplayList(listID + 4);

			//save the data
			t->setVVR(dvvr);

			addPatch(t);
		}
	}

	is.close();
	updateFastPatches();


	/*os1 << std::endl << std::endl << "--- APRES CREATION DE TOUTES LES DONNEES ---" << std::endl; //DEBUG
	for(std::map<int, STP_STBVData>::iterator itmp = bvlist.begin() ; itmp != bvlist.end() ; ++itmp) //DEBUG
	{ //DEBUG
	os1 << std::endl << "BV " << itmp->second.m_BVID << std::endl; //DEBUG
	int j = 0; //DEBUG
	for(std::vector<STP_VVR>::iterator itmp2 = itmp->second.m_VVRlimits.begin() ; itmp2 != itmp->second.m_VVRlimits.end() ; ++itmp2) //DEBUG
	{ //DEBUG
	os1 << "axe " << j << " - cos : " << itmp2->m_cosangle; //DEBUG
	os1 << " ; outBV : " << itmp2->m_outerSTP << std::endl; //DEBUG
	os1 << itmp2->m_axis.dot(itmp->second.m_points[j]) << std::endl; //DEBUG
	os1 << itmp2->m_axis.dot(itmp->second.m_points[(j + 1)%(itmp->second.m_points.size())]) << std::endl; //DEBUG
	++j;
	} //DEBUG
	os1 << "points : " << std::endl; //DEBUG
	for(j = 0 ; j < itmp->second.m_points.size() ; ++j) //DEBUG
	{ //DEBUG
	os1 << "p" << j << " : " << itmp->second.m_points[j][0] << ", " << itmp->second.m_points[j][1] << ", " <<itmp->second.m_points[j][2] << std::endl; //DEBUG
	} //DEBUG
	} //DEBUG*/

#ifdef writeos1
	os1.close(); //DEBUG
#endif
#ifdef writeos2
	os2 << "FIN CREATION OBJET" << std::endl << std::endl << std::endl; //DEBUG
	os2.close(); //DEBUG
#endif
#ifdef writeos3
	os3.close(); //DEBUG
#endif
#ifdef writeos4
	os4.close(); //DEBUG
#endif
#ifdef writeos5
	os5.close(); //DEBUG
#endif
#ifdef writeos6
	os6.close(); //DEBUG
#endif
#ifdef writeos
	os.close(); //DEBUG
#endif
	std::cout << "OBJECT CREATED" << std::endl << std::endl << std::endl;
}




void STP_BV::saveTreeInFile(const std::string& treefilename, ArchiveType type)
{
	std::ofstream os(treefilename.c_str(), std::ios::binary);

	if(!os.is_open())
	{
		std::cout << "EXCEPTION in loadTreeFromFile : could not open given file" << std::endl;
		throw std::exception();
	}

	std::cout << "START SAVING THE OBJECT TREE STRUCTURE" << std::endl;
	if(type == BINARY_ARCHIVE)
	{

	}
	else //(type == TEXT_ARCHIVE)
	{

	}

	os.close();
	std::cout << "THE OBJECT TREE STRUCTURE IS SAVED" << std::endl;
}

void STP_BV::loadTreeFromFile(const std::string& treefilename, ArchiveType type)
{
	std::ifstream is(treefilename.c_str(), std::ios::binary);

	std::cout << "START LOADING THE OBJECT TREE STRUCTURE" << std::endl; //DEBUG
#ifdef writeos2
	os2 << "DEBUT LECTURE ARBRE" << std::endl;
#endif
	if(!is.is_open())
	{
		std::cout << "EXCEPTION in loadTreeFromFile : could not open given file" << std::endl;
		throw std::exception();
	}

	if(type == BINARY_ARCHIVE)
	{
	}
	else //(type == TEXT_ARCHIVE)
	{
	}

	std::cout << "OBJECT TREE STRUCTURE LOADED" << std::endl; //DEBUG

	is.close();
}

void STP_BV::addPatch(STP_Feature* patch)
{
	m_patches.push_back(patch);
}

Point3 STP_BV::computeCenter(const std::vector<Point3>& points)
{
	Point3 res(Scalar(0), Scalar(0), Scalar(0));
	for(std::vector<Point3>::const_iterator it = points.begin() ; it != points.end() ; ++it)
	{
		res += *it;
	}
	res /= points.size();

	return res;
}

void STP_BV::updateFastPatches()
{
	if (m_fastPatches!=NULL)
	{
		delete[] m_fastPatches;
	}

	if (m_patches.size()>0)
	{
		m_fastPatches=new STP_Feature*[m_patches.size()];
		for (size_t i=0;i<m_patches.size();i++)
		{
			m_fastPatches[i]=m_patches[i];	
		}

		m_lastPatches=&m_fastPatches[m_patches.size()];
		m_patchesSize=m_patches.size();
	}
	else
	{
		m_patchesSize=0;
		m_lastPatches=m_fastPatches=NULL;

	}

}





void STP_BV::drawGLInLocalCordinates()
{
	if (drawnGL_)
	{

		for(std::vector<STP_Feature*>::const_iterator it = m_patches.begin() ; it != m_patches.end() ; ++it)
			(*it)->GLdisplay();

	}
}

void STP_BV::GLdisplayVVR() const
{
	for(std::vector<STP_Feature*>::const_iterator it = m_patches.begin() ; it != m_patches.end() ; ++it)
		(*it)->GLdisplayVVR();
}



Scalar STP_BV::supportH(const Vector3& v) const 
{

	int k;

	//A.E. : we use the default supportH function, cf DT_Convex.h
	return v*l_Support(v,k);
}

Point3 STP_BV::l_Support(const Vector3& v,int& lastFeature) const 
{


#ifdef NAIVESUPPORT
	return supportNaive(v);
#endif
#ifdef FARTHESTSUPPORT
	return supportFarthestNeighbour(v,lastFeature);
#endif
#ifdef FARTHESTSUPPORTPRIME
	return supportFarthestNeighbourPrime(v,lastFeature);
#endif
#ifdef FIRSTSUPPORT
	return supportFirstNeighbour(v,lastFeature);
#endif
#ifdef FIRSTSUPPORTPRIME
	return supportFirstNeighbourPrime(v,lastFeature);
#endif
#ifdef HYBRIDSUPPORT
	return supportHybrid(v,lastFeature);
#endif
#ifdef TREESUPPORT
	return supportTree(vp);
#endif

}

Point3 STP_BV::supportNaive(const Vector3& v) const
{
	std::vector<STP_Feature*>::const_iterator currentBV = m_patches.begin();
	bool found = false;


	while( (currentBV != m_patches.end()) && !(found = (*currentBV)->isHere(v)) )
	{
		++currentBV;
	}

	//TODO : gerer le cas ou on n'a pas trouve la zone !!!
	if(!found)
	{
		std::cout << "Probleme zuo naive !!!" << std::endl;
		if(m_patches.begin() != m_patches.end())
			return (*m_patches.begin())->support(v);
		else
			return Point3(0.0, 0.0, 0.0);
	}

	return (*currentBV)->support(v);
}

Point3 STP_BV::supportFarthestNeighbour(const Vector3& v,int& lastFeature) const
{
	STP_Feature* currentBV;
	//A.E. : We need to remember the previous Voronoi region we were in 

#ifdef REMEMBER_LAST_FEATURE
	if (lastFeature!=-1) {
		currentBV = m_patches[lastFeature];
    }
	else {
		currentBV = *(m_patches.begin());//first voronoi region search
    }
#else
	currentBV = *(m_patches.begin());//first voronoi region search
#endif

	//A.E. : the following hash table is not used in the function in its current version and is therefore commented 
	//A.E. : it seems me wrong to begin with 1 
    size_t i = 0;
    bool found = false;



	while( (i < m_patches.size()) && !(found = currentBV->isHereFarthestNeighbour(v)) )
	{
		lastFeature = currentBV->getNextBV(0);//go to the neighbour feature which common limit with the current is farthest from the vector

		currentBV = m_patches[lastFeature];
		++i;


	}






	if(!found)
	{
		std::cout << "Probleme zuo farthest !!!" << std::endl;
		if(m_patches.begin() != m_patches.end())
			return (*m_patches.begin())->support(v);
		else
			return Point3(0.0, 0.0, 0.0);
	}



	return currentBV->support(v);
}



Point3 STP_BV::supportFarthestNeighbourPrime(const Vector3& v,int& lastFeature) const
{
	STP_Feature* currentBV;
	//A.E. : We need to remember the previous Voronoi region we were in 

#ifdef REMEMBER_LAST_FEATURE
	if (lastFeature!=-1)
		currentBV = m_patches[lastFeature];
	else
		currentBV = *(m_patches.begin());//first voronoi region search

#else
	currentBV = *(m_patches.begin());//first voronoi region search
#endif


	//A.E. : the following hash table is not used in the function in its current version and is therefore commented 

	bool found = false;
	//A.E. : it seems me wrong to begin with 1 

    size_t i = 0;

	while( (i < m_patches.size()) && !(found = currentBV->isHereFarthestNeighbourPrime(v)) )
	{
		lastFeature = currentBV->getNextBVPrime();//go to the neighbour feature which common limit with the current is farthest from the vector

		currentBV = m_patches[lastFeature];
		++i;
	}






	if(!found)
	{
#ifdef SUPPORT_DEBUG
		std::cout << "Probleme zuo farthest !!!" << std::endl;
#endif
		return supportNaive(v);
		if(m_patches.begin() != m_patches.end())
			return (*m_patches.begin())->support(v);
		else
			return Point3(0.0, 0.0, 0.0);
	}


	//A.E. : test avec function naive 

	return currentBV->support(v);
}



Point3 STP_BV::supportFirstNeighbour(const Vector3& v,int& lastFeature) const
{
	STP_Feature* currentBV;
	//A.E. : We need to remember the previous Voronoi region we were in 

#ifdef REMEMBER_LAST_FEATURE
	if (lastFeature!=-1)
		currentBV = m_patches[lastFeature];
	else
		currentBV = *(m_patches.begin());//first voronoi region search

#else
	currentBV = *(m_patches.begin());//first voronoi region search
#endif

	/////A.E. : the following hash table is not used in the function in its current version and is therefore commented
	bool found = false;



	/////A.E. : it seems me wrong to begin with 1
	size_t i = 0;



	while( (i < m_patches.size()) && !(found = currentBV->isHereFirstNeighbour(v)) )
	{

		lastFeature = currentBV->getNextBVPrime();//go to the neighbour feature which common limit with the current is farthest from the vector

		currentBV = m_patches[lastFeature];
		++i;
	}









	if(!found)
	{

		std::cout << "Probleme zuo first !!!" << std::endl;
		if(m_patches.begin() != m_patches.end())
			return (*m_patches.begin())->support(v);
		else
			return Point3(0.0, 0.0, 0.0);
	}




	return currentBV->support(v);
}




Point3 STP_BV::supportFirstNeighbourPrime(const Vector3& v,int& lastFeature) const
{
	STP_Feature* currentBV;

#ifdef REMEMBER_LAST_FEATURE
	if (lastFeature!=-1)
		currentBV =m_fastPatches[lastFeature];
	else
	{
		currentBV = *m_fastPatches;//first voronoi region search
		lastFeature=0;
	}

#else
	currentBV = *(m_patches.begin());//first voronoi region search
#endif



	bool found = false;


	int i = 0;
	int idp=-1; //previous id (used to remember from witch vvr we arrived in the current


	while( (i < m_patchesSize) && !(found = currentBV->isHereFirstNeighbourPrime(v,idp)) )
	{
		idp=lastFeature;		
		lastFeature = currentBV->getNextBVPrime();//go to the neighbour

		currentBV = m_fastPatches[lastFeature];
		++i;
	}

#ifdef COUNTER
	std::cout<<i<<' ';
#endif




	if(!found)
	{
#ifdef SUPPORT_DEBUG
		std::cout << "Probleme zuo first prime !!!" << std::endl;
#endif
		return supportFarthestNeighbourPrime(v,lastFeature);
	}



	return currentBV->support(v);
}





Point3 STP_BV::supportHybrid(const Vector3& v,int& lastFeature) const
{
	STP_Feature* currentBV;

#ifdef REMEMBER_LAST_FEATURE
	if (lastFeature!=-1)
		currentBV =m_fastPatches[lastFeature];
	else
	{
		currentBV = *m_fastPatches;//first voronoi region search
		lastFeature=0;
	}

#else
	currentBV = *(m_patches.begin());//first voronoi region search
#endif



	bool found = false;


	int i = 0;
	int idp=-1; //previous id (used to remember from witch vvr we arrived in the current


	while( (i < m_patchesSize) && !(found = currentBV->isHereHybrid(v,idp)) )
	{
		idp=lastFeature;		
		lastFeature = currentBV->getNextBVPrime();//go to the neighbour

		currentBV = m_fastPatches[lastFeature];
		++i;
	}

#ifdef COUNTER
	std::cout<<i<<' ';
#endif




	if(!found)
	{
#ifdef SUPPORT_DEBUG
		std::cout << "Probleme zuo hybrid !!!" << std::endl;
#endif
		return supportFarthestNeighbourPrime(v,lastFeature);
	}



	return currentBV->support(v);
}






bool STP_BV::ray_cast(const Point3& source, const Point3& target,
					  Scalar& param, Vector3& normal) const 
{
	return false;
}

S_Object::S_ObjectType STP_BV::getType() const
{
	return S_Object::TSTP_BV;
}

int STP_BV::getFeaturesNumber()
{
	return m_patches.size();
}
