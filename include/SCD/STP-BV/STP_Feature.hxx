inline double s_STP_VVR::isInsidePrime(const Vector3& v) const
{
	return (m_axis*v - m_cosangle);
}

inline double s_STP_VVR::isInsidePlane(const Vector3& v) const
{
	return m_axis*v;
}
