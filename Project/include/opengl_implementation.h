#pragma once

#ifdef __PLATFORM_MACOSX__
#include <OpenGL/gl3.h>
#elif __PLATFORM_LINUX__
#include <glew/include/GL/glew.h>
#elif __PLATFORM_WINDOWS__
#include <glew/include/GL/glew.h>
#elif __PLATFORM_ANDROID__
#include <GLES2/gl2.h>
#endif

#include "attribute.h"
#include "mesh.h"
#include "program.h"
#include "shader.h"
#include "texture.h"
#include "utils.h"

class OpenGLImplementation {
public:
  // ----------------------------
  static void PrintGLError();
  // ----------------------------

  enum class EClearTarget
  {
    COLOR = GL_COLOR_BUFFER_BIT,
    DEPTH = GL_DEPTH_BUFFER_BIT
  };

private:
  friend class GPUCommand;
  friend class CommandPrepareMaterial;
  friend class CommandSetMaterial;
  friend class CommandDraw;
  friend class CommandClear;
  friend class CommandPrepareMesh;

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
  
  void setUniformValue(int32_t _uUniformLocation, ValueType _eValueType, const float* _pData);
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
  void enableVertexAttributesPointers(Mesh& _oMesh_);
  void disableVertexAttributesPointers(Mesh& _oMesh_);

  // Render
  void draw(const Mesh& _oMesh);
  void clear(uint32_t _uClearTarget);

  //
  void clearColor(const Color& _oColor);
};