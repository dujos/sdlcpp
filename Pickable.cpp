#include "Pickable.h"
#include "Hero.h"
#include "Sprite.h"
#include "System.h"
#include "Game.h"
#include "CollisionMode.h"
#include "Map.h"
#include <iostream>

Pickable::Pickable(Treasure& treasure, int x, int y) :
  Detector(CollisionMode::COLLISION_RECTANGLE, "", x, y, 0, 0),
  treasure(treasure),
  pickable(true) {
	this->init_sprites();
}

Pickable::~Pickable() {

}

MapEntity* Pickable::parse(Game& game, const std::string& line) {
	std::istringstream iss(line);
	
	int entity_type; int x; int y; std::string item_name;
	iss >> entity_type >> x >> y >> item_name;

	return new Pickable(Treasure(game, item_name), x, y);
}

bool Pickable::is_obstacle() {
	return false;
}

EntityType Pickable::get_entity_type() {
	return EntityType::PICKABLE;
}

void Pickable::init_sprites() {
	Sprite& item_sprite = create_sprite("pickables.txt");
	item_sprite.set_current_animation(treasure.get_item_name());
	item_sprite.set_current_direction(0);
	
	set_bounding_box(item_sprite);
}

void Pickable::notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode) {
	if(entity_overlapping.is_hero() && pickable) {
		remove_from_map();
		hero_pick_item();
	}
}

void Pickable::notify_collision(MapEntity& entity_overlapping, Sprite& other_sprite, Sprite& this_sprite) {}


void Pickable::hero_pick_item() {
	treasure.hero_take_treasure();
}