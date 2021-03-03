#include "transform_component.h"

#include "node.h"

std::string TransformComponent::sm_sName = "TRANSFORM";

TransformComponent::TransformComponent()
{
  setScale(20.0f, 20.0f, 1.0f);
  setPosition(0.0f, 0.0f, 0.0f);
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
      // WORLD MATRIX = LOCAL MATRIX * WORLD PARENT

      /*Mat4 mat4WorldTransform = pParentTransformComponent->getWorldTransform();
      mat4WorldTransform.inverse();
      return mat4WorldTransform * m_mat4LocalTransform;*/
      Mat4 mat4WorldTransform = pParentTransformComponent->getWorldTransform();
      Mat4 mat4InverseLocal = m_mat4LocalTransform;
      //mat4InverseLocal.inverse();
      Mat4 returnMat = mat4InverseLocal * mat4WorldTransform;
      returnMat.setScale(20.0f, 20.0f, 0.0f);
      return returnMat; // COMMENT: results 100 units to the left instead of right
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