#include "Engine/opengl_implementation.h"

#include <cassert>

// ---------------------------------------------------------
void OpenGLImplementation::PrintGLError()
{
  GLenum err = glGetError();
  while (err != GL_NO_ERROR)
  {
    if (err == GL_INVALID_OPERATION)
      printf("Invalid operation\n");
    else if (err == GL_INVALID_ENUM)
      printf("Invalid enum\n");
    else if (err == GL_INVALID_VALUE)
      printf("Invalid value\n");

    err = glGetError();
  }
}
// ---------------------------------------------------------

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

  _oShader_.m_iInternalId = glCreateShader(eShaderType);

  const GLchar* pSource = _oShader_.m_sCode.c_str();
  int32_t iSourceLength = (int32_t)_oShader_.m_sCode.length();
  glShaderSource(_oShader_.m_iInternalId, 1, &pSource, &iSourceLength);
}

void OpenGLImplementation::compileShader(Shader& _oShader_) {
  assert(_oShader_.m_iInternalId > -1 && "OpenGLImplementation::compileShader -> shader not created");
  glCompileShader(_oShader_.m_iInternalId);
  GLint bCompilingSuccess = 0;
  glGetShaderiv(_oShader_.m_iInternalId, GL_COMPILE_STATUS, &bCompilingSuccess);
  if (!bCompilingSuccess) {
    printf("\n");
    printf("Failed to compile shader with id %d of type %d\n", _oShader_.m_iInternalId, _oShader_.m_eType);
    GLint iLogSize = 0;
    glGetShaderiv(_oShader_.m_iInternalId, GL_INFO_LOG_LENGTH, &iLogSize);
    char* pLog = (char*) malloc(iLogSize);
    GLint iRead = 0;
    glGetShaderInfoLog(_oShader_.m_iInternalId, iLogSize, &iRead, pLog);
    printf("Compile error: %s\n", pLog);
    free(pLog);
  }
  else
  {
    printf("Successfuly compiled shader %d of type %d\n", _oShader_.m_iInternalId, _oShader_.m_eType);
    _oShader_.m_bReady = true;
  }
}
// [ \SHADERS ] 

// [ PROGRAMS ]
void OpenGLImplementation::createProgram(Program& _oProgram_) {
  assert(_oProgram_.m_bReady == false && "OpenGLImplementation::createProgram -> program already created");
  _oProgram_.m_iInternalId = glCreateProgram();
}

void OpenGLImplementation::attachShader(Shader& _oShader_, Program& _oProgram_) {
  glAttachShader(_oProgram_.m_iInternalId, _oShader_.m_iInternalId);
}

void OpenGLImplementation::linkProgram(Program& _oProgram_) {
  glLinkProgram(_oProgram_.m_iInternalId);
  // TODO: @olmo ->
  // check if the linking went OK
  _oProgram_.m_bLinked = true;
}

void OpenGLImplementation::getUniformsCount(Program& _oProgram_) {
  int32_t iCount = 0;
  glGetProgramiv(_oProgram_.m_iInternalId, GL_ACTIVE_UNIFORMS, &iCount);
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

    glGetActiveUniform(_oProgram_.m_iInternalId, i, uBufferSize, &iLength, &iSize, &eType,
      pBuffer);
    
    // TODO: @oprietos -> check if there was an error
    _oProgram_.m_vUniformsNames.emplace_back(std::string(pBuffer));
    _oProgram_.m_vUniformsLocations.push_back(getUniformLocation(_oProgram_, std::string(pBuffer)));
  }
}

int32_t OpenGLImplementation::getUniformLocation(const Program& _oProgram, const std::string& _sUniformName) {
  return glGetUniformLocation(_oProgram.m_iInternalId, _sUniformName.c_str());
}

void OpenGLImplementation::setReady(Program& _oProgram_)
{
  _oProgram_.m_bReady = true;
}

void OpenGLImplementation::useProgram(const Program& _oProgram)
{
  glUseProgram(_oProgram.getInternalId());
}

void OpenGLImplementation::setUniformValue(int32_t _uUniformLocation, ValueType _eValueType, const float* _pData)
{
  switch (_eValueType)
  {
    case ValueType::Float1:
    {
      glUniform1fv(_uUniformLocation, 1, (const GLfloat*)_pData);
      break;
    }
    case ValueType::Float2:
    {
      glUniform2fv(_uUniformLocation, 1, (const GLfloat*)_pData);
      break;
    }
    case ValueType::Float3:
    {
      glUniform3fv(_uUniformLocation, 1, (const GLfloat*)_pData);
      break;
    }
    case ValueType::Float4:
    {
      glUniform4fv(_uUniformLocation, 1, (const GLfloat*)_pData);
      break;
    }

    case ValueType::Mat2:
    {
      glUniformMatrix2fv(_uUniformLocation, 1, false, (const GLfloat*)_pData);
      break;
    }
    case ValueType::Mat3:
    {
      glUniformMatrix3fv(_uUniformLocation, 1, false, (const GLfloat*)_pData);
      break;
    }
    case ValueType::Mat4:
    {
      glUniformMatrix4fv(_uUniformLocation, 1, false, (const GLfloat*)_pData);
      break;
    }
    default:
    {
      break;
    }
  }
}
void OpenGLImplementation::setUniformValue(int32_t _uUniformLocation, ValueType _eValueType, uint32_t* _pData)
{
  switch (_eValueType)
  {
    case ValueType::Uint1:
    {
      glUniform1uiv(_uUniformLocation, 1, _pData);
      break;
    }
    case ValueType::Uint2:
    {
      glUniform2uiv(_uUniformLocation, 1, _pData);
      break;
    }
    case ValueType::Uint3:
    {
      glUniform3uiv(_uUniformLocation, 1, _pData);
      break;
    }
    case ValueType::Uint4:
    {
      glUniform4uiv(_uUniformLocation, 1, _pData);
      break;
    }
    default:
    {
      break;
    }
  }
}
void OpenGLImplementation::setUniformValue(int32_t _uUniformLocation, ValueType _eValueType, int32_t* _pData)
{
  switch (_eValueType)
  {
    case ValueType::Texture:
    case ValueType::Int1:
    {
      glUniform1iv(_uUniformLocation, 1, _pData);
      break;
    }
    case ValueType::Int2:
    {
      glUniform2iv(_uUniformLocation, 1, _pData);
      break;
    }
    case ValueType::Int3:
    {
      glUniform3iv(_uUniformLocation, 1, _pData);
      break;
    }
    case ValueType::Int4:
    {
      glUniform4iv(_uUniformLocation, 1, _pData);
      break;
    }
    default:
    {
      break;
    }
  }
}

int32_t OpenGLImplementation::getUniformLocation(const Program & _oProgram, const char * _sName)
{
  return glGetUniformLocation(_oProgram.getInternalId(), _sName);
}

int32_t OpenGLImplementation::getUniformCount(const Program & _oProgram)
{
  int32_t iCount = -1;
  glGetProgramiv(_oProgram.getInternalId(), GL_ACTIVE_UNIFORMS, &iCount);

  return iCount;
}

int32_t OpenGLImplementation::getProgramInUse()
{
  int32_t iProgramIndex = -1;
  glGetIntegeri_v(GL_CURRENT_PROGRAM, 1, &iProgramIndex);
  return iProgramIndex;
}
// [ \PROGRAMS ]

// [ TEXTURES ]
void OpenGLImplementation::uploadTexture(Texture& _oTexture_)
{
  uint32_t uId = 0;
  glGenTextures(1, &uId);
  assert(uId != GL_INVALID_VALUE && "Failed to create 1 texture");
  _oTexture_.m_iInternalId = (int32_t)uId;
  
  // TODO: switch for texture type
  assert(_oTexture_.m_eType == Texture::Type::Texture2D);
  glBindTexture(GL_TEXTURE_2D, uId);

  // TODO: switch for wraps
  assert(_oTexture_.m_eWrapS == Texture::Wrap::Repeat);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  assert(_oTexture_.m_eWrapT == Texture::Wrap::Repeat);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // TODO: switch for filters
  assert(_oTexture_.m_eMinFilter == Texture::Filter::Linear);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  assert(_oTexture_.m_eMagFilter == Texture::Filter::Linear);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // TODO: *
  GLenum eInternalFormat = GL_INVALID_ENUM;
  GLenum eFormat = GL_INVALID_ENUM;
  GLenum ePixelType = GL_INVALID_ENUM;
  switch (_oTexture_.getFormat())
  {
    case Texture::Format::RGB:
    {
      eInternalFormat = GL_RGB;
      eFormat = GL_RGB;
      ePixelType = GL_UNSIGNED_BYTE;
      
      break;
    }
    case Texture::Format::RGBA:
    {
      eInternalFormat = GL_RGBA;
      eFormat = GL_RGBA;
      ePixelType = GL_UNSIGNED_BYTE;

      break;
    }
    case Texture::Format::Depth:
    {
      eInternalFormat = GL_DEPTH_COMPONENT;
      eFormat = GL_DEPTH_COMPONENT;
      ePixelType = GL_FLOAT;

      break;
    }
    default:
    {
      assert(false && "Texture format not suported by OpenGL backend");
      break;
    }
  }

  glTexImage2D(GL_TEXTURE_2D, 0, eInternalFormat, _oTexture_.getWidth(), _oTexture_.getHeight(),
    0, eFormat, ePixelType, _oTexture_.getData());

  if (_oTexture_.getGenerateMipMaps())
    glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);

  _oTexture_.m_bReady = true;
}

void OpenGLImplementation::setActive(const Texture& _oTexture)
{
  int32_t iId = _oTexture.getInternalId();
  assert((iId > -1 && _oTexture.getIsReady() == true) && "Invalid texture");

  glActiveTexture(GL_TEXTURE0 + _oTexture.getTextureUnit());

  switch (_oTexture.getType())
  {
    case Texture::Type::Texture2D:
    {
      glBindTexture(GL_TEXTURE_2D, (uint32_t)iId);
      break;
    }
    case Texture::Type::Cubemap:
    {
      glBindTexture(GL_TEXTURE_CUBE_MAP, (uint32_t)iId);
      break;
    }
    default:
    {
      assert(false && "Texture format not yet supported");
      break;
    }
  }
}
// [ \TEXTURES ]

// [ BUFFERS ]
void OpenGLImplementation::setData(Mesh& _oMesh_)
{
  if (_oMesh_.m_iInternalId < 0)
  {
    glGenBuffers(1, (uint32_t*)&_oMesh_.m_iInternalId);
  }

  if (_oMesh_.m_bReady == false)
  {
    // TODO: figure out VAOs
    glBindBuffer(GL_ARRAY_BUFFER, _oMesh_.m_iInternalId);

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

// 
void OpenGLImplementation::enableVertexAttributesPointers(Mesh& _oMesh_)
{
  glBindBuffer(GL_ARRAY_BUFFER, _oMesh_.m_iInternalId);

  if (_oMesh_.getVerticesPositions().size() > 0)
  {
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    _oMesh_.m_bPositionsEnabled = true;
  }
  if (_oMesh_.getVerticesNormals().size() > 0)
  {
    glEnableVertexAttribArray(1);
    uint32_t uOffset = 0;
    if (_oMesh_.m_bPositionsEnabled == true)
    {
      uOffset += _oMesh_.getVerticesPositions().size() * sizeof(float);
    }
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)uOffset);
    _oMesh_.m_bNormalsEnabled = true;
  }
  if (_oMesh_.getVerticesUVs().size() > 0)
  {
    glEnableVertexAttribArray(2);
    uint32_t uOffset = 0;
    if (_oMesh_.m_bPositionsEnabled == true)
    {
      uOffset += _oMesh_.getVerticesPositions().size() * sizeof(float);
    }
    if (_oMesh_.m_bNormalsEnabled == true)
    {
      uOffset += _oMesh_.getVerticesNormals().size() * sizeof(float);
    }
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)uOffset);
    _oMesh_.m_bUVsEnabled = true;
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLImplementation::disableVertexAttributesPointers(Mesh& _oMesh_)
{
  glBindBuffer(GL_ARRAY_BUFFER, _oMesh_.m_iInternalId);

  if (_oMesh_.m_bPositionsEnabled == true)
  {
    glDisableVertexAttribArray(0);
    _oMesh_.m_bPositionsEnabled = false;
  }
  if (_oMesh_.m_bNormalsEnabled == true)
  {
    glDisableVertexAttribArray(1);
    _oMesh_.m_bNormalsEnabled = false;
  }
  if (_oMesh_.m_bUVsEnabled == true)
  {
    glDisableVertexAttribArray(2);
    _oMesh_.m_bUVsEnabled = false;
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
//

// [ RENDER ]
void OpenGLImplementation::draw(const Mesh& _oMesh)
{
  glBindBuffer(GL_ARRAY_BUFFER, _oMesh.m_iInternalId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _oMesh.m_iInternalId);

  glDrawElements(GL_TRIANGLES, _oMesh.getVerticesIndices().size(), GL_UNSIGNED_INT, 
  (void*)((_oMesh.getVerticesPositions().size() + _oMesh.getVerticesNormals().size() + _oMesh.getVerticesUVs().size()) * sizeof(float))); // TODO: have a function to calculate/return the offset for the indices. Whenever data changes in the mesh, this value must be recalculated

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLImplementation::clear(uint32_t _uClearTarget)
{
  glClear(_uClearTarget);
}

// [ \RENDER ]

// [ CLEAR COLOR ]
void OpenGLImplementation::clearColor(const Color & _oColor)
{
  glClearColor(_oColor.r / 255, _oColor.g / 255, _oColor.b / 255, _oColor.a / 255);
}
// [ \CLEAR COLOR]