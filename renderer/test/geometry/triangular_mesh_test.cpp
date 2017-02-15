#include "geometry/triangular_mesh.h"
#include "geometry/triangle3.h"
#include "geometry/bounding_box3.h"
#include "math/vector3.h"
#include "math/matrix3.h"
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
          TriangularMesh::FaceNormalMode::PHONG).build();

      plane1 = TriangularMesh::newBuilder(
          TriangularMesh::VertexNormalMode::USER_SPECIFIED,
          TriangularMesh::FaceNormalMode::FLAT).build();

      plane2 = TriangularMesh::newBuilder(
          TriangularMesh::VertexNormalMode::USER_SPECIFIED,
          TriangularMesh::FaceNormalMode::USER_SPECIFIED).build();
    }

    virtual void TearDown() {}
};

TEST_F(TriangularMeshTest, TestGeometryStructureAccess) {
  EXPECT_EQ(tetra1->vertexNum(), 4);
  EXPECT_EQ(tetra1->edgeNum(), 12);
  EXPECT_EQ(tetra1->faceNum(), 4);

  // Pick a random node, verify its position and degrees.
  unsigned int vertexId = 1;
  EXPECT_EQ(tetra1->v(vertexId).pos, Vector3(1.0, 0.0, 0.0));
  EXPECT_EQ(tetra1->v(vertexId).edges.size(), 3);

  // Pick a random edge starting that, and start traversing.
  unsigned int edgeIndex = 2;
  unsigned int eid = tetra1->v(vertexId).edges[edgeIndex];
  EXPECT_EQ(tetra1->e(eid).startVertex, vertexId);
  unsigned int endVertex = tetra1->e(eid).endVertex;

  // Verify twin edge.
  unsigned int twinEid = tetra1->e(eid).twinEdge;
  EXPECT_EQ(tetra1->e(twinEid).startVertex, endVertex);
  EXPECT_EQ(tetra1->e(twinEid).endVertex, vertexId);
  
  // Verify next and prev edges.
  unsigned int nextEid = tetra1->e(eid).nextEdge;
  unsigned int prevEid = tetra1->e(eid).prevEdge;
  EXPECT_EQ(tetra1->e(nextEid).startVertex, endVertex);
  EXPECT_EQ(tetra1->e(nextEid).endVertex, tetra1->e(prevEid).startVertex);
  EXPECT_EQ(tetra1->e(prevEid).endVertex, vertexId);
 
  // Verify face info.
  unsigned int fid = tetra1->e(eid).face;
  TriangularMesh::Face face = tetra1->f(fid);
  auto vertices = set<unsigned int>(face.vertices.cbegin(), face.vertices.cend());
  EXPECT_EQ(vertices,
      set<unsigned int>({vertexId, endVertex, tetra1->e(nextEid).endVertex}));
  auto edges = set<unsigned int>(face.edges.cbegin(), face.edges.cend());
  EXPECT_EQ(edges, set<unsigned int>({eid, nextEid, prevEid}));
}

TEST_F(TriangularMeshTest, TestGetTriangles) {

}

TEST_F(TriangularMeshTest, TestBoundingBox) {
}

TEST_F(TriangularMeshTest, TestNormalInterpolation) {

}
