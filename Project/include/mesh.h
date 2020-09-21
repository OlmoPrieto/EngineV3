#ifndef __MESH_H__
#define __MESH_H__

#include <vector>

class Mesh
{
public:
  Mesh(const std::vector<float>& _vctVerticesPositions,
    const std::vector<float>& _vctVerticesNormals,
    const std::vector<float>& _vctVerticesUVs,
    const std::vector<uint32_t>& _vctVerticesIndices);
  ~Mesh();

  bool getIsReady() const { return m_bReady; }

private:
  friend class OpenGLImplementation;

  Mesh();

  std::vector<float> m_vctVerticesPositions;
  std::vector<float> m_vctVerticesNormals;
  std::vector<float> m_vctVerticesUVs;
  std::vector<uint32_t> m_vctVerticesIndices;
  std::string m_sPath;
  uint32_t m_uInternalId = 0;
  bool m_bReady = false;
};

#endif // __MESH_H__