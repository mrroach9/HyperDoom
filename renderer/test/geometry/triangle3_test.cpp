#include "geometry/triangle3.h"
#include <cmath>
#include <gtest/gtest.h>

class Triangle3Test : public ::testing::Test {
  protected:
    hd::Triangle3 tri1;
    hd::Triangle3 tri2;

    virtual void SetUp() {
      // A right-angle triangle with v0 at origin and lying on xOy plane.
      // Essensially two-dimentional, facing up (z-positive).
      tri1 = hd::Triangle3(
        hd::Vector3(0.0, 0.0, 0.0),
        hd::Vector3(1.0, 0.0, 0.0),
        hd::Vector3(0.0, 2.0, 0.0)
      );
      // An equilateral triangle with three vertices lying on x-, y-, z-positive
      // axis, facing Octant I.
      tri2 = hd::Triangle3(
        hd::Vector3(1.0, 0.0, 0.0),
        hd::Vector3(0.0, 1.0, 0.0),
        hd::Vector3(0.0, 0.0, 1.0)
      );
    }
    virtual void TearDown() {}
};

TEST_F(Triangle3Test, TestInitAndGetters) {
  hd::Triangle3 almostZeroTri = hd::Triangle3(
    hd::Vector3(0.0, -1e-9, 0.0),
    hd::Vector3(0.0, 0.0, 0.0),
    hd::Vector3(0.0, 0.0, 1e-9)
  );

  EXPECT_TRUE(almostZeroTri == hd::Triangle3());
  EXPECT_FALSE(almostZeroTri == tri1);

  EXPECT_EQ(tri1.v(2), hd::Vector3(0.0, 2.0, 0.0));
  EXPECT_EQ(tri1.e(1), hd::Vector3(-1.0, 2.0, 0.0));
  EXPECT_EQ(tri2.e(2), hd::Vector3(1.0, 0.0, -1.0));
}

TEST_F(Triangle3Test, TestProperties) {
  EXPECT_EQ(tri1.normal(), hd::Vector3(0.0, 0.0, 1.0));
  EXPECT_EQ(tri2.normal(), hd::Vector3::identity(sqrt(3) / 3.0));

  EXPECT_EQ(tri1.boundingBox3(),
      hd::BoundingBox3(0.0, 1.0, 0.0, 2.0, 0.0, 0.0));
  EXPECT_EQ(tri2.boundingBox3(),
      hd::BoundingBox3(0.0, 1.0, 0.0, 1.0, 0.0, 1.0));

  // 1 * 2 / 2 = 1.0
  EXPECT_EQ(tri1.surfaceArea(), 1.0);
  // sqrt(3) / 4 * (sqrt(2) ^ 2)
  EXPECT_EQ(tri2.surfaceArea(), sqrt(3) / 2.0);
}
