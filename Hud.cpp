#include "Hud.h"
#include "Game.h"
#include "RupeeHud.h"
#include "Hero.h"

Hud::Hud(Game& game) :
  game(game),
  nb_elements(1) {
    elements[0] = new RupeeHud(game, RUPEE_HUD_X,
	    RUPEE_HUD_Y, RUPEE_HUD_WIDTH, RUPEE_HUD_HEIGHT);
}

Hud::~Hud() {
	for(int i = 0; i < nb_elements; i++) {
		delete elements[i];
	}
}

void Hud::update() {
	elements[0]->set_visible(true);

	for(int i = 0; i < nb_elements; i++) {
		if(elements[i] != NULL) {
		    elements[i]->update();
		}
	}
}

void Hud::display(Surface& dst_surface) {
	for(int i = 0; i < nb_elements; i++) {
		if(elements[i] != NULL) {
		    elements[i]->display(dst_surface);
		}
	}
}