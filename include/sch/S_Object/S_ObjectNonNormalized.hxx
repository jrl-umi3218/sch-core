inline Point3 S_ObjectNonNormalized::support(const Vector3& v) const
{
  Vector3 vp = (mRot_.transpose() * v).eval();
  if (vp.squaredNorm()==0)
  {
    vp << 1,0,0;
  }
  int k=-1;
  return mRot_ * l_Support(vp, k) + trans_;
}

inline Point3 S_ObjectNonNormalized::support(const Vector3& v,int &LastFeature) const
{
  Vector3 vp = (mRot_.transpose() * v).eval();
  if (vp.squaredNorm()==0)
  {
    vp << 1,0,0;
  }
  return mRot_ * l_Support(vp, LastFeature) + trans_;
}

