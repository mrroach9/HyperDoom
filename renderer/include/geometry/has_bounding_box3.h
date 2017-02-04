#ifndef _HAS_BOUNDING_BOX3_H_
#define _HAS_BOUNDING_BOX3_H_

#pragma once

#include "geometry/bounding_box3.h"

namespace hd {
  /**
   * Interface for geometry shape that has a 3-d bounding box.
   */
  class HasBoundingBox3 {
    public:
      virtual BoundingBox3 boundingBox3() const = 0;
      virtual ~HasBoundingBox3() {}
  };
}

#endif // _HAS_BOUNDING_BOX3_H_
