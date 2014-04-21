inline Point3 S_ObjectNonNormalized::support(const Vector3& v) const
{
  Vector3 vp(v);
  vp=v*mRot_; //ie : mRot.transpose*v (applying inverse transformation on the support vector)
  if (vp.normsquared()==0)
  {
    vp.Set(1,0,0);
  }
  int k=-1;
  Point3 p(mRot_ * l_Support(vp,k));
  return p+trans_;
}

inline Point3 S_ObjectNonNormalized::support(const Vector3& v,int &LastFeature) const
{
  Vector3 vp(v);
  vp= v * mRot_; //ie : mRot.transpose*v (applying inverse transformation on the support vector)
  if (vp.normsquared()==0)
  {
    vp.Set(1,0,0);
  }
  Point3 p(mRot_ * l_Support(vp,LastFeature));
  return p+trans_;
}

