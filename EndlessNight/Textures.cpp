#include "Textures.h"

//====================================================================================
// LTexture

LTexture::LTexture()
{
	//Initialize
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;

	gFont = TTF_OpenFont("Resources/lazy.ttf", 18);
	if (gFont == nullptr)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer, Uint8 r, Uint8 g, Uint8 b)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, r, g, b));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText(SDL_Renderer *gRenderer, std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	if (!gFont) {
		return false;
	}

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}


//====================================================================================
// TextureLoader

TextureLoader *TextureLoader::instance = nullptr;

TextureLoader *TextureLoader::getInstance()
{
	if (instance == nullptr) {
		return instance = new TextureLoader();
	}

	return instance;
}

TextureLoader::~TextureLoader()
{
	//Free loaded images
	gDotTexture.free();
	gRedTexture.free();
	gGreenTexture.free();
	gBlueTexture.free();
	gShimmerTexture.free();
}

bool TextureLoader::loadMedia(SDL_Renderer *gRenderer)
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if (!gDotTexture.loadFromFile("Resources/havoc.bmp", gRenderer, 32, 200, 248))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	if (!gSparkleTexture.loadFromFile("Resources/sparkle.bmp", gRenderer, 32, 200, 248))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	if (!gCoronaTexture.loadFromFile("Resources/corona.bmp", gRenderer, 32, 200, 248))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	if (!gNovaTexture.loadFromFile("Resources/nova.bmp", gRenderer, 32, 200, 248))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	//Load red texture
	if (!gRedTexture.loadFromFile("38_particle_engines/red.bmp", gRenderer))
	{
		printf("Failed to load red texture!\n");
		success = false;
	}

	//Load green texture
	if (!gGreenTexture.loadFromFile("38_particle_engines/green.bmp", gRenderer))
	{
		printf("Failed to load green texture!\n");
		success = false;
	}

	//Load blue texture
	if (!gBlueTexture.loadFromFile("38_particle_engines/blue.bmp", gRenderer))
	{
		printf("Failed to load blue texture!\n");
		success = false;
	}

	//Load shimmer texture
	if (!gShimmerTexture.loadFromFile("38_particle_engines/shimmer.bmp", gRenderer))
	{
		printf("Failed to load shimmer texture!\n");
		success = false;
	}

	//Set texture transparency
	gRedTexture.setAlpha(192);
	gGreenTexture.setAlpha(192);
	gBlueTexture.setAlpha(192);
	gShimmerTexture.setAlpha(192);

	return success;
}