#ifndef SIMPLE_TILE_PATTERN_H
#define SIMPLE_TILE_PATTERN_H

#include "Rectangle.h"
#include "TilePattern.h"

class SimpleTilePattern : public TilePattern {

protected:
	Rectangle position_in_tileset;

public:
	SimpleTilePattern(Obstacle obstacle, int x, int y, int width, int height);
	~SimpleTilePattern();

	void display(Surface& dst_surface, const Rectangle& dst_position,
		TileSet& tileset);

};


#endif