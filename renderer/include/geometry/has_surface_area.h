#ifndef _HAS_SURFACE_AREA_H_
#define _HAS_SURFACE_AREA_H_

#pragma once

namespace hd {
  /**
   * Interface for geometry shape that has surface area property.
   */
  class HasSurfaceArea {
    public:
      virtual double surfaceArea() const = 0;
      virtual ~HasSurfaceArea() = 0;
  };
}

#endif // _HAS_SURFACE_AREA_H_