#include "Camera.h"
#include "Globals.h"
#include "MapEntities.h"
#include "Hero.h"

Camera::Camera(Map& map) :
  map(map),
  camera_position(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT) {

}

Camera::~Camera() {

}

const Rectangle& Camera::get_camera_position() {
	return this->camera_position;
}

void Camera::update() {
	const Rectangle& map_location = map.get_location();

	const Rectangle& hero_center = map.get_entities().get_hero().get_center_point();
	int x = hero_center.get_x();
	int y = hero_center.get_y();

    if (map_location.get_width() < SCREEN_WIDTH) {
      x = (map_location.get_width() - SCREEN_WIDTH) / 2;
    }
    else {
      x = std::min(std::max(x - (SCREEN_WIDTH / 2), 0),
          map_location.get_width() - SCREEN_WIDTH);
    }

    if (map_location.get_height() < SCREEN_HEIGHT) {
      y = (map_location.get_height() - SCREEN_HEIGHT) / 2;
    }
    else {
      y = std::min(std::max(y - (SCREEN_HEIGHT / 2), 0),
          map_location.get_height() - SCREEN_HEIGHT);
    }

	camera_position.set_xy(x, y);
}