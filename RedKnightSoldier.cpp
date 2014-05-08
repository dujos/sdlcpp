#include "Geometry.h"
#include "Game.h"
#include "Hero.h"
#include "Map.h"
#include "MapEntities.h"
#include "Movement.h"
#include "Pickable.h"
#include "RedKnightSoldier.h"
#include "RandomMovement.h"
#include "Sprite.h"
#include "Treasure.h"


RedKnightSoldier::RedKnightSoldier(const std::string& name, int x, int y, Game& game) :
  Enemy(name, x, y),
  moving_speed(0),
  game(game) {
  
	soldier_sprite = &create_sprite("red_knight_soldier.txt");
	soldier_sprite->set_current_animation("walking");
	soldier_sprite->set_current_direction(0);
	set_direction(0);
	set_bounding_box(*soldier_sprite);

	soldier_sword_sprite = &create_sprite("red_knight_soldier_sword.txt");
	soldier_sword_sprite->set_current_animation("walking");
	soldier_sword_sprite->set_current_direction(0);
	set_direction(0);
	set_bounding_box(*soldier_sword_sprite);

	set_movement(new RandomMovement(20, 600));
}

RedKnightSoldier::~RedKnightSoldier() {
}

void RedKnightSoldier::set_animation(const std::string& animation) {
	std::list<Sprite*>::iterator it;
	for(it = get_sprites().begin(); it != get_sprites().end(); it++) {
		(*it)->set_current_animation(animation);
	}
}

int RedKnightSoldier::get_animation_direction() {
	return get_sprite().get_current_direction();
}

void RedKnightSoldier::notify_movement_changed() {
	RandomMovement* enemy_movement = (RandomMovement*)get_movement();
	int direction8 = enemy_movement->get_current_direction8();
	int old_animation_drirection = get_animation_direction();
	int animation_direction = get_sprite().get_current_animation_direction(direction8);
	if(old_animation_drirection != animation_direction && animation_direction != -1) {
		soldier_sprite->set_current_direction(animation_direction);
		soldier_sword_sprite->set_current_direction(animation_direction);
		set_direction(direction8);
	}
}

void RedKnightSoldier::notify_obstacle_reached() {
	Detector::notify_obstacle_reached();
}

void RedKnightSoldier::notify_collision(MapEntity& entity, CollisionMode collision_mode) {
	entity.notify_collision_with_enemy(*this);
}

void RedKnightSoldier::update() {
	Enemy::update();
	if(damage_taken) {
		damage_taken = false;
		if(life <= 0)
			destroy_enemy();
	}
	if(is_destroyed() && is_dying_animation_finished()) {
		get_entities().add_entity(new Pickable(Treasure(get_game(), 
			Treasure::treasure_names[Treasure::RUPEE_BLUE]), get_x(), get_y()));
		remove_from_map();
	}
}