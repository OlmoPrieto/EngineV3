#include "program.h"

Program::Program() {

}

Program::~Program() {

}

inline bool Program::isReady() const {
  return m_bReady;
}

inline bool Program::isLinked() const {
  return m_bLinked;
}

void Program::attachShader(Shader* pShader) {
  m_vShaders.emplace_back(std::make_shared<Shader>(*pShader));
}