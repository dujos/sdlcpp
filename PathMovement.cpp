#include "PathMovement.h"
#include "MapEntity.h"
#include "Geometry.h"
#include "System.h"

const std::string PathMovement::moves[] = {
    " 1  0   1  0   1  0   1  0   1  0   1  0   1  0   1  0", // 8 pixels right
    " 1 -1   1 -1   1 -1   1 -1   1 -1   1 -1   1 -1   1 -1", // 8 pixels right-up
    " 0 -1   0 -1   0 -1   0 -1   0 -1   0 -1   0 -1   0 -1", // 8 pixels up
    "-1 -1  -1 -1  -1 -1  -1 -1  -1 -1  -1 -1  -1 -1  -1 -1", // 8 pixels left-up
    "-1  0  -1  0  -1  0  -1  0  -1  0  -1  0  -1  0  -1  0", // 8 pixels left
    "-1  1  -1  1  -1  1  -1  1  -1  1  -1  1  -1  1  -1  1", // 8 pixels left-down
    " 0  1   0  1   0  1   0  1   0  1   0  1   0  1   0  1", // 8 pixels down
    " 1  1   1  1   1  1   1  1   1  1   1  1   1  1   1  1"  // 8 pixels right-down
};

PathMovement::PathMovement(const std::string& path, int speed) :
  PixelMovement(path, 0),
  current_direction(5),
  speed(speed) {
    set_path(path);
}

PathMovement::~PathMovement() {

}

void PathMovement::set_path(const std::string& path) {
	this->starting_path = path;
	restart();
}

//Sets the entity to be controlled by this movement.
void PathMovement::set_entity(MapEntity* entity) {
	Movement::set_entity(entity);
	restart();
}

void PathMovement::update() {
	PixelMovement::update();
	if(is_move_finished()) {
		start_next_move();
	}
}

//Return if movement is finished.
bool PathMovement::is_finished() {
	return (PixelMovement::is_finished() && remaining_path.size() == 0);
}

//Starts or restarts movement.
void PathMovement::restart() {
	this->remaining_path = starting_path;
	start_next_move();
}

//Return if current move of the path is finished.
bool PathMovement::is_move_finished() {
	return PixelMovement::is_finished();
}

//Starts the next 8-pixel trajectory of the path movement.
void PathMovement::start_next_move() {
	MapEntity* entity = get_entity();
	if(entity == NULL) {
		return;
	}

	if(remaining_path.size() == 0) {
		if(!is_stopped()) {
			stop();
		}
	}

	if(remaining_path.size() != 0) {
		current_direction = remaining_path[0] - '0';
		PixelMovement::set_delay(speed_to_delay(speed));
		PixelMovement::set_trajectory(moves[current_direction]);
		remaining_path = remaining_path.substr(1);
	}
}

//Converts a speed into a delay in milliseconds between each pixel move.
uint32_t PathMovement::speed_to_delay(int speed) {
	uint32_t delay = 1000 / speed;     //speed in pixels per seconds delay in miliseconds.
	return delay;
}