#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#pragma once

#include <array>

namespace hd {
  class Vector3 {
    // Constructors, destructors and initializers.
    public:
      double x, y, z;
      Vector3() : x(0.0), y(0.0), z(0.0) {}
      Vector3(double nx, double ny, double nz) : x(nx), y(ny), z(nz) {}
      Vector3(const Vector3 &v) : x(v.x), y(v.y), z(v.z) {}
      ~Vector3() {}

      // Returns vector (s, s, s).
      static Vector3 identity(double s) { return Vector3(s, s, s); }
      static Vector3 zero() { return identity(0.0); }
      static Vector3 one() { return identity(1.0); }

      // Returns standard base vectors (1, 0, 0), (0, 1, 0) and (0, 0, 1).
      static Vector3 xUnit() { return Vector3(1.0, 0.0, 0.0); }
      static Vector3 yUnit() { return Vector3(0.0, 1.0, 0.0); }
      static Vector3 zUnit() { return Vector3(0.0, 0.0, 1.0); }

    // Operators.
    public:
      Vector3& operator+=(const Vector3 &rhs);
      friend Vector3 operator+(Vector3 lhs, const Vector3 &rhs);

      Vector3& operator-=(const Vector3 &rhs);
      friend Vector3 operator-(Vector3 lhs, const Vector3 &rhs);

      // Multiplication and division with scalars.
      Vector3& operator*=(double s);
      friend Vector3 operator*(Vector3 lhs, double s);
      friend Vector3 operator*(double s, Vector3 rhs);

      // Note: passing in 0 or almost zero values will cause assertion error.
      Vector3& operator/=(double s);
      friend Vector3 operator/(Vector3 lhs, double s);

      // Comparison within error bounds.
      friend bool operator==(const Vector3& lhs, const Vector3& rhs);

      // Get component with index. 0 - x, 1 - y, 2 - z.
      // Passing in index other than 0, 1, 2 will cause assertion error.
      double operator[](int index);
      std::array<double, 3> toArray();
      void set(int index, double value);

      // Inner product, cross product and their derivitives.
      friend double operator*(const Vector3& lhs, const Vector3& rhs);
      double len();
      double len2();
      // Return normalized vector from this one.
      Vector3 normalize();
      // Normalize this vector and return its length.
      double normalizeSelf();
      // Cross product
      friend Vector3 operator^(const Vector3& lhs, const Vector3& rhs);
      // TODO: outer product equivalent matrix.
  };
}
#endif // _VECTOR3_H_
