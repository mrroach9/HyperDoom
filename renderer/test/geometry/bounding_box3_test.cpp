#include "geometry/bounding_box3.h"
#include <gtest/gtest.h>

TEST(BoundingBox3Test, TestInitWorks) {
  hd::BoundingBox3 b1 = hd::BoundingBox3(
      hd::Vector3(0.0, 1.0, 2.0), hd::Vector3(10.0, 21.0, 32.0));
  hd::BoundingBox3 b2 = hd::BoundingBox3(
      0.0, 10.0, 1.0, 21.0, 2.0, 32.0);
  EXPECT_TRUE(b1 == b2);
  EXPECT_TRUE(b2.getMinCorner() == hd::Vector3(0.0, 1.0, 2.0));
  EXPECT_TRUE(b2.getMaxCorner() == hd::Vector3(10.0, 21.0, 32.0));
}

TEST(BoundingBox3Test, TestBasicProperties) {
  hd::BoundingBox3 b = hd::BoundingBox3(
      hd::Vector3(0.0, 1.0, 2.0), hd::Vector3(10.0, 21.0, 32.0));
  EXPECT_EQ(b.size(), hd::Vector3(10.0, 20.0, 30.0));
  EXPECT_EQ(b.volume(), 10 * 20 * 30);
  EXPECT_EQ(b.surfaceArea(), 2200 /* 2 * 10 * 20 + 2 * 10 * 30 + 2 * 20 * 30 */);

  hd::BoundingBox3 bShift = b.move(hd::Vector3(10.0, 10.0, 20.0));
  EXPECT_EQ(b.size(), bShift.size());
  EXPECT_EQ(b.volume(), bShift.volume());
  EXPECT_EQ(b.surfaceArea(), bShift.surfaceArea());

  hd::BoundingBox3 bExpected = hd::BoundingBox3(
      hd::Vector3(10.0, 11.0, 22.0), hd::Vector3(20.0, 31.0, 52.0));
  EXPECT_EQ(bShift, bExpected);
}
