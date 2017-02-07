#include "geometry/triangle3.h"
#include "const.h"
#include <cassert>
#include <algorithm>

namespace hd {
  Triangle3::Triangle3() {
    _vertices = std::array<Vector3, 3> {
      Vector3::zero(), Vector3::zero(), Vector3::zero()
    };
  }

  Vector3 Triangle3::v(unsigned int index) const {
    assert(index < 3);
    return Vector3(_vertices[index]);
  }

  Vector3 Triangle3::e(unsigned int index) const {
    assert(index < 3);
    return _vertices[(index + 1) % 3] - _vertices[index];
  }

  Vector3 Triangle3::normal() const {
    Vector3 e0 = e(0);
    Vector3 e1 = e(1);
    Vector3 n = e0 ^ e1;
    assert(n.len2() > HD_EPSILON_TINY);
    return n.normalize();
  }

  bool operator==(const Triangle3& lhs, const Triangle3& rhs) {
    return lhs._vertices[0] == rhs._vertices[0]
        && lhs._vertices[1] == rhs._vertices[1]
        && lhs._vertices[2] == rhs._vertices[2];
  }

  BoundingBox3 Triangle3::boundingBox3() const {
    return BoundingBox3(
      std::min({_vertices[0].x, _vertices[1].x, _vertices[2].x}),   // minX
      std::max({_vertices[0].x, _vertices[1].x, _vertices[2].x}),   // minX
      std::min({_vertices[0].y, _vertices[1].y, _vertices[2].y}),   // minX
      std::max({_vertices[0].y, _vertices[1].y, _vertices[2].y}),   // minX
      std::min({_vertices[0].z, _vertices[1].z, _vertices[2].z}),   // minX
      std::max({_vertices[0].z, _vertices[1].z, _vertices[2].z})    // minX
    );
  }

  // Calculates the area of the triangle. We compute using cross product:
  // For triangle ABC, the length of AB x BC is the area of parallelogram supported by
  // AB and AC. Thus one half of that is the triangle area.
  double Triangle3::surfaceArea() const {
    return (e(0) ^ e(1)).len() / 2.0;
  }
}