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
// [ \PROGRAMS ]