#pragma once

#include "component.h"
#include "maths.h"

class TransformComponent : public Component
{
public:
  TransformComponent(Node* _pOwner_);
  ~TransformComponent();

  /* Component */
  const std::string& getName() const override { return sm_sName; };

  Mat4 getWorldTransform();
  void setPosition(float _fX, float _fY, float _fZ);

private:
  void setChildrenDirtyState(bool _bState);
  /* Component */
  void addComponent() override;

  Mat4 m_mat4LocalTransform;
  Vec3 m_vec3Position;
  Vec3 m_vec3Rotation;
  Vec3 m_vec3Scale;
  static std::string sm_sName;
  bool m_bDirty = true;
};