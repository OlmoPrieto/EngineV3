#include "command_prepare_mesh.h"

CommandPrepareMesh::CommandPrepareMesh(std::shared_ptr<Mesh> _spMesh)
  : m_spMesh(_spMesh)
{

}

CommandPrepareMesh::~CommandPrepareMesh()
{

}

void CommandPrepareMesh::execute()
{
  if (m_spMesh->getIsReady() == false)
  {
    sm_oOpenGL.setData(*m_spMesh.get());
    sm_oOpenGL.enableVertexAttributesPointers(*m_spMesh.get());
  }
}