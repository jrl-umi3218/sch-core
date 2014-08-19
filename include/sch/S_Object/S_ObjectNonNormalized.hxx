inline Point3 S_ObjectNonNormalized::support(const Vector3& v) const
{
  Vector3 vp = mRot_.transpose() * v;
  if (vp.squaredNorm()==0)
  {
    vp << 1,0,0;
  }
  int k=-1;
  Point3 p(mRot_ * l_Support(vp,k));
  return p+trans_;
}

inline Point3 S_ObjectNonNormalized::support(const Vector3& v,int &LastFeature) const
{
  Vector3 vp = mRot_.transpose() * v;
  if (vp.squaredNorm()==0)
  {
    vp << 1,0,0;
  }
  Point3 p(mRot_ * l_Support(vp,LastFeature));
  return p+trans_;
}

