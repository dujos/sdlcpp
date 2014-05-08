#include "MapEntities.h"
#include "TilePattern.h"
#include "Obstacle.h"
#include "Surface.h"
#include "Hero.h"
#include "Tile.h"
#include "Game.h"
#include "Map.h"

MapEntities::MapEntities(Game& game, Map& map) :
  game(game),
  map(map),
  hero(game.get_hero()),
  tile_surfaces(NULL) {
	  this->obstacle_entities.push_back(&hero);
}

MapEntities::~MapEntities() {
	destroy_all_entities();
}

Hero& MapEntities::get_hero() {
	return hero;
}

Obstacle MapEntities::get_obstacle_tile(int x, int y) {
	int y8 = y / 8;
	int x8 = x / 8;
	int index = y8 * map_width8 + x8;
	
	return obstacle_tiles[index];
}

std::list<MapEntity*>& MapEntities::get_obstacle_entities() {
	return this->obstacle_entities;
}

std::list<Detector*>& MapEntities::get_detectors() {
	return this->detector_entities;
}

void MapEntities::set_obstacle(int x8, int y8, Obstacle obstacle) {
	if(x8 >= 0 && x8 <= map_width8 && y8 >= 0 && y8 <= map_height8) {
		int index = y8 * map_width8 + x8;
		obstacle_tiles[index] = obstacle;
	}
}

void MapEntities::set_map_size(int mw8, int mh8) {
	this->map_width8 = mw8;
	this->map_height8 = mh8;
}

void MapEntities::add_tile(Tile* tile) {
	tile_entities.push_back(tile);
	tile->set_map(map);

	Obstacle obstacle = tile->get_tile_pattern().get_obstacle();

	int tile_x8 = tile->get_x() / 8;
	int tile_y8 = tile->get_y() / 8;
	int tile_width8 = tile->get_width() / 8;
	int tile_height8 = tile->get_height() / 8;

	for(int i = 0; i < tile_height8; i++) {
		for(int j = 0; j < tile_width8; j++) {
			set_obstacle(tile_x8 + j, tile_y8 + i, obstacle);
		}
	}
}

void MapEntities::add_entity(MapEntity* entity) {
	if(entity == NULL) {
		return;
	}
	if(entity->is_tile()) {
		add_tile(static_cast<Tile*> (entity));
	} else {
		if(entity->is_detector()) {
			this->detector_entities.push_back(static_cast<Detector*>(entity));
		}	
		if(entity->is_obstacle()) {
			this->obstacle_entities.push_back(entity);
		}
	}
	this->all_entities.push_back(entity);

	entity->set_map(map);
}

void MapEntities::remove_entity(MapEntity* entity) {
	if(!entity->is_removing()) {
	    remove_entities.push_back(entity);
		entity->notify_removing();
	}
}

void MapEntities::remove_tagged_entities() {
	std::list<MapEntity*>::iterator it;
	for(it = remove_entities.begin(); it != remove_entities.end(); it++) {
		MapEntity* entity = *it;
		if(entity->is_obstacle()) {
			obstacle_entities.remove(entity);
		}
		if(entity->is_detector()) {
			detector_entities.remove(static_cast<Detector*>(entity));
		}
		all_entities.remove(entity);
		destroy_entity(entity);
	}
	remove_entities.clear();
}

void MapEntities::destroy_all_entities() {
	std::vector<Tile*>::iterator it2;
	for(it2 = tile_entities.begin(); it2 != tile_entities.end(); it2++)
		destroy_entity(*it2);

	std::list<MapEntity*>::iterator it1;
	for(it1 = all_entities.begin(); it1 != all_entities.end(); it1++)
		destroy_entity(*it1);

	delete tile_surfaces;
	tile_surfaces = NULL;

	all_entities.clear();
	tile_entities.clear();
	obstacle_entities.clear();
	detector_entities.clear();
	remove_entities.clear();
	obstacle_tiles.clear();
}

void MapEntities::destroy_entity(MapEntity* entity) {
	if(!entity->is_removing())
		entity->notify_removing();
	if(entity->is_removing())
		delete entity;
}

void MapEntities::display_tiles() {
	int x = map.get_camera_position().get_x();
	int y = map.get_camera_position().get_y();
	const Rectangle map_size(x, y, map.get_width(), map.get_height());
	tile_surfaces = new Surface(map.get_width(), map.get_height());
	tile_surfaces->fill_with_color(Color::get_black());

	for(int i = 0; i < tile_entities.size(); i++) {
		Tile& tile = *tile_entities[i];
		tile.display(*tile_surfaces, map_size);
	}
}

void MapEntities::update() {
	for(std::list<MapEntity*>::iterator it = all_entities.begin(); it != all_entities.end(); it++) {
		MapEntity* entity = *it;
		if(!(entity)->is_removing()) {
		    entity->update();
		}
	}
	this->hero.update();
	remove_tagged_entities();
}

void MapEntities::display() {
	tile_surfaces->display_region(map.get_camera_position(), map.get_visible_surface());

	std::list<MapEntity*>::iterator it;
	for(it = all_entities.begin(); it != all_entities.end(); it++) {
		MapEntity* entity = *it;
		if(!(entity)->is_removing()) {
			entity->display_on_map();
		}
	}
	this->hero.display_on_map();
}