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
void OpenGLImplementation::createShader(Shader& _oShader_, Shader::EType _eType) {
  assert(_oShader_.m_bReady == false && "OpenGLImplementation::createShader -> shader already created");

  GLenum eShaderType = GLU_INVALID_ENUM;
  switch (_eType) {
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

  _oShader_.m_uInternalId = glCreateShader(eShaderType);
  glShaderSource(_oShader_.m_uInternalId, 1, (const GLchar* const*)_oShader_.m_sCode.c_str(), nullptr);
}

void OpenGLImplementation::compileShader(Shader& _oShader_) {
  assert(_oShader_.m_bReady == true && "OpenGLImplementation::compileShader -> shader not ready");
  glCompileShader(_oShader_.m_uInternalId);
  GLint bCompilingSuccess = 0;
  glGetShaderiv(_oShader_.m_uInternalId, GL_COMPILE_STATUS, &bCompilingSuccess);
  if (!bCompilingSuccess) {
    printf("Failed to compile shader with id %d of type %d\n", _oShader_.m_uInternalId, _oShader_.m_eType);
    GLint iLogSize = 0;
    glGetShaderiv(_oShader_.m_uInternalId, GL_INFO_LOG_LENGTH, &iLogSize);
    char* pLog = (char*) malloc(iLogSize);
    GLint iRead = 0;
    glGetShaderInfoLog(_oShader_.m_uInternalId, iLogSize, &iRead, pLog);
    printf("Compile error: %s\n", pLog);
    free(pLog);
  }
}
// [ \SHADERS ] 

// [ PROGRAMS ]
void OpenGLImplementation::createProgram(Program& _oProgram_) {
  assert(_oProgram_.m_bReady == false && "OpenGLImplementation::createProgram -> program already created");
  _oProgram_.m_uInternalId = glCreateProgram();
}

void OpenGLImplementation::attachShader(Shader& _oShader_, Program& _oProgram_) {
  glAttachShader(_oProgram_.m_uInternalId, _oShader_.m_uInternalId);
}

void OpenGLImplementation::linkProgram(Program& _oProgram_) {
  glLinkProgram(_oProgram_.m_uInternalId);
  // TODO: @olmo ->
  // check if the linking went OK
  _oProgram_.m_bLinked = true;
}

void OpenGLImplementation::getUniformsCount(Program& _oProgram_) {
  int32_t iCount = 0;
  glGetProgramiv(_oProgram_.m_uInternalId, GL_ACTIVE_UNIFORMS, &iCount);
  assert(iCount >= 0 && "OpenGLImplementation::getUniformCount -> count less than 0\n");
  _oProgram_.m_uUniformsCount = (uint32_t)iCount;
}

void OpenGLImplementation::getUniformsNames(Program& _oProgram_) {
  const uint32_t uBufferSize = 256;
  char* pBuffer = (char*)malloc(uBufferSize); // 256 character max for the uniform name
  
  int32_t iLength = 0;
  int32_t iSize = 0;
  GLenum eType = GL_NONE;
  for (uint32_t i = 0; i < _oProgram_.m_uUniformsCount; ++i) {
    iLength = 0;
    iSize = 0;
    eType = GL_NONE;

    glGetActiveUniform(_oProgram_.m_uInternalId, i, uBufferSize, &iLength, &iSize, &eType,
      pBuffer);
    
    // TODO: @oprietos -> check if there was an error
    _oProgram_.m_vUniformsNames.emplace_back(std::string(pBuffer));
    _oProgram_.m_vUniformsLocations.push_back(getUniformLocation(_oProgram_, std::string(pBuffer)));
  }
}

int32_t OpenGLImplementation::getUniformLocation(const Program& _oProgram, const std::string& _sUniformName) {
  return glGetUniformLocation(_oProgram.m_uInternalId, _sUniformName.c_str());
}
// [ \PROGRAMS ]

// [ BUFFERS ]
void OpenGLImplementation::setData(Mesh& _oMesh_)
{
  if (_oMesh_.m_uInternalId < 0)
  {
    glGenBuffers(1, &_oMesh_.m_uInternalId);
  }

  if (_oMesh_.m_bReady == false)
  {
    // TODO: figure out VAOs
    glBindBuffer(GL_ARRAY_BUFFER, _oMesh_.m_uInternalId);

    uint32_t uPositionsSize = _oMesh_.m_vctVerticesPositions.size() * sizeof(float);
    uint32_t uNormalsSize = _oMesh_.m_vctVerticesNormals.size() * sizeof(float);
    uint32_t uUVsSize = _oMesh_.m_vctVerticesUVs.size() * sizeof(float);
    uint32_t uIndicesSize = _oMesh_.m_vctVerticesIndices.size() * sizeof(uint32_t);
    glBufferData(GL_ARRAY_BUFFER, // allocate the whole buffer size and upload positions
      uPositionsSize + uNormalsSize + uUVsSize + uIndicesSize,
      _oMesh_.m_vctVerticesPositions.data(),
      GL_STATIC_DRAW
    );

    // Then upload the rest of the vertex data
    glBufferSubData(GL_ARRAY_BUFFER,
      uPositionsSize,
      uNormalsSize,
      _oMesh_.m_vctVerticesNormals.data()
    );
    glBufferSubData(GL_ARRAY_BUFFER,
      uPositionsSize + uNormalsSize,
      uUVsSize,
      _oMesh_.m_vctVerticesUVs.data()
    );
    glBufferSubData(GL_ARRAY_BUFFER,
      uPositionsSize + uNormalsSize + uUVsSize,
      uIndicesSize,
      _oMesh_.m_vctVerticesIndices.data()
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  _oMesh_.m_bReady = true;
}
// [ \BUFFERS ]