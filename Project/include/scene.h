#pragma once

#include <vector>

#include "gpu_command.h"
#include "node.h"
#include "camera.h"

class Scene {
public:
  Scene();
  ~Scene();

  Node& getRoot() { return m_oRoot; }

  void init();
  void update(float _fFrameTime);
  std::vector<std::unique_ptr<GPUCommand>> generateDisplayList();

private:
  Node m_oRoot;
  Camera m_oCamera;
};
