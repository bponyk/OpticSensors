#include "stdafx.h"

#include <MathBase\math\Vector3D.h>

TEST(Vector3D, CheckConstructorForZeroing)
  {
  Vector3D vec;
  EXPECT_EQ(0, vec[0]);
  EXPECT_EQ(0, vec[1]);
  EXPECT_EQ(0, vec[2]);
  }

TEST(Vector3D, CopyConstructorTest)
  {
  Vector3D vec(1,2,3);
  Vector3D vec1(vec);
  EXPECT_EQ(vec[0], vec1[0]);
  EXPECT_EQ(vec[1], vec1[1]);
  EXPECT_EQ(vec[2], vec1[2]);
  }

TEST(Vector3D, PlusVectors)
  {
  Vector3D vec(1,2,3);
  Vector3D vec2(vec);

  Vector3D vec_result = vec + vec2;
  EXPECT_EQ(2, vec_result[0]);
  EXPECT_EQ(4, vec_result[1]);
  EXPECT_EQ(6, vec_result[2]);
  }

TEST(Vector3D, MinusVectors)
  {
  Vector3D vec(1,2,3);
  Vector3D vec2(vec);

  Vector3D vec_result = vec - vec2;
  EXPECT_EQ(0, vec_result[0]);
  EXPECT_EQ(0, vec_result[1]);
  EXPECT_EQ(0, vec_result[2]);
  }

TEST(Vector3D, MultipleVectorAndValue)
  {
  Vector3D vec(1,2,3);
  Vector3D vec2(vec);
  vec2 *= 10;

  EXPECT_EQ(10, vec2[0]);
  EXPECT_EQ(20, vec2[1]);
  EXPECT_EQ(30, vec2[2]);
  }

TEST(Vector3D, DotProductVector)
  {
  Vector3D vec(1,2,3);
  Vector3D vec2(vec);
  vec2 *= 10;
  double dot_result = DotProduct(vec2, vec);
  EXPECT_EQ(140, dot_result);
  }

TEST(Vector3D, NormalizationTest)
  {
  Vector3D vec;
  vec.Randomize();
  ASSERT_DOUBLE_EQ(1, vec.LengthSq());
  }

TEST(Vector3D, CrossProductTest)
  {
  Vector3D vec;
  vec.Randomize();
  ASSERT_DOUBLE_EQ(0, vec.CrossProduct(vec).LengthSq());
  }