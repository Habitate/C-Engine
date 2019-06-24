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
		void draw(SDL_Renderer* renderer, int x, int y);
		
		//* Pass -1 to w or h to retain the current size
		void setSize(int w, int h);
		bool good();

		std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> sprite;

		SDL_Rect srcRect;
		SDL_Rect dstRect;

		bool visable;
};

class Texture{
	public:
		Texture();

		//* Supports various path 
		void load(SDL_Renderer* renderer, std::string path);
		
		int getIndex();
		void setIndex(const int index);

		int count() const;
		bool good() const; //! Good if the first sprite is valid

		//* Pass -1 to index to change all sprites
		//* Pass -1 to w or h to retain the current size
		void setSize(int index, int w, int h);

		void draw(SDL_Renderer* renderer, int x, int y);

		//* Pass -1 to the index to get rect @ spriteIndex
		SDL_Rect& getSrcRect(int index = -1);

		//* Pass -1 to the index to get rect @ spriteIndex
		SDL_Rect& getDstRect(int index = -1);

		void startAnimation();
		void stopAnimation();
		void resetAnimation();
		void runAnimationOnce();

		int animationStartIndex;
		bool animating;
		bool animatingOnce;

	private:
		//* Loads the file with the given extension
		void SingleLoad (SDL_Renderer* renderer, const std::string& fileName                       );
		
		//* Loops and loads all files with the given extension starting with x_0.ext to x_n.ext
		void MultiLoad  (SDL_Renderer* renderer, const std::string& fileName, const std::string& extension);

		std::vector<std::shared_ptr<TextureData>> sprites;
		int spriteIndex;
		bool visable;
		
};

#endif