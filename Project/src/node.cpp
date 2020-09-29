#include "node.h"

Node::Node() {

}

Node::~Node() {

}

Component* Node::getComponent(const std::string& _sName)
{
  for (std::unique_ptr<Component>& pComponent : m_vctComponents)
  {
    if (pComponent->getName() == _sName)
    {
      return pComponent.get();
    }
  }

  return nullptr;
}