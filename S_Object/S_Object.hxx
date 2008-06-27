inline Point3 S_Object::Support(const Vector3& v) const
{
	Vector3 vp(v);
	vp=v*mRot; //ie : mRot.transpose*v (applying inverse transformation on the support vector)
	Scalar norm=v.norm();
	if (norm>0)
	{
		vp/=norm;
	}
	else
	{
		vp.Set(1,0,0);
		
	}
	int k=-1;
	Point3 p(mRot * N_Support(vp,k));
	return p+trans;
}

inline Point3 S_Object::Support(const Vector3& v,int &LastFeature) const
{
	Vector3 vp(v);
	vp= v; 
	vp*=mRot; //ie : mRot.transpose*v (applying inverse transformation on the support vector)
	Scalar norm=v.norm();
	if (norm>0)
	{
		vp/=norm;
	}
	else
	{
		vp.Set(1,0,0);
		
	}
	
	Point3 p(mRot * N_Support(vp,LastFeature));
	p+=trans;
	return p;
}

inline const S_Object::TimeStamp & S_Object::CheckStamp()const
{
	return stamp;
}



inline void S_Object::GetTransformationMatrix(Scalar *d) const
{
	d[0]=mRot(0,0); d[4]=mRot(0,1); d[8]=mRot(0,2) ; d[12]=trans[0];
	d[1]=mRot(1,0); d[5]=mRot(1,1); d[9]=mRot(1,2) ; d[13]=trans[1];
	d[2]=mRot(2,0); d[6]=mRot(2,1); d[10]=mRot(2,2); d[14]=trans[2];
	d[3]=0;         d[7]=0;         d[11]=0;         d[15]=1;
}

inline const Matrix3x3& S_Object::GetOrientation() const
{
	return mRot;
}

inline const Vector3& S_Object::GetPosition() const
{
	return trans;
}
