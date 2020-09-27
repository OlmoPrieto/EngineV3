#include "command_prepare_material.h"

CommandPrepareMaterial::CommandPrepareMaterial(std::shared_ptr<MaterialInstance> _spMaterial)
  : m_spMaterial(_spMaterial)
{

}

CommandPrepareMaterial::~CommandPrepareMaterial()
{

}

void CommandPrepareMaterial::execute()
{
  const std::shared_ptr<Material>& spMaterial = m_spMaterial->getReferenceMaterial();
  std::vector<Shader>& vctShaders = spMaterial->getShaders();
  for (Shader& oShader : vctShaders)
  {
    if (oShader.getInternalId() < 0)
    {
      sm_oOpenGL.createShader(oShader, oShader.getType());
    }
    if (oShader.getIsReady() == false)
    {
      sm_oOpenGL.compileShader(oShader);
    }
  }
}