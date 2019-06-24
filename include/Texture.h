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

		void load(SDL_Renderer* renderer, std::string path);
		
		void getIndex();
		void setIndex();

		int count() const;
		bool good() const; //! Good if first sprite is valid

		//* Pass -1 to w or h to retain the current size
		//* Pass -1 to index to change all sprites
		void setSize(int index, int w, int h);

		void draw(SDL_Renderer* renderer, int x, int y);

		//* Negative values will return the current sprite @ spriteIndex
		SDL_Rect& getSrcRect(int index = -1);
		SDL_Rect& getDstRect(int index = -1);


	private:
		void SingleLoad (SDL_Renderer* renderer, const std::string& fileName                       );
		void MultiLoad  (SDL_Renderer* renderer, const std::string& fileName, const std::string& extension);

		std::vector<std::shared_ptr<TextureData>> sprites;
		int spriteIndex;
		bool visable;
};

#endif