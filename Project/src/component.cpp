#include "component.h"

#include "node.h"

Component::Component(Node* _pOwner_) 
{
  m_pOwner = _pOwner_;
  _pOwner_->addComponent(std::make_unique<Component>(*this));
}

Component::~Component() 
{

}