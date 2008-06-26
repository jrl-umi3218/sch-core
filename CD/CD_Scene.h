
#ifndef _CD_SCENE
#define _CD_SCENE

#pragma once



#include <vector>
#include "../S_Object/S_object.h"
#include "CD_PAIR.h"



class CD_Scene
{

	
public:
	CD_Scene(void);
	virtual ~CD_Scene(void);
    
	/*! Add Object to scene, returns an index that must be kept for collision detection */
	int AddObject(S_Object* O);

	/*! Withdraw an object */
	void WithdrawObject( int a);

	void IgnorePair( int a, int b);

	void ConsiderPair( int a, int b);

	CD_Pair* operator()( int a, int b) const
	{
		if (a!=b)
		{
			return (b<a)? _pairs[a][b]:_pairs[b][a];
		}
		else
			return NULL;
	}


	int  SceneProximityQuery();


	
	
	
	
	S_Object * operator[](unsigned char i)const
	{
		return _objects[i];
	}	

	size_t Size()
	{
		return _objects.size();
	}


	/*!
	 *\brief Doesn't Compute the closest points, just gives the result of last computations.
	 */
	Scalar GetWitnessPoints(int a, int b,Point3 &p1,Point3 &p2)
	{
		if (a!=b)
		{
			if (b<a)
			{
				p1=_witness[a][b];
				p2=_witness[b][a];
				return _distances[a][b];
			}
			else
			{
				p1=_witness[b][a];
				p2=_witness[a][b];
				return _distances[b][a];
			}
		}
		else
		{
			return 0;
		}
	}




protected:
	// //list of objects in the scene
	std::vector <S_Object*> _objects;

	std::vector <std::vector <CD_Pair*> > _pairs;

	std::vector <std::vector <Point3 > > _witness;

	std::vector <std::vector <Scalar > > _distances;





};

#endif