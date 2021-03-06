#include "GameState.h"
#include <algorithm>

GameState *GameState::instance = nullptr;

GameState *GameState::getInstance()
{
	if (instance == nullptr) {
		instance = new GameState();

		instance->fillBackgroundWithParticles();

		return instance;
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
	//fill with stars in bg
	fillBackgroundWithParticles();

	// move bg
	for (auto bgu = backgroundUnits.begin(); bgu != backgroundUnits.end(); bgu++) {
		(*bgu)->move();
	}

	//Move the dot
	dot.move();

	// move ammo
	for (auto ammo = playerAmmo.begin(); ammo != playerAmmo.end(); ammo++) {
		(*ammo)->move();
	}

	removeDead(backgroundUnits);
	removeDead(playerAmmo);
}

void GameState::render(SDL_Renderer* gRenderer)
{
	// render bg
	for (auto bgu = backgroundUnits.begin(); bgu != backgroundUnits.end(); bgu++) {
		(*bgu)->render(gRenderer);
	}

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

void GameState::fillBackgroundWithParticles()
{
	const int modX = (backgroundUnits.size() == 0) ? SCREEN_WIDTH : 20;

	for (int i = backgroundUnits.size(); i < 100; i++) {
		const int x = SCREEN_WIDTH - 20 + rand() % modX;
		const int y = rand() % SCREEN_HEIGHT;
		const int v = 12 + rand() % 5;
		const float a = 0;
		backgroundUnits.push_back(new StarParticle(x, y, -v, a));
	}
}

void GameState::removeDead(std::list<Dot *> &l)
{
	l.erase(
		std::remove_if(
			l.begin(),
			l.end(),
			[](Dot *d) {
				return d->mPosX > SCREEN_WIDTH || d->mPosX > SCREEN_WIDTH
					|| d->mPosX < 0 || d->mPosX < 0;
			}
		),
		l.end()
	);
}