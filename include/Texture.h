#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <memory>

class TextureData{
	public:
		//* Only supports paths like "assets/myImage.png"
		TextureData(SDL_Renderer* renderer, std::string path);
		void draw(SDL_Renderer* renderer, const int x, const int y, const double angle, const SDL_Point* center, const SDL_RendererFlip flip);
		
		//* Pass -1 to w or h to retain the current size
		void setSize(int w, int h);
		bool good();

		std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> sprite;

		SDL_Rect srcRect;
		SDL_Rect dstRect;
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

		double angle;
		SDL_Point center;
		SDL_RendererFlip flip;

		unsigned int animationStartIndex;
		bool animating;
		bool animatingOnce;
};

#endif