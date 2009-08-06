#ifndef _S_POLYHEDRONVERTEX
#define _S_POLYHEDRONVERTEX

#pragma once
#include <vector>
#include <SCD/Matrix/SCD_Types.h>

namespace SCD
{

	class S_PolyhedronVertex
	{
	public:
		S_PolyhedronVertex(void);


		virtual ~S_PolyhedronVertex(void);



		void addNeighbor(S_PolyhedronVertex*);

		Scalar supportH(const Vector3& direction)const;

		void setCordinates(const Vector3& v);

		void setCordinates(const Scalar& x,const Scalar& y,const Scalar& z);

		const Vector3& getCordinates()const;

		/*! 
		*  \brief Gives a copy of the current vertex, without the neighbors array, keeping just the cordinates and the number
		*/
		virtual S_PolyhedronVertex* clone();

		/*
		* \brief clears the Neighbors
		*/
		void clearNeighbors();


		/*
		* \brief checks if this is the support point of the polyhedron in some given direction
		* \param direction the direction vector
		* \param cuurentsupportH, is the support height of this points, usually given by a neighbor
		* \return returns a boolean answer and stores the next vertex and its support height in case it is not the support 
		*/
		virtual bool isHere(const Vector3& direction, const Scalar& currentsupportH);


		/*
		* \brief checks if this is the support point of the polyhedron in some given direction
		* \param direction the direction vector
		* \return returns a boolean answer and stores the next vertex and its support height in case it is not the support 
		*/
		virtual bool isHere(const Vector3& direction);

		/*
		* \brief updates fast access neighbors array, must be called at each neighbors modification
		*/
		void updateFastArrays();

		/*
		* \brief sets the number of the vertex in the polyhedron
		*/
		void setNumber(unsigned int);

		/*
		* \brief gets the number of the vertex in the polyhedron
		*/
		unsigned int getNumber()const;

		/*
		* \brief gets the next vertex in a support point search
		*/
		S_PolyhedronVertex* getNextVertex()const;

		/*
		* \brief gets the next vertex support height
		*/
		Scalar getNextVertexH()const;

		/*
		* \brief gets the number of neighbors
		*/

		unsigned getNumNeighbors()const;



	private:

		S_PolyhedronVertex(const S_PolyhedronVertex&);
		const S_PolyhedronVertex& operator=(const S_PolyhedronVertex&);

		Vector3 cordinates_;

		std::vector<S_PolyhedronVertex*> neighbors_;

		S_PolyhedronVertex** fastNeighbors_;
		S_PolyhedronVertex** endNeighbors_;
		unsigned int number_;

		S_PolyhedronVertex* nextVertex_;
		Scalar nextVertexH_;

	};


#include <SCD/S_Polyhedron/S_PolyhedronVertex.hxx>
}
#endif
