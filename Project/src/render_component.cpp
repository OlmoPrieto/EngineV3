#include "render_component.h"
#include "command_draw.h"
#include "command_set_material.h"

std::string RenderComponent::sm_sName = "RENDER";

RenderComponent::RenderComponent(Node* _pOwner_)
  : Component(_pOwner_)
{
  addComponent();

  m_spModel = Model3D::CreateQuad();

  //for (std::shared_ptr<Mesh>& pMesh : m_spModel->getMeshes())
  for (uint32_t i = 0; i < m_spModel->getMeshes().size(); ++i)
  {
    m_vctMaterials.push_back(Material::CreateSpriteMaterial());
  }
}

RenderComponent::~RenderComponent()
{

}

void RenderComponent::addComponent()
{
  if (m_pOwner)
    m_pOwner->addComponent<RenderComponent>(std::make_unique<RenderComponent>(*this));
}

void RenderComponent::generateDisplayListCommands(std::vector<std::unique_ptr<GPUCommand>>& vctDisplayList_)
{
  uint32_t uNumMeshes = m_spModel->getMeshes().size();
  for (uint32_t i = 0; i < uNumMeshes; ++i)
  {
    vctDisplayList_.push_back(std::make_unique<CommandSetMaterial>(m_vctMaterials[i]));
    vctDisplayList_.push_back(std::make_unique<CommandDraw>(m_spModel->getMeshes()[i]));
  }
}