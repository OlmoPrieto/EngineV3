#ifndef __OPENGL_IMPLEMENTATION_H__
#define __OPENGL_IMPLEMENTATION_H__

#include "mesh.h"
#include "program.h"
#include "shader.h"

class OpenGLImplementation {
private:
  friend class GPUCommand;
  friend class CommandPrepareMaterial;
  friend class CommandSetMaterial;
  friend class CommandDraw;

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
  void setReady(Program& _oProgram_);
  void useProgram(const Program& _oProgram);

  // Buffers
  void setData(Mesh& _oMesh_);
  
  //
  void enableVertexAttributesPointers(Mesh& _oMesh_, const Program& _oProgram);
  void disableVertexAttributesPointers(Mesh& _oMesh_, const Program& _oProgram);

  // Render
  void draw(const Mesh& _oMesh);
};

#endif  // __OPENGL_IMPLEMENTATION_H__
