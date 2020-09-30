#pragma once

#include "component.h"

#include <string>
#include <vector>

class Node {
public:
  Node();
  ~Node();

  std::vector<std::unique_ptr<Component*>>& getComponents() { return m_vctComponents; }
  Component* getComponent(const std::string& _sName);

  void addComponent(std::unique_ptr<Component*>&& _pComponent) { m_vctComponents.push_back(std::move(_pComponent)); }
  void addChild(std::unique_ptr<Node>&& _pChild) { m_vctChildren.push_back(std::move(_pChild)); }

  std::vector<std::unique_ptr<Node>>& getChildren() { return m_vctChildren; }

private:
  friend class Scene;

  std::vector<std::unique_ptr<Node>> m_vctChildren;
  std::vector<std::unique_ptr<Component*>> m_vctComponents;
  std::string m_sName;
};