#ifndef __GPU_COMMAND_H__
#define __GPU_COMMAND_H__

class GPUCommand
{
public:
  GPUCommand() = default;
  virtual ~GPUCommand() = default;

  virtual void execute() = 0;
};

#endif // __GPU_COMMAND_H__