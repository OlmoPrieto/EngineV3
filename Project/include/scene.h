#pragma once

#include <vector>

#include "gpu_command.h"
#include "node.h"

class Scene {
public:
  Scene();
  ~Scene();

  Node& getRoot() { return m_oRoot; }

  void update(float _fFrameTime);
  std::vector<std::unique_ptr<GPUCommand>> generateDisplayList();

private:
  Node m_oRoot;
};
