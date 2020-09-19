#ifndef __MESH_H__
#define __MESH_H__

#include <vector>

class Mesh
{
public:
  Mesh(const std::string& _sPath);
  Mesh(const std::vector<uint32_t>& _vctVerticesPositions,
    const std::vector<uint32_t>& _vctVerticesNormals,
    const std::vector<uint32_t>& _vctVerticesUVs,
    const std::vector<uint32_t>& _vctVerticesIndices);
  ~Mesh();

private:
  Mesh();

  std::vector<uint32_t> m_vctVerticesPositions;
  std::vector<uint32_t> m_vctVerticesNormals;
  std::vector<uint32_t> m_vctVerticesUVs;
  std::vector<uint32_t> m_vctVerticesIndices;
  std::string m_sPath;
};

#endif // __MESH_H__