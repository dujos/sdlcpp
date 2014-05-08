#include "Detector.h"
#include "Sprite.h"
#include "Hero.h"
#include "Map.h"

Detector::Detector(int collision_modes, const std::string& name, int x, int y, int width, int height) :
  MapEntity(name, 0, x, y, width, height),
  collision_modes(collision_modes) {
  
}

Detector::~Detector() {}

bool Detector::is_removing() {
	return MapEntity::is_removing();
}

void Detector::notify_removing() {
	MapEntity::notify_removing();
}

bool Detector::is_detector() {
	return true;
}

void Detector::set_collision_modes(int collision_modes) {
	this->collision_modes = collision_modes;
}

void Detector::add_collision_mode(CollisionMode collision_mode) {
	set_collision_modes(this->collision_modes | collision_mode);
}

bool Detector::has_collision_mode(CollisionMode collision_mode) {
	return (this->collision_modes & collision_mode) != 0;
}

void Detector::notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode) {}

void Detector::notify_collision(MapEntity& entity_overlapping, Sprite& this_sprite, Sprite& other_sprite) {}

bool Detector::test_collision_rectangle(MapEntity& entity) {
    return entity.overlaps(*this);
}

void Detector::check_collision(MapEntity& entity) {
	if(&entity != this) {
		if(test_collision_rectangle(entity)) {
			notify_collision(entity, CollisionMode::COLLISION_RECTANGLE);
		}
	}
}

void Detector::check_collision(MapEntity& entity, Sprite& sprite) {
	if(&entity != this) {
		std::list<Sprite*>::iterator it;
		for (it = get_sprites().begin(); it != get_sprites().end(); it++) {
			Sprite &this_sprite = *(*it);

			if(has_collision_mode(CollisionMode::COLLISION_RECTANGLE) && test_collision_rectangle(entity)) {
				notify_collision(entity, sprite, this_sprite);
			}
		}
	}
}

