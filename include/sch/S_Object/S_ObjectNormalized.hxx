inline Point3 S_ObjectNormalized::support(const Vector3& v) const
{
  Vector3 vp = mRot_.transpose()*v;
  Scalar norm=vp.norm();
  if (norm>0)
  {
    vp/=norm;
  }
  else
  {
    vp << 1,0,0;
  }
  int k=-1;
  Point3 p(mRot_ * l_Support(vp,k));
  return p+trans_;
}


inline Point3 S_ObjectNormalized::support(const Vector3& v,int &LastFeature) const
{
  Vector3 vp = mRot_.transpose()*v; 
  Scalar norm=vp.norm();
  if (norm>0)
  {
    vp/=norm;
  }
  else
  {
    vp << 1,0,0;
  }

  Point3 p(mRot_ * l_Support(vp,LastFeature));
  return p+trans_;
}
