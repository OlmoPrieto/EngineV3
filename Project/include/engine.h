#pragma once

#include <vector>

#include "component.h"
#include "gpu_command.h"

class Camera;
class Scene;

class Engine 
{
public:
  static Engine* GetInstancePtr();
  static Engine& GetInstance();

  void loop();

  void setCurrentScene(Scene* _pScene) { m_pCurrentScene = _pScene; }
  void setCurrentCamera(Camera* _pCamera) { m_pCurrentCamera = _pCamera; }

  Scene* getCurrentScene() const { return m_pCurrentScene; }
  Camera* getCurrentCamera() const { return m_pCurrentCamera; }

  void getWindowSize(uint32_t& uWidth_, uint32_t& uHeight_) { uWidth_ = m_uWindowWidth; uHeight_ = m_uWindowHeight; }

private:
  
  Engine();
  ~Engine();

  void draw();

  std::vector<std::unique_ptr<GPUCommand>> m_vctDisplayList;
  Scene* m_pCurrentScene = nullptr;
  Camera* m_pCurrentCamera = nullptr;
  uint32_t m_uWindowWidth = 720;
  uint32_t m_uWindowHeight = 480;
};