inline const S_ObjectTimeStamp & S_Object::checkStamp()const
{
  return stamp_;
}

inline void S_Object::getTransformationMatrix(Scalar *d) const
{
  d[0]=mRot_(0,0);
  d[4]=mRot_(0,1);
  d[8]=mRot_(0,2) ;
  d[12]=trans_[0];
  d[1]=mRot_(1,0);
  d[5]=mRot_(1,1);
  d[9]=mRot_(1,2) ;
  d[13]=trans_[1];
  d[2]=mRot_(2,0);
  d[6]=mRot_(2,1);
  d[10]=mRot_(2,2);
  d[14]=trans_[2];
  d[3]=0;
  d[7]=0;
  d[11]=0;
  d[15]=1;
}

inline const Matrix3x3& S_Object::getOrientation() const
{
  return mRot_;
}

inline const Vector3& S_Object::getPosition() const
{
  return trans_;
}

inline int S_Object::getSlices() const
{
  return slices_;
}

inline int S_Object::getStacks() const
{
  return stacks_;
}

