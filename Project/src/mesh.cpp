#include "mesh.h"

Mesh::Mesh()
{

}

Mesh::Mesh(const std::string& _sPath)
  : m_sPath(_sPath)
{

}

Mesh::Mesh(const std::vector<uint32_t>& _vctVerticesPositions,
  const std::vector<uint32_t>& _vctVerticesNormals,
  const std::vector<uint32_t>& _vctVerticesUVs,
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