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
  void traverseScene(Node* _pNode)
  {
    

    for (std::unique_ptr<Node>& pNode : _pNode->getChildren())
    {
      traverseScene(pNode.get());
    }

    if (_pNode == nullptr)
    {
      return;
    }
  }
}

void Scene::generateDisplayList()
{
  std::vector<GPUCommand> vctDisplayList;

}