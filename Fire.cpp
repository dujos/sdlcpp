#include "TargetMovement.h"
#include "MapEntities.h"
#include "Sprite.h"
#include "Fire.h"
#include "Game.h"
#include "Map.h"

Fire::Fire(const std::string& fire_name, int x, int y, Game& game):
  Enemy("fire", x, y),
  game(game) {

	fire_sprite = &create_sprite("fire.txt");
	fire_sprite->set_current_animation("burning");
	fire_sprite->set_current_direction(0);
	set_bounding_box_from_sprite();

	set_movement(NULL);
}

Fire::~Fire() {}

EntityType Fire::get_entity_type() {
	return EntityType::FIRE;
}

void Fire::notify_collision(MapEntity& entity, CollisionMode collision_mode) {
	entity.notify_collision_with_fire(*this);
}

void Fire::update() {
	Enemy::update();
	check_collision_with_detectors();
}
