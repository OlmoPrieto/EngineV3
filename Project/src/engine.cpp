#include "engine.h"

Engine::Engine() 
{

}

Engine::~Engine() 
{

}

Engine* Engine::GetInstancePtr() 
{
  static Engine oEngine;
  return &oEngine;
}

Engine& Engine::GetInstance()
{
  static Engine oEngine;
  return oEngine;
}