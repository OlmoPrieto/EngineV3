#include "opengl_implementation.h"

#ifdef __PLATFORM_MACOSX__
#include <OpenGL/gl3.h>
#elif __PLATFORM_LINUX__
#include <glew/include/GL/glew.h>
#elif __PLATFORM_WINDOWS__
#include <glew/include/GL/glew.h>
#elif __PLATFORM_ANDROID__
#include <GLES2/gl2.h>
#endif

#include <cassert>

OpenGLImplementation::OpenGLImplementation() {

}

OpenGLImplementation::~OpenGLImplementation() {

}

// [ SHADERS ] 
void OpenGLImplementation::createShader(Shader* pShader, Shader::EType eType) {
  assert(pShader->m_bReady == false && "OpenGLImplementation::createShader -> shader already created");

  GLenum eShaderType = GLU_INVALID_ENUM;
  switch (eType) {
    case Shader::EType::Vertex: {
      eShaderType = GL_VERTEX_SHADER;
      break;
    }
    case Shader::EType::Fragment: {
      eShaderType = GL_FRAGMENT_SHADER;
      break;
    }
    default: {
      assert(false && "OpenGLImplementation::createShader -> invalid shader type");
    }
  }

  pShader->m_uId = glCreateShader(eShaderType);
  glShaderSource(pShader->m_uId, 1, (const GLchar* const*)pShader->m_sCode.c_str(), nullptr);
}

void OpenGLImplementation::compileShader(Shader* pShader) {
  assert(pShader->m_bReady == true && "OpenGLImplementation::compileShader -> shader not ready");
  glCompileShader(pShader->m_uId);
  GLint bCompilingSuccess = 0;
  glGetShaderiv(pShader->m_uId, GL_COMPILE_STATUS, &bCompilingSuccess);
  if (!bCompilingSuccess) {
    printf("Failed to compile shader with id %d of type %d\n", pShader->m_uId, pShader->m_eType);
    GLint iLogSize = 0;
    glGetShaderiv(pShader->m_uId, GL_INFO_LOG_LENGTH, &iLogSize);
    char* pLog = (char*) malloc(iLogSize);
    GLint iRead = 0;
    glGetShaderInfoLog(pShader->m_uId, iLogSize, &iRead, pLog);
    printf("Compile error: %s\n", pLog);
    free(pLog);
  }
}
// [ \SHADERS ] 
// [ PROGRAMS ]
void OpenGLImplementation::createProgram(Program* pProgram) {
  assert(pProgram->m_bReady == false && "OpenGLImplementation::createProgram -> program already created");
  pProgram->m_uId = glCreateProgram();
}

void OpenGLImplementation::attachShader(Shader* pShader, Program* pProgram) {
  glAttachShader(pProgram->m_uId, pShader->m_uId);
}

void OpenGLImplementation::linkProgram(Program* pProgram) {
  glLinkProgram(pProgram->m_uId);
  // TODO: @olmo ->
  // check if the linking went OK
  pProgram->m_bLinked = true;
}

void OpenGLImplementation::getUniformsCount(Program* pProgram) {
  int32_t iCount = 0;
  glGetProgramiv(pProgram->m_uId, GL_ACTIVE_UNIFORMS, &iCount);
  assert(iCount >= 0 && "OpenGLImplementation::getUniformCount -> count less than 0\n");
  pProgram->m_uUniformsCount = (uint32_t)iCount;
}

void OpenGLImplementation::getUniformsNames(Program *pProgram) {
  const uint32_t uBufferSize = 256;
  char* pBuffer = (char*)malloc(uBufferSize); // 256 character max for the uniform name
  
  int32_t iLength = 0;
  int32_t iSize = 0;
  GLenum eType = GL_NONE;
  for (uint32_t i = 0; i < pProgram->m_uUniformsCount; ++i) {
    iLength = 0;
    iSize = 0;
    eType = GL_NONE;

    glGetActiveUniform(pProgram->m_uId, i, uBufferSize, &iLength, &iSize, &eType,
      pBuffer);
    
    // TODO: @oprietos -> check if there was an error
    pProgram->m_vUniformsNames.emplace_back(std::string(pBuffer));
    pProgram->m_vUniformsLocations.push_back(getUniformLocation(pProgram, std::string(pBuffer)));
  }
}

int32_t OpenGLImplementation::getUniformLocation(Program* pProgram, const std::string& sUniformName) {
  return glGetUniformLocation(pProgram->m_uId, sUniformName.c_str());
}
// [ \PROGRAMS ]