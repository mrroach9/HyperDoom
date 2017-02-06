#ifndef _MATRIX3_H_
#define _MATRIX3_H_

#pragma once

#include <array>
#include "math/vector3.h"

namespace hd {
  /**
   * 3x3 double-precision Matrix definition and its operations.
   */
  class Matrix3 {
    private:
      std::array<std::array<double, 3>, 3> _mat;
  
    // Constructors, destructors and initiators.
    public:
      Matrix3();
      Matrix3(std::array<double, 3> row1, std::array<double, 3> row2, std::array<double, 3> row3);
      Matrix3(const Vector3& row1, const Vector3& row2, const Vector3& row3)
          : Matrix3(row1.toArray(), row2.toArray(), row3.toArray()) {}
      Matrix3(const Matrix3& m) : Matrix3(m[0], m[1], m[2]) {}
      ~Matrix3() {}

      static Matrix3 diag(double s = 1.0);
      static Matrix3 zero() { return diag(0.0); }
      static Matrix3 identity() { return diag(1.0); }
      // Create cross-product-equivalent matrix from a given vector.
      // E.g. axb = M_a * b, calling this method with param a returns M_a.
      static Matrix3 crossProdMatOf(const Vector3& v);
    
    // Basic operations.
    public:
      // Additions and substractions.
      Matrix3& operator+=(const Matrix3& rhs);
      friend Matrix3 operator+(Matrix3 lhs, const Matrix3& rhs);
      Matrix3& operator-=(const Matrix3& rhs);
      friend Matrix3 operator-(Matrix3 lhs, const Matrix3& rhs);

      // Multiplication with matrices.
      Matrix3& operator*=(const Matrix3& rhs);
      friend Matrix3 operator*(const Matrix3& lhs, const Matrix3& rhs);
      friend Vector3 operator*(const Matrix3& lhs, const Vector3& rhs);
      
      // Multiplication and division with numericals.
      Matrix3& operator*=(double rhs);
      friend Matrix3 operator*(Matrix3 lhs, double rhs);
      friend Matrix3 operator*(double lhs, const Matrix3 rhs);
      Matrix3& operator/=(double rhs);
      friend Matrix3 operator/(Matrix3 lhs, double rhs);

      // Getters and setters via indices.
      // Get n-th row with []
      Vector3 operator[](int rowInd) const;
      // Set row at given index.
      void set(int rowInd, Vector3& row);
      // Set value at given row and column indices.
      void set(int rowInd, int colInd, double val);

      // Comparison within error bounds.
      friend bool operator==(const Matrix3& lhs, const Matrix3& rhs);

    // Matrix specific operations.
    public:
      // Return a new matrix whose value is the transpose of this.
      Matrix3 t() const;
      // Convert this matrix to its transpose.
      void transposeSelf();
      // Calculates the determinant.
      double det() const;
  };
}

#endif // _MATRIX3_H_