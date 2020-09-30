#include "transform_component.h"

#include "node.h"

std::string TransformComponent::sm_sName = "TRANSFORM";

TransformComponent::TransformComponent(Node* _pOwner_)
  : Component(_pOwner_)
{
  m_vec3Scale.set(1.0f, 1.0f, 1.0f);
}

TransformComponent::~TransformComponent()
{

}

Mat4 TransformComponent::getWorldTransform()
{
  if (m_pOwner)
  {
    TransformComponent* pParentTransformComponent = (TransformComponent*)m_pOwner->getComponent("TRANSFORM");
    if (pParentTransformComponent)
    {
      Mat4 mat4WorldTransform = pParentTransformComponent->getWorldTransform();
      return mat4WorldTransform * m_mat4LocalTransform;
    }
  }

  return m_mat4LocalTransform;
}

void TransformComponent::setPosition(float _fX, float _fY, float _fZ)
{
  m_vec3Position.set(_fX, _fY, _fZ);
  m_bDirty = true;
}

void TransformComponent::setChildrenDirtyState(bool _bState)
{
  if (m_pOwner)
  {
    std::vector<std::unique_ptr<Node>>& vctChildren = m_pOwner->getChildren();
    for (std::unique_ptr<Node>& pChild : vctChildren)
    {
      TransformComponent* pTransformComponent = (TransformComponent*)pChild->getComponent("TRANSFORM");
      if (pTransformComponent)
      {
        pTransformComponent->m_bDirty = _bState;
      }
    }
  }
}