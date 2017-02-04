#include <cassert>
#include "geometry/bounding_box3.h"

namespace hd {
  BoundingBox3::BoundingBox3(const Vector3& minVec, const Vector3& maxVec) {
    assert(minVec.x <= maxVec.x
        && minVec.y <= maxVec.y
        && minVec.z <= maxVec.z);
    minCorner = minVec;
    maxCorner = maxVec;
  }

  BoundingBox3::BoundingBox3(double minX, double maxX, double minY, double maxY,
      double minZ, double maxZ) {
    assert(minX <= maxX && minY <= maxY && minZ <= maxZ);
    minCorner = Vector3(minX, minY, minZ);
    maxCorner = Vector3(maxX, maxY, maxZ);
  }

  bool operator==(const BoundingBox3& lhs, const BoundingBox3& rhs) {
    return lhs.minCorner == rhs.minCorner && lhs.maxCorner == rhs.maxCorner;
  }

  double BoundingBox3::volume() const {
    Vector3 boxSize = size();
    double volume = boxSize.x * boxSize.y * boxSize.z;
    assert(volume >= 0);
    return volume;
  }

  double BoundingBox3::surfaceArea() const {
    Vector3 boxSize = size();
    double area = 2.0 * (boxSize.x * boxSize.y
        + boxSize.x * boxSize.z
        + boxSize.y * boxSize.z);
    assert(area >= 0);
    return area;
  }

  BoundingBox3 BoundingBox3::move(const Vector3& v) const {
    BoundingBox3 b = BoundingBox3(*this);
    b.moveSelf(v);
    return b;
  }

  void BoundingBox3::moveSelf(const Vector3& v) {
    minCorner += v;
    maxCorner += v;
  }
}
