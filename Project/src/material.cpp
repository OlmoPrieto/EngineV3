#include "material.h"

#include "shader.h"

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