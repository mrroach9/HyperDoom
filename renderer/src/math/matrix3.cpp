#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include "const.h"
#include "math/vector3.h"
#include "math/matrix3.h"

namespace hd {
  Matrix3::Matrix3(std::array<double, 3> row1,
      std::array<double, 3> row2,
      std::array<double, 3> row3) {
    mat[0] = row1;
    mat[1] = row2;
    mat[2] = row3;
  }

  Matrix3 Matrix3::diag(double s) {
    return Matrix3(Vector3::xUnit() * s, Vector3::yUnit() * s, Vector3::zUnit() * s);
  }

  Matrix3 Matrix3::crossProdMatOf(const Vector3& v) {
    return Matrix3(
        std::array<double, 3> {0, -v.z, v.y},
        std::array<double, 3> {v.z, 0, -v.x},
        std::array<double, 3> {-v.y, v.x, 0});
  }

  Matrix3& Matrix3::operator+=(const Matrix3& rhs) {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        this->mat[i][j] += rhs[i][j];
      }
    }
    return *this;
  }

  Matrix3 operator+(Matrix3 lhs, const Matrix3& rhs) {
    lhs += rhs;
    return lhs;
  }

  Matrix3& Matrix3::operator-=(const Matrix3& rhs) {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        this->mat[i][j] -= rhs[i][j];
      }
    }
    return *this;
  }

  Matrix3 operator-(Matrix3 lhs, const Matrix3& rhs) {
    lhs -= rhs;
    return lhs;
  }

  Matrix3& Matrix3::operator*=(const Matrix3& rhs) {
    this->mat = ((*this) * rhs).mat;
    return (*this);
  }

  Matrix3 operator*(const Matrix3& lhs, const Matrix3& rhs) {
    Matrix3 res = Matrix3::zero();
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        for (int k = 0; k < 3; ++k) {
          res.mat[i][j] += lhs.mat[i][k] * rhs.mat[k][j];
        }
      }
    }
    return res;
  }

  Vector3 operator*(const Matrix3& lhs, const Vector3& rhs) {
    Vector3 res = Vector3::zero();
    for (int i = 0; i < 3; ++i) {
      res.x += lhs.mat[0][i] * rhs[i];
      res.y += lhs.mat[1][i] * rhs[i];
      res.z += lhs.mat[2][i] * rhs[i];
    }
    return res;
  }

  Matrix3& Matrix3::operator*=(double rhs) {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        this->mat[i][j] *= rhs;
      }
    }
    return *this;
  }

  Matrix3 operator*(Matrix3 lhs, double rhs) {
    lhs *= rhs;
    return lhs;
  }

  Matrix3 operator*(double lhs, const Matrix3 rhs) {
    return rhs * lhs;
  }

  Matrix3& Matrix3::operator/=(double rhs) {
    assert(fabs(rhs) > HD_EPSILON_TINY);
    return (*this) *= 1.0 / rhs;
  }

  Matrix3 operator/(Matrix3 lhs, double rhs) {
    lhs /= rhs;
    return lhs;
  }

  Vector3 Matrix3::operator[](int rowInd) const {
    assert(rowInd >= 0 && rowInd <= 2);
    return Vector3(mat[rowInd]);
  }

  void Matrix3::set(int rowInd, Vector3& row) {
    assert(rowInd >= 0 && rowInd <= 2);
    mat[rowInd] = row.toArray();
  }

  void Matrix3::set(int rowInd, int colInd, double val) {
    assert(rowInd >= 0 && rowInd <= 2);
    assert(colInd >= 0 && colInd <= 2);
    mat[rowInd][colInd] = val;
  }

  bool operator==(const Matrix3& lhs, const Matrix3& rhs) {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (fabs(lhs.mat[i][j] - rhs.mat[i][j]) > HD_EPSILON) {
          return false;
        }
      }
    }
    return true;
  }

  Matrix3 Matrix3::t() const {
    Matrix3 m = Matrix3(*this);
    m.transposeSelf();
    return m;
  }

  void Matrix3::transposeSelf() {
    std::swap(mat[0][1], mat[1][0]);
    std::swap(mat[0][2], mat[2][0]);
    std::swap(mat[1][2], mat[2][1]);
  }

  double Matrix3::det() const {
    return mat[0][0] * mat[1][1] * mat[2][2]
        +  mat[0][1] * mat[1][2] * mat[2][0]
        +  mat[0][2] * mat[1][0] * mat[2][1]
        -  mat[2][0] * mat[1][1] * mat[0][2]
        -  mat[1][2] * mat[2][1] * mat[0][0]
        -  mat[0][1] * mat[1][0] * mat[2][2];
  }
}
