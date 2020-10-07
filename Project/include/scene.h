#pragma once

#include "node.h"

class Scene {
public:
  Scene();
  ~Scene();

  const Node& getRoot() const { return m_oRoot; }

  void update(float _fFrameTime);
  void generateDisplayList();

private:
  Node m_oRoot;
};
