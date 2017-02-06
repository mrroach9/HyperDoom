#include "geometry/triangular_mesh.h"

namespace hd {
  TriangularMesh::TriangularMesh() {
    // TODO: Implement this.
  }

  TriangularMesh::TriangularMesh(const TriangularMesh& mesh) {
    // TODO: Implement this.
  }

  TriangularMesh::~TriangularMesh() {
    // TODO: Implement this.
  }

  TriangularMesh::Builder TriangularMesh::newBuilder(
      TriangularMesh::VertexNormalMode vertexNormalMode,
      TriangularMesh::FaceNormalMode faceNormalMode) {
    return TriangularMesh::Builder(vertexNormalMode, faceNormalMode);
  }

  TriangularMesh::Vertex TriangularMesh::v(unsigned int index) const {
    // TODO: Implement this.
    return TriangularMesh::Vertex();
  }

  TriangularMesh::Face TriangularMesh::f(unsigned int index) const {
    // TODO: Implement this.
    return TriangularMesh::Face();
  }

  TriangularMesh::Edge TriangularMesh::e(unsigned int Edge) const {
    // TODO: Implement this.
    return TriangularMesh::Edge();
  }

  unsigned int TriangularMesh::vertexNum() const {
    // TODO: Implement this.
    return 0;
  }

  unsigned int TriangularMesh::edgeNum() const {
    // TODO: Implement this.
    return 0;
  }

  unsigned int TriangularMesh::faceNum() const {
    // TODO: Implement this.
    return 0;
  }

  BoundingBox3 TriangularMesh::boundingBox3() const {
    // TODO: Implement this.
    return BoundingBox3();
  }

  void TriangularMesh::populate() {
    // TODO: Implement this.
  }

  bool TriangularMesh::isPopulated() const {
    return _isPopulated;
  }

  TriangularMesh::VertexNormalMode TriangularMesh::vertexNormalMode() const {
    return _vertexNormalMode;
  }

  TriangularMesh::FaceNormalMode TriangularMesh::faceNormalMode() const {
    return _faceNormalMode;
  }

  TriangularMesh::Builder::Builder(
      TriangularMesh::VertexNormalMode vertexNormalNode,
      TriangularMesh::FaceNormalMode faceNormalMode) {
    // TODO: Implement this.
  }

  TriangularMesh::Builder& TriangularMesh::Builder::addVertex(const Vector3& v) {
    // TODO: Implement this.
    return *this;
  }

  TriangularMesh::Builder& TriangularMesh::Builder::addVertex(
      const Vector3& v, const Vector3& vn) {
    // TODO: Implement this.
    return *this;
  }

  TriangularMesh::Builder& TriangularMesh::Builder::addFace(
      const std::array<unsigned int, 3>& face) {
    // TODO: Implement this.
    return *this;
  }

  TriangularMesh::Builder& TriangularMesh::Builder::addFace(
      const std::array<unsigned int, 3>& face, const Vector3& fn) {
    // TODO: Implement this.
    return *this;
  }

  TriangularMesh* TriangularMesh::Builder::build(bool populate) {
    // TODO: Implement this.
    return _instance.release();
  }
}
