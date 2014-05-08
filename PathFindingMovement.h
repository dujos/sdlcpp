#ifndef PATH_FINDING_MOVEMENT_H
#define PATH_FINDING_MOVEMENT_H

#include "Type.h"
#include "PathMovement.h"

/**
 * Movement used by entities to move to an entity by 
 * shortest possible route.
 */
class PathFindingMovement : public PathMovement {

private:
	MapEntity* target;			/** targeted entity */
	uint32_t next_move_date;

	MapEntity* get_target();

protected:
	void update();
	void recompute_movement();

public:
	PathFindingMovement(int speed, MapEntity& target);
	~PathFindingMovement();

	void set_target(MapEntity& target);
	bool is_finished();

};

#endif