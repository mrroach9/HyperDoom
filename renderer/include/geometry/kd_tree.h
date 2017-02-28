#ifndef _KD_TREE_H_
#define _KD_TREE_H_

#include <vector>
#include <memory>
#include "geometry/has_bounding_box3.h"
#include "geometry/triangle3.h"
#include "geometry/bounding_box3.h"

namespace hd {
  /**
   * Data structure for K-d tree, which can provide fast lookup of geometry entities with given
   * range in 3d space.
   *
   * K-d tree is essentially a binary search tree with each non-leaf node representing a bounding
   * box in 3d space, with its two children a subdivision of the bounding box, usually along the
   * longest dimension. Each leaf nodes stores a list of actuall geometry entities that,
   * under certain partition rules, belong to their parent bounding box (e.g. partition by gravity
   * center coordinates).
   *
   * Depth of the K-d tree is limited by different criteria, either stopping at a fixed max level
   * or stop smartly when containing set is small. This is to avoid the depth of the tree becoming
   * too deep, a waste of both time and space.
   *
   * We restrict our K-d tree to a render-time read-only data strcuture, built from fixed scene
   * and models. Therefore the tree can only be constructed from raw list of entities, rather than
   * exposing incremental insert and delete methods.
   *
   * Multiple partitioning methods can be used to heuristically improve the query-time performance,
   * a few of which will be supported: partitioning by median, or by SAH (Surface Area Heuristic).
   * For more details, please refer to:
   *     Physically Based Rendering, Third Edition. Matt Pharr, Wenzel Jakob, Greg Humphreys. 
   */
  class KdTree {
    class PartitionPlane {
      public:
        // Represents the type of plane we're using to split the bounding box.
        // 0 -- x, 1 -- y, 2 -- z.
        unsigned int planeType;
        // E.g. if planeType = 0 and value = 1.0, it means the plane is x = 1.0.
        double value;
      public:
        PartitionPlane(): planeType(0), value(0.0) {}
        PartitionPlane(unsigned int planeTypeArg, double valueArg)
            : planeType(planeTypeArg), value(valueArg) {}
    };

    /**
     * Data structure for a single tree node. Stores pointers to left and right children if not
     * leaf, or a list of entities stored at leaf node.
     * If not a leaf node, partition plane is also defined to describe the subdivision between
     * left and right children.
     */
    class Node : public HasBoundingBox3 {
      public:
        BoundingBox3 boundingBox;
        bool isLeaf;
        std::vector<Triangle3> entities;
        PartitionPlane partitionPlane;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
      public:
        Node() {}
        ~Node() {}
    };

    /**
     * Modes for how a list of geometry entities are partitioned into two lists.
     */
    enum PartitionMode {
      // Sorting all entities by their gravity centers along the longest axis, then
      // divide them into two equal halves (or differ at most 1) along that axis.
      CENTER_MEDIAN,
      // Surface Area Heuristics, a smart way of partitioning list of entities to 
      // minimize the probablity of rays intersecting with both halves.
      SAH
    };

    /**
     * Modes to limit tree depths.
     */
    enum DepthLimitMode {
      // Set a max level constraint to the tree respect to total number of nodes n.
      // An experience value of d = 8 + 1.3 * log(N) is proven to be effective.
      MAX_LEVEL,
      // Stop partitioning when number of entities enclosed is less than a fixed value.
      MIN_ENTITIES
    };
  };
}

#endif //_KD_TREE_H_
