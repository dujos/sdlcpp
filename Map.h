#ifndef MAP_H
#define MAP_H

#include "Rectangle.h"
#include "Globals.h"
#include "Ground.h"
#include "Obstacle.h"
#include "Type.h"
#include "TileSet.h"

#include <string>

class Map {

private:
	Game* game;
	Surface* visible_surface;
	MapEntities* entities;
	Camera* camera;

	int tileset_id;
	TileSet* tileset;

	Rectangle location;

public:
	Map(Game& game);
	~Map();

	void load_map();
    
	//map properties
	int get_width();
	int get_width8();
	int get_height();
	int get_height8();
	Rectangle get_location();
	TileSet& get_tileset();

	//game objects
	Surface& get_visible_surface();
	MapEntities& get_entities();
	Game& get_game();
	const Rectangle& get_camera_position();

	//collisions with obstacles (checked before a move)
	bool test_collision_with_border(const Rectangle& collision_box);
	bool test_collision_with_entities(const Rectangle& collision_box, MapEntity& check_entity);
	bool test_collision_with_obstacles(const Rectangle& collision_box, MapEntity& check_entity);
	bool test_collision_with_obstacles(int x, int y, MapEntity& check_entity);
	bool test_collision_with_tiles(int x, int y, MapEntity& check_entity);
	Ground get_ground_tile(int x, int y);
	Ground get_ground_tile(const Rectangle& coordinates);

	//collisions with detectors (checked after a move)
	void check_collision_with_detectors(MapEntity& entity);
	void check_collision_with_detectors(MapEntity& entity, Sprite& sprite);

	static Ground obstacle_to_ground(Obstacle obstacle);

	//main loop
	void update();
	void display();
	void display_sprite(Sprite& sprite, const Rectangle& rec);
	void display_sprite(Sprite& sprite, int x, int y);
};

#endif