#include <SCD/STP-BV/STP_BV_P.h>

using namespace SCD;

STP_BV_P::STP_BV_P(void)
{
}

STP_BV_P::~STP_BV_P(void)
{
}

void STP_BV_P::constructFromFile(const std::string &filename)
{
	STP_BV::constructFromFile(filename);
	poly.openFromFile(filename+std::string(".otp"));
}

#ifdef WITH_OPENGL
void STP_BV_P::constructFromFileWithGL(const std::string &filename)
{
	STP_BV::constructFromFileWithGL(filename);
	poly.openFromFile(filename+std::string(".otp"));
}
#endif

Point3 STP_BV_P::l_Support(const Vector3 &v,int &lastFeature) const
{
	poly.support(v,lastFeature);
	int k=lastFeature;
	return STP_BV::l_Support(v,k);
}

#ifdef WITH_OPENGL
void STP_BV_P::drawGLInLocalCordinates()
{
	STP_BV::drawGLInLocalCordinates();
	poly.drawGL();
}
#endif

S_Object::S_ObjectType STP_BV_P::getType() const
{
	return S_Object::TSTP_BV_WithPolyhedron;
}

