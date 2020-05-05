//
// Created by Alex on 05/05/2020.
//

#ifndef ANGRYBIRDS_BUTTONCOMPONENT_H
#define ANGRYBIRDS_BUTTONCOMPONENT_H

#include "Components/UI/UIComponent.h"
#include <Engine/Text.hpp>

class ButtonComponent : public UIComponent
{
 public:
  ButtonComponent(std::string text);
  ~ButtonComponent() override = default;

  void update() override;

 private:
  ASGE::Text button_text;
};

#endif // ANGRYBIRDS_BUTTONCOMPONENT_H
