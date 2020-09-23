#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <memory>
#include <string>
#include <vector>

#include "program.h"

class Shader;
class Program;
class MaterialInstance;

class Material {
public:
  Material(const std::string& _sName, const std::string& _sMaterialDefinitionPath);
  ~Material();

  std::string getName() const { return m_sName; }

private:
  friend class MaterialInstance;

  Material();

  std::vector<std::weak_ptr<Shader>> m_vShaders;
  Program m_oProgram;
  std::string m_sName;
  std::string m_sMaterialDefinitionPath;
  static const float m_fVersion;

  // Attributes will be defined *here* by the asset file
  /* possible appereance of attributes:
  {
    Type  (enum class EAttributeType)
    Name  (std::string)
  }
  */
};

class MaterialInstance
{
public:
  MaterialInstance(std::shared_ptr<Material> _spMaterial);
  ~MaterialInstance();

  // void setAttributeValue(name, value);
  // any getAttributeValue(name);

private:
  std::shared_ptr<Material> m_spMaterial;
  // std::vector<attributes the material has> m_vctAttributes;
  /* possible appereance of attributes:
  {
    Type  (enum class EAttributeType)
    Name  (std::string)
    Value (void*)
  }
  */
};

#endif  // __MATERIAL_H__
