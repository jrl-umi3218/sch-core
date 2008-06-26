#include "CD_Scene.h"

CD_Scene::CD_Scene(void)
{
}

CD_Scene::~CD_Scene(void)
{
}


int CD_Scene::AddObject(S_Object *O)
{

	unsigned int i;
	/*looking for an empty place*/
	for (i=0;(i<_objects.size())&&(_objects[i]!=NULL);++i);
	
	
	/*filling objects and possibly updating _pairs and _witness matrix*/
	if (i==_objects.size())
	{
		_objects.push_back(O);

		std::vector <Point3> vect;

		Point3 point;

		std::vector < CD_Pair *> v;
		std::vector < Scalar > vp;
		
		_pairs.push_back (v);
		_distances.push_back(vp);
		
		for (unsigned int j=0;j<i;++j)
		{
			_pairs[i].push_back(NULL);
			_distances[i].push_back(0);
		}
		
		_witness.push_back(vect);
		
		for (unsigned int k=0;k<=i;++k)
		{
			_witness[i].push_back(point);
			for (size_t j=_witness[k].size();j<=i;++j)
				_witness[k].push_back(point);
		}

	

		
	}
	else
	{
		_objects[i]=O;
	}


	for (unsigned int j=0;j<i;j++)
	{
		_pairs[i][j]=new CD_Pair(_objects[j],O);
	}

	for (unsigned int j=i+1;j<_objects.size();++j)
	{
		_pairs[j][i]=new CD_Pair(O,_objects[j]);
	}

	return i;
}

int CD_Scene::SceneProximityQuery()
{
	int collisions=0;
	
	for (unsigned int i=0;i<_pairs.size();++i)
	{
		for (unsigned int j=0;j<_pairs[i].size();++j)
		{
			if ((_pairs[i][j]!=NULL)&&((_distances[i][j]=_pairs[i][j]->GetClosestPoints(_witness[i][j],_witness[j][i]))<=0))
			{
				++collisions;

			}
		}
	}

	return collisions;
}