#include "render_component.h"

RenderComponent::RenderComponent(Node* _pOwner_)
  : m_pOwner(_pOwner_)
  , m_oModel(Model3D::CreateQuad())
  , m_oMaterial(Material::CreateSpriteMaterial())
{
  _pOwner_->addComponent(this);
}

RenderComponent::~RenderComponent()
{

}