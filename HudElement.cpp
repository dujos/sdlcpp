#include "HudElement.h"
#include "Game.h"
#include "System.h"
#include "Color.h"

HudElement::HudElement(Game& game, int x, int y, int width, int height) :
  game(&game),
  equipment(&game.get_equipment()),
  surface_displayed(width, height),
  visible(true),
  opacity(255) {
    set_position(x, y);
}

HudElement::~HudElement() {}

void HudElement::set_visible(bool visible) {
	this->visible = visible;
}

void HudElement::set_position(int x, int y) {
	dst_position.set_xy(x, y);
}

void HudElement::set_opacity(int opacity) {
	if(this->opacity != opacity) {
		this->opacity = opacity;
		surface_displayed.set_opacity(opacity);
		rebuild();
	}
}

bool HudElement::is_visible() {
	return this->visible;
}

void HudElement::rebuild() {

}

void HudElement::update() {

}

void HudElement::display(Surface& dst_surface) {
	if(is_visible()) {
		surface_displayed.display(dst_surface, dst_position);
		surface_displayed.fill_with_color(Color::get_white());
	}
}