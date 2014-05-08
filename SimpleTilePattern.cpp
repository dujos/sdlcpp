#include "SimpleTilePattern.h"
#include "TileSet.h"
#include "Surface.h"
#include "Map.h"

SimpleTilePattern::SimpleTilePattern(Obstacle obstacle, int x, int y, 
	int width, int height) : 
  TilePattern(obstacle, width, height),
	position_in_tileset(x, y, width, height) {

}

SimpleTilePattern::~SimpleTilePattern() {

}

void SimpleTilePattern::display(Surface& dst_surface, const Rectangle& dst_position,
	TileSet& tileset) {
	
	Surface& tileset_image = tileset.get_tiles_image();
	tileset_image.display_region(position_in_tileset, dst_surface, dst_position);
}
 