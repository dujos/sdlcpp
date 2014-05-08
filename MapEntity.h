#ifndef MAP_ENTITY_H
#define MAP_ENTITY_H

#include "CollisionMode.h"
#include "EntityType.h"
#include "Rectangle.h"
#include "Type.h"

#include <string>
#include <list>

/**
 * Abstract class for all objects placed on the map.
 * Example of entities include tiles, enemies, hero etc.
 * Each entity has:
 * a bounding box to represent its position on the map.
 * an origin point relative to rectangles top-left corner.
 * some entities may also have a name, movement and some sprites.
 */

class MapEntity {

public:
	static const Rectangle directions_to_move[8];			/** converts a direction of (0-7) to a one pixel move */
	
	typedef MapEntity* (CreationFunction)(Game &game, const std::string& line);
    static CreationFunction* creation_functions[]; 

private:
	Rectangle origin;								/** coordinates of the origin point of the entity 
													  * relative to the top left corner of its rectangle.
													  * When get_x() or get_y() is called you get the 
													  * coordinates of the origin point of the map and not
													  * the coordinates of the top left corner. */

	Rectangle bounding_box;							/** this rectangle represents the position of the entity 
													  * of the map and is used for the collision tests. */
	std::string name;								/** name of the entity */
	int current_direction;							/** current direction of our entity */
	
	Map* map;										/** map where this entity is located */
	Movement* movement;								/** movement of this entity */

	std::list<Movement*> old_movements;				/** old movements to be destroyed asap */

	std::list<Sprite*> sprites;						/** list of sprites of the entity */
	std::list<Sprite*> old_sprites;					/** sprites to be destroyed asap */

	// Entity state.
	bool removing;									/** indicates that the entity is not valid because 
													  * its about to be removed */

protected:
	MapEntity();
	MapEntity(const std::string& name, int direction, int x, int y, int width, int height);
	MapEntity(int x, int y, int width, int height);

	// Entity properties.
	void set_direction(int dir);
	void set_size(const Rectangle &rec);
	void set_size(int width, int height);
	void set_origin(const Rectangle &rec);
	void set_origin(int x, int y);

	void clear_old_movements();
	void clear_old_sprites();

	// Sprites.
	void set_sprites_to_map(Map& map);

public:
	virtual ~MapEntity();
	void remove_from_map();
	virtual void notify_removing();
	bool is_removing();

	virtual EntityType get_entity_type() = 0;
	virtual bool is_detector();
	virtual bool is_obstacle();
	virtual bool is_tile();
	bool is_hero();
	bool is_enemy();

	// Access to objects.
	Hero& get_hero();
	MapEntities& get_entities();
	Game& get_game();
	Map& get_map();

	// Sprites.
	std::list<Sprite*>& get_sprites();
	Sprite& create_sprite(const std::string& animation_set_id);
	Sprite& get_sprite();
	void remove_sprite(Sprite& sprite);
	void clear_sprites();

	// Movement.
	Movement* get_movement();
	void set_movement(Movement* movement);
	void clear_movement();

	virtual void notify_movement_finished();
	virtual void notify_position_changed();
	virtual void notify_movement_changed();
	virtual void notify_obstacle_reached();

	// Map.
	void set_map(Map& map);
	bool is_on_map();

	// Position.
	int get_x();
	int get_y();
	const Rectangle get_xy();
	void set_x(int x);
	void set_y(int y);
	void set_xy(int x, int y);
	void set_xy(const Rectangle &rec);
	void set_bounding_box(const Rectangle &rec);
	void set_bounding_box_from_sprite();
	Rectangle get_bounding_box();
	void set_bounding_box(Sprite& sprite);

	// Entity properties.
	int get_width();
	int get_height();
	const Rectangle& get_size();
	const Rectangle& get_origin();
	const Rectangle get_center_point();
	int get_direction();
	const std::string& get_name() const;

	// Displayed.
	const Rectangle get_displayed_xy();

	// Geometry
	bool overlaps(int x, int y);
	bool overlaps(const Rectangle &rec);
	bool overlaps(MapEntity &entity);

	int get_distance(int x, int y);
	int get_distance(MapEntity& other);

	// Collisions
	virtual bool is_obstacle_for(MapEntity& other);
	virtual bool is_hero_obstacle(Hero& hero);
	virtual bool is_destructible_obstacle(Destructible& destructible);
	virtual bool is_enemy_obstacle(Enemy& other);
	virtual bool is_jumper_obstacle(Jumper& jumper);

	virtual void check_collision_with_detectors();
	virtual void check_collision_with_detectors(Sprite& sprite);

	virtual void notify_collision_with_enemy(Enemy& enemy);
	virtual void notify_collision_with_enemy(Enemy& enemy, Sprite& enemy_sprite, Sprite& this_sprite);
	virtual void notify_collision_with_bubble(Bubble& bubble);
	virtual void notify_collision_with_destructible(Destructible& destructible);
	virtual void notify_collision_with_sensor(Sensor& sensor);
	virtual void notify_collision_with_jumper(Jumper& jumper);
	virtual void notify_collision_with_fire(Fire& fire);
	virtual void notify_collision_with_chest(Chest& chest);

	virtual void notify_sprite_frame_changed(Sprite& sprite, 
		const std::string& current_animation, int frame);

	// Loop
	virtual void update();
	virtual void display_on_map();
};

#endif