#ifndef TILE_SET_H
#define TILE_SET_H

#include "Surface.h"

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>

class TileSet {

private:
	int tileset_id;

	std::map<int, TilePattern*> tile_patterns;
	
	Surface* tiles_image;
	
	void add_tile_pattern(int tile_pattern_id, TilePattern* tile_pattern);

public:
	TileSet(int tileset_id);
	~TileSet();

	void load();
	void unload();
	
	Surface& get_tiles_image();
	TilePattern& get_tile_pattern(int id);

	void set_images(TileSet& other);
	
};

#endif