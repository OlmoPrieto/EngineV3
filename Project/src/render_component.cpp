#include "render_component.h"

std::string RenderComponent::sm_sName = "RENDER";

RenderComponent::RenderComponent(Node* _pOwner_)
  : Component(_pOwner_)
  , m_oModel(Model3D::CreateQuad())
  , m_oMaterial(Material::CreateSpriteMaterial())
{
  addComponent();
}

RenderComponent::~RenderComponent()
{

}

void RenderComponent::addComponent()
{
  if (m_pOwner)
    m_pOwner->addComponent<RenderComponent>(std::make_unique<RenderComponent>(*this));
}