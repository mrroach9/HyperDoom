#include "geometry/triangular_mesh.h"

// TODO: add all implementations.
namespace hd {
  TriangularMesh::TriangularMesh() {

  }

  TriangularMesh::TriangularMesh(std::vector<std::array<double, 3>> points,
      std::vector<std::array<unsigned int, 3>> faces) {

  }

  TriangularMesh::TriangularMesh(std::vector<Vector3> points,
      std::vector<std::array<unsigned int, 3>> faces) {

  }

  TriangularMesh::TriangularMesh(const TriangularMesh& mesh) {

  }

  TriangularMesh::~TriangularMesh() {

  }

  TriangularMesh::Vertex TriangularMesh::v(unsigned int index) const {
    return TriangularMesh::Vertex();
  }

  TriangularMesh::Face TriangularMesh::f(unsigned int index) const {
    return TriangularMesh::Face();
  }

  TriangularMesh::Edge TriangularMesh::e(unsigned int Edge) const {
    return TriangularMesh::Edge();
  }

  unsigned int TriangularMesh::getVertexNum() const {
    return 0;
  }

  unsigned int TriangularMesh::getEdgeNum() const {
    return 0;
  }

  unsigned int TriangularMesh::getFaceNum() const {
    return 0;
  }

  BoundingBox3 TriangularMesh::boundingBox3() const {
    return BoundingBox3();
  }

  void TriangularMesh::populate() {

  }
}