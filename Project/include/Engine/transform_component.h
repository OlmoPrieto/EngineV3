#pragma once

#include "component.h"
#include "maths.h"

class TransformComponent : public Component
{
public:
  TransformComponent();
  ~TransformComponent();

  /* Component */
  const std::string& getName() const override { return sm_sName; };

  Mat4 getWorldTransform();
  void setPosition(float _fX, float _fY, float _fZ);
  void setPosition(const Vec3& _v3Pos);
  void setScale(float _fX, float _fY, float _fZ);

  const Vec3& getPosition() { return m_vec3Position; }

private:
  void setChildrenDirtyState(bool _bState);

  Mat4 m_mat4LocalTransform;
  Vec3 m_vec3Position;
  Vec3 m_vec3Rotation;
  Vec3 m_vec3Scale;
  static std::string sm_sName;
  bool m_bDirty = true;
};