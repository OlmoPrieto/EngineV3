#include "Engine/shader.h"

Shader::Shader()
{

}

Shader::Shader(EType _eType, const std::string& _sSource)
  : m_eType(_eType)
  , m_sCode(_sSource)
{

}

Shader::~Shader()
{

}