inline Point3 S_ObjectNonNormalized::Support(const Vector3& v) const
{
	Vector3 vp(v);
	vp=v*mRot; //ie : mRot.transpose*v (applying inverse transformation on the support vector)
	int k=-1;
	Point3 p(mRot * N_Support(vp,k));
	return p+trans;
}

inline Point3 S_ObjectNonNormalized::Support(const Vector3& v,int &LastFeature) const
{
	Vector3 vp(v);
	vp= v * mRot; //ie : mRot.transpose*v (applying inverse transformation on the support vector)
	Point3 p(mRot * N_Support(vp,LastFeature));
	return p+trans;
}