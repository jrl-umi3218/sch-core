#include <sch/S_Polyhedron/S_Polyhedron.h>
#include <exception>
#include <iostream>
#include <fstream>

#include <sch/File_Parsing/SimplestParsing.h>

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

S_Object::S_ObjectType S_Polyhedron::getType() const
{
  return S_Object::TPolyhedron;
}

std::size_t S_Polyhedron::getTrianglesNumber() const
{
  return poly.triangles_.size();
}
