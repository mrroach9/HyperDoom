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
      Vector3 _minCorner;
      Vector3 _maxCorner;

    // Initializers and deconstructors.
    public:
      BoundingBox3() : _minCorner(0.0, 0.0, 0.0), _maxCorner(0.0, 0.0, 0.0) {}
      BoundingBox3(const Vector3& minVec, const Vector3& maxVec);
      BoundingBox3(double minX, double maxX, double minY, double maxY, double minZ, double maxZ);
      BoundingBox3(const BoundingBox3& box)
          : _minCorner(box._minCorner), _maxCorner(box._maxCorner) {}
      ~BoundingBox3() {}

    // Getters and setters.
    public:
      Vector3 minCorner() const { return Vector3(_minCorner); }
      Vector3 maxCorner() const { return Vector3(_maxCorner); }
      double minX() const { return _minCorner.x; }
      double minY() const { return _minCorner.y; }
      double minZ() const { return _minCorner.z; }
      double maxX() const { return _maxCorner.z; }
      double maxY() const { return _maxCorner.y; }
      double maxZ() const { return _maxCorner.z; }
      double lenX() const { return _maxCorner.x - _minCorner.x; }
      double lenY() const { return _maxCorner.y - _minCorner.y; }
      double lenZ() const { return _maxCorner.z - _minCorner.z; }
  
    // Basic properties and operations.
    public:
      // Compare bounding boxes within error bounds.
      friend bool operator==(const BoundingBox3& lhs, const BoundingBox3& rhs);
      Vector3 size() const { return _maxCorner - _minCorner; }      
      double volume() const override;
      double surfaceArea() const override;
      // Returns a new bounding box by moving this one by the given vector.
      BoundingBox3 move(const Vector3& v) const;
      // Move this bounding box by a given vector.
      void moveSelf(const Vector3& v);
  };
}

#endif // _BOUNDING_BOX3_H_