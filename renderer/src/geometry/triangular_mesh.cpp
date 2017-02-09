#include "geometry/triangular_mesh.h"
#include <cassert>

namespace hd {
  TriangularMesh::TriangularMesh() {
    // TODO: Implement this.
  }

  TriangularMesh::TriangularMesh(const TriangularMesh& mesh) {
    // TODO: Implement this.
  }

  TriangularMesh::~TriangularMesh() {
    _vertices.clear();
    _edges.clear();
    _faces.clear();
  }

  TriangularMesh::Builder TriangularMesh::newBuilder(
      TriangularMesh::VertexNormalMode vertexNormalMode,
      TriangularMesh::FaceNormalMode faceNormalMode) {
    return TriangularMesh::Builder(vertexNormalMode, faceNormalMode);
  }

  TriangularMesh::Vertex TriangularMesh::v(unsigned int index) const {
    assert(index <  vertexNum());
    return _vertices[index];
  }

  TriangularMesh::Face TriangularMesh::f(unsigned int index) const {
    assert(index < faceNum());
    return _faces[index];
  }

  TriangularMesh::Edge TriangularMesh::e(unsigned int index) const {
    assert(index < edgeNum());
    return _edges[index];
  }

  unsigned int TriangularMesh::vertexNum() const {
    return _vertices.size();
  }

  unsigned int TriangularMesh::edgeNum() const {
    return _edges.size();
  }

  unsigned int TriangularMesh::faceNum() const {
    return _faces.size();
  }

  Triangle3 TriangularMesh::triangle(unsigned int index) const {
    // TODO: Implement this.
    return Triangle3();
  }

  Vector3 TriangularMesh::normal(const TriangularMesh::MeshPoint& p) const {
    // TODO: Implement this.
    return Vector3();
  }


  BoundingBox3 TriangularMesh::boundingBox3() const {
    assert(isPopulated());
    return _boundingBox;    
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
      TriangularMesh::VertexNormalMode vertexNormalMode,
      TriangularMesh::FaceNormalMode faceNormalMode) {
    _instance = std::unique_ptr<TriangularMesh>(new TriangularMesh());
    _instance->_vertexNormalMode = vertexNormalMode;
    _instance->_faceNormalMode = faceNormalMode;
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
    if (populate && !_instance->isPopulated()) {
      _instance->populate();
    }
    return _instance.release();
  }
}
