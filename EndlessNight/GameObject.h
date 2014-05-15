#ifndef GameObject_h
#define GameObject_h

#include "ExternalLibs.h"
#include "Textures.h"

//Particle count
const int TOTAL_PARTICLES = 20;

class Particle
{
public:
	//Initialize position and animation
	Particle(int x, int y);

	//Shows the particle
	void render(SDL_Renderer* gRenderer);

	//Checks if particle is dead
	bool isDead();

private:
	//Offsets
	int mPosX, mPosY;

	//Current frame of animation
	int mFrame;

	//Type of particle
	LTexture *mTexture;
};

//The dot that will move around on the screen
class Dot
{
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 10;

	//Initializes the variables and allocates particles
	Dot();

	//Deallocates particles
	~Dot();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move();

	//Shows the dot on the screen
	void render(SDL_Renderer* gRenderer);

private:
	//The particles
	Particle* particles[TOTAL_PARTICLES];

	//Shows the particles
	void renderParticles(SDL_Renderer * gRenderer);

	//The X and Y offsets of the dot
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;
};

#endif