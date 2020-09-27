#pragma once

#include "opengl_implementation.h"

class OpenGLImplementation;

class GPUCommand
{
public:
  GPUCommand() = default;
  virtual ~GPUCommand() = default;

  virtual void execute() = 0;

protected:
  static OpenGLImplementation sm_oOpenGL;
};