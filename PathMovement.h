#ifndef PATH_MOVEMENT_H
#define PATH_MOVEMENT_H

#include "PixelMovement.h"
#include "Type.h"

class PathMovement : public PixelMovement {

private:
	std::string starting_path;                                        /** Path is a movement in (0-7) direction */
	std::string remaining_path;                                       /** Remaining part of the path */
	int current_direction;

	int speed;                                                        /** Movement speed in pixels per second */
	static const std::string moves[];								  /** 8 pixel trajectory for each direction (0 - 7) */
	
	static uint32_t speed_to_delay(int speed);

	void start_next_move();
	bool is_move_finished();

public:
	PathMovement(const std::string& path, int speed);
	~PathMovement();

	void set_entity(MapEntity* entity);
	virtual void update();
	virtual bool is_finished();

	void restart();

	void set_path(const std::string& path);
};

#endif