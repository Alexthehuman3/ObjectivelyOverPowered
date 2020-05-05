#include <string>

#include <Engine/InputEvents.h>
#include <Engine/Keys.h>
#include <Engine/Logger.hpp>
#include <Engine/Point2D.h>
#include <Engine/Sprite.h>

#include "game.h"
/**
 *   @brief   Default Constructor.
 */
ESDR::ESDR(ASGE::GameSettings settings) : OGLGame(settings)
{
  renderer->setClearColour(ASGE::COLOURS::SLATEGRAY);
  inputs->use_threads = false;
  toggleFPS();

  /*
  // every game needs a good background
  menu_background = renderer->createRawSprite();
  menu_background->loadTexture("/data/images/menu.jpg");
  menu_background->width(static_cast<float>(ASGE::SETTINGS.window_width));
  menu_background->height(static_cast<float>(ASGE::SETTINGS.window_height));
   */

  // create a camera pointing at the mid-point of the screen
  camera = ASGE::Camera2D{ static_cast<float>(ASGE::SETTINGS.window_width),
                           static_cast<float>(ASGE::SETTINGS.window_height) };

  camera.lookAt(
    ASGE::Point2D{ static_cast<float>(-ASGE::SETTINGS.window_width) / 2.f,
                   static_cast<float>(-ASGE::SETTINGS.window_height) / 2.f });

  logStartup();
}

void ESDR::logStartup() const
{
  // these are just examples of the logging system.. you dont need to keep em
  std::ostringstream s{ "initialised complete" };
  Logging::ERRORS(s.str());
  Logging::WARN(s.str());
  Logging::INFO(s.str());
  Logging::DEBUG(s.str());
  Logging::TRACE(s.str());
  Logging::log(
    Logging::timestamp() + " \x1b[35;1m[CUSTOM]\x1b[0m " + s.str() + '\n');
}

/**
 *   @brief   Destructor.
 *   @details Remove any non-managed memory and callbacks.
 */
ESDR::~ESDR()
{
  delete menu_background;
  this->inputs->unregisterCallback(static_cast<unsigned int>(key_callback_id));

  this->inputs->unregisterCallback(
    static_cast<unsigned int>(mouse_callback_id));
}

/**
 *   @brief   Initialises the game.
 *   @details The game window is created and all assets required to
 *            run the game are loaded. The keyHandler and clickHandler
 *            callback should also be set in the initialise function.
 *   @return  True if the game initialised correctly.
 */
bool ESDR::init()
{
  key_callback_id =
    inputs->addCallbackFnc(ASGE::E_KEY, &ESDR::keyHandler, this);

  mouse_callback_id =
    inputs->addCallbackFnc(ASGE::E_MOUSE_CLICK, &ESDR::clickHandler, this);

  setupObjects();
  setupPositions();
  return true;
}

/**
 *   @brief   Processes any key inputs
 *   @details This function is added as a callback to handle the game's
 *            keyboard input. For this game, calls to this function
 *            are thread safe, so you may alter the game's state as
 *            you see fit.
 *   @param   data The event data relating to key input.
 *   @see     KeyEvent
 *   @return  void
 */
void ESDR::keyHandler(ASGE::SharedEventData data)
{
  auto key = static_cast<const ASGE::KeyEvent*>(data.get());

  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    signalExit();
  }

  if (in_menu)
  {
    if (key->key == ASGE::KEYS::KEY_ENTER)
    {
      in_menu = false;
    }
  }
  else
  {
    if (key->key == ASGE::KEYS::KEY_R)
    {
      in_menu = true;
    }
  }
}

/**
 *   @brief   Processes any click inputs
 *   @details This function is added as a callback to handle the game's
 *            mouse button input. For this game, calls to this function
 *            are thread safe, so you may alter the game's state as you
 *            see fit.
 *   @param   data The event data relating to key input.
 *   @see     ClickEvent
 *   @return  void
 */
void ESDR::clickHandler(ASGE::SharedEventData data)
{
  auto click = static_cast<const ASGE::ClickEvent*>(data.get());

  double x_pos = click->xpos;
  double y_pos = click->ypos;

  Logging::TRACE("x_pos: " + std::to_string(x_pos));
  Logging::TRACE("y_pos: " + std::to_string(y_pos));
}

/**
 *   @brief   Updates the scene
 *   @details Prepares the renderer subsystem before drawing the
 *            current frame. Once the current frame is has finished
 *            the buffers are swapped accordingly and the image shown.
 *   @return  void
 */
void ESDR::update(const ASGE::GameTime& game_time)
{
  // auto dt_sec = game_time.delta.count() / 1000.0;;
  // make sure you use delta time in any movement calculations!

  if (!in_menu)
  {
    camera.update(game_time);
  }
}

/**
 *   @brief   Renders the scene
 *   @details Renders all the game objects to the current frame.
 *            Once the current frame is has finished the buffers are
 *            swapped accordingly and the image shown.
 *   @return  void
 */
void ESDR::render()
{
  renderer->setFont(0);
  renderer->setProjectionMatrix(camera.getView());
  if (in_menu)
  {
    if (menu_background)
    {
      renderer->renderSprite(*menu_background);
    }
  }
}

void ESDR::setupObjects() {}

void ESDR::setupPositions() {}