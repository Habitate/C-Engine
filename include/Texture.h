#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <memory>

//TODO: Add more concise exception definitions

class TextureData{
	public:
		TextureData();

		//* Only supports paths with full extensions. E.x.: "image.png"
		TextureData(SDL_Renderer* const renderer, const std::string& path);

		// Copyable
		TextureData(TextureData& obj);
		TextureData& operator=(TextureData& obj);

		// Moveable
		TextureData(TextureData&& obj);
		TextureData& operator=(TextureData&& obj);

		void setWidth(const int width) noexcept;
		void setHeight(const int width) noexcept;
		void setDimensions(const int width, const int height) noexcept;

		//* Syncs dstRect dimensions with those of srcRect
		void resetDimensions() noexcept;

		//* Draw the texure using custom parameters
		void draw_ext(SDL_Renderer* const renderer, const int x, const int y, const double& angle, const SDL_Point& center, const SDL_RendererFlip& flip) const;
		//* Draws the texture without taking the flip, center and angle into consideration
		void draw_raw(SDL_Renderer* const renderer, const int x, const int y) const;
		//* Draws the texture using the last known coordinates
		void draw_static(SDL_Renderer* const renderer) const;

		//TODO: Implement
		bool check_collision(const TextureData& sprite) const noexcept;

		//* Returns if the sprite is not null
		bool good() const noexcept;

	private:
		std::shared_ptr<SDL_Texture> sprite;
		mutable SDL_Rect dstRect;
		SDL_Rect srcRect;
};

class Sprite{
	public:
		Sprite();
		
		//* Loads the file with the given name
		void load_single(SDL_Renderer* renderer, const std::string& fileName);
		//* Loops and loads all files with the given extension starting with *_0.ext to *_n.ext
		void load_multiple(SDL_Renderer* renderer, const std::string& fileName, const std::string& extension);

		unsigned int count() const noexcept;

		void draw(SDL_Renderer* renderer, const int x, const int y);

		//* If setAll is set to true, index is ignored
		//* Pass -1 to w or h to retain the current size
		void setDimensions(unsigned int index, int w, int h, bool setAll = false);

		void setWidth(const int width) noexcept;
		void setHeight(const int width) noexcept;
		void setDimensions(const int width, const int height) noexcept;

		//Animation control
		void runAnimation_once() const noexcept;
		void runAnimation_continous() const noexcept;

		void stopAnimation() const noexcept;
		void resetAnimation() const noexcept;

		unsigned int getIndex() const noexcept;
		void setIndex(const unsigned int index);

		//Animation bounds
		void setAnimationBounds(unsigned int lower, unsigned int upper);
		void setAnimationBound_upper(unsigned int bound);
		void setAnimationBound_lower(unsigned int bound);

	private:
		std::vector<std::unique_ptr<TextureData>> textures;
		bool visable;

		//Animation variables
		unsigned int lower_animation_bound;
		unsigned int upper_animation_bound;
		unsigned int sprite_index;
		bool animating_once;
		bool animating;
};

#endif