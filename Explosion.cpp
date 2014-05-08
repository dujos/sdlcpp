#include "CollisionMode.h"
#include "Explosion.h"
#include "Sprite.h"

Explosion::Explosion(const std::string& name, const Rectangle& xy) :
  Detector(CollisionMode::COLLISION_RECTANGLE, name, xy.get_x(), xy.get_y(), 48, 48) {
	create_sprite("explosion.txt");
	set_bounding_box_from_sprite();
}

Explosion::~Explosion() {
}

EntityType Explosion::get_entity_type() {
	return EntityType::EXPLOSION;
}

bool Explosion::can_be_obstacle() {
	return false;
}

void Explosion::notify_collision(MapEntity &entity_overlapping, CollisionMode collision_mode) {
	
}

void Explosion::notify_collision_with_sensor(Sensor& sensor, CollisionMode collision_mode) {

}

void Explosion::notify_sprite_frame_changed(Sprite& sprite, const std::string& animation, int frame) {
	if(frame == 1) {
		check_collision_with_detectors();
	}
}

void Explosion::update() {
	Detector::update();
	if(get_sprite().is_animation_finished())
		remove_from_map();
}