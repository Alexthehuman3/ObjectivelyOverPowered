//
// Created by Alex on 05/05/2020.
//

#include "GameObject.h"

ButtonComponent* GameObject::getButtonComp()
{
  return buttonComponent;
}

void GameObject::setButtonComp(ButtonComponent* newButtonComp)
{
  buttonComponent = newButtonComp;
}
