#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <memory>

class TextureData{
	public:
		TextureData();

		//* Only supports paths like "assets/myImage.png"
		void Load(SDL_Renderer* renderer, std::string path);
		void Draw(SDL_Renderer* renderer, int x, int y);

		//* Pass -1 to w or h to retain the current size
		void ChangeSize(int w, int h);

		bool Good();

		//SDL_Texture* sprite;
		std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> sprite;

		SDL_Rect srcRect;
		SDL_Rect dstRect;

		bool visable;
};

class Texture{
	public:
		Texture();

		void Load       (SDL_Renderer* renderer, std::string path                           );
		void SingleLoad (SDL_Renderer* renderer, std::string fileName                       );
		void MultiLoad  (SDL_Renderer* renderer, std::string fileName, std::string extension);

		int getSpriteCount();

		//! Returns good if, atleast, the first sprite is valid
		bool Good();

		//* Pass -1 to w or h to retain the current size
		//* Pass -1 to index to change all sprites
		void ChangeSize(int index, int w, int h);
		void Draw(SDL_Renderer* renderer, int x, int y);

		std::vector<std::shared_ptr<TextureData>> sprites;

		int spriteIndex;
		bool visable;
};

#endif