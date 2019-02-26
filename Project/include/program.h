#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "shader.h"

#include <cstdint>
#include <memory>
#include <vector>

class Program {
public:
  Program();
  ~Program();

  inline bool isReady() const;
  inline bool isLinked() const;
  void attachShader(Shader* pShader);

private:
  friend class OpenGLImplementation;

  // TODO: @olmo ->
  // implement support for retrieving the number of
  // uniforms the attached shaders have, their names 
  // and their location. Use a std::unordered_map
  // to relate uniforms names and locations

  std::vector<std::weak_ptr<Shader>> m_vShaders;
  uint32_t m_uId = 0;
  bool m_bReady = false;
  bool m_bLinked = false;
};

#endif  // __PROGRAM_H__
