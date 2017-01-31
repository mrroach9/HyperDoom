#include "math/matrix3.h"
#include "math/vector3.h"
#include <gtest/gtest.h>
#include <array>

class Matrix3Test : public ::testing::Test {
  protected:
    hd::Matrix3 m1;
    hd::Matrix3 m2;
    virtual void SetUp() {
      m1 = hd::Matrix3(
          std::array<double, 3>{1.0, 2.0, 3.0},
          std::array<double, 3>{4.0, 5.0, 6.0},
          std::array<double, 3>{7.0, 8.0, 9.0}
      );
      m2 = hd::Matrix3(
          std::array<double, 3>{0.0, -1.0, 0.0},
          std::array<double, 3>{2.0, 1000.0, 0.0003},
          std::array<double, 3>{3.0, 0.0, -1000000.0}
      );
    }
    virtual void TearDown() {}
};

TEST_F(Matrix3Test, TestInitWorks) {
  hd::Matrix3 mat1 = hd::Matrix3();
  EXPECT_EQ(mat1, hd::Matrix3::zero());

  hd::Matrix3 mat2 = hd::Matrix3(
      std::array<double, 3>{1.0, 0.0, 0.0},
      std::array<double, 3>{0.0, 1.0, 0.0},
      std::array<double, 3>{0.0, 0.0, 1.0}
  );
  hd::Matrix3 mat3 = hd::Matrix3(
      hd::Vector3::xUnit(),
      hd::Vector3::yUnit(),
      hd::Vector3::zUnit()
  );
  EXPECT_EQ(mat2, mat3);
  EXPECT_EQ(mat2, hd::Matrix3::identity());
  EXPECT_EQ(mat3, hd::Matrix3::diag(1.0));
}

TEST_F(Matrix3Test, TestBasicOperators) {
  // m3 == m1 + m2.
  hd::Matrix3 m3 = hd::Matrix3(
      std::array<double, 3>{1.0, 1.0, 3.0},
      std::array<double, 3>{6.0, 1005.0, 6.0003},
      std::array<double, 3>{10.0, 8.0, -999991.0}
  );
  EXPECT_TRUE(m1 + m2 == m3);
  EXPECT_TRUE(m3 - m2 == m1);
  EXPECT_TRUE(2 * m3 - 2 * m2 == 2 * m1);
  m1 += m2;
  EXPECT_TRUE(m1 == m3);
  m1 -= m2;
  EXPECT_TRUE(m1 + m2 == m3);
  EXPECT_TRUE(m3 + hd::Matrix3::diag(1e-9) == m3);
  EXPECT_TRUE(m3 / 2.0 == m3 * 0.5);
}

TEST_F(Matrix3Test, TestGettersAndSettersViaIndices) {
  EXPECT_EQ(m1[0][0], 1.0);
  EXPECT_EQ(m1[2][1], 8.0);
  m1.set(2, hd::Vector3(-1.0, -2.0, -3.0));
  EXPECT_EQ(m1[2][0], -1.0);
  EXPECT_EQ(m1[2][1], -2.0);
  m1.set(1, 0, -100.0);
  EXPECT_EQ(m1[1], hd::Vector3(-100.0, 5.0, 6.0));
}

TEST_F(Matrix3Test, TestAdvancedOperations) {
  EXPECT_EQ(m1 * hd::Matrix3::identity(), m1);
  EXPECT_EQ(m1 * hd::Matrix3::diag(3.0), m1 * 3.0);
  hd::Matrix3 m3 = hd::Matrix3(
      std::array<double, 3>{2.0, 3.0, -1.0},
      std::array<double, 3>{1.0, 0.0, 4.0},
      std::array<double, 3>{-2.0, 2.0, 10.0}
  );
  // m4 == m1 * m3.
  hd::Matrix3 m4 = hd::Matrix3(
      std::array<double, 3>{-2.0, 9.0, 37.0},
      std::array<double, 3>{1.0, 24.0, 76.0},
      std::array<double, 3>{4.0, 39.0, 115.0}  
  );
  EXPECT_EQ(m1 * m3, m4);
  // m5 == m1^T
  hd::Matrix3 m5 = hd::Matrix3(
      std::array<double, 3>{1.0, 4.0, 7.0},
      std::array<double, 3>{2.0, 5.0, 8.0},
      std::array<double, 3>{3.0, 6.0, 9.0}  
  );
  EXPECT_EQ(m1.t(), m5);
  // Verifies that transpose is self-reflective.
  EXPECT_EQ(m5.t(), m1);
  EXPECT_EQ(m1.t().t(), m1);
  m5.transposeSelf();
  EXPECT_EQ(m1, m5);
  // Verifies that (A*B)^T = B^T * A^T.
  EXPECT_EQ(m3.t() * m1.t(), m4.t());

  // Verifies the value of determinant calculation.
  EXPECT_EQ(m1.det(), 0.0);
  m1.set(2, 2, 10.0);
  EXPECT_EQ(m1.det(), -3.0);
  EXPECT_EQ(hd::Matrix3::diag(3.0).det(), 27.0);
}

TEST_F(Matrix3Test, TestCrossProdMat) {
  hd::Vector3 v1 = hd::Vector3(1.0, -1.0, 2.0);
  hd::Vector3 v2 = hd::Vector3(-0.5, 0.0, 1.0);
  // v3 = v1 ^ v2.
  hd::Vector3 v3 = hd::Vector3(-1.0, -2.0, -0.5);
  EXPECT_EQ(hd::Matrix3::crossProdMatOf(v1) * v2, v3);
  EXPECT_EQ(hd::Matrix3::crossProdMatOf(v1) * v2, v1 ^ v2);
}