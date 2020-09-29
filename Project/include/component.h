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

  static std::string& getName() { return sm_sName; }

protected:
  static std::string sm_sName;
  Node* m_pOwner = nullptr;
};
