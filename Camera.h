#ifndef CAMERA_H
#define CAMERA_H

#include "Rectangle.h"
#include "MapEntity.h"
#include "Map.h"

class Camera {

private:
	Map& map;
	Rectangle camera_position;

public:
	Camera(Map& map);
	~Camera();

	const Rectangle& get_camera_position();

	void update();
};


#endif