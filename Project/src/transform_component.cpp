#include "transform_component.h"

#include "node.h"

std::string TransformComponent::sm_sName = "TRANSFORM";

TransformComponent::TransformComponent()
{
  setScale(20.0f, 20.0f, 10.0f);
  setPosition(360.0f, 240.0f, 0.0f);
}

TransformComponent::~TransformComponent()
{

}

Mat4 TransformComponent::getWorldTransform()
{
  if (m_bDirty)
  {
    m_mat4LocalTransform.setPosition(m_vec3Position);
    m_mat4LocalTransform.setScale(m_vec3Scale);

    m_bDirty = false;
  }

  Node* pParent = m_pOwner->getParent();
  if (pParent)
  {
    TransformComponent* pParentTransformComponent = pParent->getComponent<TransformComponent>("TRANSFORM");
    if (pParentTransformComponent)
    {
      Mat4 mat4WorldTransform = pParentTransformComponent->getWorldTransform();
      mat4WorldTransform.inverse();
      return m_mat4LocalTransform * mat4WorldTransform;
    }
  }

  return m_mat4LocalTransform;
}

void TransformComponent::setPosition(float _fX, float _fY, float _fZ)
{
  m_vec3Position.set(_fX, _fY, _fZ);
  m_bDirty = true;
}

void TransformComponent::setScale(float _fX, float _fY, float _fZ)
{
  m_vec3Scale.set(_fX, _fY, _fZ);
  m_bDirty = true;
}

void TransformComponent::setChildrenDirtyState(bool _bState)
{
  if (m_pOwner)
  {
    std::vector<std::unique_ptr<Node>>& vctChildren = m_pOwner->getChildren();
    for (std::unique_ptr<Node>& pChild : vctChildren)
    {
      TransformComponent* pTransformComponent = pChild->getComponent<TransformComponent>("TRANSFORM");
      if (pTransformComponent)
        pTransformComponent->m_bDirty = _bState;
    }
  }
}