#ifndef Textures_h
#define Textures_h

#include "ExternalLibs.h"

//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer* gRenderer, Uint8 r=0x0, Uint8 g=0xff, Uint8 b=0xff);

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

class TextureLoader
{
public:
	static TextureLoader *getInstance();
	~TextureLoader();

	//Loads media
	bool loadMedia(SDL_Renderer *gRenderer);

	//Scene textures
	LTexture gDotTexture;
	LTexture gRedTexture;
	LTexture gGreenTexture;
	LTexture gBlueTexture;
	LTexture gShimmerTexture;

private:
	static TextureLoader *instance;

	TextureLoader() = default;
	TextureLoader(const TextureLoader&) = delete;
	TextureLoader & operator=(const TextureLoader&) = delete;

};

#endif