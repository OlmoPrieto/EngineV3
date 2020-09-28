#pragma once

#include <memory>

#include "gpu_command.h"
#include "material.h"

class CommandDraw : public GPUCommand
{
public:
  CommandDraw(std::shared_ptr<Mesh> _spMesh);
  ~CommandDraw();

  void execute() override;

private:
  std::shared_ptr<Mesh> m_spMesh;
};