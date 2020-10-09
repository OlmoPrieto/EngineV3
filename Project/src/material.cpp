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

std::shared_ptr<MaterialInstance> Material::CreateSpriteMaterial()
{
  Material oMaterial;
  oMaterial.m_sName = "Sprite";
  
  std::string sVertexSource = 
    "#version 330"
    "layout (location = 0) position;"
    "layout (location = 1) normal;"
    "layout (location = 2) uv;"
    "uniform mat4 MVP;"
    "out vec2 vertex_uv;"
    "int main()"
    "{"
    "  gl_Position = MVP* vec4(position, 1.0);"
    "  vertex_uv = vec2(uv.x, uv.y);"
    "}"
  ;

  std::string sFragmentSource =
    "#version 330"
    "out vec2 vertex_uv;"
    "int main()"
    "{"
    "   gl_FragColor = vec4(vertex_uv.x, vertex_uv.y, 0.0, 1.0);"
    "}"
  ;

  oMaterial.m_vctShaders.emplace_back(Shader::EType::Vertex, sVertexSource);
  oMaterial.m_vctShaders.emplace_back(Shader::EType::Fragment, sFragmentSource);

  oMaterial.m_oProgram.attachShader(&oMaterial.m_vctShaders[0]);
  oMaterial.m_oProgram.attachShader(&oMaterial.m_vctShaders[1]);

  oMaterial.m_dctAttributesTable.emplace("MVP", ValueType::Mat4);

  //

  std::shared_ptr<MaterialInstance> oMaterialInstance = std::make_shared<MaterialInstance>(std::make_shared<Material>(oMaterial));

  /*std::unique_ptr<Attribute> oMVP = std::make_unique<Attribute>(ValueType::Mat4, "MVP");
  oMaterialInstance.m_vctAttributes.push_back(oMVP);*/

  std::unordered_map<std::string, ValueType>::iterator itAttribute = oMaterial.m_dctAttributesTable.begin();
  while (itAttribute != oMaterial.m_dctAttributesTable.end())
  {
    std::unique_ptr<Attribute> oMVP = std::make_unique<Attribute>(itAttribute->second, itAttribute->first);
    //oMaterialInstance.m_vctAttributes.push_back(std::move(std::make_unique<Attribute>(itAttribute->second, itAttribute->first)));
    oMaterialInstance->m_vctAttributes.push_back(std::move(oMVP));

    ++itAttribute;
  }

  return std::move(oMaterialInstance);
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

std::unique_ptr<Attribute>& MaterialInstance::getAttribute(const std::string & _sName)
{
  for (std::unique_ptr<Attribute>& pAttribute : m_vctAttributes)
  {
    if (pAttribute->getName() == _sName)
    {
      return pAttribute;
    }
  }
}