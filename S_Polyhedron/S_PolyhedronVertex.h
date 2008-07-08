#ifndef _S_POLYHEDRONVERTEX
#define _S_POLYHEDRONVERTEX

#pragma once
#include <vector>
#include "../Matrix/SCD_Types.h"

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

	void clearNeighbors();
	

	virtual bool isHere(const Vector3& direction, const Scalar& currentsupportH);
	virtual bool isHere(const Vector3& direction);

	void updateFastArrays();

	void setNumber(unsigned int);
	unsigned int getNumber()const;

	S_PolyhedronVertex* getNextVertex()const;
	Scalar getNextVertexH()const;

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

#include "S_PolyhedronVertex.hxx"

#endif