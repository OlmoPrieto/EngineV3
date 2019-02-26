#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "scene.h"
#include "component.h"

class Engine {
public:
  static Engine* Instance();
  Component* CreateComponent();

private:
  Engine();
  ~Engine();

  Scene m_oScene;
};

#endif  // __ENGINE_H__