#include <sch/S_Polyhedron/Polyhedron_algorithms.h>

#include <sch/File_Parsing/SimplestParsing.h>

#include <fstream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <set>

//#define CD_POLYHEDRON_ALGORITHM_VERBOSE_MODE //VERBOSE mode (slows down the algorithm) default is commented

using namespace sch;

Polyhedron_algorithms::Polyhedron_algorithms(void)
    : fastVertexes_(0x0),
      lastVertexes_(0x0),
      numberOfVertices_(0)
{

}

Polyhedron_algorithms::Polyhedron_algorithms(const Polyhedron_algorithms &p)
  :triangles_(p.triangles_)
  ,fastVertexes_(0x0)
  ,lastVertexes_(0x0)
{
  for (unsigned i=0; i<p.vertexes_.size(); ++i)
  {
    vertexes_.push_back(p.vertexes_[i]->clone());
  }

  updateVertexNeighbors();

  updateFastArrays();
}

Polyhedron_algorithms::~Polyhedron_algorithms(void)
{
  if (fastVertexes_!=NULL)
  {
    delete[] fastVertexes_;
  }
  for (unsigned int i=0; i<vertexes_.size(); ++i)
  {
    delete vertexes_[i];
  }
}

const Polyhedron_algorithms& Polyhedron_algorithms::operator =(const Polyhedron_algorithms &p)
{
  if (this==&p)
  {
    return *this;
  }
  else
  {
    clear();
    triangles_=p.triangles_;

    for (unsigned i=0; i<p.vertexes_.size(); ++i)
    {
      vertexes_.push_back(p.vertexes_[i]->clone());
    }

    updateVertexNeighbors();

    updateFastArrays();


    return *this;
  }
}


int Polyhedron_algorithms::getEdgeKey(PolyhedronEdge e)
{
  return ((e.a<e.b)?(e.a*vertexes_.size()+e.b):(e.b*vertexes_.size()+e.a));
}

void Polyhedron_algorithms::getEdges()
{
  PolyhedronEdge edge;
  std::vector<PolyhedronEdge> triangleEdges;
  std::set<int, std::greater<int>> edgesSet;
  for(size_t i = 0; i < triangles_.size(); i++)
  {
    edge.a = triangles_[i].a;
    edge.b = triangles_[i].b;
    edge.computeEdge(vertexes_);
    triangleEdges.push_back(edge);
    
    edge.a = triangles_[i].b;
    edge.b = triangles_[i].c;
    edge.computeEdge(vertexes_);
    triangleEdges.push_back(edge);
    
    edge.a = triangles_[i].c;
    edge.b = triangles_[i].a;
    edge.computeEdge(vertexes_);
    triangleEdges.push_back(edge);

    for(auto j = triangleEdges.begin(); j != triangleEdges.end(); j++)
    {
      if(!edgesSet.count(getEdgeKey(*j)))
      {
        edges_.push_back(*j);
        edgesSet.insert(getEdgeKey(*j));
      }
    }
    triangleEdges.clear();
  }
}

void Polyhedron_algorithms::openFromFile(const std::string &filename)
{
  clear();

  std::ifstream is(filename.c_str());
  if(!is.is_open())
  {
    std::stringstream errmsg;
    errmsg << "EXCEPTION: Unable to open File " << filename << std::endl;
    throw std::invalid_argument(errmsg.str());
  }

  std::string line;

  // Discard first line
  std::getline(is, line);
  size_t nr_vertexes;
  size_t nr_faces;
  is>>nr_vertexes; //get the number of points
  vertexes_.reserve(nr_vertexes);
  is>>nr_faces;
  triangles_.reserve(nr_faces);
  // Discard the last number
  std::getline(is, line);
  for (size_t g=0; g<nr_vertexes; g++)
  {
    Scalar y[3];
    is >> y[0] >> y[1] >> y[2];//get the coords

    S_PolyhedronVertex *v;
    v=new S_PolyhedronVertex();
    v->setCoordinates(y[0],y[1],y[2]);
    v->setNumber(unsigned (vertexes_.size()));
    vertexes_.push_back(v);

  }

  //get the normals
  const size_t normalSearchLen = 13;
  const char normalSearch[normalSearchLen + 1] = "    - normal:";
  const size_t verticesSearchLen = 15;
  const char verticesSearch[verticesSearchLen + 1] = "    - vertices:";
  PolyhedronEdge edge;
  Vector3 p1, p2;
  while(std::getline(is, line).good())
  {
    if(line.substr(0, normalSearchLen) == normalSearch)
    {
      std::stringstream ss;
      ss << line.substr(normalSearchLen);
      Scalar y[3];

      PolyhedronTriangle t;

      ss>>y[0];
      ss>>y[1];
      ss>>y[2];

      t.normal.Set(y[0],y[1],y[2]);
      t.normal.normalize();

      while(std::getline(is, line).good())
      {
        if(line.substr(0, verticesSearchLen) == verticesSearch)
        {
          std::stringstream ss;
          ss << line.substr(verticesSearchLen);
          char c = '\0';
          while(c!='p' && ss.good()) { ss.get(c); }
          ss >> t.a;
          c = '\0';
          while(c!='p' && ss.good()) { ss.get(c); }
          ss >> t.b;
          c = '\0';
          while(c!='p' && ss.good()) { ss.get(c); }
          ss >> t.c;

          //updatingNeighbors
          vertexes_[t.a]->addNeighbor(vertexes_[t.b]);
          vertexes_[t.a]->addNeighbor(vertexes_[t.c]);

          vertexes_[t.b]->addNeighbor(vertexes_[t.a]);
          vertexes_[t.b]->addNeighbor(vertexes_[t.c]);

          vertexes_[t.c]->addNeighbor(vertexes_[t.a]);
          vertexes_[t.c]->addNeighbor(vertexes_[t.b]);

          triangles_.push_back(t);

          break;
        }
      }
    }
  }

  for (unsigned int i=0; i<vertexes_.size(); i++)
  {
    vertexes_[i]->updateFastArrays();
  }

  deleteVertexesWithoutNeighbors();

  getEdges();
}

void Polyhedron_algorithms::updateVertexNeighbors()
{
  for (unsigned i=0; i<triangles_.size(); ++i)
  {
    //updatingNeighbors
    vertexes_[triangles_[i].a]->addNeighbor(vertexes_[triangles_[i].b]);
    vertexes_[triangles_[i].a]->addNeighbor(vertexes_[triangles_[i].c]);

    vertexes_[triangles_[i].b]->addNeighbor(vertexes_[triangles_[i].a]);
    vertexes_[triangles_[i].b]->addNeighbor(vertexes_[triangles_[i].c]);

    vertexes_[triangles_[i].c]->addNeighbor(vertexes_[triangles_[i].a]);
    vertexes_[triangles_[i].c]->addNeighbor(vertexes_[triangles_[i].b]);
  }

  for (unsigned i=0; i<vertexes_.size(); ++i)
  {
    vertexes_[i]->updateFastArrays();
  }
}

void Polyhedron_algorithms::clear()
{
  for (unsigned int i=0; i<vertexes_.size(); ++i)
  {
    delete vertexes_[i];
  }
  vertexes_.clear();
  triangles_.clear();
  updateFastArrays();
}

void Polyhedron_algorithms::clearNeighbors()
{
  for (unsigned i=0; i<vertexes_.size(); ++i)
  {
    vertexes_[i]->clearNeighbors();
    vertexes_[i]->updateFastArrays();
  }
}

void Polyhedron_algorithms::updateFastArrays()
{
  if (fastVertexes_!=NULL)
  {
    delete[] fastVertexes_;
  }
  numberOfVertices_ = unsigned(vertexes_.size());
  if (numberOfVertices_ > 0)
  {
    fastVertexes_ = new S_PolyhedronVertex *[numberOfVertices_];
    for (unsigned int i = 0; i < numberOfVertices_; ++i)
    {
      fastVertexes_[i]=vertexes_[i];
    }

    lastVertexes_ = &(fastVertexes_[numberOfVertices_]);
  }
  else
  {
    fastVertexes_=lastVertexes_=NULL;
  }
}

Point3 Polyhedron_algorithms::naiveSupport(const Vector3&v)const
{
  S_PolyhedronVertex** current;

  current=fastVertexes_;

  Scalar supportH=(*current)->supportH(v);

  Vector3 best=(*current)->getCoordinates();

  current++;

  for (unsigned i = 1; i < numberOfVertices_; i++, current++)
  {
    if ((*current)->supportH(v) > supportH)
    {
      supportH = (*current)->supportH(v);
      best = (*current)->getCoordinates();
    }
  }

  return best;
}

Point3 Polyhedron_algorithms::support(const Vector3&v,int &lastFeature)const
{
  S_PolyhedronVertex* current;
  Scalar supportH;

  if (numberOfVertices_==0)
  {
    std::stringstream errmsg;
    errmsg << "The polyhedron is empty, impossible to compute support function " << std::endl;
    throw std::length_error(errmsg.str());
  }

  if (lastFeature==-1)
  {
    current=*fastVertexes_;
  }
  else
  {
    current=fastVertexes_[lastFeature];
  }

  bool b=current->isHere(v);

  unsigned iterations = 0;

  while (!b)
  {
    supportH= current->getNextVertexH();
    current = current->getNextVertex();
    b=current->isHere(v,supportH);
    ++iterations;

    /// if the number of iterations is bigger than the number of vertices it means that we entered an infinite loop
    ///the best is te return the support computed using the naive version 
    if (iterations>numberOfVertices_) 
    {
#ifdef CD_POLYHEDRON_ALGORITHM_VERBOSE_MODE
      std::cout << "Problem Support Polyhedron, Naive method triggered" << std::endl;
#endif
      return naiveSupport(v);
    }
  }

  lastFeature=current->getNumber();


  return current->getCoordinates();
}

void Polyhedron_algorithms::deleteVertexesWithoutNeighbors()
{
  int *cache=new int[vertexes_.size()];
  std::vector<S_PolyhedronVertex*> v;
  int index=0;

  for (unsigned i=0; i<vertexes_.size(); ++i)
  {
    if (vertexes_[i]->getNumNeighbors()>0)
    {
      v.push_back(vertexes_[i]);
      vertexes_[i]->setNumber(index);
      cache[i]=index++;
    }
    else
    {
      delete vertexes_[i];
      cache[i]=-1;
    }
  }

  for (unsigned i=0; i<triangles_.size(); ++i)
  {
    triangles_[i].a=cache[triangles_[i].a];
    triangles_[i].b=cache[triangles_[i].b];
    triangles_[i].c=cache[triangles_[i].c];
  }

  vertexes_=v;


  updateFastArrays();

  delete[] cache;

}
