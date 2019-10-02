#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <array>
#include "camera.h"
#include "drawable.h"

class Image : public Drawable{
	public:
		explicit Image() noexcept;
		//* Only supports paths with full extensions. E.x.: "image.png"
		explicit Image(SDL_Renderer* const renderer, const std::string& path);

		// Copyable
		explicit Image(const Image& obj) noexcept;
		Image& operator=(const Image& obj) noexcept;

		// Moveable
		explicit Image(Image&& obj) noexcept;
		Image& operator=(Image&& obj) noexcept;

		~Image() override;

		//*----------------------------------------------------

		void load(const std::string& path);

		void set_renderer(SDL_Renderer* const renderer) override;

		//* Set the dimensions
		void set_dimensions(const int width, const int height) noexcept;
		void set_width(const int width) noexcept;
		void set_height(const int height) noexcept;

		//* Syncs dstRect dimensions with those of srcRect
		void reset_dimensions() noexcept;
		void reset_width() noexcept;
		void reset_height() noexcept;

		void draw(const Camera& camera = {}, const SDL_Point& coords = {0, 0}, const double& angle = 0, const SDL_Point* const center = nullptr, const SDL_RendererFlip& flip = SDL_FLIP_NONE) const override;

		[[nodiscard]] const SDL_Rect& get_src_rect() const noexcept;
		[[nodiscard]] const SDL_Rect& get_dst_rect() const noexcept;

		[[nodiscard]] bool good() const noexcept;

	private:
		std::shared_ptr<SDL_Texture> texture;
		mutable SDL_Rect dstRect;
		SDL_Rect srcRect;
};
