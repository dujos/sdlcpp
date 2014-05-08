#include "Bubble.h"
#include "CollisionMode.h"
#include "Enemy.h"
#include "Fire.h"
#include "Game.h"
#include "Geometry.h"
#include "Map.h"
#include "MapEntities.h"
#include "RedKnightSoldier.h"
#include "SpriteAnimationSet.h"
#include "StraightMovement.h"
#include "System.h"

#include <iostream>

Enemy::Enemy(const std::string& name, int x, int y) :
  Detector(CollisionMode::COLLISION_RECTANGLE, name, x, y, 0, 0),
  life(10),
  damage_taken(false) {

}

Enemy::~Enemy() {}

MapEntity* Enemy::parse(Game& game, const std::string& line) {
	std::istringstream iss(line);

	std::string name; int entity_type; int enemy_type; int x; int y;
	iss >> entity_type >> x >> y >> name >> enemy_type;

	if(enemy_type == Enemy::EnemyType::BUBBLE) {
		return new Bubble(name, x, y, game);
	} else if(enemy_type == Enemy::EnemyType::FIRE) {
		return new Fire(name, x, y, game);
	} else if(enemy_type == Enemy::EnemyType::RED_KNIGHT_SOLDIER) {
		return new RedKnightSoldier(name, x, y, game);
	}
}

EntityType Enemy::get_entity_type() {
	return EntityType::ENEMY;
}

void Enemy::destroy_enemy() {
	clear_movement();
	clear_sprites();
	create_sprite("enemy_killed.txt");
	get_sprite().set_current_animation("killed");
}

bool Enemy::is_destroyed() {
	if(life <= 0 && get_sprite().get_current_animation_name() == "killed")
		return true;
	return false;
}

bool Enemy::is_dying_animation_finished() {
	return get_sprite().is_animation_finished();
}

bool Enemy::is_damage_taken() {
	return damage_taken;
}

void Enemy::damage_enemy() {
	this->damage_taken = true;
	this->life = 0;
}

void Enemy::notify_movement_finished() {
	Detector::notify_movement_finished();
}

void Enemy::notify_position_changed() {
	Detector::notify_position_changed();
}

void Enemy::notify_movement_changed() {
	Detector::notify_movement_changed();
}

void Enemy::notify_obstacle_reached() {
	Detector::notify_obstacle_reached();
}

bool Enemy::is_obstacle_for(MapEntity& other) {
	return other.is_enemy_obstacle(*this);
}

bool Enemy::is_destructible_obstacle(Destructible& destructible) {
	return true;
}

void Enemy::notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode) {
	entity_overlapping.notify_collision_with_enemy(*this);
}

void Enemy::notify_collision(MapEntity& entity_overlapping, Sprite& other_overlapping, Sprite& this_overlapping) {
	entity_overlapping.notify_collision_with_enemy(*this);
}

void Enemy::update() {
	Detector::update();
}

void Enemy::display_on_map() {
	Detector::display_on_map();
}
