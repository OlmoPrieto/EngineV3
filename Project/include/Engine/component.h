#pragma once

#include <string>

class Node;

class Component {
public:
  enum class EType
  {
    Transform = 0,
    Render
  };

  virtual ~Component();

  virtual const std::string& getName() const = 0;

  void setOwner(Node* _pNode) { m_pOwner = _pNode; }

protected:
  Node* m_pOwner = nullptr;
};
