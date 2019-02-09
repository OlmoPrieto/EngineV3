#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "scene.h"
#include "component.h"

class Engine {
public:
  static Engine* Instance();
  template <typename T>
  Component<T>* CreateComponent();

private:
  Engine();
  ~Engine();

  Scene m_scene;
};

#endif  // __ENGINE_H__