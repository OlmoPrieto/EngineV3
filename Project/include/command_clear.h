#pragma once

#include "gpu_command.h"
#include "utils.h"

class CommandClear : public GPUCommand
{
public:
  CommandClear(const Color& _oColor);
  ~CommandClear();

  void execute() override;

private:
  Color m_oColor;
};