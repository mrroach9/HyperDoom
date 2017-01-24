#include "const.h"
#include "math/vector3.h"
#include <cassert>
#include <cmath>

namespace hd {
  Vector3& Vector3::operator+=(const Vector3 &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  Vector3 operator+(Vector3 lhs, const Vector3 &rhs) {
    lhs += rhs;
    return lhs;
  }

  Vector3& Vector3::operator-=(const Vector3 &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  Vector3 operator-(Vector3 lhs, const Vector3 &rhs) {
    lhs -= rhs;
    return lhs;
  }

  Vector3& Vector3::operator*=(double s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }

  Vector3 operator*(Vector3 lhs, double s) {
    lhs *= s;
    return lhs;
  }

  Vector3 operator*(double s, Vector3 rhs) {
    rhs *= s;
    return rhs;
  }

  bool operator==(const Vector3& lhs, const Vector3& rhs) {
    return fabs(lhs.x - rhs.x) < HD_EPSILON
        && fabs(lhs.y - rhs.y) < HD_EPSILON
        && fabs(lhs.z - rhs.z) < HD_EPSILON;
  }
  
  Vector3& Vector3::operator/=(double s) {
    assert(fabs(s) > HD_EPSILON_TINY);
    return (*this) *= (1.0 / s);
  }

  Vector3 operator/(Vector3 lhs, double s) {
    lhs /= s;
    return lhs;
  }

  double Vector3::operator[](int index) {
    assert(index >= 0 && index <= 2);
    return index == 0 ? x : (index == 1 ? y : z);
  }

  std::array<double, 3> Vector3::toArray() {
    std::array<double, 3> a = {x, y, z};
    return a;
  }

  void Vector3::set(int index, double value) {
    assert(index >= 0 && index <= 2);
    if (index == 0) {
      x = value;
    } else if (index == 1) {
      y = value;
    } else {
      z = value;
    }
  }

  double operator*(const Vector3& lhs, const Vector3& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
  }

  double Vector3::len() {
    return sqrt(len2());
  }

  double Vector3::len2() {
    return (*this) * (*this);
  }

  Vector3 Vector3::normalize() {
    Vector3 v = Vector3(*this);
    v.normalizeSelf();
    return v;
  }

  double Vector3::normalizeSelf() {
    double l = len2();
    if (l < HD_EPSILON_TINY) {
      return 0;
    }
    l = sqrt(l);
    (*this) /= l;
    return l;
  }

  Vector3 operator^(const Vector3& lhs, const Vector3& rhs) {
    return Vector3(
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x);
  }
}