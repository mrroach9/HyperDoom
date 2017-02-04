#ifndef _TRIANGULAR_MESH_H_
#define _TRIANGULAR_MESH_H_

#pragma once

#include <vector>
#include "math/vector3.h"
#include "geometry/bounding_box3.h"
#include "geometry/has_surface_area.h"
#include "geometry/has_bounding_box3.h"

namespace hd {
  /**
   * Definitions and operations for a triangular mesh. The mesh is maintained as
   * a Doubly-Connected Edge List (DCEL):
   *
   * - Each vertex has its own position and (optionaly) a normal, with a list of
   * outgoing half-edges. 
   * - A face (triangle) contains pointers to its three vertices and three belonging
   * half-edges (going counter-clockwise), optionally a normal vector.
   * - A half-edge and its twin edge (coincide spatially but of opposite directions)
   * define a spatial edge. Each half-edge points from one vertex to another
   * (one-diretional), and belongs to exactly one face (while its twin edge belongs to
   * the adjacent face).
   *
   * For more details please read:
   *   Computational Geometry: Algorithms and Applications (second edition), Chapter 2.2
   *   M. de Berg, M. van Kreveld, M. Overmars, O. Schwarzkopf.
   */

  // TODO: add constructors and property methods for Vertex/Edge/Face.
  // TODO: add ser/des solutions.
  // TODO: implement all methods.
  // TODO: add Triangle3 class and getTriangle() method.
  // TODO: add normal interpolation enums, getters and normal getters.
  class TriangularMesh : public HasBoundingBox3 {
    /**
     * Definitions of vertices of DCEL.
     */
    class Vertex {
      public:
        // Position of the vertex.
        Vector3 pos;
        // Normal vector of the vertex. Might be zero if the parent mesh does not support
        // normal interpolation.
        Vector3 normal;
        // A list of indices of half-edges started from this vertex (outgoing).
        std::vector<unsigned int> edgeList;
    };

    /**
     * Definitions of half-edges of DCEL.
     */
    class Edge {
      public:
        // Indices of start and end vertices of this edge.
        unsigned int startVertex;
        unsigned int endVertex;
        // Index of triangle face this edge belongs to.
        unsigned int face;
        // Index of its twin edge. If its value is INVALID_ID, this edge has no twin edge
        // and thus on the boundary of a manifold.
        unsigned int twinEdge;
        // Index of the next edge, which belongs to the same face as this one, and starts
        // from the end vertex of this edge.
        unsigned int nextEdge;
    };

    /**
     * Definitions of triangular faces of DCEL.
     */
    class Face {
      public:
        // List of all vertices' indices of this triangle.
        std::array<unsigned int, 3> vertices;
        // List of all half-edges belonging to this triangle.
        // Note: edges in this array might not be sorted in counterclock-wise order. Please
        // rely on edge.nextEdge to traverse the face.
        std::array<unsigned int, 3> edges;
        Vector3 normal;
    };
    
    private:
      std::vector<Vertex> vertices;
      std::vector<Edge> edges;
      std::vector<Face> faces;
      BoundingBox3 boundingBox;
    
    public:
      TriangularMesh();
      TriangularMesh(std::vector<std::array<double, 3>> points,
          std::vector<std::array<unsigned int, 3>> faces);
      TriangularMesh(std::vector<Vector3> points,
          std::vector<std::array<unsigned int, 3>> faces);
      TriangularMesh(const TriangularMesh& mesh);
      ~TriangularMesh();
  
    public:
      // Get vertex/face/edge at given index. We intentioanlly made these method names
      // super short because they're heavily used in long chaining calls.
      Vertex v(unsigned int index) const;
      Face f(unsigned int index) const;
      Edge e(unsigned int Edge) const;

      // Get number of vertices/edges/faces.
      unsigned int getVertexNum() const;
      unsigned int getEdgeNum() const;
      unsigned int getFaceNum() const;

      // More properties and operations.
      BoundingBox3 boundingBox3() const;
  
    public:
      // Construct all data from row input (usually only vertex coordinates and faces).
      // This includes construction of edge list and refereces in face/vertex structure,
      // pre-calculation and interpolation of normals.
      void populate();
  };
}

#endif // _TRIANGULAR_MESH_H_
