/** 
 * @file
 * @brief Class @ref ASGE::Renderer
 */

#pragma once

#include "Engine/Colours.h"
#include "Engine/Texture.h"
#include "GameSettings.hpp"
#include "Text.hpp"
#include "Viewport.hpp"
#include <memory>
#include <string>

namespace ASGE {

	namespace SHADER_LIB
	{
		class  Shader;
	}

	struct Font;
	class  Input;
	class  Sprite;

	/**
	*  @brief the renderer used in the game.
	*  
	*  The renderer is the heart and sole of the engine. 
	*  It's responsible for managing rendering, shaders
	*  input initialisation, the window etc. This class
	*  defines the interface that all platform specific
	*  renders must utilise. This allows renderers to be
	*  replaced easily if their interface matches. The 
	*  platform specific renders may use batching or 
	*  texture caching but this is not enforced.
	*/
	class Renderer
	{

	public:

//		/**
//		*  The renderer (platform) type.
//		*/
//		enum class RenderLib
//		{
//			INVALID = -1,  /**< Invalid engine. There is a serious issue here. */
//			LEGACY_GL = 1, /**< OGL 3.3 supported rendering. */
//      MODERN_GL = 2  /**< Modern OGL engine require 4.5+. */
//		}; RenderLib getRenderLibrary() noexcept;

	public:

		/**
		*  The constructor.
		*  The constructor must be provided with the type
		*  of renderer that is going to be used in the game.
		*  @param render_lib the renderer library being used.
		*/
   Renderer() = default;

		/**
		*  Default destructor.
		*/
		virtual ~Renderer() = default;

		/**
		*  Sets the clear colour.
		*  This colour will be used to clear the window
		*  on every update. Allowing a clean slate before
		*  performing the next render.
		*  @param rgb A RGB defined colour to use for clearing.
		*  @see Colour
		*/
		virtual void setClearColour(Colour rgb) = 0;

		/**
		*  Loads a font that can be used to render text
		*  @param font The filepath to the font file.
		*  @param pt The size of the font to use in atlas generation.
		*  @return The loaded font index.
		*/
		virtual int loadFont(const char* font, int pt) = 0;

		/**
		*  Loads a font that can be used to render text
		*  @param name The name of the font. 
		*  @param data A binary font loaded in memory.
		*  @param size The buffer size. 
		*  @param pt The size of the font to use in atlas generation.
		*  @return The loaded font index.
		*/
		virtual int loadFontFromMem(const char* name, const unsigned char* data, unsigned int size, int pt) = 0;

		/**
		*  Initialises the renderer. 
		*  Performs all the initialisation of the renderer, its
		*  framework and the window creation.
		*  @param w The width of the window in pixels. 
		*  @param h The height of the window in pixels.
		*  @param mode Should the window launch in fullscreen.
		*  @return True if success.
		*  @see WindowMode
		*/
		virtual bool init() = 0;

		/**
		*  Exits the renderer and performs clean-up. 
		*  @return True if achieved gracefully.
		*/
		virtual bool exit() = 0;

		/**
		*  Sets the pre render environment.
		*  Can be used amongst other things to reset render
		*  settings and to clear the screen.
		*/
		virtual void preRender() = 0;

		/**
		*  Sets the post render environment.
		*  Can be used amongst other things to update OSD
		*  settings and to flush batched render calls.
		*/
		virtual void postRender() = 0;

		/**
		*  Renders a string to the screen.
		*  @deprecated since 2.0
		*  @see RenderString
		*  @param [in] str The text to render.
		*  @param [in] x The text position in the X axis.
		*  @param [in] y The text starting position in the Y axis.
		*  @param [in] colour The colour to use for rendering.
		*/
		void renderText(std::string str, int x, int y, const Colour& colour);

		/**
		*  Renders a string to the screen.
		*  @deprecated since 2.0
		*  @see RenderString
		*  @param [in] str The text to render.
		*  @param [in] x The text position in the X axis.
		*  @param [in] y The text starting position in the Y axis.
		*/
		void renderText(std::string str, int x, int y);

    virtual void renderText(Text&&) = 0;
    virtual void renderText(const Text&) = 0;

		/**
		*  Sets the default text colour. 
		*  When rendering text, if a colour is not specificed
		*  the default one will be used instead. This can be set
		*  using this function.
		*  @param colour The colour to use.
		*/
		virtual void setDefaultTextColour(const Colour& colour) = 0;

		/**
		*  Locates a shader using its ID.
		*  Shaders are stored/cached so to prevent dangling pointers
		*  handle's can be used to retrieve the shader. It is recommended
		*  not to store the returned shader as it's memory location could
	    *  change over time.
		*  @param shader_handle The shader to find.
		*/
		virtual SHADER_LIB::Shader* findShader(int shader_handle) = 0;

		/**
		*  Returns the currently active font. 
		*  When rendering text, if a colour is not specificed
		*  the default one will be used instead. This can be set
		*  using this function.
		*  @return Font The font currently being used by the renderer.
		*  @see Font
		*/
		[[nodiscard]] virtual const Font& getDefaultFont() const = 0;

    /**
    *  Returns a font.
    *  When loading fonts they will be assigned an index, you can
    *  retrieve the font using its index to access additional
    *  font related functionality
    *  @param idx The loaded font index
    *  @return Font The font stored in idx otherwise current loaded
    *  @see Font
    */
    virtual const Font& getFont(int idx) const = 0;

		/**
		*  Sets the currently active font.
		*  In order for this to work, a valid id must be provided. 
		*  The ID is returned from the load font function, so it
		*  is advisable to keep a record of it. 
		*  @param id The index of the font to use (must be loaded).
		*/
		virtual void setFont(int id) = 0;

		/**
		*  Renders a sprite to the screen.
		*  All the rendering params are stored within the 
		*  sprite class itself.
		*  @param [in] sprite A reference to the sprite to render.
		*  @see Sprite
		*/
		virtual void renderSprite(const Sprite& sprite) = 0;

		/**
		*  Sets the sprite rendering mode. Useful for batching.
		*  @param mode The SpriteSortMode used for rendering.
		*  @see SpriteSortMode
		*/
		virtual void setSpriteMode(SpriteSortMode mode) = 0;

		/**
		*  Attempts to enable the requested window mode.
		*  Will only swap if the mode is different and will
		*  attempt to perform this operation gracefully as
		*  possible. 
		*  @param mode The requested window mode.
		*/
		virtual void setWindowedMode(GameSettings::WindowMode mode) = 0;

		/**
		*  Sets the window title.
		*  @param str The name of the window.
		*/
		virtual void setWindowTitle(const char* str) = 0;

		/**
		*  Tells the graphics subsystem to swap buffers.
		*/
		virtual void swapBuffers() = 0;

		/**
		*  Creates an input system, linked to the renderer.
		*  @return A uniquely owned input system.
		*/
		virtual std::unique_ptr<Input> inputPtr() = 0;

		/**
		*  Creates a new Sprite using ownership semantics.
		*  The sprite will be auto-deallocated when it falls
		*  out of scope, so be careful where to store it. 
		*  @return A uniquely owned sprite.
		*/
		virtual std::unique_ptr<Sprite> createUniqueSprite() = 0;

		/**
		*  Creates a new Sprite using the heap.
		*  The sprite will be leaked when it falls
		*  out of scope, so needs to be manually freed.
		*  @return A dynamically allocated sprite.
		*/
		virtual Sprite*	createRawSprite() = 0;

    virtual ASGE::Texture2D*
    createNonCachedTexture(int width, int height, ASGE::Texture2D::Format, void* data) = 0;

    virtual ASGE::Texture2D* createCachedTexture(
      std::string id, int width, int height, ASGE::Texture2D::Format, void* data) = 0;

    int initPixelShaderFromFile(std::string filename);
    virtual int  initPixelShader(std::string shader) = 0;
		virtual void setActiveShader(ASGE::SHADER_LIB::Shader*) = 0;

    GameSettings::WindowMode getWindowMode() noexcept;

    [[nodiscard]] virtual unsigned int windowHeight()  const noexcept = 0;
    [[nodiscard]] virtual unsigned int windowWidth()   const noexcept = 0;

    virtual SHADER_LIB::Shader* getShader() = 0;
    virtual void setProjectionMatrix(float camera_x, float camera_y, float width, float height) = 0;
    virtual void setProjectionMatrix(const Viewport& view) = 0;

	protected:
		GameSettings::WindowMode window_mode = GameSettings::WindowMode::WINDOWED; /**< The window mode being used. */
		//RenderLib lib = RenderLib::INVALID; /**< The renderer being used. */
		Colour cls = COLOURS::STEELBLUE; /**< The clear colour. Used to blank the window every redraw. */
		Colour default_text_colour = COLOURS::YELLOWGREEN; /**< The default text colour. Used when no colour is specified. */
	};
}