#include "Destructible.h"
#include "Hero.h"
#include "MapEntities.h"
#include "System.h"
#include "Game.h"
#include "Map.h"
#include "Sprite.h"

const Destructible::Properties Destructible::properties[] = {
	{"pot", "pot.txt"},
	{"bush", "bush.txt"},
	{"white_stone", "stone_white.txt"},
	{"black_stone", "stone_black.txt"}
};

Destructible::Destructible(const std::string& name, int x, int y, DestructibleType type) :
  Detector(CollisionMode::COLLISION_NONE | CollisionMode::COLLISION_CENTER,
	 name, x, y, 16, 16),
  type(type) {
	create_sprite(get_animation_set_id());
	set_bounding_box_from_sprite();
}

Destructible::~Destructible() {

}

MapEntity* Destructible::parse(Game& game, const std::string& line) {
	std::istringstream iss(line);

	int entity_type; int x; int y; std::string name; int type;
	iss >> entity_type >> x >> y >> name >> type;

	return new Destructible(name, x, y, (DestructibleType)type);
}

EntityType Destructible::get_entity_type() {
	return EntityType::DESTRUCTIBLE;
}

const std::string& Destructible::get_animation_set_id() {
	return properties[type].animation_set_id;
}

bool Destructible::is_obstacle_for(MapEntity& other) {
	return true;
}

void Destructible::notify_collision(MapEntity& entity, CollisionMode collision_mode) {
	entity.notify_collision_with_destructible(*this);
}

void Destructible::update() {
	MapEntity::update();
}