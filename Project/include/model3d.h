#ifndef __MODEL3D_H__
#define __MODEL3D_H__

#include <memory>
#include <vector>

#include "mesh.h"

class Model3D
{
public:
  ~Model3D();

  static std::shared_ptr<Model3D> CreateQuad();
  static std::shared_ptr<Model3D> CreateMesh(const std::string& _sPath);

private:
  Model3D();
  Model3D(const std::string& _sPath);

  std::vector<Mesh> m_vctMeshes;
};

#endif // __3DMODEL_H__