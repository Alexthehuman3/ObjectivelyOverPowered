//
// Created by Alex on 05/05/2020.
//

#ifndef ANGRYBIRDS_UICOMPONENT_H
#define ANGRYBIRDS_UICOMPONENT_H

#include <Engine/GameTime.h>
#include <Engine/Point2D.h>
#include <GameObjects/GameObject.h>

namespace ASGE
{
  class Renderer;
  class Sprite;
}
class UIComponent
{
 public:
  UIComponent()          = default;
  virtual ~UIComponent() = default;
  virtual void update();
  virtual void render();

 private:
  ASGE::Point2D UI_pos = { 0, 0 };
};

#endif // ANGRYBIRDS_UICOMPONENT_H
