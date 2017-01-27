#include <array>
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
    // TODO: impl.
    return Matrix3();
  }

  Matrix3& Matrix3::operator+=(const Matrix3& rhs) {
    // TODO: impl.
    return *this;
  }

  Matrix3 operator+(Matrix3 lhs, const Matrix3& rhs) {
    lhs += rhs;
    return lhs;
  }

  Matrix3& Matrix3::operator-=(const Matrix3& rhs) {
    // TODO: impl.
    return *this;
  }

  Matrix3 operator-(Matrix3 lhs, const Matrix3& rhs) {
    lhs -= rhs;
    return lhs;
  }

  Matrix3& Matrix3::operator*=(const Matrix3& rhs) {
    // TODO: impl.
    return *this;
  }

  Matrix3 operator*(Matrix3 lhs, const Matrix3& rhs) {
    lhs *= rhs;
    return lhs;
  }

  Matrix3& Matrix3::operator*=(double rhs) {
    // TODO: impl.
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
    // TODO: impl.
    return *this;
  }

  Matrix3 operator/(Matrix3 lhs, double rhs) {
    lhs /= rhs;
    return lhs;
  }

  Vector3& Matrix3::operator[](int rowInd) const {
    // TODO: impl.
    return Vector3();
  }

  void Matrix3::set(int rowInd, Vector3& row) {
    // TODO: impl.
  }

  void Matrix3::set(int rowInd, int colInd, double val) {
    // TODO: impl.
  }

  bool operator==(const Matrix3& lhs, const Matrix3& rhs) {
    // TODO: impl.
    return true;
  }

  Matrix3 Matrix3::t() const {
    Matrix3 m = Matrix3(*this);
    m.transposeSelf();
    return m;
  }

  void Matrix3::transposeSelf() {
    // TODO: impl.
  }

  double Matrix3::det() const {
    // TODO: impl.
    return 0;
  }
}
