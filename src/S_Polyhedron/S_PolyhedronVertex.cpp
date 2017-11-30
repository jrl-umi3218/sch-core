#include <sch/S_Polyhedron/S_PolyhedronVertex.h>

//#define POLYHEDRON_VERTEX_VERBOSE_MODE //VERBOSE mode (slows down the algorithm) default is commented

using namespace sch;
S_PolyhedronVertex::S_PolyhedronVertex(void):fastNeighbors_(NULL),endNeighbors_(NULL)
{
}

S_PolyhedronVertex::~S_PolyhedronVertex(void)
{
  if (fastNeighbors_!=NULL)
  {
    delete[] fastNeighbors_;
  }
}

void S_PolyhedronVertex::clearNeighbors()
{
  neighbors_.clear();
}

S_PolyhedronVertex* S_PolyhedronVertex::clone()
{
  S_PolyhedronVertex* p=new S_PolyhedronVertex();
  p->setCoordinates(cordinates_);
  p->setNumber(number_);
  return p;
}

void S_PolyhedronVertex::updateFastArrays()
{
  if (fastNeighbors_!=NULL)
  {
    delete[] fastNeighbors_;
  }
  if (neighbors_.size()>0)
  {
    fastNeighbors_=new S_PolyhedronVertex*[neighbors_.size()];
    for (unsigned int i=0; i<neighbors_.size(); i++)
    {
      fastNeighbors_[i]=neighbors_[i];
    }

    endNeighbors_=&(fastNeighbors_[neighbors_.size()]);
  }
  else
  {
    fastNeighbors_=endNeighbors_=NULL;
  }
}

void S_PolyhedronVertex::addNeighbor(S_PolyhedronVertex *n)
{
  neighbors_.push_back(n);
}

Scalar S_PolyhedronVertex::supportH(const Vector3 &direction)const
{
  return direction*cordinates_;
}

bool S_PolyhedronVertex::isHere(const Vector3 &direction,const  Scalar &currentsupportH)
{
  S_PolyhedronVertex** iterator_;
  nextVertex_=NULL;
  Scalar temp;

  nextVertexH_=currentsupportH;

  for (iterator_=fastNeighbors_; iterator_!=endNeighbors_; ++iterator_)
  {
    temp=(*iterator_)->supportH(direction);
    if (temp>nextVertexH_)
    {
#ifdef POLYHEDRON_VERTEX_VERBOSE_MODE
      std::cout.precision(20);
      std::cout<<"new H "<<temp<<" last H "<<nextVertexH_<<std::endl;
#endif
      nextVertexH_=temp;
      nextVertex_=*iterator_;
    }
  }

  return (currentsupportH>=nextVertexH_);
}


bool S_PolyhedronVertex::isHere(const Vector3 &direction)
{
  S_PolyhedronVertex** iterator_;
  nextVertex_=NULL;
  Scalar temp;

  nextVertexH_=direction*cordinates_;

  for (iterator_=fastNeighbors_; iterator_!=endNeighbors_; ++iterator_)
  {
    if ((temp=(*iterator_)->supportH(direction))>nextVertexH_)
    {
      nextVertexH_=temp;
      nextVertex_=*iterator_;
    }
  }

  return (nextVertex_==NULL);
}

unsigned S_PolyhedronVertex::getNumNeighbors()const
{
  return static_cast<unsigned int>(neighbors_.size());
}

void S_PolyhedronVertex::setCordinates(const Scalar &x,const  Scalar &y, const Scalar &z)
{
  setCoordinates(x, y, z);
}

void S_PolyhedronVertex::setCoordinates(const Scalar &x,const  Scalar &y, const Scalar &z)
{
  cordinates_.Set(x,y,z);
}

void S_PolyhedronVertex::setCordinates(const Vector3 &v)
{
  setCoordinates(v);
}

void S_PolyhedronVertex::setCoordinates(const Vector3 &v)
{
  cordinates_=v;
}

const Vector3& S_PolyhedronVertex::getCordinates()const
{
  return getCoordinates();
}

const Vector3& S_PolyhedronVertex::getCoordinates()const
{
  return cordinates_;
}

void S_PolyhedronVertex::setNumber(unsigned int n)
{
  number_=n;
}

S_PolyhedronVertex* S_PolyhedronVertex::getNextVertex() const
{
  return nextVertex_;
}

Scalar S_PolyhedronVertex::getNextVertexH() const
{
  return nextVertexH_;
}
