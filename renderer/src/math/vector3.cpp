#include "const.h"
#include "math/vector3.h"
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
}