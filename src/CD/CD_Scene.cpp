#include <sch/CD/CD_Scene.h>

using namespace sch;

CD_Scene::CD_Scene(void)
{
}

CD_Scene::~CD_Scene(void)
{
  for(unsigned i=0; i<pairs_.size(); ++i)
    for(unsigned j=0; j<pairs_[i].size(); ++j)
      if(pairs_[i][j] != 0x0)
      {
        delete pairs_[i][j];
        pairs_[i][j] = 0x0;
      }
}

int CD_Scene::addObject(S_Object *O)
{
  unsigned int i;
  /*looking for an empty place*/
  for (i=0; (i<objects_.size())&&(objects_[i]!=NULL); ++i);


  /*filling objects and possibly updating _pairs and _witness matrix*/
  if (i==objects_.size())
  {
    objects_.push_back(O);

    std::vector <Point3> vect;

    Point3 point;

    std::vector < CD_Pair *> v;
    std::vector < Scalar > vp;

    pairs_.push_back (v);
    distances_.push_back(vp);

    for (unsigned int j=0; j<i; ++j)
    {
      pairs_[i].push_back(0x0);
      distances_[i].push_back(0);
    }

    witness_.push_back(vect);

    for (unsigned int k=0; k<=i; ++k)
    {
      witness_[i].push_back(point);
      for (size_t j=witness_[k].size(); j<=i; ++j)
        witness_[k].push_back(point);
    }
  }
  else
  {
    objects_[i]=O;
  }


  for (unsigned int j=0; j<i; j++)
  {
    pairs_[i][j]=new CD_Pair(objects_[j],O);
  }

  for (unsigned int j=i+1; j<objects_.size(); ++j)
  {
    pairs_[j][i]=new CD_Pair(O,objects_[j]);
  }

  return i;
}

int CD_Scene::sceneProximityQuery()
{
  int collisions=0;

  for (unsigned int i=0; i<pairs_.size(); ++i)
    for (unsigned int j=0; j<pairs_[i].size(); ++j)
      if ((pairs_[i][j]!=0x0)&&((distances_[i][j]=pairs_[i][j]->getClosestPoints(witness_[i][j],witness_[j][i]))<=0))
        ++collisions;

  return collisions;
}
