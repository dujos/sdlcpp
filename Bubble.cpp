#include "PathFindingMovement.h"
#include "Movement.h"
#include "StraightMovement.h"
#include "TargetMovement.h"
#include "CircleMovement.h"
#include "MapEntities.h"
#include "Geometry.h"
#include "Bubble.h"
#include "Sprite.h"
#include "Hero.h"
#include "Game.h"
#include "Map.h"

Bubble::Bubble(const std::string& name, int x, int y, Game& game) :
  Enemy(name, x, y),
  moving_speed(40),
  game(game) {
  
	bubble_sprite = &create_sprite("bubble.txt");
	bubble_sprite->set_current_animation("walking");
	bubble_sprite->set_current_direction(0);
	set_bounding_box_from_sprite();

	set_movement(new CircleMovement(x, y, 50));
}

Bubble::~Bubble() {}

void Bubble::notify_obstacle_reached() {}

void Bubble::notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode) {
	entity_overlapping.notify_collision_with_bubble(*this);
}