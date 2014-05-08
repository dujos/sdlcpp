#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL.h>

class System {

private:
	static uint32_t ticks;

public:
	static void init();
	static void quit();
	static void update();

	static uint32_t now();
	static void sleep(uint32_t duration);
};

#endif