

inline CD_Simplex::CD_Simplex(const Point3& p):type(point),S1(p)
{
}

inline CD_Simplex::CD_Simplex(const Point3& p1,const Point3& p2):type(segment),S1(p1),S2(p2)
{
}

inline CD_Simplex::CD_Simplex(const Point3& p1,const Point3& p2,const Point3& p3):type(triangle),S1(p1),S2(p2),S3(p3)
{	
}

inline CD_Simplex::CD_Simplex(const Point3& p1,const Point3& p2,const Point3& p3,const Point3& p4):type(tetrahedron),S1(p1),S2(p2),S3(p3),S4(p4)
{
}




inline bool CD_Simplex::IsAffinelyDependent() const
{
	switch (type)
	{
	case segment:
		return ab_.normsquared()<=zero;
	case triangle:
		{
			return (ab_^ac_).normsquared()<=zero4;
		}
	case tetrahedron:
		return fabs(Matrix3x3(ab_,ac_,ad_).determinant())<=zero3;
	default:
		return false;
	}
}

inline const Vector3& CD_Simplex::AB() const
{
	return ab_;
}

inline const Vector3& CD_Simplex::AC() const
{
	return ac_;
}

inline const Vector3& CD_Simplex::AD() const
{
	return ad_;
}




inline void CD_Simplex::updateVectors()
{
		switch (type)
	{
		case tetrahedron:
		{
			ab_=S1-S4;
			ac_=S2-S4;
			ad_=S3-S4;
			return;
		}
	case segment:
		ab_=S1-S2;
		return;
	case triangle:
		{
			ab_=S1-S3;
			ac_=S2-S3;
			return;
		}
	
	default:
		return;
	}
	
}


inline CD_Simplex::Type CD_Simplex::getType() const
{
	return type;
	
}



inline Point3& CD_Simplex::operator[](unsigned char i)
{
	return ((i==0) ? S1: (i==1)? S2: (i==2) ? S3 : S4);
}


inline const Point3& CD_Simplex:: operator[](unsigned char i) const
{
	return ((i==0) ? S1: (i==1)? S2: (i==2) ? S3 : S4);
}

inline CD_Simplex& CD_Simplex::operator=(const CD_Simplex& s)
{
	type=s.type;
	switch (type)
	{
	
	case triangle:
		S1=s.S1;
		S2=s.S2;
		S3=s.S3;
		return *this;
	case segment:
		S1=s.S1;
		S2=s.S2;
		return *this;
	case point:
		S1=s.S1;
		return *this;
	default:
		S1=s.S1;
		S2=s.S2;
		S3=s.S3;
		S4=s.S4;
		return *this;
	}
}


inline CD_Simplex& CD_Simplex::operator=(const Point3& p)
{
	type=point;
	S1=p;
	return *this;
}


inline bool CD_Simplex::operator==(const CD_Simplex& s)
{
	if (type!=s.type)
		return false;
	switch (type)
	{
	case triangle:
		return (S1==s.S1)&&(S2==s.S2)&&(S3==s.S3);
	case segment:
		return (S1==s.S1)&&(S2==s.S2);
	case point:
		return (S1==s.S1);
	default:
		return (S1==s.S1)&&(S2==s.S2)&&(S3==s.S3)&&(S4==s.S4);
	}
}



inline bool CD_Simplex::operator!=(const CD_Simplex& s)
{
	return !((*this)==s);
}

inline CD_Simplex& CD_Simplex::operator+=(const Point3& p)
{

	switch (type)
	{
	case point:
		S2=p;
		type=segment;
		return *this;	
	case segment:
		S3=p;
		type=triangle;
		return *this;
	default:
		S4=p;
		type=tetrahedron;
		return *this;
	}
	return *this;
	

}


inline CD_Simplex CD_Simplex::operator+(const Point3& p) const
{

	if (type==point)
	{
		return CD_Simplex(S1,p);
	}
	else if (type==segment)
	{
		return CD_Simplex(S1,S2,p);
	}
	else if (type==triangle)
	{
		return CD_Simplex(S1,S2,S3,p);
	}
	return *this;

}

inline void CD_Simplex::Filter(const CD_SimplexKeptPoints &f)
{
	unsigned char i=0;
	unsigned char a;
	Vector3 s[4];

	switch (type)
	{
	
	case tetrahedron:
		a=4;
		break;
	case triangle:
		a=3;
		break;
	case segment:
		a=2;
		break;
	default :
		return;
	}

	
	for (unsigned char j=0;j<a;++j)
	{
		if (f[j]>=0)
		{		
			s[i]=(*this)[f[j]];
			++i;
		}
		else
			break;

	}

	for (unsigned char k=0;k<i;++k)
	{
		(*this)[k]=s[k];
	}

	switch (i)
	{
	case 3:
		type=triangle;
		return;
	case 2:
		type=segment;
		return;
	case 1:
		type=point;
		return;
	default:
		type= tetrahedron;
		return;

	}
}

inline Scalar CD_Simplex::SquareDistanceAtOrigin(const Vector3 &v)const
{
	switch (type)
	{
	case point:
		return S1.normsquared();

	default:
		

		Scalar d(v*S2);
		return d*d/v.normsquared();
	
	}
	
}
