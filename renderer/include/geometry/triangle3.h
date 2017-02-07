#ifndef _TRIANGLE3_H_
#define _TRIANGLE3_H_

#pragma once

#include <array>
#include "geometry/bounding_box3.h"
#include "geometry/has_bounding_box3.h"
#include "geometry/has_surface_area.h"
#include "math/vector3.h"

namespace hd {
  /**
   * Definition and operations of a 3-d space triangle.
   * Unlike TriangularMesh::Face, which only stores reference to internal vertices
   * and edges, this data structure wraps a complete description of a triangle,
   * including its three vertices and all derived properties.
   */
   // TODO: add entity id.
  class Triangle3 : public HasBoundingBox3, public HasSurfaceArea {
    private:
      // v[0], v[1] and v[2] are considered in counter-clockwise order, that is, applying right-hand
      // rule from v[0] to v[1] to v[2] yields upper normal direction of the triangle.
      std::array<Vector3, 3> _vertices;

    // Constructors, destructors and initializers.
    public:
      Triangle3();
      Triangle3(const std::array<Vector3, 3>& v) : _vertices(v) {}
      Triangle3(const Vector3& v0, const Vector3& v1, const Vector3& v2)
          : _vertices(std::array<Vector3, 3> {v0, v1, v2}) {}
      Triangle3(const Triangle3& t) : _vertices(t._vertices) {}
      ~Triangle3() {}

    public:
      // Returns vertex at given index.
      Vector3 v(unsigned int index) const;
      // Returns directed edge vector at given index:
      //   e(0) = v[0]->v[1]
      //   e(1) = v[1]->v[2]
      //   e(2) = v[2]->v[0]
      Vector3 e(unsigned int index) const;
      friend bool operator==(const Triangle3& lhs, const Triangle3& rhs);

      Vector3 normal() const;
      BoundingBox3 boundingBox3() const;
      double surfaceArea() const;
  };
}

#endif // _TRIANGLE3_H_