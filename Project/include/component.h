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

  Component(Node* _pOwner_);
  virtual ~Component();

  virtual const std::string& getName() const = 0;

protected:
  virtual void addComponent() = 0;

  Node* m_pOwner = nullptr;
};
