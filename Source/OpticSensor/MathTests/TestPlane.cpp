#include "stdafx.h"

#include <MathBase\math\Plane3D.h>

TEST(Plane3D, PlaneIntersectionTest)
{
  Vector3D norm(1,1,1);
  Vector3D vec1(20,20,20);
  Vector3D vec2(-15,-15,-7);

  Plane3D plane(norm,3);
  Vector3D point;
  EXPECT_EQ(true, plane.GetIntersectionPoint(point, vec1, vec2));
  EXPECT_NEAR(-plane.GetDistance(), point.DotProduct(plane.GetNormal()), Vector3D::Precision());
}