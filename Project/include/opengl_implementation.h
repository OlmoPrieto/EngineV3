#pragma once

#include "attribute.h"
#include "mesh.h"
#include "program.h"
#include "shader.h"
#include "texture.h"
#include "utils.h"

class OpenGLImplementation {
private:
  friend class GPUCommand;
  friend class CommandPrepareMaterial;
  friend class CommandSetMaterial;
  friend class CommandDraw;
  friend class CommandClear;

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
  
  void setUniformValue(int32_t _uUniformLocation, ValueType _eValueType, float* _pData);
  void setUniformValue(int32_t _uUniformLocation, ValueType _eValueType, uint32_t* _pData);
  void setUniformValue(int32_t _uUniformLocation, ValueType _eValueType, int32_t* _pData);

  int32_t getUniformLocation(const Program& _oProgram, const char* _sName);
  int32_t getUniformCount(const Program& _oProgram);

  int32_t getProgramInUse();

  // Textures
  void uploadTexture(Texture& _oTexture_);
  void setActive(const Texture& _oTexture);

  // Buffers
  void setData(Mesh& _oMesh_);
  
  //
  void enableVertexAttributesPointers(Mesh& _oMesh_, const Program& _oProgram);
  void disableVertexAttributesPointers(Mesh& _oMesh_, const Program& _oProgram);

  // Render
  void draw(const Mesh& _oMesh);

  //
  void clearColor(const Color& _oColor);
};