#ifndef _S_POLYHEDRONVERTEX
#define _S_POLYHEDRONVERTEX

#pragma once
#include <vector>
#include <SCD/scd_api.h>
#include <SCD/Matrix/SCD_Types.h>

namespace SCD
{

	class S_PolyhedronVertex
	{
	public:
		SCD_API S_PolyhedronVertex(void);


		SCD_API virtual ~S_PolyhedronVertex(void);



		SCD_API void addNeighbor(S_PolyhedronVertex*);

		SCD_API Scalar supportH(const Vector3& direction)const;

		SCD_API void setCordinates(const Vector3& v);

		SCD_API void setCordinates(const Scalar& x,const Scalar& y,const Scalar& z);

		SCD_API const Vector3& getCordinates()const;

		/*! 
		*  \brief Gives a copy of the current vertex, without the neighbors array, keeping just the cordinates and the number
		*/
		SCD_API virtual S_PolyhedronVertex* clone();

		/*
		* \brief clears the Neighbors
		*/
		SCD_API void clearNeighbors();


		/*
		* \brief checks if this is the support point of the polyhedron in some given direction
		* \param direction the direction vector
		* \param cuurentsupportH, is the support height of this points, usually given by a neighbor
		* \return returns a boolean answer and stores the next vertex and its support height in case it is not the support 
		*/
		SCD_API virtual bool isHere(const Vector3& direction, const Scalar& currentsupportH);


		/*
		* \brief checks if this is the support point of the polyhedron in some given direction
		* \param direction the direction vector
		* \return returns a boolean answer and stores the next vertex and its support height in case it is not the support 
		*/
		SCD_API virtual bool isHere(const Vector3& direction);

		/*
		* \brief updates fast access neighbors array, must be called at each neighbors modification
		*/
		SCD_API void updateFastArrays();

		/*
		* \brief sets the number of the vertex in the polyhedron
		*/
		SCD_API void setNumber(unsigned int);

		/*
		* \brief gets the number of the vertex in the polyhedron
		*/
		SCD_API unsigned int getNumber()const;

		/*
		* \brief gets the next vertex in a support point search
		*/
		SCD_API S_PolyhedronVertex* getNextVertex()const;

		/*
		* \brief gets the next vertex support height
		*/
		SCD_API Scalar getNextVertexH()const;

		/*
		* \brief gets the number of neighbors
		*/

		SCD_API unsigned getNumNeighbors()const;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
      ar & cordinates_;
      ar & neighbors_;
      //ar & fastNeighbors_;
      //ar & endNeighbors_;
      ar & number_;
      //ar & nextVertex_;
      ar & nextVertexH_;
    }

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
