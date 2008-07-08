#ifndef _S_POLYHEDRON
#define _S_POLYHEDRON

#pragma once
#include "..\s_object\s_objectNonNormalized.h"
#include "S_polyhedronvertex.h"

#include <string>
#include <vector>

struct S_PolyhedronTriangle
{
	unsigned int a,b,c;
	Vector3 normal;
};

class S_Polyhedron :
	public S_ObjectNonNormalized
{
public:
	S_Polyhedron(void);

	S_Polyhedron(const S_Polyhedron&);
	
	
	virtual ~S_Polyhedron(void);
	
	const S_Polyhedron& operator =(const S_Polyhedron&);

	virtual void DrawGL() const;
	
	void loadFromFile(const std::string&);


	void updateFastArrays();

	Point3 NaiveSupport(const Vector3& v)const;

	/*! 
	 *  \brief updates the Neighborhood of the vertexes, must be called on polyhedron 
	 *  \which vertexes have no neighbors, or after calling clearNeighbors.
	 */
	void updateVertexNeighbors();

	void clearNeighbors();

	void clear();

	void deleteVertexesWithoutNeighbors();


protected:
	virtual Point3 N_Support(const Vector3& v, int& lastFeature)const;
	virtual	S_ObjectType GetType() const;




protected:
	
	std::vector<S_PolyhedronVertex*> vertexes_;

	std::vector<S_PolyhedronTriangle> triangles_;

	S_PolyhedronVertex ** fastVertexes_;
	S_PolyhedronVertex ** lastVertexes_;
	int displayList_;

		


};

#endif