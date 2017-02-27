#include "geometry/triangular_mesh.h"
#include "geometry/triangle3.h"
#include "geometry/bounding_box3.h"
#include "math/vector3.h"
#include "math/matrix3.h"
#include "const.h"
#include <memory>
#include <set>
#include <gtest/gtest.h>

using namespace hd;
using namespace std;

class TriangularMeshTest : public ::testing::Test {
  protected:
    // A tetrahedral pyramid with top point at origin, and three base points
    // at (1, 0, 0), (0, 1, 0), (0, 0, 1). Using flat face normal and averaged
    // vertex normal.
    unique_ptr<TriangularMesh> tetra1;
    // The same tetrahedron as tetra1, but with averaged vertex normal and phong
    // interpolated face normal.
    unique_ptr<TriangularMesh> tetra2;
    // A plane made of 2 triangles. Using flat face normal and user specified
    // vertex normal.
    unique_ptr<TriangularMesh> plane1;
    // The same plane as plane2 but with user specified face and vertex normal.
    unique_ptr<TriangularMesh> plane2;
    
    virtual void SetUp() {
      tetra1 = TriangularMesh::newBuilder(
              TriangularMesh::VertexNormalMode::AVERAGED,
              TriangularMesh::FaceNormalMode::FLAT)
          .addVertex(Vector3(0, 0, 0))
          .addVertex(Vector3(1, 0, 0))
          .addVertex(Vector3(0, 1, 0))
          .addVertex(Vector3(0, 0, 1))
          .addFace({1, 0, 2})
          .addFace({1, 3, 0})
          .addFace({0, 3, 2})
          .addFace({1, 2, 3})
          .build();
      
      tetra2 = TriangularMesh::newBuilder(
              TriangularMesh::VertexNormalMode::AVERAGED,
              TriangularMesh::FaceNormalMode::PHONG)
          .addVertex(Vector3(0, 0, 0))
          .addVertex(Vector3(1, 0, 0))
          .addVertex(Vector3(0, 1, 0))
          .addVertex(Vector3(0, 0, 1))
          .addFace({1, 0, 2})
          .addFace({1, 3, 0})
          .addFace({0, 3, 2})
          .addFace({1, 2, 3})
          .build();

      //   0---1---2
      //   |  /|  /|
      //   | / | / |
      //   |/  |/  |
      //   3---4---5
      //   |  /|  /|
      //   | / | / |
      //   |/  |/  |
      //   6---7---8
      plane1 = TriangularMesh::newBuilder(
          TriangularMesh::VertexNormalMode::USER_SPECIFIED,
          TriangularMesh::FaceNormalMode::FLAT)
          .addVertex(Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addVertex(Vector3(1.0, 0.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addVertex(Vector3(2.0, 0.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addVertex(Vector3(0.0, 1.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addVertex(Vector3(1.0, 1.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addVertex(Vector3(2.0, 1.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addVertex(Vector3(0.0, 2.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addVertex(Vector3(1.0, 2.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addVertex(Vector3(2.0, 2.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addFace({0, 3, 1})
          .addFace({1, 4, 2})
          .addFace({1, 3, 4})
          .addFace({2, 4, 5})
          .addFace({3, 6, 4})
          .addFace({4, 7, 5})
          .addFace({4, 6, 7})
          .addFace({5, 7, 8})
          .build();

      plane2 = TriangularMesh::newBuilder(
          TriangularMesh::VertexNormalMode::USER_SPECIFIED,
          TriangularMesh::FaceNormalMode::USER_SPECIFIED)
          .addVertex(Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addVertex(Vector3(1.0, 0.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addVertex(Vector3(2.0, 0.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addVertex(Vector3(0.0, 1.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addVertex(Vector3(1.0, 1.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addVertex(Vector3(2.0, 1.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addVertex(Vector3(0.0, 2.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addVertex(Vector3(1.0, 2.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addVertex(Vector3(2.0, 2.0, 0.0), Vector3(0.0, 0.0, 1.0))
          .addFace({0, 3, 1}, Vector3(0.0, 0.0, 1.0))
          .addFace({1, 4, 2}, Vector3(0.0, 0.0, 1.0))
          .addFace({1, 3, 4}, Vector3(0.0, 0.0, 1.0))
          .addFace({2, 4, 5}, Vector3(0.0, 0.0, 1.0))
          .addFace({3, 6, 4}, Vector3(0.0, 0.0, 1.0))
          .addFace({4, 7, 5}, Vector3(0.0, 0.0, 1.0))
          .addFace({4, 6, 7}, Vector3(0.0, 0.0, 1.0))
          .addFace({5, 7, 8}, Vector3(0.0, 0.0, 1.0))
          .build();
    }

    virtual void TearDown() {}

    protected:
      // Attempt to traverse through vertices, edges and faces to verify the structure
      // of a given mesh, by specifying a vertex id to start with, and an edge index indicating
      // which edge to start with from the given vertex's outgoing edge list.
      void verifyTraversal(const unique_ptr<TriangularMesh>& mesh,
          unsigned int vertexId,
          const Vector3& expectedPos,
          unsigned int expectedDegree,
          unsigned int edgeIndexFromVertex,
          bool expectedHasTwinEdge) {
        // Pick the vertex and verify its position and degrees.
        EXPECT_EQ(mesh->v(vertexId).pos, expectedPos);
        EXPECT_EQ(mesh->v(vertexId).edges.size(), expectedDegree);

        // Pick the edge from selected vertex and start traversing.
        unsigned int eid = mesh->v(vertexId).edges[edgeIndexFromVertex];
        EXPECT_EQ(mesh->e(eid).startVertex, vertexId);
        unsigned int endVertex = mesh->e(eid).endVertex;

        // Verify twin edge and its start/end vertices being reverse of the original edge.
        unsigned int twinEid = mesh->e(eid).twinEdge;
        if (expectedHasTwinEdge) {
          EXPECT_EQ(mesh->e(twinEid).startVertex, endVertex);
          EXPECT_EQ(mesh->e(twinEid).endVertex, vertexId);
        } else {
          EXPECT_EQ(twinEid, HD_INVALID_ID);
        }
        
        // Verify next and prev edges.
        unsigned int nextEid = mesh->e(eid).nextEdge;
        unsigned int prevEid = mesh->e(eid).prevEdge;
        EXPECT_EQ(mesh->e(nextEid).startVertex, endVertex);
        EXPECT_EQ(mesh->e(nextEid).endVertex, mesh->e(prevEid).startVertex);
        EXPECT_EQ(mesh->e(prevEid).endVertex, vertexId);
      
        // Verify face info.
        unsigned int fid = mesh->e(eid).face;
        TriangularMesh::Face face = mesh->f(fid);
        // Verify the vertices of the face is exactly the same set of vertices traversed
        // previously with next and prev edges. Same for edges.
        auto vertices = set<unsigned int>(face.vertices.cbegin(), face.vertices.cend());
        EXPECT_EQ(vertices,
            set<unsigned int>({vertexId, endVertex, mesh->e(nextEid).endVertex}));
        auto edges = set<unsigned int>(face.edges.cbegin(), face.edges.cend());
        EXPECT_EQ(edges, set<unsigned int>({eid, nextEid, prevEid}));
      }
        
};

TEST_F(TriangularMeshTest, TestGeometryStructureTraversal_tetra1) {
  EXPECT_EQ(tetra1->vertexNum(), 4);
  EXPECT_EQ(tetra1->edgeNum(), 12);
  EXPECT_EQ(tetra1->faceNum(), 4);
  verifyTraversal(tetra1, 1, /* vertex id */
      Vector3(1.0, 0.0, 0.0), /* expected pos */
      3, /* expected degree */
      2, /* edge index from picked vertex */
      true /* should have a twin edge */);
}

TEST_F(TriangularMeshTest, TestGeometryStructureTraversal_plane1) {
  EXPECT_EQ(plane1->vertexNum(), 9);
  EXPECT_EQ(plane1->edgeNum(), 24);
  EXPECT_EQ(plane1->faceNum(), 8);
  verifyTraversal(plane1, 4, /* vertex id */
      Vector3(1.0, 1.0, 0.0), /* expected pos */
      6, /* expected degree */
      3, /* edge index from picked vertex */
      true /* should have a twin edge */);
  verifyTraversal(plane1, 8, /* vertex id */
      Vector3(2.0, 2.0, 0.0), /* expected pos */
      1, /* expected degree */
      0, /* edge index from picked vertex */
      false /* should not have a twin edge */);
}

TEST_F(TriangularMeshTest, TestGetTriangles) {
  Triangle3 tri1 = Triangle3(Vector3(1, 0, 0), Vector3(0, 0, 0), Vector3(0, 1, 0));
  EXPECT_EQ(tetra1->triangle(0), tri1);
  Triangle3 tri2 = Triangle3(Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1));
  EXPECT_EQ(tetra2->triangle(3), tri2);

  Triangle3 tri3 = Triangle3(Vector3(2, 0, 0), Vector3(1, 1, 0), Vector3(2, 1, 0));
  EXPECT_EQ(plane1->triangle(3), tri3);
  EXPECT_EQ(plane2->triangle(3), tri3);
}

TEST_F(TriangularMeshTest, TestBoundingBox) {
  BoundingBox3 box1 = BoundingBox3(Vector3(0, 0, 0), Vector3(1, 1, 1));
  EXPECT_EQ(tetra1->boundingBox3(), box1);
  EXPECT_EQ(tetra2->boundingBox3(), box1);

  BoundingBox3 box2 = BoundingBox3(Vector3(0, 0, 0), Vector3(2, 2, 0));
  EXPECT_EQ(plane1->boundingBox3(), box2);
  EXPECT_EQ(plane2->boundingBox3(), box2);
}

TEST_F(TriangularMeshTest, TestNormalInterpolation) {
  // p1 is the center of the equiliterral triangle face of the tetrahedon.
  TriangularMesh::MeshPoint p1 = TriangularMesh::MeshPoint(3, Vector3::one() / 3.0);
  // p2 is a point on the triangle of the tetrahedon lying on xOy plane. 
  TriangularMesh::MeshPoint p2 = TriangularMesh::MeshPoint(0, Vector3(0.6, 0.3, 0.1));

  EXPECT_EQ(tetra1->pos(p1), Vector3::one() / 3.0);
  EXPECT_EQ(tetra2->pos(p1), Vector3::one() / 3.0);
  EXPECT_EQ(tetra1->normal(p1), Vector3::one().normalize());
  EXPECT_EQ(tetra2->normal(p1), -1 * Vector3::one().normalize());

  EXPECT_EQ(tetra1->pos(p2), Vector3(0.6, 0.1, 0.0));
  EXPECT_EQ(tetra2->pos(p2), Vector3(0.6, 0.1, 0.0));
  EXPECT_EQ(tetra1->normal(p2), -1 * Vector3::zUnit());
  // Normal at p2 n = 0.6 * n1 + 0.3 * n0 + 0.1 * n2
  // n1 = (fn0 + fn1 + fn3).normalize()
  //    = ((0, 0, -1) + (0, -1, 0) + (1, 1, 1).normalize()).normalze()
  //    = (0.6947465906, -0.5085898027, -0.5085898027)
  // n2 = (fn0 + fn2 + fn3).normalize()
  //    = (-0.5085898027, 0.6947465906, -0.5085898027)
  // n0 = (fn0 + fn1 + fn2).normalize()
  //    = (-1, -1, -1).normalize()
  //    = (-0.5773502692, -0.5773502692, -0.5773502692)
  // n  = (0.19278389333, -0.40888430332, -0.52921794265).normalize
  //    = (0.2769861700, -0.5874728184, -0.7603646160)
  EXPECT_EQ(tetra2->normal(p2), Vector3(0.2769861700, -0.5874728184, -0.7603646160));
}
