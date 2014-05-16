#include "GameState.h"
#include <algorithm>

GameState *GameState::instance = nullptr;

GameState *GameState::getInstance()
{
	if (instance == nullptr) {
		return instance = new GameState();
	}

	return instance;
}

GameState::GameState() : textColor({ 0xFF, 0xFF, 0xFF, 0xFF })
{
	fpsTimer.start();
}

GameState::~GameState()
{
	fpsTimer.stop();
}

void GameState::handleEvent(SDL_Event& e)
{
	//Handle input for the dot
	dot.handleEvent(e);
}

void GameState::move()
{
	//Move the dot
	dot.move();

	// render ammo
	for (auto ammo = playerAmmo.begin(); ammo != playerAmmo.end(); ammo++) {
		(*ammo)->move();
	}

	playerAmmo.erase(
			std::remove_if(
				playerAmmo.begin(),
				playerAmmo.end(),
				[](Dot *d) {
					return d->mPosX > SCREEN_WIDTH || d->mPosX > SCREEN_WIDTH 
						|| d->mPosX < 0 || d->mPosX < 0;
				}
			),
			playerAmmo.end()
		);


}

void GameState::render(SDL_Renderer* gRenderer)
{
	//Render objects
	dot.render(gRenderer);

	// render ammo
	for (auto ammo = playerAmmo.begin(); ammo != playerAmmo.end(); ammo++) {
		(*ammo)->render(gRenderer);
	}
}

void GameState::renderFPS(SDL_Renderer* gRenderer)
{
	avgFPS = 0.5f*avgFPS + 0.5f*(countedFrames / (fpsTimer.getTicks() / 1000.f));

	//Set text to be rendered
	timeText.str("");
	timeText << "Average Frames Per Second " << avgFPS;

	//Render text
	if (!TextureLoader::getInstance()->gFPSTextTexture.loadFromRenderedText(gRenderer, timeText.str().c_str(), textColor))
	{
		printf("Unable to render FPS texture!\n");
	}

	TextureLoader::getInstance()->gFPSTextTexture.render(gRenderer, 0, (SCREEN_HEIGHT - TextureLoader::getInstance()->gFPSTextTexture.getHeight()));

	++countedFrames;
}