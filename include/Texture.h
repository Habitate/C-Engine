#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <memory>

//TODO: Add more concise exception definitions

class TextureData{
	public:
		TextureData(const SDL_Renderer* const renderer, const std::string& path) : 
		sprite(), dstRect{0, 0, 0, 0}, srcRect{0, 0, 0, 0), flip(SDL_FLIP_NONE), center{0, 0}
		angle(0){}

		//* Only supports paths with full extensions. E.x.: "image.png"
		TextureData(const SDL_Renderer* const renderer, const std::string& path) : 
		sprite(), dstRect{0, 0, 0, 0}, srcRect{0, 0, 0, 0), flip(SDL_FLIP_NONE), center{0, 0}
		angle(0){
			sprite = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(renderer, path.c_str()), SDL_DestroyTexture);
		
			if(!sprite){
				throw std::runtime_error("Failed to load sprite!");
			}

			SDL_QueryTexture(sprite.get(), nullptr, nullptr, &srcRect.w, &srcRect.h);
    		dstRect = srcRect;

			std::cout << Color(10) << "Successfully loaded sprite: \"" << Color(14) << path << Color(10) << "\"\n" << Color(7);
		}

		const SDL_Rect& getSrcRect() const noexcept{
			return srcRect;
		}
		const SDL_Rect& getDstRect() const noexcept{
			return dstRect;
		}
		SDL_Rect& getSrcRect() noexcept{
			return srcRect;
		}
		SDL_Rect& getDstRect() noexcept{
			return dstRect;
		}

		void setWidth(const int width) noexcept{
			dstRect.w = width;
		}
		void setHeight(const int width) noexcept{
			dstRect.w = width;
		}

		void setSize(const int width, const int height) noexcept{
			dstRect.w = width;
			dstRect.h = height;
		}

		bool good() const noexcept{
			return (bool)sprite;
		}

		void draw_ex(SDL_Renderer* const renderer, const int x, const int y, const double angle, const SDL_Point* const center, const SDL_RendererFlip flip) const noexcept{
			if(!sprite){
				throw std::runtime_error("Attempted to draw an uninitialized sprite!");
			}

			dstRect.x = x;
			dstRect.y = y;

			SDL_RenderCopyEx(renderer, sprite.get(), &srcRect, &dstRect, angle, center, flip);
		}

		void draw(SDL_Renderer* const renderer, const int x, const int y) const noexcept{
			if(!sprite){
				throw std::runtime_error("Attempted to draw an uninitialized sprite!");
			}

			dstRect.x = x;
			dstRect.y = y;

			SDL_RenderCopy(renderer, sprite.get(), &srcRect, &dstRect);
		}

	private:
		std::shared_ptr<SDL_Texture> sprite;

		mutable SDL_Rect dstRect;
		SDL_Rect srcRect;

		SDL_RendererFlip flip;
		SDL_Point center;
		double angle;
};

class Texture{
	public:
		Texture();

		//* Supports various path 
		void load(SDL_Renderer* renderer, std::string path);
		
		unsigned int getIndex();
		void setIndex(const unsigned int index);

		unsigned int count() const noexcept;
		bool good() const noexcept; //! Good if the first sprite is valid

		//* If setAll is set to true, index is ignored
		//* Pass -1 to w or h to retain the current size
		void setSize(unsigned int index, int w, int h, bool setAll = false);

		void draw(SDL_Renderer* renderer, const int x, const int y);

		//* Pass -1 to the index to get rect @ spriteIndex
		SDL_Rect& getSrcRect(unsigned int index, bool getCurrent = true);
		const SDL_Rect& getSrcRect(unsigned int index, bool getCurrent = true) const;

		//* Pass -1 to the index to get rect @ spriteIndex
		SDL_Rect& getDstRect(unsigned int index, bool getCurrent = true);
		const SDL_Rect& getDstRect(unsigned int index, bool getCurrent = true) const;

		void startAnimation();
		void stopAnimation();
		void resetAnimation();
		void runAnimationOnce();

	//private:
		//* Loads the file with the given name
		void SingleLoad (SDL_Renderer* renderer, const std::string& fileName);
		
		//* Loops and loads all files with the given extension starting with x_0.ext to x_n.ext
		void MultiLoad  (SDL_Renderer* renderer, const std::string& fileName, const std::string& extension);

		std::vector<std::shared_ptr<TextureData>> sprites;
		unsigned int spriteIndex;
		bool visable;

		unsigned int animationStartIndex;
		bool animating;
		bool animatingOnce;
};

#endif