#pragma once

#include <memory>

#include "component.h"
#include "material.h"
#include "model3d.h"
#include "node.h"

class RenderComponent : public Component
{
public:
  RenderComponent(Node* _pOwner_);
  ~RenderComponent();

  std::shared_ptr<Model3D> getModel() const { return m_oModel; }
  std::shared_ptr<MaterialInstance> getMaterialInstance() const { return std::make_shared<MaterialInstance>(m_oMaterial); }

private:
  std::shared_ptr<Model3D> m_oModel;
  MaterialInstance m_oMaterial;
  Node* m_pOwner = nullptr;
};