#include <math.h>

class Point
{
 private:
  double x;
  double y;

 public:
  Point() {
    x = 0;
    y = 0;
  }
  void move(double dx, double dy) {
    x = x + dx;
    y = y + dy;
  }
  double distanceFrom(const Point & p) {
    double dis;
    dis = sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    return dis;
  }
};
