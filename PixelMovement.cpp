#include "PixelMovement.h"
#include "MapEntity.h"
#include "System.h"
#include <sstream>

PixelMovement::PixelMovement(const std::string& trajectory_string, 
	uint32_t delay) :
  Movement(),
  next_move_date(0),
  delay(delay),
  finished(false) {
	set_trajectory(trajectory_string);
}

PixelMovement::~PixelMovement() {

}

/**
 * Return a trajectory of this movement. A string of translations that
 * compose this movement.
 */
const std::string& PixelMovement::get_trajectory() {
	if(trajectory.size() > 0 && trajectory_string.size() == 0) {
		// trajectory does not exist as string lets create the string.
		std::list<Rectangle>::iterator it;
		std::ostringstream oss;
		for(it = trajectory.begin(); it != trajectory.end(); it++) {
			const Rectangle& step = *it;
			oss << step.get_x() << " " << step.get_y() << " ";
		}
		trajectory_string = oss.str();
	}
	return trajectory_string;
}

/**
 * Sets trajectory of this movement.
 * This function can be called even if the object was moving with a previous trajectory.
 * The old trajectory is replaced and the movement starts from beginning of the new trajectory.
 */
void PixelMovement::set_trajectory(const std::list<Rectangle>& trajectory) {
	this->trajectory = trajectory;
	this->trajectory_string = "";

	restart();
}

/**
 * Sets trajectory of this movement.
 */
void PixelMovement::set_trajectory(const std::string& trajectory_string) {
	int dx = 0;
	int dy = 0;
	trajectory.clear();
	std::istringstream iss(trajectory_string);
	while(iss >> dx) {
		iss >> dy;
		trajectory.push_back(Rectangle(dx, dy));
	}
	this->trajectory_string = trajectory_string;
	restart();
}

uint32_t PixelMovement::get_delay() {
	return this->delay;
}

//Change delay between two numbers.
void PixelMovement::set_delay(uint32_t delay) {
	this->delay = delay;
}

//Restart movement.
void PixelMovement::restart() {
	int length = get_length();
	if(length == 0) {
		finished = true;
	} else {
		finished = false;
		trajectory_iterator = trajectory.begin();
		next_move_date = System::now() + delay;

		if(get_entity() != NULL) {
			get_entity()->notify_movement_changed();
		}
	}
}

void PixelMovement::update() {
	Movement::update();

	uint32_t now = System::now();
	while(now >= next_move_date
		&& !finished
		&& (get_entity() == NULL || get_entity()->get_movement() == this)) {

	    Rectangle old_xy(get_x(), get_y());
		make_next_step();

		bool success = (get_x() != old_xy.get_x() || get_y() != old_xy.get_y());
		if(success) {
			this->notify_obstacle_reached();
		}
    }
}

//Makes a move in the path when a path is not finished yet.
void PixelMovement::make_next_step() {
	bool success = false;
	const Rectangle& dxy = *trajectory_iterator;

	if(!test_collision_with_obstacles(dxy.get_x(), dxy.get_y())) {
		translate_xy(dxy);
		success = true;
	}
	
	next_move_date += delay;
	trajectory_iterator++;

	if(trajectory_iterator == trajectory.end()) {
		finished = true;  
	}
}

// Return the total number of moves in this trajectory.
int PixelMovement::get_length() {
	return trajectory.size();
}

// Return if entity controlled by this movement is moving.
bool PixelMovement::is_started() {
	return !finished;
}

// Return if movement is finished the end of trajectory was reached.
bool PixelMovement::is_finished() {
	return finished;
}

