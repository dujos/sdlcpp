#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Rectangle.h"
#include "Type.h"


// Abstract class representing movement.
// Parent class of all movement types.
class Movement {

protected:
	static int next_id;						/** next unique id to assocciate with movement instance */
	int id;									/** a number identifiying this movement */

	MapEntity* entity;						/** entity controlled by this movement */
	Rectangle xy;							/** if entity is null movement is applied to this object */

	bool suspended;							/** indicates if movement is suspended */

	uint32_t last_move_date;				/** date of last move_x and move_y change */
	uint32_t when_suspended;				/** indicates when movement is suspended */

protected:
	Movement();
	MapEntity* get_entity();

	uint32_t get_when_suspended();

public:
	virtual ~Movement();
	
	bool is_suspended();
	virtual void set_suspended(bool suspended);

	// Entity
	virtual void set_entity(MapEntity* entity);

	// Position
	int get_x();
	int get_y();
	const Rectangle get_xy();

	void set_x(int x);
	void set_y(int y);
	void set_xy(const Rectangle& xy);
	void set_xy(int x, int y);

	// Move
	void translate_x(int x);
	void translate_y(int y);
	void translate_xy(int x, int y);
    void translate_xy(const Rectangle& dxy);

	// Obstacles
	bool test_collision_with_obstacles(int dx, int dy);
	bool test_collision_with_obstacles(const Rectangle& dxy);
	bool test_collision_with_borders(int dx, int dy);
	
	// Movement
	bool is_stopped();
	virtual bool is_started();
	virtual void stop();
	virtual bool is_finished();

	virtual void notify_position_changed();
	virtual void notify_obstacle_reached();
	virtual void notify_moving_entity();
	virtual void update();

	const Rectangle get_displayed_xy();
};


#endif