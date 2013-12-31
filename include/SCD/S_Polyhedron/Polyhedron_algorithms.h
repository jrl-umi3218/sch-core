#pragma once

#ifndef _POLYHEDRON_ALGORITHMS
#define _POLYHEDRON_ALGORITHMS

#include <SCD/Matrix/SCD_Types.h>
#include <SCD/S_Polyhedron/S_PolyhedronVertex.h>

#include <string>
#include <vector>

namespace SCD
{
	struct PolyhedronTriangle
	{
  		unsigned int a,b,c;
	  	Vector3 normal;
    public:
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & a;
        ar & b;
        ar & c;
        ar & normal;
      }
	};

	struct Polyhedron_algorithms
	{
	public:
		SCD_API Polyhedron_algorithms(void);
		SCD_API Polyhedron_algorithms(const Polyhedron_algorithms&);

		SCD_API ~Polyhedron_algorithms(void);

		SCD_API const Polyhedron_algorithms & operator=(const Polyhedron_algorithms&);


		/*! 
		*  \brief updates the fast access arrays, must be called after each polyhedron modification
		*/
		SCD_API void updateFastArrays();

		SCD_API Point3 naiveSupport(const Vector3& v)const;

		/*! 
		*  \brief updates the Neighborhood of the vertexes, must be called on polyhedron 
		*  \which vertexes have no neighbors, or after calling clearNeighbors.
		*/
		SCD_API void updateVertexNeighbors();

		/*! 
		*  \brief clears the neighbors tables;
		*/
		SCD_API void clearNeighbors();

		/*! 
		*  \brief clears all the polyhedron;
		*/
		SCD_API void clear();

		/*
		* \brief deletes aal the vertexes that dont have neighbors;
		*/
		SCD_API void deleteVertexesWithoutNeighbors();


		/*
		*\brief Computes the support point of the polyhedron
		*/

		SCD_API Point3 support(const Vector3& v, int& lastFeature)const;


		/*
		* \brief loads the polyhedron from a file. the file must be in the format of Qhull conconvex.exe output, called with these options : 
		* \ "qconvex.exe TI <input_filename> TO <output_filename> Qt o f" 
		*/

		SCD_API void openFromFile(const std::string& filename);

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & vertexes_;
			ar & triangles_;
			//ar & fastVertexes_;
			//ar & lastVertexes_;
		}

		std::vector<S_PolyhedronVertex*> vertexes_;

		std::vector<PolyhedronTriangle> triangles_;
		S_PolyhedronVertex ** fastVertexes_;
		S_PolyhedronVertex ** lastVertexes_;
	};
}

#endif
