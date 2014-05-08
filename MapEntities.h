#ifndef MAP_ENTITIES_H
#define MAP_ENTITIES_H

#include "EntityType.h"
#include "Obstacle.h"
#include "Type.h"

#include <vector>
#include <map>
#include <list>

class MapEntities {

private:
	// Game objects
	Game& game;
	Map& map;
	Hero& hero;

	// Map properties
	int map_width8;												/** Number of 8x8 squares in a row of the map */
	int map_height8;											/** Number of 8x8 squares in a column of the map */

	Surface* tile_surfaces;										/** Tiles are drawn on this surface */

	// Dynamic entities
	std::list<MapEntity*> all_entities;							/** All map entities except tiles */
	std::list<MapEntity*> remove_entities;						/** List of entities to be removed */
	std::list<Detector*>  detector_entities;					/** List of entities able to detect other entities in the map */
	std::list<MapEntity*> obstacle_entities;					/** List of entities able to be an obstacle for other entities 
																	on the map. */
	// Tiles
	std::vector<Tile*> tile_entities;							/** All tiles of the map */
	std::map<int, Obstacle> obstacle_tiles;						/** ALl obstacle tiles of the map */
	
	void set_obstacle(int x8, int y8, Obstacle obstacle);

public:
	MapEntities(Game& game, Map& map);
	~MapEntities();

	Hero& get_hero();

	Obstacle get_obstacle_tile(int x, int y);
	std::list<MapEntity*>& get_obstacle_entities(); 
	std::list<Detector*>& get_detectors();

	void set_map_size(int mw8, int mh8);

	void add_tile(Tile* tile);

	void add_entity(MapEntity* entity);
	void remove_entity(MapEntity* entity);
	void remove_tagged_entities();

	void destroy_all_entities();
	void destroy_entity(MapEntity* entity);

	void display_tiles();
	void update();
	void display();
};

#endif