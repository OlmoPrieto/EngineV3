#ifndef __NODE_H__
#define __NODE_H__

#include "component.h"

#include <string>
#include <vector>

class Node {
public:
  Node();
  ~Node();


private:
  friend class Scene;

  std::vector<Node> m_children;
  std::vector<Component*> m_components;
  std::string m_name;
};

#endif  // __NODE_H__
