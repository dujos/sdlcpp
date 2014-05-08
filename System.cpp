#include "Color.h"
#include "InputEvent.h"
#include "Random.h"
#include "System.h"
#include "Sprite.h"
#include "VideoManager.h"

uint32_t System::ticks = 0;

void System::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	Color::init();
	InputEvent::init();
	Random::init();
	VideoManager::init();
}

void System::quit() {
	Sprite::quit();
	VideoManager::quit();
	Color::quit();
	//TextSurface::quit();
	SDL_Quit();
}

void System::update() {
	ticks = SDL_GetTicks();
}

uint32_t System::now() {
	return ticks;
}

void System::sleep(uint32_t duration) {
	SDL_Delay(duration);
}