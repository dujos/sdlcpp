#include "TilePattern.h"
#include "Surface.h"

TilePattern::TilePattern(Obstacle obstacle, int width, int height) :
  obstacle(obstacle),
  width(width),
  height(height) {

}

TilePattern::~TilePattern() {

}

int TilePattern::get_width() const {
	return this->width;
}

int TilePattern::get_height() const {
	return this->height;
}

Obstacle TilePattern::get_obstacle() const {
	return this->obstacle;
}