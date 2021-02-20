#include "render_component.h"

#include "camera.h"
#include "command_draw.h"
#include "command_prepare_material.h"
#include "command_prepare_mesh.h"
#include "command_set_material.h"
#include "engine.h"
#include "transform_component.h"

std::string RenderComponent::sm_sName = "RENDER";

RenderComponent::RenderComponent()
{
  m_spModel = Model3D::CreateQuad();

  //for (std::shared_ptr<Mesh>& pMesh : m_spModel->getMeshes())
  for (uint32_t i = 0; i < m_spModel->getMeshes().size(); ++i)
  {
    m_vctMaterials.push_back(Material::CreateSpriteMaterial());
  }
}

RenderComponent::~RenderComponent()
{

}

void RenderComponent::generateDisplayListCommands(std::vector<std::unique_ptr<GPUCommand>>& vctDisplayList_)
{
  Mat4 mat4Projection = Engine::GetInstance().getCurrentCamera()->getProjectionMatrix();

  uint32_t uNumMeshes = m_spModel->getMeshes().size();
  for (uint32_t i = 0; i < uNumMeshes; ++i)
  {
    std::unique_ptr<Attribute>& oMVP = m_vctMaterials[i]->getAttribute("MVP");

    TransformComponent* pTransformComp = m_pOwner->getComponent<TransformComponent>("TRANSFORM");
    assert(pTransformComp);
    oMVP->setValue<Mat4>(pTransformComp->getWorldTransform() * mat4Projection);

    if (m_vctMaterials[i]->checkReady() == false)
      vctDisplayList_.push_back(std::make_unique<CommandPrepareMaterial>(m_vctMaterials[i]));

    vctDisplayList_.push_back(std::make_unique<CommandSetMaterial>(m_vctMaterials[i]));
    
    if (m_spModel->getMeshes()[i]->getIsReady() == false)
      vctDisplayList_.push_back(std::make_unique<CommandPrepareMesh>(m_spModel->getMeshes()[i]));

    vctDisplayList_.push_back(std::make_unique<CommandDraw>(m_spModel->getMeshes()[i]));
  }
}