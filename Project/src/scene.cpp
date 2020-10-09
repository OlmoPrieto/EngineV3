#include "scene.h"

#include <vector>

#include "gpu_command.h"
#include "render_component.h"
#include "transform_component.h"

Scene::Scene() 
{
  m_oRoot.m_sName = "ROOT";
}

Scene::~Scene() 
{

}

void Scene::update(float _fFrameTime)
{

}

namespace
{
  void traverseScene(Node* _pNode, std::vector<std::unique_ptr<GPUCommand>>& vctDisplayList_)
  {
    if (_pNode == nullptr)
    {
      return;
    }

    RenderComponent* pRenderComponent = _pNode->getComponent<RenderComponent>("RENDER");
    if (pRenderComponent)
    {
      pRenderComponent->generateDisplayListCommands(vctDisplayList_);
    }

    for (std::unique_ptr<Node>& pNode : _pNode->getChildren())
    {
      traverseScene(pNode.get(), vctDisplayList_);
    }
  }
}

void Scene::generateDisplayList()
{
  std::vector<std::unique_ptr<GPUCommand>> vctDisplayList;
  traverseScene(&m_oRoot, vctDisplayList);
}