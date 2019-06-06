#include <sch/S_Object/S_Sphere.h>
#include <sch/S_Object/S_Box.h>
#include <sch/CD/CD_Pair.h>

int main()
{
  sch::S_Sphere sphere(0.1);
  sch::S_Box box(0.1, 0.1, 0.1);
  sch::Matrix4x4 box_t;
  box_t(0, 3) = 0.2;
  box.setTransformation(box_t);
  sch::CD_Pair p(&sphere, &box);
  std::cout << "Distance between sphere and box: " << std::sqrt(p.getDistance()) << "\n";
  return 0;
}
