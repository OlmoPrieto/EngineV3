#include "Engine/scene.h"

#include "Engine/command_clear.h"
#include "Engine/render_component.h"
#include "Engine/opengl_implementation.h"
#include "Engine/render_component.h"
#include "Engine/transform_component.h"
#include "Engine/engine.h"
#include "Engine/input.h"

Scene::Scene()
  //: m_oCamera(Camera::EType::Orthographic, Engine::s_uWindowWidth, Engine::s_uWindowHeight)
  : m_oCamera(Camera::EType::Perspective, Engine::s_uWindowWidth, Engine::s_uWindowHeight)
{
  m_oRoot.m_sName = "ROOT";
}

Scene::~Scene() 
{

}

void Scene::init()
{
  std::unique_ptr<RenderComponent> oRenderComponent = std::make_unique<RenderComponent>();
  std::vector<std::shared_ptr<MaterialInstance>>& vctMaterialInstances = oRenderComponent->getMaterialInstances();
  std::unique_ptr<Attribute>& pTextureAttribute = vctMaterialInstances[0]->getAttribute("textureImage");
  m_oTextureTest = std::make_shared<Texture>();
  m_oTextureTest->load("assets/textures/uv_checker.png");
  m_oTextureTest->setWrapS(Texture::Wrap::Repeat);
  m_oTextureTest->setWrapT(Texture::Wrap::Repeat);
  m_oTextureTest->setMinFilter(Texture::Filter::Linear);
  m_oTextureTest->setMagFilter(Texture::Filter::Linear);
  m_oTextureTest->setFormat(Texture::Format::RGBA);
  pTextureAttribute->setValue(m_oTextureTest);

  std::unique_ptr<TransformComponent> oTransformComponent = std::make_unique<TransformComponent>();
  oTransformComponent->setPosition(0.0f, 0.0f, -20.0f);
  //oTransformComponent->setPosition(0.0f, 0.0f, 0.0f);
  oTransformComponent->setScale(10.0f, 10.0f, 1.0f);
  m_oRoot.addComponent(std::move(oRenderComponent));
  m_oRoot.addComponent(std::move(oTransformComponent));

  std::unique_ptr<Node> pNewNode = std::make_unique<Node>();
  std::unique_ptr<RenderComponent> oRenderComponent2 = std::make_unique<RenderComponent>();
  vctMaterialInstances = oRenderComponent2->getMaterialInstances();
  std::unique_ptr<Attribute>& pTextureAttribute2 = vctMaterialInstances[0]->getAttribute("textureImage");
  pTextureAttribute2->setValue(m_oTextureTest);

  std::unique_ptr<TransformComponent> oTransformComponent2 = std::make_unique<TransformComponent>();
  oTransformComponent2->setPosition(10.0f, 0.0f, 0.0f);
  //oTransformComponent2->setScale(100.0f, 100.0f, 1.0f);
  oTransformComponent2->setScale(1.0f, 1.0f, 1.0f);
  pNewNode->m_sName = "child";
  pNewNode->addComponent(std::move(oRenderComponent2));
  pNewNode->addComponent(std::move(oTransformComponent2));

  m_oRoot.addChild(std::move(pNewNode));
  
  Engine::GetInstance().setCurrentCamera(&m_oCamera);
}

void Scene::update(float _fFrameTime)
{


  if (Input::tapped())
  {
    printf("Tapped\n");
    TransformComponent* pTransformRoot = m_oRoot.getComponent<TransformComponent>("TRANSFORM");
    const Vec3& v3CurrentPosRoot = pTransformRoot->getPosition();
    pTransformRoot->setPosition(v3CurrentPosRoot.x + 0.0f, v3CurrentPosRoot.y, v3CurrentPosRoot.z);
    
    TransformComponent* pTransformChild = m_oRoot.getChildren()[0]->getComponent<TransformComponent>("TRANSFORM");
    const Vec3& v3CurrentPosChild = pTransformChild->getPosition();
    pTransformChild->setPosition(v3CurrentPosChild.x + 1.0f, v3CurrentPosChild.y, v3CurrentPosChild.z);
  }
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

std::vector<std::unique_ptr<GPUCommand>> Scene::generateDisplayList()
{
  std::vector<std::unique_ptr<GPUCommand>> vctDisplayList;
  vctDisplayList.push_back(std::make_unique<CommandClear>((uint32_t)OpenGLImplementation::EClearTarget::COLOR | (uint32_t)OpenGLImplementation::EClearTarget::DEPTH));
  traverseScene(&m_oRoot, vctDisplayList);

  return vctDisplayList;
}