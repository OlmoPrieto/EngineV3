#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <memory>
#include <string>
#include <vector>

#include "program.h"

class Shader;
class Program;

class Material {
public:
  Material(const std::string& _sName, const std::string& _sMaterialDefinitionPath);
  ~Material();

  std::string getName() const { return m_sName; }

private:
  Material();

  std::vector<std::weak_ptr<Shader>> m_vShaders;
  Program m_oProgram;
  std::string m_sName;
  std::string m_sMaterialDefinitionPath;
  static const float m_fVersion;
};

#endif  // __MATERIAL_H__
