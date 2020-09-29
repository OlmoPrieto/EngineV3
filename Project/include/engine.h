#pragma once

#include "scene.h"
#include "component.h"

class Engine 
{
public:
  static Engine* Instance();

private:
  Engine();
  ~Engine();

  Scene m_oScene;
};