#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <memory>

#include "Texture.h"

class Sprite{
	public:
		Sprite() noexcept;
		Sprite(SDL_Renderer* renderer, const std::string& fileName);
		Sprite(SDL_Renderer* renderer, const std::string& fileName, const std::string& extension);
		Sprite(SDL_Renderer* renderer, const std::string& fileName, const std::string& extension, unsigned int animation_begin, unsigned animation_end);

		// Copyable
		Sprite(Sprite& obj) noexcept;
		Sprite& operator=(Sprite& obj) noexcept;

		// Moveable
		Sprite(Sprite&& obj) noexcept;
		Sprite& operator=(Sprite&& obj) noexcept;
		
		//* Loads the file with the given name
		void load_single(SDL_Renderer* renderer, const std::string& fileName);
		//* Loops and loads all files with the given extension from *_0.ext to *_n.ext
		void load_multiple(SDL_Renderer* renderer, const std::string& fileName, const std::string& extension);

		//* Returns the count of internal textures
		unsigned int count() const noexcept;

		unsigned int get_index() const noexcept;
		void set_index(const unsigned int index);

		Texture& operator[](const unsigned int index) noexcept; 
		const Texture& operator[](const unsigned int index) const noexcept;

		Texture& at(const unsigned int index);
		const Texture& at(const unsigned int index) const;

		//* Draw the texure using custom parameters
		void draw_ext(SDL_Renderer* const renderer, const int x, const int y, const double& angle, const SDL_Point* const center, const SDL_RendererFlip& flip) const;
		//* Draws the texture
		void draw_raw(SDL_Renderer* const renderer, const int x, const int y) const;

		//* Set the dimensions of all the textures within the sprite
		void set_dimensions(const int w, const int h) noexcept;
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
		bool is_animating() const noexcept;
		bool is_animating_once() const noexcept;

		void set_depth(unsigned int depth);
		unsigned int get_depth() const;

	private:
		bool valid_texture_selection(const unsigned int pos) const noexcept;

		std::vector<std::unique_ptr<Texture>> textures;
		bool visable;

		//Animation variables
		mutable unsigned int sprite_index;
		unsigned int animation_begin;
		unsigned int animation_end;
		mutable bool animating_once;
		mutable bool animating;
};

#endif // SPRITE_H