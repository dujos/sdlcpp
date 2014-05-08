#include "PathFindingMovement.h"
#include "PathFinding.h"
#include "MapEntity.h"
#include "System.h"

/**
 * Creates a chase movement.
 */
PathFindingMovement::PathFindingMovement(int speed, MapEntity& target) :
  PathMovement("", speed),
  target(get_target()) {
	  set_target(target);
}

PathFindingMovement::~PathFindingMovement() {

}

MapEntity* PathFindingMovement::get_target() {
	return target;
}

// Set target to be chased
void PathFindingMovement::set_target(MapEntity& target) {
	this->target = &target;
	next_move_date = System::now() + 100;
}

// Update position
void PathFindingMovement::update() {
	PathMovement::update();

	if(PathMovement::is_finished()) {
		if(target != NULL && System::now() >= next_move_date) {
			recompute_movement();
		}
	}
}

void PathFindingMovement::recompute_movement() {
	PathFinding path_finding(get_entity()->get_map(), *get_entity(), *target);
	std::string path = path_finding.compute_path();

	uint32_t min_delay;
	if(path.size() == 0) {
		// Target is too far.
		path = "";
		min_delay = 3000;
	} else {
		// Path is found lets update the path frequetly.
		min_delay = 300;
	}
	next_move_date = System::now() + min_delay;

	set_path(path);
}

bool PathFindingMovement::is_finished() {
	return false;
}