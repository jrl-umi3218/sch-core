inline Point3 S_Object::support(const Vector3& v) const
{
	Vector3 vp(v);
	vp=v*mRot_; //ie : mRot.transpose*v (applying inverse transformation on the support vector)
	Scalar norm=vp.norm();
	if (norm>0)
	{
		vp/=norm;
	}
	else
	{
		vp.Set(1,0,0);
		
	}
	int k=-1;
	Point3 p(mRot_ * n_Support(vp,k));
	return p+trans_;
}

inline Point3 S_Object::support(const Vector3& v,int &LastFeature) const
{
	Vector3 vp(v);
	vp= v * mRot_; //ie : mRot.transpose*v (applying inverse transformation on the support vector)
	Scalar norm=vp.norm();
	if (norm>0)
	{
		vp/=norm;
	}
	else
	{
		vp.Set(1,0,0);
		
	}
	
	Point3 p(mRot_ * n_Support(vp,LastFeature));
	return p+trans_;
}

inline const S_ObjectTimeStamp & S_Object::checkStamp()const
{
	return stamp_;
}



inline void S_Object::getTransformationMatrix(Scalar *d) const
{
	d[0]=mRot_(0,0); d[4]=mRot_(0,1); d[8]=mRot_(0,2) ; d[12]=trans_[0];
	d[1]=mRot_(1,0); d[5]=mRot_(1,1); d[9]=mRot_(1,2) ; d[13]=trans_[1];
	d[2]=mRot_(2,0); d[6]=mRot_(2,1); d[10]=mRot_(2,2); d[14]=trans_[2];
	d[3]=0;         d[7]=0;         d[11]=0;         d[15]=1;
}

inline const Matrix3x3& S_Object::getOrientation() const
{
	return mRot_;
}

inline const Vector3& S_Object::getPosition() const
{
	return trans_;
}
