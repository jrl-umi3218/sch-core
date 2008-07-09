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

	virtual void drawGL() const;

   /*
	* \brief loads the polyhedron from a file. the file must be in the format of Qhull conconvex.exe output, called with these options : 
	* \ "qconvex.exe TI <input_filename> TO <output_filename> Qt o f" 
	*/
	
	void loadFromFile(const std::string&);

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


protected:
	virtual Point3 n_Support(const Vector3& v, int& lastFeature)const;
	virtual	S_ObjectType getType() const;




protected:
	
	std::vector<S_PolyhedronVertex*> vertexes_;

	std::vector<S_PolyhedronTriangle> triangles_;

	S_PolyhedronVertex ** fastVertexes_;
	S_PolyhedronVertex ** lastVertexes_;
	int displayList_;

		


};

#endif