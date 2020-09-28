#include "command_draw.h"

CommandDraw::CommandDraw(std::shared_ptr<Mesh> _spMesh)
  : m_spMesh(_spMesh)
{

}

CommandDraw::~CommandDraw()
{

}

void CommandDraw::execute()
{
  sm_oOpenGL.draw(*m_spMesh);
}