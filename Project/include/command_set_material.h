#pragma once

#include <memory>

#include "gpu_command.h"
#include "material.h"

/* This command will set the values for the material attributes (uniforms) */
class CommandSetMaterial : public GPUCommand
{
public:
  CommandSetMaterial(std::shared_ptr<MaterialInstance> _spMaterial);
  ~CommandSetMaterial();

  void execute() override;

private:
  std::shared_ptr<MaterialInstance> m_spMaterial;
};