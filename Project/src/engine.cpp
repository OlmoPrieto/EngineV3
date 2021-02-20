#include "engine.h"

#include "scene.h"
#include "camera.h"

uint32_t Engine::s_uWindowWidth = 720u;
uint32_t Engine::s_uWindowHeight = 480u;

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

void Engine::loop()
{
  if (m_pCurrentScene)
    m_pCurrentScene->update(0.01666f);

  draw();
}

void Engine::draw()
{
  if (m_pCurrentScene)
    m_vctDisplayList = m_pCurrentScene->generateDisplayList();

  for (std::unique_ptr<GPUCommand>& pCommand : m_vctDisplayList)
  {
    pCommand->execute();
  }

  m_vctDisplayList.clear();
}