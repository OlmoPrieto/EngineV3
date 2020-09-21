#include "mesh.h"

Mesh::Mesh()
{

}

Mesh::Mesh(const std::vector<float>& _vctVerticesPositions,
  const std::vector<float>& _vctVerticesNormals,
  const std::vector<float>& _vctVerticesUVs,
  const std::vector<uint32_t>& _vctVerticesIndices)
  : m_vctVerticesPositions(_vctVerticesPositions)
  , m_vctVerticesNormals(_vctVerticesNormals)
  , m_vctVerticesUVs(_vctVerticesUVs)
  , m_vctVerticesIndices(_vctVerticesIndices)
{

}

Mesh::~Mesh()
{

}