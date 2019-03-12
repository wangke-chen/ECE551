#include <math.h>

#include <cstdio>
#include <cstdlib>

#include "point.h"

class Circle
{
 private:
  Point center;
  const double radius;

 public:
  Circle(Point c, const double r) : center(c), radius(r) {}
  void move(double dx, double dy) { center.move(dx, dy); }
  double intersectionArea(const Circle & otherCircle) {
    double dis = center.distanceFrom(otherCircle.center);

    if (dis >= (radius + otherCircle.radius)) {
      return 0;
    }
    if (dis <= (radius - otherCircle.radius)) {
      return acos(-1.0) * pow(otherCircle.radius, 2);
    }
    if (dis <= (otherCircle.radius - radius)) {
      return acos(-1.0) * pow(radius, 2);
    }
    double angle1 = acos((radius * radius + dis * dis - otherCircle.radius * otherCircle.radius) /
                         (2.0 * radius * dis));
    double angle2 = acos((-radius * radius + dis * dis + otherCircle.radius * otherCircle.radius) /
                         (2.0 * otherCircle.radius * dis));
    return (angle1 * pow(radius, 2) + angle2 * pow(otherCircle.radius, 2) -
            radius * dis * sin(angle1));
  }
};
