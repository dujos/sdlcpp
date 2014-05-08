#ifndef HUD_H
#define HUD_H

#include "Type.h"

class Hud {

private:
	Game& game;
	int nb_elements;
	HudElement* elements[1];

public:
	Hud(Game& game);
	~Hud();

	void update();
	void display(Surface& dst_surface);
};

#endif