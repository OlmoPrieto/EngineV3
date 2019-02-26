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

  Shader(const std::string& sSource);
  ~Shader();

  inline bool isReady() const;

private:
  friend class OpenGLImplementation;

  Shader();

  std::string m_sCode;
  EType m_eType = EType::Invalid;
  uint32_t m_uId = 0;
  bool m_bReady = false;
};

#endif  // __SHADER_H__