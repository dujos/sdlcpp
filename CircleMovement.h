#ifndef CIRCLE_MOVEMENT_H
#define CIRCLE_MOVEMENT_H

#include "MapEntity.h"
#include "Movement.h"

class CircleMovement : public Movement {

private:
	//center of circle
	MapEntity* center_entity;
	Rectangle center_point;

	int radius_speed;

	//angle
	int current_angle;
	int new_angle;
	int starting_angle;
	int angle_increment;
	uint32_t next_angle_date;
	uint32_t next_angle_delay;

	//radius
	int current_radius;

	//stop after an amount of time
	uint32_t duration;
	uint32_t end_movement_date;

	//stop after a certain rotations
	int max_rotations;
	int current_rotation_count;

	//restart when stopped
	uint32_t loop_delay;
	uint32_t restart_date;

	void recompute_movement();

public:
	CircleMovement();
	CircleMovement(int x, int y);
	CircleMovement(int x, int y, int radius);
	~CircleMovement();

	void update();
	//properties
	void set_center(const Rectangle& center_point);
	void set_center(MapEntity& center_entity);
	void set_radius(int radius);
	void set_angle_speed(int angle_speed);
	void set_starting_angle(double starting_angle);
	void set_loop(uint32_t delay);
	void set_max_rotations(int max_rotations);
	void set_duration(uint32_t duration);

	//state
	void start();
	void stop();
	bool is_started();
	bool is_finished();
};

#endif