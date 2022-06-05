#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "attribute.h"
#include "program.h"

class Shader;
class Program;
class MaterialInstance;

class Material {
public:

  Material(const std::string& _sName, const std::string& _sMaterialDefinitionPath);
  ~Material();

  // TODO: placeholder
  static std::shared_ptr<MaterialInstance> CreateSpriteMaterial();

  std::string getName() const { return m_sName; }
  const std::vector<Shader>& getShaders() const { return m_vctShaders; }
  std::vector<Shader>& getShaders() { return m_vctShaders; }
  Program& getProgram() { return m_oProgram; }

private:
  friend class MaterialInstance;

  Material();

  std::unordered_map<std::string, ValueType> m_dctAttributesTable;
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
  bool checkReady();

  std::vector<std::unique_ptr<Attribute>>& getAttributes() { return m_vctAttributes; }
  std::unique_ptr<Attribute>& getAttribute(const std::string& _sName);

  // void setAttributeValue(name, value);
  // any getAttributeValue(name);

private:
  friend class Material;

  std::vector<std::unique_ptr<Attribute>> m_vctAttributes;
  std::shared_ptr<Material> m_spMaterial;
  bool m_bReady = false;  // Will be true when the Shaders and the Programs are ready
  // std::vector<attributes the material has> m_vctAttributes;
  /* possible appereance of attributes:
  {
    Type  (enum class EAttributeType)
    Name  (std::string)
    Value (void*)
  }
  */
};