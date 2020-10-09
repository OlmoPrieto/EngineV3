#pragma once

#include <memory>

#include "component.h"
#include "material.h"
#include "model3d.h"
#include "node.h"

class GPUCommand;

class RenderComponent : public Component
{
public:
  RenderComponent(Node* _pOwner_);
  ~RenderComponent();

  /* Component */
  const std::string& getName() const override { return sm_sName; }

  std::shared_ptr<Model3D> getModel() const { return m_spModel; }
  std::vector<std::shared_ptr<MaterialInstance>>& getMaterialInstances() { return m_vctMaterials; }

  void generateDisplayListCommands(std::vector<std::unique_ptr<GPUCommand>>& vctDisplayList_);

private:
  /* Component */
  void addComponent() override;

  std::shared_ptr<Model3D> m_spModel;
  std::vector<std::shared_ptr<MaterialInstance>> m_vctMaterials;
  static std::string sm_sName;
};