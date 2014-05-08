#ifndef TILE_PATTERN_H
#define TILE_PATTERN_H

#include "Type.h"
#include "Obstacle.h"

class TilePattern {

protected:
	const Obstacle obstacle;
	const int width;
	const int height;

public:
	TilePattern(Obstacle obstacle, int width, int height);
	virtual ~TilePattern();
	
	int get_width() const;
	int get_height() const;
	Obstacle get_obstacle() const;
	
	virtual void display(Surface& dst_surface, const Rectangle& dst_position,
		TileSet& tileset) = 0;

};

#endif