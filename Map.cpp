#include "Map.h"
#include "Game.h"
#include "Sprite.h"
#include "MapEntities.h"
#include "EntityType.h"
#include "MapEntity.h"
#include "Hero.h"
#include "Globals.h"
#include "Surface.h"
#include "Pickable.h"
#include "Destructible.h"
#include "Enemy.h"
#include "Color.h"
#include "Camera.h"

#include <sstream>
#include <iostream>
#include <fstream>

Map::Map(Game& game) :
  game(&game),
  entities(NULL),
  tileset(NULL) {
    entities = new MapEntities(game, *this);
	camera = new Camera(*this);

	load_map();
	entities->display_tiles();
}

Map::~Map() {
	delete entities;
	delete camera;
	delete visible_surface;
}

void Map::load_map() {
	const std::string& map_name = "map.txt";
	std::ifstream file(map_name, std::ifstream::in);

	int x, y, map_width, map_height, tileset_id; 
	std::string line;

	// First line maps general information.
	std::getline(file, line);
	std::istringstream is(line);
	is >> x >> y >> map_width >> map_height >> tileset_id;
	
	location.set_size(map_width, map_height);
	location.set_xy(x, y);

	//set map size 8x8
	int map_width8 = map_width / 8;
	int map_height8 = map_height / 8;
	entities->set_map_size(map_width8, map_height8);

	visible_surface = new Surface(map_width, map_height);
	tileset = new TileSet(tileset_id);
	tileset->load();

	MapEntities& entities = get_entities();
	while(std::getline(file, line)) {
		std::istringstream iss(line);

		std::string token;
		std::getline(iss, token, '\t');
		int entity_type = std::atoi(token.c_str());

		MapEntity *entity = MapEntity::creation_functions[entity_type](*game, line);
		entity->set_map(*this);
		entities.add_entity(entity);
	}
	file.close();
}

int Map::get_width() {
	return this->location.get_width();
}

int Map::get_width8() {
	return get_width() / 8;
}

int Map::get_height() {
	return this->location.get_width();
}

int Map::get_height8() {
	return get_height() / 8;
}

Rectangle Map::get_location() {
	return location;
}

TileSet& Map::get_tileset() {
	return *this->tileset;
}

Surface& Map::get_visible_surface() {
	return *visible_surface;
}

MapEntities& Map::get_entities() {
	return *entities;
}

Game& Map::get_game() {
	return *game;
}

const Rectangle& Map::get_camera_position() {
	return camera->get_camera_position();
}

bool Map::test_collision_with_border(const Rectangle& collision_box) {
	return collision_box.get_x() < 0 
		|| collision_box.get_x() + collision_box.get_width() > get_width()
		|| collision_box.get_y() < 0
		|| collision_box.get_y() + collision_box.get_height() > get_height();
}

bool Map::test_collision_with_entities(const Rectangle& collision_box, MapEntity& check_entity) {
	std::list<MapEntity*>& obstacle_entities = entities->get_obstacle_entities();
	bool collision = false;
	
	std::list<MapEntity*>::iterator it;
	for(it = obstacle_entities.begin(); it != obstacle_entities.end() && !collision; it++) {
		MapEntity* entity = *it;
		collision = entity != &check_entity 
			&& entity->overlaps(collision_box) 
			&& entity->is_obstacle_for(check_entity);
	}
	return collision;
}

// Test if rectangle collides with map obstacles.
bool Map::test_collision_with_obstacles(const Rectangle& collision_box, MapEntity& check_entity) {
	bool collision = false;
	// collision with tiles
	int x1 = collision_box.get_x();
	int x2 = x1 + collision_box.get_width() - 1;
	int y1 = collision_box.get_y();
	int y2 = y1 + collision_box.get_height() - 1;
	
	for (int x = x1; x <= x2 && !collision; x++) {
		collision = test_collision_with_tiles(x1, y1, check_entity) ||
			test_collision_with_tiles(x, y2, check_entity);
	}

	for (int y = y1; y <= y2 && !collision; y++) {
		collision = test_collision_with_tiles(x1, y1, check_entity) ||
			test_collision_with_tiles(x2, y, check_entity);
	}

	// test collision with entities
	if(!collision) {
		collision = test_collision_with_entities(collision_box, check_entity);
	}
	return collision;
}

bool Map::test_collision_with_obstacles(int x, int y, MapEntity& check_entity) {
	bool collision;
	// test tiles
	collision = test_collision_with_tiles(x, y, check_entity);
	
	// test entities
	if(!collision) {
		Rectangle collision_box(x, y, 1, 1);
		collision = test_collision_with_entities(collision_box, check_entity);
	}
	return collision;
}

bool Map::test_collision_with_tiles(int x, int y, MapEntity& check_entity) {
	bool on_obstacle = false;
	// get obstacle property of the tile 
	Obstacle obstacle = entities->get_obstacle_tile(x, y);

	if(Obstacle::OBSTACLE == obstacle) {
		on_obstacle = true;
	}
	return on_obstacle;
}

void Map::check_collision_with_detectors(MapEntity& entity) {
	std::list<Detector*> detectors = entities->get_detectors();
	std::list<Detector*>::iterator detector;
	for(detector = detectors.begin(); detector != detectors.end(); detector++) {
		if(!(*detector)->is_removing()) {
			(*detector)->check_collision(entity);
		}
	}
}

void Map::check_collision_with_detectors(MapEntity& entity, Sprite& sprite) {
	std::list<Detector*> detectors = entities->get_detectors();
	std::list<Detector*>::iterator detector;
	for(detector = detectors.begin(); detector != detectors.end(); detector++) {
		if(!(*detector)->is_removing()) {
			(*detector)->check_collision(entity, sprite);
		}
	}
}


Ground Map::get_ground_tile(int x, int y) {
	return obstacle_to_ground(entities->get_obstacle_tile(x, y));
}

Ground Map::get_ground_tile(const Rectangle& coordinates) {
	return get_ground_tile(coordinates.get_x(), coordinates.get_y());
}

Ground Map::obstacle_to_ground(Obstacle obstacle) {
	Ground ground = Ground::NORMAL;
	switch(obstacle) {
		case Obstacle::OBSTACLE_HOLE:
			ground = Ground::HOLE;
			break;
		case Obstacle::OBSTACLE_NONE:
		case Obstacle::OBSTACLE:
			ground = Ground::NORMAL;
			break;
	}
	return ground;
}

void Map::update() {
	entities->update();
	camera->update();
}

void Map::display() {
	if(entities != NULL) {
		visible_surface->fill_with_color(Color::get_white());
		entities->display();
	}
}

void Map::display_sprite(Sprite& sprite, const Rectangle& xy) {
	display_sprite(sprite, xy.get_x(), xy.get_y());
}

void Map::display_sprite(Sprite& sprite, int x, int y) {
	const Rectangle& camera_position = get_camera_position();
	sprite.raw_display(*visible_surface, x - camera_position.get_x(), y - camera_position.get_y());
}