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
  // TODO: when everything is working, put an if (m_spMaterial->isReady() == false)
  // anything that modifies a Material (changing a Shader, Program...) should set
  // everything to not ready

  if (m_spMaterial->checkReady() == false)
  {
    const std::shared_ptr<Material>& spMaterial = m_spMaterial->getReferenceMaterial();
  
    Program& oProgram = spMaterial->getProgram();
    if (oProgram.getInternalId() < 0)
    {
      sm_oOpenGL.createProgram(oProgram);
    }
  
    uint32_t uAttachedShaders = 0;
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
      if (oProgram.getIsReady() == false && oProgram.getIsLinked() == false)
      {
        sm_oOpenGL.attachShader(oShader, oProgram);
        ++uAttachedShaders;
      }
    }

    if (uAttachedShaders == vctShaders.size() && oProgram.getIsLinked() == false)
    {
      sm_oOpenGL.linkProgram(oProgram);

      // Maybe retrieve uniforms locations here?

      sm_oOpenGL.setReady(oProgram);
    }

    m_spMaterial->checkReady();
  }
}