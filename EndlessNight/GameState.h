#ifndef GameState_h
#define GameState_h

#include "ExternalLibs.h"
#include "GameObject.h"
#include <list>
#include <string>
#include <sstream>

class GameState
{
public:
	static GameState *getInstance();
	~GameState();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move();

	//Shows the dot on the screen
	void render(SDL_Renderer* gRenderer);

	void renderFPS(SDL_Renderer* gRenderer);

	//--------------------------------------------------------------
	//The dot that will be moving around on the screen
	Dot dot;

	// collision lists
	std::list<Dot *> playerAmmo;
	std::list<Dot *> enemies;
	std::list<Dot *> backgroundUnits;

private:
	//--------------------------------------------------------------
	//fps stuff
	//Set text color as black
	SDL_Color textColor;

	//The frames per second timer
	LTimer fpsTimer;

	//Start counting frames per second
	int countedFrames = 0;

	//In memory text stream
	std::stringstream timeText;

	//Calculate and correct fps
	float avgFPS = 0;

	//--------------------------------------------------------------
	// utils
	void fillBackgroundWithParticles();
	void removeDead(std::list<Dot *> &l);

	//--------------------------------------------------------------
	// design
	static GameState *instance;

	GameState();
	GameState(const GameState&) = delete;
	GameState & operator=(const GameState&) = delete;
};


#endif