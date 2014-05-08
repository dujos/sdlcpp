#include "Tile.h"
#include "TilePattern.h"

Tile::Tile(int x, int y, int width, int height, int tile_pattern_id) :
  MapEntity(x, y, width, height),
  tile_pattern_id(tile_pattern_id),
  tile_pattern(NULL) {
  
}
  
Tile::~Tile() {

}

MapEntity* Tile::parse(Game& game, const std::string& line) {
	std::istringstream iss(line);
	
	int entity_type; int x; int y; int width; int height; int tile_pattern_id;
	iss >> entity_type >> x >> y >> width >> height >> tile_pattern_id;

	return new Tile(x, y, width, height, tile_pattern_id);
}

EntityType Tile::get_entity_type() {
	return EntityType::TILE;
}

bool Tile::is_tile() {
	return true;
}

void Tile::set_map(Map& map) {
	MapEntity::set_map(map);
	tile_pattern = &map.get_tileset().get_tile_pattern(tile_pattern_id);
}

void Tile::display_on_map() {
	//display(get_map().get_visible_surface(), get_map().get_camera_position());
}

void Tile::display(Surface& dst_surface, const Rectangle& dst_position) {
	int x = this->get_x();
	int y = this->get_y();
	Rectangle dst;
	dst.set_xy(x, y);
	tile_pattern->display(dst_surface, dst, get_map().get_tileset());
}

TilePattern& Tile::get_tile_pattern() {
	return *tile_pattern;
}