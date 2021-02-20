#pragma once

#include "gpu_command.h"

class CommandClear : public GPUCommand
{
public:
  CommandClear(uint32_t _uClearTarget);
  ~CommandClear();

  void execute() override;

private:
  uint32_t m_uClearTarget;
};