#pragma once
#include "GameObjects/GameObject.h"
#include <Engine/Camera2D.hpp>
#include <Engine/OGLGame.h>
#include <string>

/**
 *  An OpenGL Game based on ASGE.
 */
class AngryBirds : public ASGE::OGLGame
{
 public:
  explicit AngryBirds(ASGE::GameSettings settings);
  ~AngryBirds() final;
  bool init();

 private:
  void keyHandler(ASGE::SharedEventData data);
  void clickHandler(ASGE::SharedEventData data);
  void update(const ASGE::GameTime&) override;
  void render() override;
  void setupObjects();
  void setupPositions();

  int key_callback_id           = -1; /**< Key Input Callback ID. */
  int mouse_callback_id         = -1; /**< Mouse Input Callback ID. */
  bool in_menu                  = true;
  ASGE::Sprite* menu_background = nullptr;
  ASGE::Camera2D camera;
  void logStartup() const;

  GameObject bird;
};