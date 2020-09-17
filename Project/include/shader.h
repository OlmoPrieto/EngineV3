#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <cstdint>

class Shader {
public:
  enum class EType {
    Invalid = 0,
    Vertex,
    Fragment,
  };

  Shader(EType _eType, const std::string& _sSource);
  ~Shader();

  bool isReady() const { return m_bReady; }
  
  // TODO: make a method to instant compile the shader

private:
  friend class OpenGLImplementation;

  Shader();

  std::string m_sCode;
  EType m_eType = EType::Invalid;
  uint32_t m_uId = 0;
  bool m_bReady = false;
};

#endif  // __SHADER_H__