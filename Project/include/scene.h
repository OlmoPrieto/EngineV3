#ifndef __SCENE_H__
#define __SCENE_H__

#include "node.h"

class Scene {
public:
  Scene();
  ~Scene();

private:
  Node m_root;
};

#endif  // __SCENE_H__
