inline Point3 S_ObjectNonNormalized::support(const Vector3& v) const
{
	Vector3 vp(v);
	vp=v*mRot_; //ie : mRot.transpose*v (applying inverse transformation on the support vector)
	int k=-1;
	Point3 p(mRot_ * n_Support(vp,k));
	return p+trans_;
}

inline Point3 S_ObjectNonNormalized::support(const Vector3& v,int &LastFeature) const
{
	Vector3 vp(v);
	vp= v * mRot_; //ie : mRot.transpose*v (applying inverse transformation on the support vector)
	Point3 p(mRot_ * n_Support(vp,LastFeature));
	return p+trans_;
}