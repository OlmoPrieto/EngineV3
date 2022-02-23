#include "model3d.h"

Model3D::Model3D()
{

}

Model3D::Model3D(const std::string& _sPath)
{

}

Model3D::~Model3D()
{

}

std::shared_ptr<Model3D> Model3D::CreateQuad()
{
  std::vector<float> vctPositions(
  {
    -1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
     1.0f, -1.0f, 0.0f
     
    /*-0.5f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f*/
  });
  std::vector<float> vctNormals(
  {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
  });
  std::vector<float> vctUVs(
  {
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f
  });
  std::vector<uint32_t> vctIndices(
  {
    0, 1, 2, 3, 2, 1
  });

  std::shared_ptr<Model3D> spModel = std::make_shared<Model3D>();
  spModel->m_vctMeshes.emplace_back(std::make_shared<Mesh>(vctPositions, vctNormals, vctUVs, vctIndices));

  return std::move(spModel);
}

std::shared_ptr<Model3D> Model3D::CreateMesh(const std::string & _sPath)
{
  return std::shared_ptr<Model3D>(new Model3D(_sPath));
}
