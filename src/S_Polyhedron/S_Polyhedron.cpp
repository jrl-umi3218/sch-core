#include <sch/S_Polyhedron/S_Polyhedron.h>
#include <exception>
#include <iostream>
#include <fstream>

#include <sch/File_Parsing/SimplestParsing.h>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>

using namespace sch;

S_Polyhedron::S_Polyhedron(void):poly()
{
}

S_Polyhedron::S_Polyhedron(const S_Polyhedron& p):poly(p.poly)
{
}

S_Polyhedron::~S_Polyhedron(void)
{
}

const S_Polyhedron& S_Polyhedron::operator =(const S_Polyhedron &p)
{
  poly=p.poly;
  return *this;
}

void S_Polyhedron::updateVertexNeighbors()
{
  poly.updateVertexNeighbors();
}

void S_Polyhedron::clear()
{
  poly.clear();
}

void S_Polyhedron::clearNeighbors()
{
  poly.clearNeighbors();
}

void S_Polyhedron::updateFastArrays()
{
  poly.updateFastArrays();
}

Point3 S_Polyhedron::naiveSupport(const Vector3& v)const
{
  return poly.naiveSupport(v);
}

Point3 S_Polyhedron::l_Support(const Vector3& v,int &lastFeature)const
{
  return poly.support(v,lastFeature);
}

void S_Polyhedron::deleteVertexesWithoutNeighbors()
{
  poly.deleteVertexesWithoutNeighbors();
}

void S_Polyhedron::constructFromFile(const std::string& filename)
{
  poly.openFromFile(filename);
}

void S_Polyhedron::loadFromBinary(const std::string & filename)
{
  try
  {
    std::ifstream ifs(filename.c_str(), std::ios::binary);
    boost::archive::binary_iarchive ia(ifs);
    ia >> *this;
  }
  catch(...)
  {
    std::cerr << "Could not load S_Polyhedron from binary file: " << std::endl;
  }
}

void S_Polyhedron::saveToBinary(const std::string & filename)
{
  std::ofstream ofs(filename.c_str(), std::ios::binary);
  if(!ofs.is_open())
  {
    std::cerr << "Could not open file: " << filename << std::endl;
    return;
  }
  boost::archive::binary_oarchive oa(ofs);
  oa << *this;
}

S_Object::S_ObjectType S_Polyhedron::getType() const
{
  return S_Object::TPolyhedron;
}

int S_Polyhedron::getTrianglesNumber() const
{
  return static_cast<int>(poly.triangles_.size());
}
