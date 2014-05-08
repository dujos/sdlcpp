#ifndef TILE_H
#define TILE_H

#include "Type.h"
#include "MapEntity.h"
#include "Map.h"

#include <sstream>
#include <iostream>
#include <fstream>

class Tile : public MapEntity {

private:
	int tile_pattern_id;
	TilePattern* tile_pattern;

public:
	Tile(int x, int y, int width, int height, int tile_pattern_id);
	~Tile();

	static MapEntity* parse(Game& game, const std::string& line);

	EntityType get_entity_type();

	bool is_tile();

	void set_map(Map& map);
	
	void display_on_map();
	void display(Surface& dst_surface, const Rectangle& dst_position);
	TilePattern& get_tile_pattern();

};


#endif