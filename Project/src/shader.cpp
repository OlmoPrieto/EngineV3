#include "shader.h"

Shader::Shader() {

}

Shader::Shader(const std::string& sSource) {
  m_sCode = sSource;
}

Shader::~Shader() {
  
}

inline bool Shader::isReady() const {
  return m_bReady;
}