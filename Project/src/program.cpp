#include "program.h"

Program::Program() {

}

Program::~Program() {

}

void Program::attachShader(Shader* pShader) {
  m_vShaders.emplace_back(std::make_shared<Shader>(*pShader));
}