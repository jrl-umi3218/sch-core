/*
* SOLID - Software Library for Interference Detection
* 
* Copyright (C) 2001-2003  Dtecta.  All rights reserved.
*
* This library may be distributed under the terms of the Q Public License
* (QPL) as defined by Trolltech AS of Norway and appearing in the file
* LICENSE.QPL included in the packaging of this file.
*
* This library may be distributed and/or modified under the terms of the
* GNU General Public License (GPL) version 2 as published by the Free Software
* Foundation and appearing in the file LICENSE.GPL included in the
* packaging of this file.
*
* This library is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
* WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* Commercial use or any other use of this library not covered by either 
* the QPL or the GPL requires an additional license from Dtecta. 
* Please contact info@dtecta.com for enquiries about the terms of commercial
* use of this library.
*/

#ifndef TRIEDGE_H
#define TRIEDGE_H

#include <vector>
#include <iostream>

#include <SCD/scd_api.h>
#include <SCD/Matrix/SCD_Types.h>

//#define DEBUG

namespace SCD
{

	class Depth_Triangle;

	typedef unsigned short Index_t;

	class Depth_Edge;
	class Depth_TriangleStore;


	bool link(const Depth_Edge& edge0, const Depth_Edge& edge1);
	void half_link(const Depth_Edge& edge0, const Depth_Edge& edge1);


	class Depth_Edge {
	private:    
		Depth_Triangle *m_triangle;
		int       m_index;

	public:
		Depth_Edge() {}
		Depth_Edge(Depth_Triangle *triangle, int index) 
			: m_triangle(triangle), 
			m_index(index) 
		{}

		bool silhouette(const Vector3 *verts, Index_t index, Depth_TriangleStore& triangleStore) const;

		Depth_Triangle *triangle() const { return m_triangle; }
		int       index()    const { return m_index; }

		Index_t  getSource() const;
		Index_t  getTarget() const;
	};



	class Depth_Triangle {
	private:
		Index_t     m_indices[3];
		Depth_Edge        m_adjEdges[3];

		bool        m_obsolete;

		Scalar   m_det;
		Scalar   m_lambda1;
		Scalar   m_lambda2;
		Vector3  m_closest;
		Scalar   m_dist2;

	public:
		SCD_API Depth_Triangle() {}
		SCD_API Depth_Triangle(Index_t i0, Index_t i1, Index_t i2) 
			:	m_obsolete(false) 
		{
			m_indices[0] = i0; 
			m_indices[1] = i1; 
			m_indices[2] = i2;
		}

		SCD_API Index_t operator[](int i) const { return m_indices[i]; } 

		SCD_API const Depth_Edge& getAdjEdge(int i) const { return m_adjEdges[i]; }

		SCD_API void setObsolete(bool obsolete) 
		{ 
#ifdef SCD_DEBUG
			std::cout << "Triangle " <<  m_indices[0] << ' ' << m_indices[1] << ' ' << m_indices[2] << " obsolete" << std::endl;
#endif	
			m_obsolete = obsolete; 
		}

		SCD_API bool isObsolete() const { return m_obsolete; }


		SCD_API bool computeClosest(const Vector3 *verts);

		SCD_API const Vector3& getClosest() const { return m_closest; } 

		SCD_API bool isClosestInternal() const
		{ 
			return m_lambda1 >= Scalar(0.0) && 
				m_lambda2 >= Scalar(0.0) && 
				m_lambda1 + m_lambda2 <= m_det;
		} 

		SCD_API bool isVisibleFrom(const Vector3 *verts, Index_t index) const
		{
			Vector3 lever = verts[index] - m_closest;
			return (m_closest* lever) > Scalar(0.0);
		}

		SCD_API Scalar getDist2() const { return m_dist2; }

		SCD_API Vector3 getClosestPoint(const Vector3 *points) const 
		{
			const Vector3& p0 = points[m_indices[0]];

			return p0 + ( (points[m_indices[1]] - p0)*m_lambda1 + 
				(points[m_indices[2]] - p0)*m_lambda2) / m_det;
		}

		SCD_API bool silhouette(const Vector3 *verts, Index_t index, Depth_TriangleStore& triangleStore); 

		friend bool link(const Depth_Edge& edge0, const Depth_Edge& edge1);
		friend void half_link(const Depth_Edge& edge0, const Depth_Edge& edge1);
	};


	static const int MaxTriangles = 200;

	class Depth_TriangleStore
	{
	private:


		Depth_Triangle m_triangles[MaxTriangles];
		int      m_free;
	public:
		SCD_API Depth_TriangleStore()
			: m_free(0)
		{}

		SCD_API void clear() { m_free = 0; }

		SCD_API int getFree() const { return m_free; }

		SCD_API Depth_Triangle& operator[](int i) { return m_triangles[i]; }
		SCD_API Depth_Triangle& last() { return m_triangles[m_free - 1]; }

		SCD_API void setFree(int backup) { m_free = backup; }


		SCD_API Depth_Triangle *newTriangle(const Vector3 *verts, Index_t i0, Index_t i1, Index_t i2) 
		{ 
			Depth_Triangle *newTriangle = 0;
			if (m_free != MaxTriangles)
			{
				newTriangle = &m_triangles[m_free++];
				new (newTriangle) Depth_Triangle(i0, i1, i2);
				if (!newTriangle->computeClosest(verts))
				{
					--m_free;
					newTriangle = 0;
				}
			}

			return newTriangle;
		}
	};

	extern Depth_TriangleStore g_triangleStore;


	inline int circ_next(int i) { return (i + 1) % 3; } 
	inline int circ_prev(int i) { return (i + 2) % 3; } 

	inline Index_t Depth_Edge::getSource() const 
	{ 
		return (*m_triangle)[m_index]; 
	}

	inline Index_t Depth_Edge::getTarget() const
	{
		return (*m_triangle)[circ_next(m_index)]; 
	}
}
#endif
