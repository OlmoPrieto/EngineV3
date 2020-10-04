#include "component.h"

#include "node.h"

Component::Component(Node* _pOwner_) 
{
  m_pOwner = _pOwner_;
}

Component::~Component() 
{

}