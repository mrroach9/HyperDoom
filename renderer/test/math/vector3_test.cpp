#include "math/vector3.h"
#include <gtest/gtest.h>

TEST(Vector3Test, TestInitWorks) {
  hd::Vector3 v = hd::Vector3();
  EXPECT_DOUBLE_EQ(v.x, 0.0);
  EXPECT_DOUBLE_EQ(v.y, 0.0);
  EXPECT_DOUBLE_EQ(v.z, 0.0);

  v = hd::Vector3(1.0, 2.0, 3.0);
  EXPECT_DOUBLE_EQ(v.x, 1.0);
  EXPECT_DOUBLE_EQ(v.y, 2.0);
  EXPECT_DOUBLE_EQ(v.z, 3.0);

  v = hd::Vector3::identity(2.0);
  EXPECT_DOUBLE_EQ(v.x, 2.0);
  EXPECT_DOUBLE_EQ(v.y, 2.0);
  EXPECT_DOUBLE_EQ(v.z, 2.0);
}

TEST(Vector3Test, TestBasicOperators) {
  hd::Vector3 v = hd::Vector3::identity(0.3);
  hd::Vector3 u = hd::Vector3(1.0, 1.0, 1.0);
  hd::Vector3 w = hd::Vector3(u);

  EXPECT_TRUE(u == w);
  EXPECT_TRUE(u == hd::Vector3::identity(1.0));
  u *= 0.3;
  EXPECT_TRUE(u == v);
  EXPECT_TRUE(w * 0.3 == v);

  u.x += 1e-9;
  u.y -= 1e-9;
  u.z += 1e-8;
  EXPECT_TRUE(u == v);

  v = hd::Vector3(1.0, 2.0, 3.0);
  u = hd::Vector3(2.0, 5.0, 8.0);
  EXPECT_TRUE(u + v == hd::Vector3(3.0, 7.0, 11.0));
  EXPECT_TRUE(u - v == hd::Vector3(1.0, 3.0, 5.0));
  u += v;
  EXPECT_DOUBLE_EQ(u.x, 3.0);
  EXPECT_DOUBLE_EQ(u.y, 7.0);
  EXPECT_DOUBLE_EQ(u.z, 11.0);
}
