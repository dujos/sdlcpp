#include "Jumper.h"
#include "Hero.h"
#include "Sprite.h"
#include "Game.h"
#include "Map.h"

Jumper::Jumper(const std::string& name, int x, int y, int direction) :
	Detector(COLLISION_RECTANGLE, name, x, y, 0, 0) {
	
	set_direction(direction);
	init_sprites();
}

Jumper::~Jumper() {}

MapEntity* Jumper::parse(Game& game, const std::string& line) {
	std::istringstream iss(line);
	
	int entity_type; int x; int y; std::string name; int direction;
	iss >> entity_type >> x >> y >> name >> direction;

	return new Jumper(name, x, y, direction);
}

EntityType Jumper::get_entity_type() {
	return EntityType::JUMPER;
}

void Jumper::init_sprites() {
	Sprite& sprite = create_sprite("jumper.txt");
	sprite.set_current_animation("jumper");
	sprite.set_current_direction(0);
	set_bounding_box_from_sprite();
}

void Jumper::notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode) {
	entity_overlapping.notify_collision_with_jumper(*this);
}