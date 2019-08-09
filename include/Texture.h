#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <array>

class Texture{
	public:
		Texture() noexcept;

		//* Only supports paths with full extensions. E.x.: "image.png"
		Texture(SDL_Renderer* const renderer, const std::string& path);

		~Texture();

		// Copyable
		Texture(Texture& obj) noexcept;
		Texture& operator=(Texture& obj) noexcept;

		// Moveable
		Texture(Texture&& obj) noexcept;
		Texture& operator=(Texture&& obj) noexcept;

		void load(SDL_Renderer* const renderer, const std::string& path);

		//* Set the dimensions
		void set_width(const int width) noexcept;
		void set_height(const int width) noexcept;
		void set_dimensions(const int width, const int height) noexcept;

		//* Syncs dstRect dimensions with those of srcRect
		void reset_width() noexcept;
		void reset_height() noexcept;
		void reset_dimensions() noexcept;

		//* Draw the texure using custom parameters
		void draw_ext(SDL_Renderer* const renderer, const int x, const int y, const double& angle, const SDL_Point* const center, const SDL_RendererFlip& flip) const;
		//* Draws the texture
		void draw_raw(SDL_Renderer* const renderer, const int x, const int y) const;

		bool check_collision(const Texture& texture) const noexcept;

		const SDL_Rect& get_src_rect() const noexcept;
		const SDL_Rect& get_dst_rect() const noexcept;

		bool good() const noexcept;

		static std::array<std::string, 17> SUPPORTED_DATA_TYPES;

	private:
		std::shared_ptr<SDL_Texture> imageData;
		mutable SDL_Rect dstRect;
		SDL_Rect srcRect;
};

#endif // TEXTURE_H