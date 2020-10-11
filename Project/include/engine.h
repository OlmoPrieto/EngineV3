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

private:
  
  Engine();
  ~Engine();

  void draw();

  std::vector<std::unique_ptr<GPUCommand>> m_vctDisplayList;
  Scene* m_pCurrentScene = nullptr;
  Camera* m_pCurrentCamera = nullptr;
};