#include "Engine/transform_component.h"

#include "Engine/node.h"

std::string TransformComponent::sm_sName = "TRANSFORM";

TransformComponent::TransformComponent()
{
  setScale(1.0f, 1.0f, 1.0f);
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
      // WORLD MATRIX = WORLD PARENT * LOCAL MATRIX in row major
      Mat4 mat4WorldTransform = pParentTransformComponent->getWorldTransform();
      Mat4 mat4Local = m_mat4LocalTransform;
      Mat4 returnMat = mat4WorldTransform * mat4Local;
      return returnMat;
    }
  }

  return m_mat4LocalTransform;
}

void TransformComponent::setPosition(float _fX, float _fY, float _fZ)
{
  m_vec3Position.set(_fX, _fY, _fZ);
  m_bDirty = true;
}

void TransformComponent::setPosition(const Vec3& _v3Pos)
{
  m_vec3Position = _v3Pos;
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