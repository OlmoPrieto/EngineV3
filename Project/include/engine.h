#pragma once

#include "scene.h"
#include "component.h"

class Engine 
{
public:
  static Engine* GetInstancePtr();
  static Engine& GetInstance();

private:
  Engine();
  ~Engine();
};