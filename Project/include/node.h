#pragma once

#include "component.h"

#include <string>
#include <vector>

class Node {
public:
  Node();
  ~Node();

  std::vector<Component*>& getComponents() { return m_vctComponents; }
  Component* getComponent(const std::string& _sName);

  void addComponent(Component* _pComponent) { m_vctComponents.push_back(_pComponent); }


private:
  friend class Scene;

  std::vector<Node> m_vctChildren;
  std::vector<Component*> m_vctComponents;
  std::string m_sName;
};