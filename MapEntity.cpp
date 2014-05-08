#include "Bubble.h"
#include "Chest.h"
#include "Destructible.h"
#include "Enemy.h"
#include "Geometry.h"
#include "Game.h"
#include "Hero.h"
#include "Jumper.h"
#include "MapEntities.h"
#include "MapEntity.h"
#include "Movement.h"
#include "Map.h"
#include "Pickable.h"
#include "Sprite.h"
#include "System.h"
#include "Sensor.h"
#include "SpriteAnimationSet.h"
#include "Tile.h"

#include <iostream>

MapEntity::CreationFunction* MapEntity::creation_functions[] = {
  Pickable::parse,
  Destructible::parse,
  Enemy::parse,
  Sensor::parse,
  Tile::parse,
  Jumper::parse,
  Chest::parse,
};

const Rectangle MapEntity::directions_to_move[] = {
	Rectangle( 1,  0),
	Rectangle( 1,  1),
	Rectangle( 0,  1),
	Rectangle(-1,  1),
	Rectangle(-1,  0),
	Rectangle(-1, -1),
	Rectangle( 0, -1),
	Rectangle( 1, -1),

};

MapEntity::MapEntity() :
  map(NULL),
  name(""),
  bounding_box(0, 0),
  current_direction(0),
  movement(NULL),
  removing(false) {
	origin.set_xy(0, 0);
	set_size(0, 0);
}

MapEntity::MapEntity(const std::string &name, int dir, int x, int y, int width, int height) :
  map(NULL),
  name(name),
  bounding_box(x, y),
  current_direction(dir),
  movement(NULL),
  removing(false) {
	origin.set_xy(0, 0);
	set_size(width, height);
}

MapEntity::MapEntity(int x, int y, int width, int height) :
  map(NULL),
  name(""),
  bounding_box(x, y),
  current_direction(0),
  movement(NULL),
  removing(false) {
	origin.set_xy(0, 0);
	set_size(width, height);
}

MapEntity::~MapEntity() {
	clear_movement();
	clear_old_movements();
	clear_sprites();
	clear_old_sprites();
}

void MapEntity::remove_from_map() {
	get_map().get_entities().remove_entity(this);
}

void MapEntity::notify_removing() {
	this->removing = true;
}

bool MapEntity::is_removing() {
	return this->removing;
}

bool MapEntity::is_detector() {
	return false;
}

bool MapEntity::is_obstacle() {
	return true;
}

bool MapEntity::is_tile() {
	return false;
}

MapEntities& MapEntity::get_entities() {
	return map->get_entities();
}

Hero& MapEntity::get_hero() {
	return get_entities().get_hero();
}

Game& MapEntity::get_game() {
	return map->get_game();
}

Map& MapEntity::get_map() {
	return *map;
}

std::list<Sprite*>& MapEntity::get_sprites() {
	return sprites;
}

Sprite& MapEntity::create_sprite(const std::string& animation_set_id) {
	Sprite* sprite = new Sprite(animation_set_id);
	sprites.push_back(sprite);
	return *sprite;
}

Sprite& MapEntity::get_sprite() {
	return *sprites.front();
}

void MapEntity::remove_sprite(Sprite& sprite) {
	std::list<Sprite*>::iterator it;
	for(it = sprites.begin(); it != sprites.end(); it++) {
		if(*it == &sprite) {
			old_sprites.push_back(&sprite);
		}
	}
}

void MapEntity::clear_sprites() {
	old_sprites = sprites;
	sprites.clear();
}

void MapEntity::clear_old_sprites() {
	std::list<Sprite*>::iterator it;
	for(it = old_sprites.begin(); it != old_sprites.end(); it++) {
		Sprite* sprite = *it;
		sprites.remove(sprite);
		delete sprite;
	}
	old_sprites.clear();
}

void MapEntity::clear_old_movements() {
	std::list<Movement*>::iterator it;
	for(it = old_movements.begin(); it != old_movements.end(); it++) {
		Movement* movement = *it;
		delete movement;
	}
	old_movements.clear();
}

Movement* MapEntity::get_movement() {
	return movement;
}

void MapEntity::set_movement(Movement* movement) {
	this->movement = movement;
	if(movement != NULL) {
		movement->set_entity(this);
	}
}

void MapEntity::clear_movement() {
	if(movement != NULL) {
		movement->set_entity(NULL);
		old_movements.push_back(movement);
		movement = NULL;
	}
}

void MapEntity::notify_movement_finished() {}

void MapEntity::notify_position_changed() {
	get_map().check_collision_with_detectors(*this);
}

void MapEntity::notify_movement_changed() {}

void MapEntity::notify_obstacle_reached() {}

void MapEntity::set_sprites_to_map(Map& map) {
	std::list<Sprite*>::iterator it;
	for(it = sprites.begin(); it != sprites.end(); it++) {
		Sprite* sprite = *it;
		sprite->set_map(map);
	}
}

void MapEntity::set_map(Map& map) {
	this->map = &map;
	if (&get_game().get_map() == &map) {
		set_sprites_to_map(map);
	}
}

bool MapEntity::is_on_map() {
	return map != NULL;
}

void MapEntity::set_direction(int dir) {
	this->current_direction = dir;
}

void MapEntity::set_size(const Rectangle &rec) {
	bounding_box.set_size(rec);
}

void MapEntity::set_size(int width, int height) {
	bounding_box.set_size(width, height);
}

void MapEntity::set_origin(const Rectangle &rec) {
	set_origin(rec.get_x(), rec.get_y());
}

void MapEntity::set_origin(int x, int y) {
	bounding_box.move_xy(origin.get_x() - x, origin.get_y() - y);
	origin.set_xy(x, y);
}

int MapEntity::get_x() {
	return bounding_box.get_x() + origin.get_x();
}

int MapEntity::get_y() {
	return bounding_box.get_y() + origin.get_y();
}

const Rectangle MapEntity::get_xy() {
	return Rectangle(get_x(), get_y());
}

void MapEntity::set_x(int x) {
	bounding_box.set_x(x - origin.get_x());
}

void MapEntity::set_y(int y) {
	bounding_box.set_y(y- origin.get_y());
}

void MapEntity::set_xy(int x, int y) {
	set_x(x);
	set_y(y);
}

void MapEntity::set_xy(const Rectangle &rec) {
	set_xy(rec.get_x(), rec.get_y());
}

void MapEntity::set_bounding_box(const Rectangle &bounding_box) {
	this->bounding_box = bounding_box;
}

void MapEntity::set_bounding_box_from_sprite() {
	Sprite& sprite = this->get_sprite();
	this->set_size(sprite.get_size());
	this->set_origin(sprite.get_origin());
}

Rectangle MapEntity::get_bounding_box() {
	return this->bounding_box;
}

void MapEntity::set_bounding_box(Sprite& sprite) {
	set_size(sprite.get_size());
	set_origin(sprite.get_origin());
}

int MapEntity::get_width() {
	return bounding_box.get_width();
}

int MapEntity::get_height() {
	return bounding_box.get_height();
}

const Rectangle& MapEntity::get_size() {
	return this->bounding_box;
}

const Rectangle& MapEntity::get_origin() {
	return this->origin;
}

const Rectangle MapEntity::get_center_point() {
	return bounding_box.get_center();
}

int MapEntity::get_direction() {
	return this->current_direction;
}

const std::string& MapEntity::get_name() const {
	return this->name;
}

const Rectangle MapEntity::get_displayed_xy() {
	return get_xy();
}

bool MapEntity::overlaps(int x, int y) {
	return bounding_box.contains(x, y);
}

bool MapEntity::overlaps(const Rectangle &rec) {
	return bounding_box.overlaps(rec);
}

bool MapEntity::overlaps(MapEntity& entity) {
	return overlaps(entity.get_bounding_box());
}

int MapEntity::get_distance(int x, int y) {
	return (int) Geometry::get_distance(get_x(), get_y(), x, y);
}

int MapEntity::get_distance(MapEntity& other) {
	return (int) Geometry::get_distance(get_x(), get_y(), 
		other.get_x(), other.get_y());
}

bool MapEntity::is_obstacle_for(MapEntity& other) {
	return false;
}

bool MapEntity::is_hero_obstacle(Hero& hero) {
	return false;
}

bool MapEntity::is_destructible_obstacle(Destructible& destructible) {
	return true;
}

bool MapEntity::is_enemy_obstacle(Enemy& enemy) {
	return false;
}

bool MapEntity::is_jumper_obstacle(Jumper& jumper) {
	return true;
}

bool MapEntity::is_hero() {
	return this->get_entity_type() == EntityType::HERO;
}

bool MapEntity::is_enemy() {
	return this->get_entity_type() == EntityType::ENEMY;
}

void MapEntity::check_collision_with_detectors() {
	get_map().check_collision_with_detectors(*this);
}

void MapEntity::check_collision_with_detectors(Sprite& sprite) {
	get_map().check_collision_with_detectors(*this, sprite);
}

void MapEntity::notify_collision_with_enemy(Enemy& enemy) {}

void MapEntity::notify_collision_with_enemy(Enemy& enemy, Sprite& enemy_sprite, Sprite& this_sprite) {}

void MapEntity::notify_collision_with_bubble(Bubble& bubble) {}

void MapEntity::notify_collision_with_destructible(Destructible& destructible) {}

void MapEntity::notify_collision_with_sensor(Sensor& sensor) {}

void MapEntity::notify_collision_with_jumper(Jumper& jumper) {}

void MapEntity::notify_collision_with_fire(Fire& fire) {}

void MapEntity::notify_collision_with_chest(Chest& chest) {}

void MapEntity::notify_sprite_frame_changed(Sprite& sprite, const std::string& current_animation, int frame) {}

void MapEntity::update() {
	std::list<Sprite*>::iterator it;
	for(it = sprites.begin(); it != sprites.end(); it++) {
		Sprite* sprite = *it;
		sprite->update();
		notify_sprite_frame_changed(*sprite, 
			sprite->get_current_animation_name(), sprite->get_current_frame());
	}
	clear_old_sprites();
	
	if(movement != NULL) {
		movement->update();
	}
	clear_old_movements();
}

void MapEntity::display_on_map() {
	Map& map = get_map();
	std::list<Sprite*>::iterator it;
	for(it = sprites.begin(); it != sprites.end(); it++) {
		Sprite& sprite = *(*it);
		map.display_sprite(sprite, get_displayed_xy());
	}
}