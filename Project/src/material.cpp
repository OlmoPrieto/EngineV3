#include "material.h"

#include <cassert>

#include "shader.h"

// MATERIAL

const float Material::m_fVersion = 0.0;

Material::Material() 
{
  
}

Material::Material(const std::string& _sName, const std::string& _sMaterialDefinitionPath)
  : m_sName(_sName)
  , m_sMaterialDefinitionPath(_sMaterialDefinitionPath)
{
  // Load definition
  // --

  
}

Material::~Material() 
{

}

MaterialInstance Material::CreateSpriteMaterial()
{
  Material oMaterial;
  oMaterial.m_sName = "Sprite";
  
  std::string sVertexSource = 
  ""
  ;

  std::string sFragmentSource =
  ""
  ;

  oMaterial.m_vctShaders.emplace_back(Shader::EType::Vertex, sVertexSource);
  oMaterial.m_vctShaders.emplace_back(Shader::EType::Fragment, sFragmentSource);

  oMaterial.m_oProgram.attachShader(&oMaterial.m_vctShaders[0]);
  oMaterial.m_oProgram.attachShader(&oMaterial.m_vctShaders[1]);

  // TODO: add Attributes

  MaterialInstance oMaterialInstance(std::make_shared<Material>(oMaterial));
  return oMaterialInstance;
}


// MATERIAL INSTANCE
MaterialInstance::MaterialInstance(std::shared_ptr<Material> _spMaterial)
  : m_spMaterial(_spMaterial)
{

}

MaterialInstance::~MaterialInstance()
{

}

bool MaterialInstance::checkReady()
{
  bool bReady = true;
  for (const Shader& oShader : m_spMaterial->m_vctShaders)
  {
    if (oShader.getIsReady() == false)
    {
      bReady = false;
      break;
    }
  }
  bReady |= m_spMaterial->m_oProgram.getIsReady();
  m_bReady = bReady;

  return m_bReady;
}