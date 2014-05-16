#include "GameObject.h"
#include <math.h>

const double PI = 3.14159265;

Particle::Particle(int x, int y)
{
	//Set offsets
	mPosX = x - 5 + (rand() % 40);
	mPosY = y - 5 + (rand() % 57);

	//Initialize animation
	mFrame = rand() % 5;

	//Set type
	switch (rand() % 3)
	{
	case 0: mTexture = &(TextureLoader::getInstance()->gRedTexture); break;
	case 1: mTexture = &(TextureLoader::getInstance()->gGreenTexture); break;
	case 2: mTexture = &(TextureLoader::getInstance()->gBlueTexture); break;
	}
}

void Particle::render(SDL_Renderer* gRenderer)
{
	//Show image
	mTexture->render(gRenderer, mPosX, mPosY);

	//Show shimmer
	if (mFrame % 2 == 0)
	{
		TextureLoader::getInstance()->gShimmerTexture.render(gRenderer, mPosX, mPosY);
	}

	//Animate
	mFrame++;
}

bool Particle::isDead()
{
	return mFrame > 10;
}

Dot::Dot()
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Initialize the target
	targetX = 0;
	targetY = 0;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	firePrimary = false;

	//Initialize particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		particles[i] = new Particle(mPosX, mPosY);
	}

	clock.start();
}

Dot::~Dot()
{
	//Delete particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		delete particles[i];
	}
}

void Dot::handleEvent(SDL_Event& e)
{
	//If mouse event happened 
	if (e.type == SDL_MOUSEMOTION) {
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
		targetX = x;
		targetY = y;
	}
	
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		firePrimary = true;
	}
	else if (e.type == SDL_MOUSEBUTTONUP) {
		firePrimary = false;
	}

	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: case SDLK_w: mVelY -= DOT_VEL; break;
		case SDLK_DOWN: case SDLK_s: mVelY += DOT_VEL; break;
		case SDLK_LEFT: case SDLK_a: mVelX -= DOT_VEL; break;
		case SDLK_RIGHT: case SDLK_d: mVelX += DOT_VEL; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: case SDLK_w: mVelY += DOT_VEL; break;
		case SDLK_DOWN: case SDLK_s: mVelY -= DOT_VEL; break;
		case SDLK_LEFT: case SDLK_a: mVelX += DOT_VEL; break;
		case SDLK_RIGHT: case SDLK_d: mVelX -= DOT_VEL; break;
		}
	}
}

void Dot::move()
{
	//Move the dot left or right
	mPosX += mVelX;

	//If the dot went too far to the left or right
	if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH))
	{
		//Move back
		mPosX -= mVelX;
	}

	//Move the dot up or down
	mPosY += mVelY;

	//If the dot went too far up or down
	if ((mPosY < 0) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT))
	{
		//Move back
		mPosY -= mVelY;
	}

	//fire
	const Uint32 toc = clock.getTicks();
	if ( (toc - firePrimaryLastTick) > firePrimaryCoolDown) {
		firePrimaryLastTick = toc;

		//create new instance of ammo
		Dot *ammo = new Dot();
	}
}

void Dot::render(SDL_Renderer* gRenderer)
{
	int row = 9 * (atan((targetY - mPosY) / (float)abs(mPosX - targetX)) + PI / 2.0) / PI;
	row = row > 0 ? row : 0;
	row = row < 9 ? row : 8;

	SDL_Rect gSpriteClip;
	gSpriteClip.x = 4;
	gSpriteClip.y = row*58 + 16;
	gSpriteClip.w = 40;
	gSpriteClip.h = 57;

	const SDL_RendererFlip flip = (mPosX > targetX) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	//Show the dot
	TextureLoader::getInstance()->gDotTexture.render(gRenderer, mPosX, mPosY, &gSpriteClip, 0.0, nullptr, flip);

	//Show particles on top of dot
	// renderParticles(gRenderer);
}

void Dot::renderParticles(SDL_Renderer * gRenderer)
{
	//Go through particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		//Delete and replace dead particles
		if (particles[i]->isDead())
		{
			delete particles[i];
			particles[i] = new Particle(mPosX, mPosY);
		}
	}

	//Show particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		particles[i]->render(gRenderer);
	}
}

Ammo::Ammo(int x, int y, int vel, float angle)
{

}

void Ammo::render(SDL_Renderer* gRenderer)
{
	SDL_Rect gSpriteClip;
	gSpriteClip.x = 231;
	gSpriteClip.y = 553;
	gSpriteClip.w = 14;
	gSpriteClip.h = 14;

	//Show the dot
	TextureLoader::getInstance()->gDotTexture.render(gRenderer, mPosX, mPosY, &gSpriteClip, 0.0, nullptr);

	//Show particles on top of dot
	renderParticles(gRenderer);
}