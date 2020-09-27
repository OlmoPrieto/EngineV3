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
  //typedef std::vector<std::weak_ptr<Shader>> TShaderRefs;

  Material(const std::string& _sName, const std::string& _sMaterialDefinitionPath);
  ~Material();

  std::string getName() const { return m_sName; }
  const std::vector<Shader>& getShaders() const { return m_vctShaders; }
  std::vector<Shader>& getShaders() { return m_vctShaders; }
  const Program& getProgram() const { return m_oProgram; }

private:
  friend class MaterialInstance;

  Material();

  std::vector<Shader> m_vctShaders;
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

  const std::shared_ptr<Material>& getReferenceMaterial() const { return m_spMaterial; }

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
