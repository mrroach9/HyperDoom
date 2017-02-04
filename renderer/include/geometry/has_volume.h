#ifndef _HAS_VOLUME_H_
#define _HAS_VOLUME_H_

#pragma once

namespace hd {
  /**
   * Interface for geometry shape that has volume property.
   */
  class HasVolume {
    public:
      virtual double volume() const = 0;
      virtual ~HasVolume() = 0 {}
  };
}

#endif // _HAS_VOLUME_H_