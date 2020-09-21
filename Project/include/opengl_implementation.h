#ifndef __OPENGL_IMPLEMENTATION_H__
#define __OPENGL_IMPLEMENTATION_H__

#include "mesh.h"
#include "program.h"
#include "shader.h"

class OpenGLImplementation {
private:

  OpenGLImplementation();
  ~OpenGLImplementation();

  // Shaders
  void createShader(Shader& _oShader_, Shader::EType _eType);
  void compileShader(Shader& _oShader_);

  // Programs
  void createProgram(Program& _oProgram_);
  void attachShader(Shader& _oShader_, Program& _oProgram_);
  void linkProgram(Program& _oProgram_);
  void getUniformsCount(Program& oProgram_);
  void getUniformsNames(Program& _oProgram_);
  int32_t getUniformLocation(const Program& _oProgram, const std::string& _sUniformName);

  // Buffers
  void setData(Mesh& _oMesh_);
  

  // TODO:
  // enable vertex attributes array
};

#endif  // __OPENGL_IMPLEMENTATION_H__
