#ifndef GameObject_h
#define GameObject_h

#include "ExternalLibs.h"
#include "Textures.h"
#include "GameTimers.h"

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
	//Maximum axis velocity of the dot
	static const int DOT_VEL = 6;

	//Initializes the variables and allocates particles
	Dot();

	//Deallocates particles
	~Dot();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	virtual void move();

	//Shows the dot on the screen
	virtual void render(SDL_Renderer* gRenderer);

	//The X and Y offsets of the dot
	int mPosX, mPosY;

protected:
	//The dimensions of the dot
	const int DOT_WIDTH = 40;
	const int DOT_HEIGHT = 57;

	//The particles
	Particle* particles[TOTAL_PARTICLES];

	//Shows the particles
	void renderParticles(SDL_Renderer * gRenderer);

	int targetX, targetY;

	//The velocity of the dot
	int mVelX, mVelY;

	bool isDead;

private:
	bool firePrimary;
	float firePrimaryCoolDown;
	Uint32 firePrimaryLastTick;

	bool fireSecondary;
	float fireSecondaryCoolDown;
	Uint32 fireSecondaryLastTick;

	LTimer clock;
};

class Ammo : public Dot
{
public:
	Ammo(int x, int y, int vel, float f);
	//Moves the dot
	virtual void move() override;
	virtual void render(SDL_Renderer* gRenderer) override;

private:
	float angle;
};

class StarParticle : public Dot
{
public:
	StarParticle(int x, int y, int vel, float angle);
	//Moves the dot
	virtual void move() override;
	virtual void render(SDL_Renderer* gRenderer) override;

private:
	Uint8 alpha;
};

#endif