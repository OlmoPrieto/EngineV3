#pragma once

#include <memory>

#include "gpu_command.h"
#include "material.h"

/* This command will create, compile, link, attach and everything GPU related           */
/* with Materials: Shaders and Programs. Should also retrieve the attributes locations  */
class CommandPrepareMaterial : public GPUCommand
{
public:
  CommandPrepareMaterial(std::shared_ptr<MaterialInstance> _spMaterial);
  ~CommandPrepareMaterial();

  void execute() override;

private:
  std::shared_ptr<MaterialInstance> m_spMaterial;
};