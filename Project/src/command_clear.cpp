#include "command_clear.h"

#include "opengl_implementation.h"

CommandClear::CommandClear(uint32_t _uClearTarget)
  : m_uClearTarget(_uClearTarget)
{

}

CommandClear::~CommandClear()
{

}

void CommandClear::execute()
{
  sm_oOpenGL.clear(m_uClearTarget);
}