#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "shader.h"

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

class Program {
public:
  Program();
  ~Program();

  bool getIsReady() const { return m_bReady; }
  bool getIsLinked() const { return m_bLinked; }
  void attachShader(Shader* pShader);

private:
  friend class OpenGLImplementation;

  // TODO: @olmo ->
  // implement support for retrieving the number of
  // uniforms the attached shaders have, their names 
  // and their location. Use a std::unordered_map
  // to relate uniforms names and locations

  std::unordered_map<std::string, uint32_t> m_mUniformsNamesPos;
  std::vector<std::string> m_vUniformsNames;
  std::vector<uint32_t> m_vUniformsLocations;
  std::vector<std::weak_ptr<Shader>> m_vShaders;
  int32_t m_iInternalId = -1;
  uint32_t m_uUniformsCount = 0;
  bool m_bReady = false;
  bool m_bLinked = false;
};

#endif  // __PROGRAM_H__
