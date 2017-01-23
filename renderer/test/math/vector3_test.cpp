#include "math/vector3.h"
#include <gtest/gtest.h>

TEST(Vector3Test, TestInitWorks) {
    Vector3 v = Vector3();
    EXPECT_EQ(v.x, 0.0);
    EXPECT_EQ(v.y, 0.0);
    EXPECT_EQ(v.z, 0.0);
}
