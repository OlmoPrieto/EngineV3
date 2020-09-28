#pragma once

#include <string>

class Component {
public:
  Component();
  ~Component();

  std::string getName() const { return m_sName; }

private:
  std::string m_sName;
};
