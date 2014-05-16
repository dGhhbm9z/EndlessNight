#include "GameState.h"

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
	playerAmmo.reserve(100);
	enemies.reserve(30);
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
}

void GameState::render(SDL_Renderer* gRenderer)
{
	//Render objects
	dot.render(gRenderer);
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