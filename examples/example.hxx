/*!
 * \brief compare a and b using the absolute value of the difference
 * \param a
 * \param b
 * \param str a description displayed in case of the comparison failed
 * \param espilon distance between the objects
 */
template <class T>
inline bool compare(const T & a, const T & b, const std::string & str, double epsilon = 1e-12)
{
  if (fabs(a-b) >= epsilon)
  {
    std::cerr << "Error in "<< str << ":" << std::endl;
    std::cerr << a << std::endl << b << std::endl;
    return false;
  }
  return true;
}

/*!
 * \brief Specilizatio of the comparison method for vector3
 */
inline bool compare(const sch::Vector3 & a, const sch::Vector3 & b, const std::string & str, double epsilon = 1e-12)
{
  if ((a-b).norm() >= epsilon)
  {
    std::cerr << "Error in "<< str << ":" << std::endl;
    std::cerr << a << std::endl << b << std::endl;
    return false;
  }
  return true;
}

