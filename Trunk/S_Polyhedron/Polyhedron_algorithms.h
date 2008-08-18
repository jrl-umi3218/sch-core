#pragma once

#ifndef _POLYHEDRON_ALGORITHMS
#define _POLYHEDRON_ALGORITHMS

#include "../Matrix/SCD_Types.h"
#include "S_polyhedronvertex.h"

#include <string>
#include <vector>

namespace SCD
{
	struct PolyhedronTriangle
	{
		unsigned int a,b,c;
		Vector3 normal;
	};

	struct Polyhedron_algorithms
	{
	public:
		Polyhedron_algorithms(void);
		Polyhedron_algorithms(const Polyhedron_algorithms&);



		~Polyhedron_algorithms(void);


		const Polyhedron_algorithms & operator=(const Polyhedron_algorithms&);



		/*
		*\brief Draws the Polyhedron in OpenGL
		*/

		virtual void drawGL();

		/*! 
		*  \brief updates the fast access arrays, must be called after each polyhedron modification
		*/
		void updateFastArrays();

		Point3 naiveSupport(const Vector3& v)const;

		/*! 
		*  \brief updates the Neighborhood of the vertexes, must be called on polyhedron 
		*  \which vertexes have no neighbors, or after calling clearNeighbors.
		*/
		void updateVertexNeighbors();

		/*! 
		*  \brief clears the neighbors tables;
		*/
		void clearNeighbors();

		/*! 
		*  \brief clears all the polyhedron;
		*/
		void clear();

		/*
		* \brief deletes aal the vertexes that dont have neighbors;
		*/
		void deleteVertexesWithoutNeighbors();


		/*
		*\brief Computes the support point of the polyhedron
		*/

		Point3 support(const Vector3& v, int& lastFeature)const;




		/*
		* \brief loads the polyhedron from a file. the file must be in the format of Qhull conconvex.exe output, called with these options : 
		* \ "qconvex.exe TI <input_filename> TO <output_filename> Qt o f" 
		*/

		void openFromFile(const std::string& filename);

		std::vector<S_PolyhedronVertex*> vertexes_;

		std::vector<PolyhedronTriangle> triangles_;
		S_PolyhedronVertex ** fastVertexes_;
		S_PolyhedronVertex ** lastVertexes_;


		int displayList_;


	};
}

#endif