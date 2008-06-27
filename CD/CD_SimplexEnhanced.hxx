inline CD_SimplexEnhanced::CD_SimplexEnhanced(const Point3& p):CD_Simplex(p)
{
	norm1_=p.normsquared();
}

inline CD_SimplexEnhanced::CD_SimplexEnhanced(const Point3& p1,const Point3& p2):CD_Simplex(p1,p2)
{
	norm1_=p1.normsquared();
	norm2_=p2.normsquared();
}

inline CD_SimplexEnhanced::CD_SimplexEnhanced(const Point3& p1,const Point3& p2,const Point3& p3):CD_Simplex(p1,p2,p3)
{	
	norm1_=p1.normsquared();
	norm2_=p2.normsquared();
}

inline CD_SimplexEnhanced::CD_SimplexEnhanced(const Point3& p1,const Point3& p2,const Point3& p3,const Point3& p4):CD_Simplex(p1,p2,p3,p4)
{
	norm1_=p1.normsquared();
	norm2_=p2.normsquared();
	norm3_=p3.normsquared();

}




inline CD_SimplexEnhanced::CD_SimplexEnhanced(const Point3& p,Scalar norm):CD_Simplex(p),norm1_(norm)
{
}

inline CD_SimplexEnhanced::CD_SimplexEnhanced(const Point3& p1,const Point3& p2,Scalar norm1,Scalar norm2):CD_Simplex(p1,p2),norm1_(norm1),norm2_(norm2)
{
}

inline CD_SimplexEnhanced::CD_SimplexEnhanced(const Point3& p1,const Point3& p2,const Point3& p3,Scalar norm1,Scalar norm2,Scalar norm3):CD_Simplex(p1,p2,p3),norm1_(norm1),norm2_(norm2),norm3_(norm3)
{	
}

inline CD_SimplexEnhanced::CD_SimplexEnhanced(const Point3& p1,const Point3& p2,const Point3& p3,const Point3& p4,Scalar norm1,Scalar norm2,Scalar norm3,Scalar norm4):CD_Simplex(p1,p2,p3,p4),norm1_(norm1),norm2_(norm2),norm3_(norm3),norm4_(norm4)
{
}


 
inline CD_SimplexEnhanced& CD_SimplexEnhanced::operator=(const CD_SimplexEnhanced& s)
{
	if (this==&s)
		return *this;

	type=s.type;
	switch (type)
	{
	
	case triangle:
		S1=s.S1;
		S2=s.S2;
		S3=s.S3;
		norm1_=s.norm1_;
		norm2_=s.norm2_;
		norm3_=s.norm3_;

		return *this;
	case segment:
		S1=s.S1;
		S2=s.S2;
		norm1_=s.norm1_;
		norm2_=s.norm2_;
		
		return *this;
	case point:
		S1=s.S1;
		norm1_=s.norm1_;
		
		return *this;
	default:
		S1=s.S1;
		S2=s.S2;
		S3=s.S3;
		S4=s.S4;
		norm1_=s.norm1_;
		norm2_=s.norm2_;
		norm3_=s.norm3_;
		norm4_=s.norm4_;

		return *this;
	}
}

inline CD_SimplexEnhanced& CD_SimplexEnhanced::operator+=(const Point3& p)
{

	switch (type)
	{
	case point:
		S2=p;
		norm2_=S2.normsquared();
		type=segment;
		return *this;	
	case segment:
		S3=p;
		type=triangle;
		norm2_=S3.normsquared();
		return *this;
	default:
		S4=p;
		type=tetrahedron;
		norm4_=S4.normsquared();
		return *this;
	}
	return *this;
	

}


inline CD_SimplexEnhanced CD_SimplexEnhanced::operator+(const Point3& p) const
{

	if (type==point)
	{
		return CD_SimplexEnhanced(S1,p);
	}
	else if (type==segment)
	{
		return CD_SimplexEnhanced(S1,S2,p);
	}
	else if (type==triangle)
	{
		return CD_SimplexEnhanced(S1,S2,S3,p);
	}
	return *this;

}


inline Scalar CD_SimplexEnhanced::farthestPointDistance() const
{
	
	switch (type)
	{

	case triangle:
		if (norm1_>norm2_)
		{
			if (norm1_>norm3_)
			{
				return norm1_;
			}
			else
			{
				return norm3_;
			}
		}
		else
		{
			if (norm2_>norm3_)
			{
				return norm2_;
			}
			else
			{
				return norm3_;
			}
		}

	case segment:

		if (norm1_>norm2_)
		{
			return norm1_;
		}
		else
		{
			return norm2_;
		}

		
	case point:
		return norm1_;

	default:
		if (norm1_>norm2_)
		{
			if (norm1_>norm3_)
			{
				if (norm1_>norm4_)
				{
					return norm1_;
				}
				else
				{
					return norm4_;
				}
			}
			else
			{
				if (norm3_>norm4_)
				{
					return norm3_;
				}
				else
				{
					return norm4_;
				}

			}
		}
		else
		{
			if (norm2_>norm3_)
			{
				if (norm2_>norm4_)
				{
					return norm2_;
				}
				else
				{
					return norm4_;
				}
			}
			else
			{
				if (norm3_>norm4_)
				{
					return norm3_;
				}
				else
				{
					return norm4_;
				}

			}
		}


	}

}

