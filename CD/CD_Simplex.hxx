

inline CD_Simplex::CD_Simplex(const Point3& p):type(CD_Point),S1(p)
{
}

inline CD_Simplex::CD_Simplex(const Point3& p1,const Point3& p2):type(CD_Segment),S1(p1),S2(p2)
{
}

inline CD_Simplex::CD_Simplex(const Point3& p1,const Point3& p2,const Point3& p3):type(CD_Triangle),S1(p1),S2(p2),S3(p3)
{	
}

inline CD_Simplex::CD_Simplex(const Point3& p1,const Point3& p2,const Point3& p3,const Point3& p4):type(CD_Tetrahedron),S1(p1),S2(p2),S3(p3),S4(p4)
{
}


template <typename T>
inline void exchangeTest(T &a,T &b,T &c)
{
	if (&a!=&b)
	{
		c=a;
		a=b;
		b=c;
	}
}

template <typename T>
inline void exchange(T &a,T &b,T &c)
{
	c=a;
	a=b;
	b=c;
}


inline bool CD_Simplex::isAffinelyDependent() const
{
	switch (type)
	{
	case CD_Segment:
		return ab_.normsquared()<=zero;
	case CD_Triangle:
		{
			return (ab_^ac_).normsquared()<=zero4;
		}
	case CD_Tetrahedron:
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
		case CD_Tetrahedron:
		{
			ab_=S1-S4;
			ac_=S2-S4;
			ad_=S3-S4;
			return;
		}
	case CD_Segment:
		ab_=S1-S2;
		return;
	case CD_Triangle:
		{
			ab_=S1-S3;
			ac_=S2-S3;
			return;
		}
	
	default:
		return;
	}
	
}


inline CD_SimplexType CD_Simplex::getType() const
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
	
	case CD_Triangle:
		S1=s.S1;
		S2=s.S2;
		S3=s.S3;
		return *this;
	case CD_Segment:
		S1=s.S1;
		S2=s.S2;
		return *this;
	case CD_Point:
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
	type=CD_Point;
	S1=p;
	return *this;
}


inline bool CD_Simplex::operator==(const CD_Simplex& s)
{
	if (type!=s.type)
		return false;
	switch (type)
	{
	case CD_Triangle:
		return (S1==s.S1)&&(S2==s.S2)&&(S3==s.S3);
	case CD_Segment:
		return (S1==s.S1)&&(S2==s.S2);
	case CD_Point:
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
	case CD_Point:
		S2=p;
		type=CD_Segment;
		return *this;	
	case CD_Segment:
		S3=p;
		type=CD_Triangle;
		return *this;
	default:
		S4=p;
		type=CD_Tetrahedron;
		return *this;
	}
	return *this;
	

}


inline CD_Simplex CD_Simplex::operator+(const Point3& p) const
{

	if (type==CD_Point)
	{
		return CD_Simplex(S1,p);
	}
	else if (type==CD_Segment)
	{
		return CD_Simplex(S1,S2,p);
	}
	else if (type==CD_Triangle)
	{
		return CD_Simplex(S1,S2,S3,p);
	}
	return *this;

}

inline void CD_Simplex::filter(const CD_SimplexKeptPoints &f)
{

	//CD_Simplex test=*this;
	switch (f.type)
	{
	case CD_None:
		return;
	
	case CD_Segment:
		{
			type=CD_Segment;
			Vector3 cache;
			char a[]={0,1,2,3};
			char b;
			exchangeTest<Vector3>(S1,(*this)[f.b1],cache);
			exchange<char>(a[0],a[f.b1],b);

			S2=(*this)[a[f.b2]];
			return;
		}
	case CD_Triangle:
		{
			type=CD_Triangle;
			Vector3 cache;
			char a[]={0,1,2,3};
			char b;
			exchangeTest<Vector3>(S1,(*this)[f.b1],cache);
			exchange<char>(a[0],a[f.b1],b);

			exchangeTest<Vector3>(S2,(*this)[a[f.b2]],cache);
			exchange<char>(a[a[1]],a[a[f.b2]],b);

			S3=(*this)[a[f.b3]];
			return;
			
		}
	case CD_Point:
		{
			Vector3 cache;
			type=CD_Point;
			S1=(*this)[f.b1];
			return;
		}
	default:
		{
			type=CD_Tetrahedron;
			Vector3 cache;
			char a[]={0,1,2,3};
			char b;
			exchangeTest<Vector3>(S1,(*this)[f.b1],cache);
			exchange<char>(a[0],a[f.b1],b);

			exchangeTest<Vector3>(S2,(*this)[a[f.b2]],cache);
			exchange<char>(a[a[1]],a[a[f.b2]],b);

			exchangeTest<Vector3>(S3,(*this)[a[f.b3]],cache);
			exchange<char>(a[a[2]],a[a[f.b3]],b);

			S4=(*this)[a[f.b4]];
			return ;

		}
	}
	
	/*switch (f.type)
	{
	
	case CD_Segment:
		if (*this!=CD_Simplex(test[f.b1],test[f.b2]))
		{
			int i=0;
			i++;
		}
		break;
	case CD_Triangle:
		if (*this!=CD_Simplex(test[f.b1],test[f.b2],test[f.b3]))
		{
			int i=0;
			i++;
		}
		break;
	case CD_Point:
		if (*this!=CD_Simplex(test[f.b1]))
		{
			int i=0;
			i++;
		}
		break;
	default:
		if (*this!=CD_Simplex(test[f.b1],test[f.b2],test[f.b3],test[f.b4]))
		{
			int i=0;
			i++;
		}


	}*/
	/*unsigned char i=0;
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

	}*/
}

inline Scalar CD_Simplex::squareDistanceAtOrigin(const Vector3 &v)const
{
	switch (type)
	{
	case CD_Point:
		return S1.normsquared();

	default:
		

		Scalar d(v*S2);
		return d*d/v.normsquared();
	
	}
	
}
