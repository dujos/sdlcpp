#ifndef STRAIGHT_MOVEMENT_H
#define STRAIGHT_MOVEMENT_H

#include "Movement.h"

// A straight movement represented by a speed vector. 
class StraightMovement: public Movement {

private:
	// Speed vector.
	double angle;					/** angle between the speed vector and horizontal axis in radians */
	
	double speed_x;					/** speed in x direction, 
									  *	positive value moving right,
									  * negative value moving left. */
	double speed_y;					/** speed in y direction, 
									  *	positive value moving down,
									  * negative value moving up. */
	
	int move_x;						/** number of pixels of next x move : 0, 1 or -1 */
	int move_y;						/** number of pixels of next y move : 0, 1 or -1  */

	Rectangle start_xy;				/** starting position when movement is started 
									  * (reset when speed or the angle changes) */

	uint32_t delay_x;				/** delay in ticks between a move of 1 pixels */
	uint32_t delay_y;				/** delay in ticks between a move of 1 pixels */

	uint32_t next_move_date_x;		/** date of next move x move in ticks */
	uint32_t next_move_date_y;		/** date of next move y move in ticks */

	bool finished;					/** indicates an obstacle was reached */

protected:
	void set_next_move_date_x(uint32_t next_move_date_x);
	void set_next_move_date_y(uint32_t next_move_date_y);

	void update_y();
	void update_x();
	
public:
	StraightMovement();
	StraightMovement(double angle, double speed);
	virtual ~StraightMovement();

	void set_suspended(bool suspended);

	// Speed vector
	void set_speed_x(double x_speed);
	void set_speed_y(double y_speed);
	void set_speed(double speed);

	int get_current_direction8();

	double get_speed();
	double get_angle();
	void set_angle(double angle);

	bool is_finished();
	void set_finished();

	void stop();

	void notify_moving_entity();

	void set_entity(MapEntity* entity);
	virtual void update();

};

#endif