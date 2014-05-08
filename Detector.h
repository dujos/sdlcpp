#ifndef DETECTOR_H
#define DETECTOR_H

#include "CollisionMode.h"
#include "MapEntity.h"

#include <sstream>
#include <iostream>
#include <fstream>

class Detector : public MapEntity {

private:
	int collision_modes;

public:
	Detector(int collision_modes, const std::string& name, int x, int y, int width, int height);
	virtual ~Detector();

	void notify_removing();
	bool is_removing();

	//properties of detector
	bool is_detector();
	void set_collision_modes(int collision_modes);
	void add_collision_mode(CollisionMode collision_mode);
	bool has_collision_mode(CollisionMode collision_mode);

	//collision testing functions
	virtual void notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode);
	virtual void notify_collision(MapEntity& entity_overlapping, Sprite& this_sprite, Sprite& other_sprite);

	bool test_collision_rectangle(MapEntity& entity);
	
	void check_collision(MapEntity& entity);
	void check_collision(MapEntity& entity, Sprite& sprite);
};


#endif