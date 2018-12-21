#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>

class Texture{
	public:
		Texture();
		~Texture();

		//* Only supports paths like "assets/myImage.png"
		void Load(SDL_Renderer* renderer, std::string path);
		void Draw(SDL_Renderer* renderer, int x, int y);

		//* Pass -1 to w or h to retain the current size
		void ChangeSize(int w, int h);

		SDL_Texture* sprite;
		SDL_Rect srcRect;
		SDL_Rect dstRect;

		bool good;
		bool visable;
};

class MultiTexture{
	public:
		MultiTexture();
		~MultiTexture();

		//* Only supports paths like "assets/myImage"
		void Load(SDL_Renderer*, std::string path);
		void Draw(SDL_Renderer*, int x, int y);

		//* Pass -1 to w or h to retain the current size
		//* Pass -1 to index to change all sprites
		void ChangeSize(int index, int w, int h);

		std::vector<Texture*> sprites;
		SDL_Rect srcRect;
		SDL_Rect dstRect;

		int spriteIndex;
		int spriteCount;
		int timeFrame;

		bool visable;
};

#endif