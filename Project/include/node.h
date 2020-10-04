#pragma once

#include "component.h"

#include <string>
#include <vector>

class Node {
public:
  Node();
  ~Node();

  std::vector<std::unique_ptr<Component>>& getComponents() { return m_vctComponents; }
  template <class T>
  T* getComponent(const std::string& _sName)
  {
    for (std::unique_ptr<Component>& pComponent : m_vctComponents)
    {
      if (pComponent->getName() == _sName)
      {
        return (T*)pComponent.get();
      }
    }

    return nullptr;
  }

  template <class T>
  void addComponent(std::unique_ptr<T>&& _pComponent) { m_vctComponents.push_back(std::move(_pComponent)); }
  void addChild(std::unique_ptr<Node>&& _pChild) { m_vctChildren.push_back(std::move(_pChild)); }

  std::vector<std::unique_ptr<Node>>& getChildren() { return m_vctChildren; }

private:
  friend class Scene;

  std::vector<std::unique_ptr<Node>> m_vctChildren;
  std::vector<std::unique_ptr<Component>> m_vctComponents;
  std::string m_sName;
};