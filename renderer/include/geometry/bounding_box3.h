#ifndef _BOUNDING_BOX3_H_
#define _BOUNDING_BOX3_H_

#pragma once

#include "math/vector3.h"
#include "geometry/has_surface_area.h"
#include "geometry/has_volume.h"

namespace hd {
  /**
   * 3-dimensional bounding box. The bounding box is defined by it's top-left-front corner and
   * right-bottom-rear corner vectors, with all faces parallel to xOy, yOz, zOx planes.
   */
  class BoundingBox3 : public HasSurfaceArea, public HasVolume {
    private:
      // Positions of two corners of the bounding box. The x, y, z components of minCorner must
      // be less or equal to those of maxCorner, respectively.
      Vector3 minCorner;
      Vector3 maxCorner;

    public:
      BoundingBox3() : minCorner(0.0, 0.0, 0.0), maxCorner(0.0, 0.0, 0.0) {}
      BoundingBox3(const Vector3& minVec, const Vector3& maxVec);
      BoundingBox3(double minX, double maxX, double minY, double maxY, double minZ, double maxZ);
      BoundingBox3(const BoundingBox3& box)
          : minCorner(box.minCorner), maxCorner(box.maxCorner) {}
      ~BoundingBox3() {}

    public:
      Vector3 getMinCorner() const { return Vector3(minCorner); }
      Vector3 getMaxCorner() const { return Vector3(maxCorner); }
      Vector3 length() const { return maxCorner - minCorner; }
      double minX() const { return minCorner.x; }
      double minY() const { return minCorner.y; }
      double minZ() const { return minCorner.z; }
      double maxX() const { return maxCorner.z; }
      double maxY() const { return maxCorner.y; }
      double maxZ() const { return maxCorner.z; }
      double lenX() const { return maxCorner.x - minCorner.x; }
      double lenY() const { return maxCorner.y - minCorner.y; }
      double lenZ() const { return maxCorner.z - minCorner.z; }
    
    public:
      // Compare bounding boxes within error bounds.
      friend bool operator==(const BoundingBox3& lhs, const BoundingBox3& rhs);
      double volume() const override;
      double surfaceArea() const override;
      // Returns a new bounding box by moving this one by the given vector.
      BoundingBox3 move(const Vector3& v) const;
      // Move this bounding box by a given vector.
      void moveSelf(const Vector3& v);
  };
}

#endif // _BOUNDING_BOX3_H_