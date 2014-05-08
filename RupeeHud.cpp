#include "Surface.h"
#include "Game.h"
#include "RupeeHud.h"
#include "Sprite.h"
#include "Counter.h"

RupeeHud::RupeeHud(Game& game, int x, int y, int width, int height) :
  HudElement(game, x, y, width, height),
  counter(NULL) {
    image_rupee = new Surface("rupee.png");
	this->counter_value_displayed = -1;
	counter = new Counter(3, 14, 1);
	rebuild();
}

RupeeHud::~RupeeHud() {
	delete this->image_rupee;
	if(counter != NULL) {
	    delete this->counter;
	}
}

bool RupeeHud::is_visible() {
	return HudElement::is_visible();
}

void RupeeHud::rebuild() {
	HudElement::rebuild();
	if(counter != NULL) {
		Rectangle src_position(0, 0, 12, 12);
		Rectangle dst_position(0, 0);
		image_rupee->display_region(src_position, surface_displayed, dst_position);
		counter->display(surface_displayed);
	}
}

void RupeeHud::update() {
	HudElement::update();
	
	int green = equipment->get_item("rupee_green").get_current_amount();
	int blue = equipment->get_item("rupee_blue").get_current_amount();
	int red = equipment->get_item("rupee_red").get_current_amount();
	counter->set_value(green + blue + red);
	rebuild();
}