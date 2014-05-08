#include "Bubble.h"
#include "DamageState.h"
#include "Destructible.h"
#include "Game.h"
#include "Hero.h"
#include "PlayerMovement.h"
#include "PlayerMovementState.h"
#include "FireballState.h"
#include "JumpingState.h"
#include "Jumper.h"
#include "FreeState.h"
#include "MapEntities.h"
#include "Map.h"
#include "System.h"
#include "Sensor.h"
#include "Sprite.h"
#include "State.h"
#include "TargetMovement.h"
#include "YameyamekaState.h"

const int Hero::normal_walking_speed = 112;

Hero::Hero() :
  MapEntity("hero", 0, 350, 450, 16, 16),
  walking_speed(normal_walking_speed),
  state(NULL),
  ground(Ground::NORMAL),
  next_ground_date(0),
  damaged(false),
  tunic_sprite(NULL),
  light_sprite(NULL),
  shadow_sprite(NULL) {
	set_origin(8, 13);
	
	tunic_sprite = &create_sprite("tunic.txt");
	light_sprite = &create_sprite("light.txt");

	set_state(new FreeState(*this));
	last_ground_coordinates.set_xy(260, 220);
	set_movement(new PlayerMovement(walking_speed));
}

Hero::~Hero() {
	delete tunic_sprite;
	delete shadow_sprite;
	delete light_sprite;
	delete state;

	std::list<State*>::iterator it;
	for(it = old_states.begin(); it != old_states.end(); it++) {
		delete *it;
	}
}

void Hero::set_state(State* new_state) {
	State* old_state = this->state;
	if(old_state != NULL) {
		old_state->stop(new_state);
	}
	old_states.push_back(old_state);
	
	this->state = new_state;
	state->start(old_state);
	check_position();
}

Sprite& Hero::get_tunic_sprite() {
	return *tunic_sprite;
}

Sprite& Hero::get_shadow_sprite() {
	return *shadow_sprite;
}

Sprite& Hero::get_light_sprite() {
	return *light_sprite;
}

EntityType Hero::get_entity_type() {
	return EntityType::HERO;
}

void Hero::notify_movement_changed() {
	PlayerMovement* playerMovement = (PlayerMovement*)get_movement();
	int direction8 = playerMovement->get_current_direction8();

	int old_animation_drirection = get_animation_direction();
	int animation_direction = tunic_sprite->get_current_animation_direction(direction8);
	if(old_animation_drirection != animation_direction && animation_direction != -1) {
		set_animation_direction(animation_direction);
		set_direction(direction8);
	}
	state->notify_movement_changed();
	check_position();
}

void Hero::notify_movement_finished() {
	state->notify_movement_finished();
	check_position();
}

void Hero::notify_position_changed() {
	state->notify_position_changed();
	check_position();	
}

void Hero::notify_obstacle_reached() {
	MapEntity::notify_obstacle_reached();
	state->notify_obstacle_reached();
	check_position();
}

void Hero::notify_control_pressed(GameControls::GameKey control) {
	state->notify_control_pressed(control);
}

void Hero::notify_control_released(GameControls::GameKey control) {
	state->notify_control_released(control);
}

void Hero::set_animation_direction(int direction4) {
	tunic_sprite->set_current_direction(direction4);
	light_sprite->set_current_direction(direction4);
}

void Hero::set_animation_light() {
	light_sprite->set_current_animation("light");
}

void Hero::set_animation_stopped() {
	tunic_sprite->set_current_animation("stopped");
}

void Hero::set_animation_walking() {
	tunic_sprite->set_current_animation("walking");
}

void Hero::set_animation_falling() {
	tunic_sprite->set_current_animation("falling");
}

void Hero::set_animation_damage() {
	tunic_sprite->set_current_animation("damage");
}

void Hero::set_animation_hadouken() {
	tunic_sprite->set_current_animation("fireball");
}

void Hero::set_animation_yameyameka() {
	tunic_sprite->set_current_animation("yameyameka");
}

void Hero::set_animation_dying() {
	tunic_sprite->set_current_animation("dying");
}

void Hero::set_animation_jumping() {
	tunic_sprite->set_current_animation("jumping");
}

bool Hero::is_animation_finished() {
	return tunic_sprite->is_animation_finished();
}

void Hero::set_map(Map& map) {
	MapEntity::set_map(map);
}

void Hero::check_game_over() {
	if(state->can_start_game_over()) {
		get_game().start_game_over();
	}
}

void Hero::reset_movement() {
	get_movement()->stop();
}

int Hero::get_walking_speed() {
	return this->walking_speed;
}

void Hero::set_walking_speed(int walking_speed) {
	if(this->walking_speed != walking_speed) {
		this->walking_speed = walking_speed;
		state->notify_walking_speed_changed();
	}
}

int Hero::get_animation_direction() {
	return tunic_sprite->get_current_direction();
}

int Hero::get_movement_direction() {
	return state->get_movement_direction8();
}

bool Hero::is_obstacle_for(MapEntity& other) {
	return other.is_hero_obstacle(*this);
}

bool Hero::is_hole_obstacle() {
	return true;
}

void Hero::update_movement() {
	if(get_movement() == NULL)
		return;
	get_movement()->update();
}

void Hero::update_state() {
	state->update();

	std::list<State*>::iterator it;
	for(it = old_states.begin(); it != old_states.end(); it++) {
		delete *it;
	}
	old_states.clear();
}

void Hero::check_position() {
	if(!is_on_map())
		return;
}

void Hero::notify_collision_with_sensor(Sensor& sensor) {
	sensor.start_sensor();
}

void Hero::notify_collision_with_jumper(Jumper& jumper) {
	if(state->can_jump()) {
		int jump_direction = jumper.get_direction();
		start_jumping();
	}
}

void Hero::notify_collision_with_fire(Fire& fire) {
	this->get_game().start_game_over();
}

void Hero::notify_collision_with_bubble(Bubble& bubble) {
	this->damage(bubble);
}

void Hero::notify_collision_with_chest(Chest& chest) {
	std::cout << "chest collision" << std::endl;
}

void Hero::start_jumping() {
	set_state(new JumpingState(*this));
}

void Hero::start_fireball() {
	set_state(new FireballState(*this));
}

void Hero::start_yameyameka() {
	set_state(new YameyamekaState(*this));
}

void Hero::start_hero() {
	set_state(new FreeState(*this));
}

void Hero::damage(MapEntity& source) {
	set_state(new DamageState(*this, source.get_xy()));
}

void Hero::damage(const Rectangle& source) {
	set_state(new DamageState(*this, source));
}

bool Hero::is_damaged() {
	return damaged;
}

void Hero::set_damaged(bool d) {
	this->damaged = d;
}

void Hero::update() {
	update_movement();
	update_state();
	tunic_sprite->update();
	light_sprite->update();
	check_collision_with_detectors();
	//check_game_over();
}

void Hero::display_on_map() {
	this->state->display_on_map();
}

Ground Hero::get_ground_tile() {
	return get_map().get_ground_tile(get_ground_point());
}

const Rectangle Hero::get_ground_point() {
	return Rectangle(get_x(), get_y(), 1, 1);
}

void Hero::set_ground(Ground ground) {
	if(this->ground != ground && ground != Ground::EMPTY) {
		this->ground = ground;
	}
}