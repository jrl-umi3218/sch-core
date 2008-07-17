#ifndef __STP_BV_H
#define __STP_BV_H

#pragma once
#include "..\s_object\s_object.h"
#include "STP_Feature.h"


#include <vector>
#include <list>
#include <map>

namespace SCD
{

	enum ArchiveType
	{
		BINARY_ARCHIVE,
		TEXT_ARCHIVE
	};

	/*!  \struct s_toruslinkedBV
	*  \brief Stores the IDs of the BV to which a torus is linked.
	*  \author Cochet-Grasset Amelie
	*  \date    september 2007
	*/
	typedef struct s_toruslinkedBV
	{
		int buffer[4];
	} toruslinkedBV;

	/*!  \struct s_Triangle
	*  \brief Defines a triangle
	*  \author Cochet-Grasset Amelie
	*  \date    september 2007
	*/
	typedef struct s_Triangle
	{
		/*! 
		*  \brief Default constructor
		*/
		s_Triangle() {};
		/*! 
		*  \brief Constructor
		*  \param vertex1 first vertex of the triangle
		*  \param vertex2 second vertex of the triangle
		*  \param vertex3 third vertex of the triangle
		*/
		s_Triangle(const Point3& vertex1, const Point3& vertex2, const Point3& vertex3);

		Point3 m_vertex1;
		Point3 m_vertex2;
		Point3 m_vertex3;
	} Triangle;

	/*!  \struct s_SphereApproxim
	*  \brief Functor
	*  \author Cochet-Grasset Amelie
	*  \date    september 2007
	*
	*  
	*/
	typedef struct s_SphereApproxim
	{
		/*! 
		*  \brief Constructor
		*  \param vertices
		*  \param step
		*  \param sphereCenter
		*  \param sphereRadius
		*/
		s_SphereApproxim(std::vector<Point3>& vertices, int step, const Point3& sphereCenter, double sphereRadius);

		/*! 
		*  \brief operator parenthesis
		*  \param vertices
		*  \param currentStep
		*/
		void operator ()(const Triangle& vertices, const int& currentStep) const;

		std::vector<Point3>& m_vertices;
		int m_step;
		Point3 m_sphereCenter;
		float m_sphereRadius;
	} SphereApproxim;

	/*!  \class s_PointsComparator
	*  \brief Functor
	*  \author Cochet-Grasset Amelie
	*  \date    september 2007
	*
	*  
	*/
	typedef struct s_PointsComparator: public std::binary_function<const Point3&, const Point3&, bool>
	{
		/*! 
		*  \brief Default constructor
		*/
		s_PointsComparator();

		/*! 
		*  \brief Constructor
		*  \param axis
		*  \param points
		*/
		void setData(const Point3& axis, const std::vector<Point3>& points);

		/*! 
		*  \brief operator parenthesis
		*  \param id1
		*  \param id2
		*/
		bool operator ()(int id1, int id2) const;

		Point3 m_axis;
		std::vector<Point3> m_points;
	} PointsComparator;


	class STP_BV :
		public S_Object
	{
	public:
		STP_BV(void);
		STP_BV(const STP_BV&);


		virtual ~STP_BV(void);



		virtual STP_BV & operator=(const STP_BV&);


		virtual Point3  n_Support(const Vector3& v, int& lastFeature)const;

		virtual S_ObjectType getType() const;

		virtual void drawGLInLocalCordinates();



		/*!
		*  \brief Constructs the object from a file describing its STP_BV decomposition
		*  \param filename path to the file describing the STP_BV decomposition of the object
		*
		*/
		virtual void constructFromFile(const std::string& filename);


		/*!
		*  \brief Constructs the object from a file describing its STP_BV decomposition
		*  \param filename path to the file describing the STP_BV decomposition of the object
		*
		* This method computes all the needed data for display and every distance calculation method.
		*/
		virtual void constructFromFileWithGL(const std::string& filename);


		/*!
		*  \brief 
		*  \param treefilename path to the binary file to contain the tree of the object
		*  \param type kind of Boost archive to use. Currently either BINARY_ARCHIVE or TEXT_ARCHIVE (this is default value)
		*  \warning Binary archives are platform dependent.
		*/
		void saveTreeInFile(const std::string& treefilename, ArchiveType type = TEXT_ARCHIVE);

		/*!
		*  \brief Adds a bouding volume to the object
		*  \param patch bounding volume to add to the object
		*/
		void addPatch(STP_Feature* patch);


		/*! 
		*  \brief Displays the limits of the object's voronoi regions
		*/
		void GLdisplayVVR() const;
		/*!
		*  \brief Print the support tree in a file
		*  \param filename name of the file
		*/
		void printSupportTree(std::string filename) const;

		/*!
		*  \brief
		*  \param v direction
		*/
		virtual Scalar supportH(const Vector3& v) const;

		/*!
		*  \brief
		*  \param v direction
		*/
		virtual Point3 supportNaive(const Vector3& v) const;
		/*!
		*  \brief
		*  \param v direction
		*/
		virtual Point3 supportFarthestNeighbour(const Vector3& v,int& lastFeature) const;
		/*!
		*  \brief
		*  \param v direction
		*/

		virtual Point3 supportFarthestNeighbourPrime(const Vector3& v,int& lastFeature) const;
		/*! 
		*  \brief
		*  \param v direction
		*/


		virtual Point3 supportFirstNeighbour(const Vector3& v,int& lastFeature) const;
		/*!
		*  \brief gives the support for a vector using the First neighbour method.
		*  \param v direction
		*/

		virtual Point3 supportFirstNeighbourPrime(const Vector3& v,int& lastFeature) const;


		/*!
		*  \brief I don't know
		*  \param source
		*  \param target
		*  \param param
		*  \param normal
		*/
		virtual bool ray_cast(const Point3& source, const Point3& target,
			Scalar& param, Vector3& normal) const;
	public: //DEBUG
		//protected:

		/*!
		*  \brief Load the tree structure of the object from a file
		*  \param treefilename path to the binary file containing the tree of the object
		*
		* This uses Boost serialization library.
		*/
		void loadTreeFromFile(const std::string& treefilename, ArchiveType type = TEXT_ARCHIVE);

		/*!
		*  \brief Computes the points of an arc
		*  \param p1 first point of the arc
		*  \param p2 last point of the arc
		*  \param center center around which the arc revolves
		*  \param radius radius of the arc
		*  \param step number of subdivisions
		*  \param res vector to store the resulting points (including first and last points)
		*/
		void computeArcPointsBetween(const Point3& p1, const Point3& p2, const Point3& center, double radius, int step, std::vector<Point3>* res) const;
		/*!
		*  \brief Computes the points of
		*  \param p1 first point
		*  \param p2 last point
		*  \param cosangle no use
		*  \param axis axis of the cone
		*  \param step number of subdivision
		*  \param res vector to store the resulting points (including first and last points)
		*/
		void computeConePointsBetween(const Point3& p1, const Point3& p2, double cosangle, Vector3 axis, int step, std::vector<Point3>* res);
		/*!
		*  \brief Computes the intersection of two segments
		*  \param l1p1 first point of the first line
		*  \param l1p2 last point of the first line
		*  \param l2p1 first point of the second line
		*  \param l2p2 last point of the second line
		*  \return the result
		*/
		Point3 computeLinesCommonPoint(const Point3& l1p1, const Point3& l1p2,
			const Point3& l2p1, const Point3& l2p2) const;


		/*!
		*  \brief Computes the center of a surface defined by a list of points
		*  \param points vector containing all the points
		*  \return the center
		*/
		Point3 computeCenter(const std::vector<Point3>& points);


		/*!
		*  \brief Updates the dynamical array fastPatches. Must be called after each patches modification
		* 
		*/
		void updateFastPatches();





	protected:
		std::vector<STP_Feature*> m_patches;

		STP_Feature * * m_fastPatches;
		STP_Feature * * m_lastPatches;
		int m_patchesSize;
		bool drawnGL_;

	};
}
#endif