#ifndef PIXEL_MOVEMENT_H
#define PIXEL_MOVEMENT_H

#include "Type.h"
#include "Movement.h"
#include "Rectangle.h"
#include <list>

/**
 * Movement of an entity that follows a sequence of pixel precise moves.
 */
class PixelMovement : public Movement {

	//movement properties
	std::list<Rectangle> trajectory;                          /** Trajectory. Each element represents a move in pixels */
	std::string trajectory_string;                            /** String representation of trajectory */
	uint32_t next_move_date;								  /** Next move date */
	uint32_t delay;                                           /** Delay between two translations */

	//current state
	std::list<Rectangle>::iterator trajectory_iterator;       /** Current element of trajectory */
	bool finished;                                            /** Has the object reached the end of the trajectory */

	void make_next_step();

public:
	//Constructor and desconstructor
	PixelMovement(const std::string& trajectory_string, uint32_t delay);
	virtual ~PixelMovement();

	//properties
	const std::string& get_trajectory();
	void set_trajectory(const std::list<Rectangle>& trajectory);
	void set_trajectory(const std::string& trajectory_name);
	
	uint32_t get_delay();
	void set_delay(uint32_t delay);
	
	//state
	bool is_started();
	virtual bool is_finished();
	int get_length();
	void restart();

	virtual void update();
};

#endif