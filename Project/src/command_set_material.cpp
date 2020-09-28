#include "command_set_material.h"

CommandSetMaterial::CommandSetMaterial(std::shared_ptr<MaterialInstance> _spMaterial)
  : m_spMaterial(_spMaterial)
{

}

CommandSetMaterial::~CommandSetMaterial()
{

}

void CommandSetMaterial::execute()
{
  const std::shared_ptr<Material>& spMaterial = m_spMaterial->getReferenceMaterial();

  if (m_spMaterial->checkReady() == true)
  {
    Program& oProgram = spMaterial->getProgram();
    sm_oOpenGL.useProgram(oProgram);
  }
  /*
  else
  {
    // swap if else order
    Create a CommandPrepareMaterial(m_spMaterial);
  }
  */
}