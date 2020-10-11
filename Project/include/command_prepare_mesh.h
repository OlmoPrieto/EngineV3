#pragma once

#include <memory>

#include "gpu_command.h"

class CommandPrepareMesh : public GPUCommand
{
public:
  CommandPrepareMesh(std::shared_ptr<Mesh> _spMesh);
  ~CommandPrepareMesh();

  void execute() override;

private:
  std::shared_ptr<Mesh> m_spMesh;
};