#ifndef __OPENGL_IMPLEMENTATION_H__
#define __OPENGL_IMPLEMENTATION_H__

#include "program.h"
#include "shader.h"

class OpenGLImplementation {
private:

  OpenGLImplementation();
  ~OpenGLImplementation();

  // Shaders
  void createShader(Shader* pShader, Shader::EType eType);
  void compileShader(Shader* pShader);

  // Programs
  void createProgram(Program* pProgram);
  void attachShader(Shader* pShader, Program* pProgram);
  void linkProgram(Program* pProgram);
  void getUniformsCount(Program* pProgram);
  void getUniformsNames(Program* pProgram);
  int32_t getUniformLocation(Program* pProgram, const std::string& sUniformName);
};

#endif  // __OPENGL_IMPLEMENTATION_H__
