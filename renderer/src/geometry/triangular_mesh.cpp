#include "geometry/triangular_mesh.h"
#include <cassert>

namespace hd {
  TriangularMesh::TriangularMesh() {
    _vertices.clear();
    _edges.clear();
    _faces.clear();
    _isPopulated = false;
    _vertexNormalMode = TriangularMesh::VertexNormalMode::AVERAGED;
    _faceNormalMode = TriangularMesh::FaceNormalMode::FLAT;
  }

  TriangularMesh::TriangularMesh(const TriangularMesh& mesh) {
    _vertices.insert(_vertices.end(), mesh._vertices.begin(), mesh._vertices.end());
    _edges.insert(_edges.end(), mesh._edges.begin(), mesh._edges.end());
    _faces.insert(_faces.end(), mesh._faces.begin(), mesh._faces.end());
    _isPopulated = mesh._isPopulated;
    _boundingBox = mesh._boundingBox;
    _vertexNormalMode = mesh._vertexNormalMode;
    _faceNormalMode = mesh._faceNormalMode;
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
    assert(isPopulated());
    assert(index < faceNum());
    auto f = _faces[index];
    auto faceVertices = std::array<Vector3, 3>();
    for (int vInd = 0; vInd < 3; ++vInd) {
      faceVertices[vInd] = v(f.vertices[vInd]).pos;
    }
    return Triangle3(faceVertices);
  }

  Vector3 TriangularMesh::normal(const TriangularMesh::MeshPoint& p) const {
    assert(isPopulated());
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
    assert(_instance->vertexNormalMode() != TriangularMesh::VertexNormalMode::USER_SPECIFIED);
    assert(!_instance->isPopulated());
    _instance->_vertices.push_back(TriangularMesh::Vertex(v));
    return *this;
  }

  TriangularMesh::Builder& TriangularMesh::Builder::addVertex(
      const Vector3& v, const Vector3& vn) {
    assert(_instance->vertexNormalMode() == TriangularMesh::VertexNormalMode::USER_SPECIFIED);
    assert(!_instance->isPopulated());
    _instance->_vertices.push_back(TriangularMesh::Vertex(v, vn));
    return *this;
  }

  TriangularMesh::Builder& TriangularMesh::Builder::addFace(
      const std::array<unsigned int, 3>& face) {
    assert(_instance->faceNormalMode() != TriangularMesh::FaceNormalMode::USER_SPECIFIED);
    assert(!_instance->isPopulated());
    _instance->_faces.push_back(TriangularMesh::Face(face));
    return *this;
  }

  TriangularMesh::Builder& TriangularMesh::Builder::addFace(
      const std::array<unsigned int, 3>& face, const Vector3& fn) {
    assert(_instance->faceNormalMode() == TriangularMesh::FaceNormalMode::USER_SPECIFIED);
    assert(!_instance->isPopulated());
    _instance->_faces.push_back(TriangularMesh::Face(face, fn));
    return *this;
  }

  TriangularMesh* TriangularMesh::Builder::build(bool populate) {
    if (populate && !_instance->isPopulated()) {
      _instance->populate();
    }
    return _instance.release();
  }
}
