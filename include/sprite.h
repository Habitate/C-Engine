#pragma once

#include <vector>
#include <memory>

#include "Image.h"
#include "camera.h"

#include "drawable.h"

class Sprite : Drawable{
	public:
		Sprite() noexcept;
		explicit Sprite(SDL_Renderer* const renderer, const std::string& fileName);
		explicit Sprite(SDL_Renderer* const renderer, const std::string& fileName, const std::string& extension);
		explicit Sprite(SDL_Renderer* const renderer, const std::string& fileName, const std::string& extension, unsigned int animation_begin, unsigned animation_end);

		// Copyable
		explicit Sprite(const Sprite& obj);
		Sprite& operator=(const Sprite& obj);

		// Moveable
		explicit Sprite(Sprite&& obj) noexcept;
		Sprite& operator=(Sprite&& obj) noexcept;
		
		~Sprite() noexcept;

		//*----------------------------------------------------

		//* Loads the file with the given name
		void load_single(SDL_Renderer* const renderer, const std::string& fileName);
		//* Loops and loads all files with the given extension from *_0.ext to *_n.ext
		void load_multiple(SDL_Renderer* const renderer, const std::string& fileName, const std::string& extension);

		//* Returns the count of internal textures
		[[nodiscard]] unsigned int count() const noexcept;

		[[nodiscard]] unsigned int get_index() const noexcept;
		void set_index(const unsigned int index);

		void draw(const Camera& camera = {}, const SDL_Point& coords = {0, 0}, const double& angle = 0, const SDL_Point* const center = nullptr, const SDL_RendererFlip& flip = SDL_FLIP_NONE) const override;

		//* Set the dimensions of all the textures within the sprite
		void set_dimensions(const int width, const int height) noexcept;
		void set_width(const int width) noexcept;
		void set_height(const int height) noexcept;

		void reset_dimensions() noexcept;
		void reset_width() noexcept;
		void reset_height() noexcept;

		//Animation control
		//* Automatically used to advance the animation, can be used manually to skip frames
		void iterate() const noexcept;
		void animate_once() const noexcept;
		void animate_continuos() const noexcept;

		void stop_animating() const noexcept;
		void reset_animation() const noexcept;

		//Animation bounds
		void set_animation_range(unsigned int begin, unsigned int end);
		void set_animation_begin(unsigned int begin);
		void set_animation_end(unsigned int end);

		//Animation info
		[[nodiscard]] bool is_animating() const noexcept;
		[[nodiscard]] bool is_animating_once() const noexcept;

		//* Checks if every single internal image is valid
		[[nodiscard]] bool good() const noexcept;
		
	private:
		[[nodiscard]] bool is_valid_texture_selection(const unsigned int pos) const noexcept;

		std::vector<std::shared_ptr<SDL_Texture>> textures;

		SDL_Rect src_rect;
		mutable SDL_Rect dst_rect;

		//Animation variables
		mutable unsigned int sprite_index;
		unsigned int animation_begin;
		unsigned int animation_end;
		mutable bool animating_once;
		mutable bool animating;
};
