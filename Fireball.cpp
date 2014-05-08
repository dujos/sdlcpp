#include "StraightMovement.h"
#include "RedKnightSoldier.h"
#include "Destructible.h"
#include "Fireball.h"
#include "System.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Hero.h"
#include "Game.h"
#include "Map.h"

Fireball::Fireball(Hero& hero, int speed) :
  MapEntity(),
  hero(hero),
  speed(speed),
  collision(false) {
	int direction = hero.get_animation_direction();
	Sprite& sprite = create_sprite("fireball.txt");
	sprite.set_current_direction(direction);
	set_xy(hero.get_center_point());
	set_bounding_box_from_sprite();

	Movement* movement = new StraightMovement(get_angle(direction), 150);
	set_movement(movement);

	disapear_date = System::now() + 2000;
}

Fireball::~Fireball() {}

int Fireball::get_angle(int direction4) {
	if(direction4 % 4 == 0) {
		return 0;
	} else if(direction4 % 4 == 1) {
		return 90;
	} else if(direction4 % 4 == 2) {
		return 180;
	} else if(direction4 % 4 == 3) {
		return 270;
	}
}

EntityType Fireball::get_entity_type() {
	return EntityType::FIREBALL;
}

void Fireball::update() {
	MapEntity::update();

	check_collision_with_detectors();
	
	float now = System::now();
	
	if(collision || has_reached_border() || now >= disapear_date) {
		clear_movement();
		remove_from_map();
	}
}

bool Fireball::has_reached_border() {
	return get_map().test_collision_with_border(this->get_bounding_box());
}

void Fireball::notify_collision_with_destructible(Destructible& destructible) {
	this->collision = true;
}

void Fireball::notify_collision_with_enemy(Enemy& enemy, Sprite& enemy_sprite, Sprite& this_sprite) {}

void Fireball::notify_collision_with_enemy(Enemy& enemy) {
	this->collision = true;
	enemy.damage_enemy();
}
