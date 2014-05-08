#include "TileSet.h"
#include "SimpleTilePattern.h"

TileSet::TileSet(int tileset_id) :
  tileset_id(tileset_id),
  tiles_image(NULL) {

}

TileSet::~TileSet() {
	std::map<int, TilePattern*>::iterator it;
	for(it = tile_patterns.begin(); it != tile_patterns.end(); it++) {
		delete it->second;
	}
	if(tiles_image != NULL) {
		delete tiles_image;
		tiles_image = NULL;
	}
}

void TileSet::add_tile_pattern(int id, TilePattern *tile_pattern) {
	if(tile_patterns.count(id) == 0) {
		tile_patterns[id] = tile_pattern;
	}
}

void TileSet::load() {
	std::ostringstream oss;
	oss << "tilesets" << std::setfill('0') << std::setw(2) << tileset_id << ".txt";
	const std::string& file_name = oss.str();
	std::ifstream file(file_name, std::ifstream::in);

	std::string line; int tile_pattern_id, obstacle, x, y, width, height;
	while(std::getline(file, line)) {
		std::istringstream iss(line);
		iss >> tile_pattern_id >> x >> y >> width >> height >> obstacle;
		TilePattern* pattern = new SimpleTilePattern((Obstacle) obstacle, x, y, width, height);
		add_tile_pattern(tile_pattern_id, pattern);
	}
	file.close();

	std::ostringstream os;
	os << "tilesets" << std::setfill('0') << std::setw(2) << tileset_id << ".png";
	tiles_image = new Surface(os.str());
}

Surface& TileSet::get_tiles_image() {
	return *tiles_image;
}

TilePattern& TileSet::get_tile_pattern(int id) {
	TilePattern* tile_pattern = tile_patterns[id];
	return *tile_pattern;
}

void TileSet::set_images(TileSet& other) {
	delete tiles_image;
	tiles_image = new Surface(other.get_tiles_image());
}