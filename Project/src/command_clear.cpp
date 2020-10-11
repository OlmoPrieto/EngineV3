#include "command_clear.h"

#include "opengl_implementation.h"

CommandClear::CommandClear(const Color& _oColor)
  : m_oColor(_oColor)
{

}

CommandClear::~CommandClear()
{

}

void CommandClear::execute()
{
  sm_oOpenGL.clearColor(m_oColor);
}