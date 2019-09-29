#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <array>
#include "camera.h"
#include "drawable.h"

class Texture : public Drawable{
	public:
		static const std::array<std::string, 17> SUPPORTED_DATA_TYPES;

		explicit Texture() noexcept;
		//* Only supports paths with full extensions. E.x.: "image.png"
		explicit Texture(SDL_Renderer* const renderer, const std::string& path);

		// Copyable
		explicit Texture(const Texture& obj) noexcept;
		Texture& operator=(const Texture& obj) noexcept;

		// Moveable
		explicit Texture(Texture&& obj) noexcept;
		Texture& operator=(Texture&& obj) noexcept;

		~Texture() override;

		//*----------------------------------------------------

		void load(const std::string& path);

		void set_renderer(SDL_Renderer* const renderer) override;

		//* Set the dimensions
		void set_width(const int width) noexcept;
		void set_height(const int width) noexcept;
		void set_dimensions(const int width, const int height) noexcept;

		//* Syncs dstRect dimensions with those of srcRect
		void reset_width() noexcept;
		void reset_height() noexcept;
		void reset_dimensions() noexcept;

		void draw(const Camera& camera = {}, const SDL_Point& coords = {0, 0}, const double& angle = 0, const SDL_Point* const center = nullptr, const SDL_RendererFlip& flip = SDL_FLIP_NONE) const override;

		[[nodiscard]] bool check_collision(const Texture& texture) const noexcept;

		[[nodiscard]] const SDL_Rect& get_src_rect() const noexcept;
		[[nodiscard]] const SDL_Rect& get_dst_rect() const noexcept;

		[[nodiscard]] bool good() const noexcept;

	private:
		std::shared_ptr<SDL_Texture> imageData;
		mutable SDL_Rect dstRect;
		SDL_Rect srcRect;
};
