#include "Engine/material.h"

#include <cassert>

#include "Engine/shader.h"

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
    "#version 330\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 normal;\n"
    "layout (location = 2) in vec3 uv;\n"
    "uniform mat4 MVP;\n"
    "out vec2 vertex_uv;\n"
    "void main()\n"
    "{\n"
    "  gl_Position = MVP * vec4(position, 1.0);\n"
    "  vertex_uv = vec2(uv.x, uv.y);\n"
    "}\n"
  ;

  std::string sFragmentSource =
    "#version 330\n"
    "in vec2 vertex_uv;\n"
    "uniform sampler2D textureImage;\n"
    "void main()\n"
    "{\n"
    "  gl_FragColor = texture(textureImage, vertex_uv);\n"
    "}\n"

    //"#version 330\n"
    //"in vec2 vertex_uv;\n"
    //"void main()\n"
    //"{\n"
    ////"  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    //"  gl_FragColor = vec4(vertex_uv.x, vertex_uv.y, 0.0, 1.0);\n"
    //"}\n"
  ;

  oMaterial.m_vctShaders.emplace_back(Shader::EType::Vertex, sVertexSource);
  oMaterial.m_vctShaders.emplace_back(Shader::EType::Fragment, sFragmentSource);

  oMaterial.m_oProgram.attachShader(&oMaterial.m_vctShaders[0]);
  oMaterial.m_oProgram.attachShader(&oMaterial.m_vctShaders[1]);

  oMaterial.m_dctAttributesTable.emplace("MVP", ValueType::Mat4);
  oMaterial.m_dctAttributesTable.emplace("textureImage", ValueType::Texture);

  //

  std::shared_ptr<MaterialInstance> oMaterialInstance = std::make_shared<MaterialInstance>(std::make_shared<Material>(oMaterial));

  std::unordered_map<std::string, ValueType>::iterator itAttribute = oMaterial.m_dctAttributesTable.begin();
  while (itAttribute != oMaterial.m_dctAttributesTable.end())
  {
    std::unique_ptr<Attribute> oAttribute = std::make_unique<Attribute>(itAttribute->second, itAttribute->first);
    oMaterialInstance->m_vctAttributes.push_back(std::move(oAttribute));

    ++itAttribute;
  }

  return std::move(oMaterialInstance);
}

std::shared_ptr<MaterialInstance> Material::CreateSpriteMaterial2()
{
  Material oMaterial;
  oMaterial.m_sName = "Sprite2";

  std::string sVertexSource =
    "#version 330\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 normal;\n"
    "layout (location = 2) in vec3 uv;\n"
    "uniform mat4 MVP;\n"
    "out vec2 vertex_uv;\n"
    "void main()\n"
    "{\n"
    "  gl_Position = MVP * vec4(position, 1.0);\n"
    "  vertex_uv = vec2(uv.x, uv.y);\n"
    "}\n"
    ;

  std::string sFragmentSource =
    /*"#version 330\n"
    "in vec2 vertex_uv;\n"
    "uniform sampler2D textureImage;\n"
    "void main()\n"
    "{\n"
    "  gl_FragColor = texture(textureImage, vertex_uv);\n"
    "}\n"*/

    "#version 330\n"
    "in vec2 vertex_uv;\n"
    "void main()\n"
    "{\n"
    //"  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "  gl_FragColor = vec4(vertex_uv.x, vertex_uv.y, 1.0, 1.0);\n"
    "}\n"
    ;

  oMaterial.m_vctShaders.emplace_back(Shader::EType::Vertex, sVertexSource);
  oMaterial.m_vctShaders.emplace_back(Shader::EType::Fragment, sFragmentSource);

  oMaterial.m_oProgram.attachShader(&oMaterial.m_vctShaders[0]);
  oMaterial.m_oProgram.attachShader(&oMaterial.m_vctShaders[1]);

  oMaterial.m_dctAttributesTable.emplace("MVP", ValueType::Mat4);
  //oMaterial.m_dctAttributesTable.emplace("textureImage", ValueType::Texture);

  //

  std::shared_ptr<MaterialInstance> oMaterialInstance = std::make_shared<MaterialInstance>(std::make_shared<Material>(oMaterial));

  std::unordered_map<std::string, ValueType>::iterator itAttribute = oMaterial.m_dctAttributesTable.begin();
  while (itAttribute != oMaterial.m_dctAttributesTable.end())
  {
    std::unique_ptr<Attribute> oAttribute = std::make_unique<Attribute>(itAttribute->second, itAttribute->first);
    oMaterialInstance->m_vctAttributes.push_back(std::move(oAttribute));

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