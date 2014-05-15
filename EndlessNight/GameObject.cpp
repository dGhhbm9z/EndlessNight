#include "GameObject.h"

Particle::Particle(int x, int y)
{
	//Set offsets
	mPosX = x - 5 + (rand() % 25);
	mPosY = y - 5 + (rand() % 25);

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

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	//Initialize particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		particles[i] = new Particle(mPosX, mPosY);
	}
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
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY -= DOT_VEL; break;
		case SDLK_DOWN: mVelY += DOT_VEL; break;
		case SDLK_LEFT: mVelX -= DOT_VEL; break;
		case SDLK_RIGHT: mVelX += DOT_VEL; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY += DOT_VEL; break;
		case SDLK_DOWN: mVelY -= DOT_VEL; break;
		case SDLK_LEFT: mVelX += DOT_VEL; break;
		case SDLK_RIGHT: mVelX -= DOT_VEL; break;
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
}

void Dot::render(SDL_Renderer* gRenderer)
{
	//Show the dot
	TextureLoader::getInstance()->gDotTexture.render(gRenderer, mPosX, mPosY);

	//Show particles on top of dot
	renderParticles(gRenderer);
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