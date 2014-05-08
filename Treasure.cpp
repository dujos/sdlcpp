#include "Surface.h"
#include "Game.h"
#include "Treasure.h"
#include "Map.h"
#include "Sprite.h"
#include "Counter.h"

const std::string Treasure::treasure_names[] = {
	"rupee_green", 
	"rupee_blue", 
	"rupee_red", 
	"heart"
};

Treasure::Treasure(Game& game, std::string item_name) :
  game(&game),
  item_name(item_name),
  sprite(NULL) {
}

Treasure::~Treasure() {
	delete sprite;
}

// Return equipment item depending on this treasures content(item name).
Item& Treasure::get_equipment_item() const {
	return game->get_equipment().get_item(get_item_name());
}

const std::string& Treasure::get_item_name() const {
	return item_name;
}

// Add item to hero's equipment.
void Treasure::hero_take_treasure() const {
	Equipment& equipment = game->get_equipment();
	equipment.add_item(get_item_name());
}

// Display the treasure.
void Treasure::display(Surface& dst_surface, int x, int y) {
	if(sprite == NULL) {
		sprite = new Sprite("pickables.txt");
		sprite->set_current_animation(item_name);
		sprite->set_current_direction(0);
	}
	sprite->raw_display(dst_surface, Rectangle(x, y));
}