#ifndef _TRIANGULAR_MESH_H_
#define _TRIANGULAR_MESH_H_

#pragma once

#include <memory>
#include <vector>
#include "math/vector3.h"
#include "geometry/bounding_box3.h"
#include "geometry/has_surface_area.h"
#include "geometry/has_bounding_box3.h"
#include "geometry/triangle3.h"

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
   *
   * DCELs require population and calculation of derived data upon creation. The constructors
   * are private and therefore, you must and you can only build a triangular mesh via
   * TriangularMesh::Builder (except for copy constructor).
   */

  // TODO: add constructors and property methods for Vertex/Edge/Face.
  // TODO: add ser/des solutions.
  // TODO: add Triangle3 class and getTriangle() method.
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

    /**
     * Definition of different modes of normal vector calculation on vertices.
     */
    enum class VertexNormalMode {
      // User specifies normal vector for each vertex.
      USER_SPECIFIED,
      // Normal of a vertex is calculated by averaging normals of all its adjacent faces.
      // If face normals are provided by users, we use the provided value. Otherwise
      // We use the flat normal (the unit normal vector orthoganal to the face).
      AVERAGED
    };

    /**
     * Definition of different modes of normal vector calculation on faces.
     */
    enum class FaceNormalMode {
      // User specifies normal vector for each face.
      USER_SPECIFIED,
      // Use the unit normal vector orthoganal to the face.
      FLAT,
      // Linearly interpolate normal vector from normals of all its vertices.
      // More specifically, if a point p on a triangle can be represented as
      //    p = a * v1 + b * v2 + c * v3,
      // where vi's are the coordinates of the three vertices of the face and a, b, c are
      // positive real numbers satisfying a + b + c = 1, then the normal of p, denoted as
      // N(p), is calculated as N(p) = a * N(v1) + b * N(v2) + c * N(v3).
      //
      // Note: if vertex mode is not USER_SPECIFIED, then we first need to calculate vertex
      // normal by averaging flat normals of faces, then use the averaged vertex normal
      // to do Phong interpolation.
      PHONG
    };

    /**
     * A descriptor for any point on the triangular mesh, represented by a face index and
     * parametric representation of the point. More specifically, if the face f is formed by
     * vertex v0, v1 and v2 (in this order), the representation of a point on this face,
     * (f, a, b, c) represents the point a * v0 + b * v1 + c * v2.
     * Note that 0 <= a, b, c <= 1 and a + b + c = 1 must be hold.
     * Also, users of this class should never care about the order and value of the parameters
     * as it's closely related to the representation of its belonging triangular mesh, whose
     * order of vertices in a face is also an internal data.
     */
    class MeshPoint {
      private:
        unsigned int faceId;
        Vector3 params;
      public:
        MeshPoint(unsigned int fid, const Vector3& p): faceId(fid), params(p) {}
        MeshPoint(const MeshPoint& p): faceId(p.faceId), params(p.params) {}
        ~MeshPoint() {}
    };

    private:
      std::vector<Vertex> _vertices;
      std::vector<Edge> _edges;
      std::vector<Face> _faces;
      BoundingBox3 _boundingBox;
      bool _isPopulated;
      VertexNormalMode _vertexNormalMode;
      FaceNormalMode _faceNormalMode;
    
    public:
      TriangularMesh(const TriangularMesh& mesh);
      ~TriangularMesh();
      class Builder;
      static Builder newBuilder(
          VertexNormalMode vertexNormalMode,
          FaceNormalMode faceNormalMode);
    private:
      friend class Builder;
      TriangularMesh();

    public:
      // Get vertex/face/edge at given index. We intentioanlly made these method names
      // super short because they're heavily used in long chaining calls.
      Vertex v(unsigned int index) const;
      Face f(unsigned int index) const;
      Edge e(unsigned int index) const;
      // Get a full descriptor for face at a given index.
      // Note: User specified or averaged face/vertex normals are not included in the 
      // returned shape descriptor. This return value assumes a triangle with natually defined
      // face normal.
      Triangle3 triangle(unsigned int index) const;
      // Calculate the interpolated normal vector for any point on the manifold.
      friend class MeshPoint;
      Vector3 normal(const MeshPoint& p) const;

      // Get number of vertices/edges/faces.
      unsigned int vertexNum() const;
      unsigned int edgeNum() const;
      unsigned int faceNum() const;

      // More properties and operations.
      BoundingBox3 boundingBox3() const;

      VertexNormalMode vertexNormalMode() const;
      FaceNormalMode faceNormalMode() const;
  
    public:
      // Construct all data from row input (usually only vertex coordinates and faces).
      // This includes construction of edge list and refereces in face/vertex structure,
      // pre-calculation and interpolation of normals.
      void populate();
      bool isPopulated() const;
    
    class Builder {
      private:
        std::unique_ptr<TriangularMesh> _instance;

      public:
        Builder(VertexNormalMode vertexNormalMode, FaceNormalMode faceNormalMode);

        // Add a vertex. For this method and the method below, the order of vertex insertion
        // determined vertex index (or ID). Please make sure you're inserting vertices as the
        // same order they appear in face list.
        Builder& addVertex(const Vector3& v);
        // Add vertex with normal. This method is only allowed when vertexNormalMode
        // is USER_SPECIFIED.
        Builder& addVertex(const Vector3& v, const Vector3& vn);
        // Add a triangular face with its three vertices' indices. The indices of vertices are
        // determined by the order you inserted them. The order of the three vertices of the
        // face is considered counter-clockwise, that is. if the list is {v1, v2, v3}, then
        // the right-hand rule applying from v1 to v2 to v3, determines the normal direction
        // of the face, or, the outside of the face.
        Builder& addFace(const std::array<unsigned int, 3>& face);
        // Add a face with normal. This method is only allowed when
        // faceNormalMode is USER_SPECIFIED.
        Builder& addFace(const std::array<unsigned int, 3>& face, const Vector3& fn);
      public:
        TriangularMesh* build(bool populate);
    };
  };
}

#endif // _TRIANGULAR_MESH_H_
