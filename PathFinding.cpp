#include "PathFinding.h"
#include "MapEntity.h"
#include "Map.h"

const Rectangle PathFinding::neighbours_locations[] = {
  Rectangle( 8,  0, 16, 16 ),
  Rectangle( 8, -8, 16, 16 ),
  Rectangle( 0, -8, 16, 16 ),
  Rectangle(-8, -8, 16, 16 ),
  Rectangle(-8,  0, 16, 16 ),
  Rectangle(-8,  8, 16, 16 ),
  Rectangle( 0,  8, 16, 16 ),
  Rectangle( 8,  8, 16, 16 )

};

PathFinding::PathFinding(Map& map, MapEntity& source, MapEntity& target) :
  map(map),
  source(source),
  target(target),
  max_distance(200) {

}

PathFinding::~PathFinding() {

}

/**
 * Compute shortest path between source point and target point.
 * Return path or empty string if path not found(path is not found)
 * if distance is larger than 208 units.
 */
std::string PathFinding::compute_path() {
	Rectangle source_rectangle = source.get_bounding_box();
	Rectangle target_rectangle = target.get_bounding_box();
	
	std::string path = "";

	int target_index = get_square_index(target_rectangle);
	int total_mdistance = get_manhattan_distance(source_rectangle, target_rectangle);
	
	//std::cout << "computing path from: " << source_rectangle << ", to: " << target_rectangle << std::endl;
	
	// distance between two entities is too big to check.
	if(total_mdistance > max_distance) {
		return path;
	}

	Node starting_node;
	
	starting_node.location = source_rectangle;
	int index = get_square_index(source_rectangle);
	starting_node.index = index;
	starting_node.last_cost = 0;
	starting_node.heuristic = total_mdistance;
	starting_node.total_cost = starting_node.last_cost + starting_node.heuristic;
	starting_node.direction = ' ';
	starting_node.parent_index = -1;

	// Put starting node and its index on the open list.
	opened_list[index] = starting_node;
	open_list_indices.push_front(index);

	bool finished = false;
	while(!finished) {
		// Pick the node with the smallest total_distance on the opened_list
		int index = open_list_indices.front();
		Node* current_node = &opened_list[index];
		// Pop index from the opened_list
		open_list_indices.pop_front();
		// Push node on the closed list
		closed_list[index] = *current_node;
		opened_list.erase(index);
		current_node = &closed_list[index];

		//std::cout << "Picking the lowest cost node in the open list ("
		//<< (open_list_indices.size() + 1) << " elements): "
		//<< current_node->location << ", index = " << current_node->index
		//<< ", cost = " << current_node->last_cost << " + " << current_node->heuristic << "\n";

		// Check if we reached the destination.
		if(index == target_index) {
			finished = true;
			path = rebuild_path(current_node);
		} else {
			// Look at accessible nodes.
			// std::cout << " looking for accessible states\n";
			for(int i = 0; i < 8; i++) {
				Node new_node;
				int cost = (i & 1) ? 8 : 11;
				new_node.last_cost = current_node->last_cost + cost;
				new_node.location = current_node->location;
				new_node.location.move_xy(neighbours_locations[i]);
				new_node.index = get_square_index(new_node.location);
				
				//std::cout << "  node in direction " << i << ": index = " << new_node.index << std::endl;

				// Is node in closed list.
				bool in_closed_list = closed_list.find(new_node.index) != closed_list.end();
				
				if(!in_closed_list 
					&& get_manhattan_distance(new_node.location, target_rectangle) < max_distance
					&& is_move_valid(*current_node, i)) {

					bool in_opened_list = opened_list.find(new_node.index) != opened_list.end();
					if(!in_opened_list) {
						// Not in the open list so we add it
						new_node.heuristic = get_manhattan_distance(new_node.location, target_rectangle);
						new_node.total_cost = new_node.last_cost + new_node.heuristic;
						// Set parent index
						new_node.parent_index = index;
						// Set new direction
						new_node.direction = '0' + i;
						
						// Insert node in opened list
						opened_list[new_node.index] = new_node;
						add_index_sorted(&opened_list[new_node.index]);

					} else {
						// Node is already in the open list.
						Node* existing_node = &opened_list[new_node.index];
						// Check to see if current path is better.
						if(new_node.last_cost < existing_node->last_cost) {
							existing_node->last_cost = new_node.last_cost;
							existing_node->total_cost = existing_node->last_cost + existing_node->heuristic;
							existing_node->parent_index = index;
							open_list_indices.sort();
						}
					}
				}
			}
			if(open_list_indices.empty()) {
				finished = true;
			}
		}
	}
	//std::cout << "path found: " << path << ", open nodes: " << opened_list.size() << ", closed nodes: " 
	//<< closed_list.size() << std::endl;
	return path;
}

/**
 * Add index of a node to the sorted list of indices of the open list.
 */
void PathFinding::add_index_sorted(Node* node) {
	bool inserted = false;
	std::list<int>::iterator iter;
	for(iter = open_list_indices.begin(); iter != open_list_indices.end() && !inserted; iter++) {
		int index = *iter;
		Node* current_node = &opened_list[index];
		// Check to see if new_node total distance is smaller than existing nodes.
		if(current_node->total_cost >= node->total_cost) {
			open_list_indices.insert(iter, node->index);
			inserted = true;
		}
	}

	// Push node index to the back of the list.
	if(!inserted) {
		open_list_indices.push_back(node->index);
	}
}

/**
 * Returns index of a square in a map containing 8x8 squares.
 */
int PathFinding::get_square_index(const Rectangle& location) {
	int x8 = location.get_x() / 8;
	int y8 = location.get_y() / 8;

	return y8 * map.get_width8()  + x8;
}

/**
 * Return manhattan distance between to points.
 * Manhatann distance is the sum of horizontal and vertical components
 */
int PathFinding::get_manhattan_distance(const Rectangle& point1, const Rectangle& point2) {
	return std::abs(point2.get_x() - point1.get_x()) + std::abs(point2.get_y() - point1.get_y());
}

/**
 * Builds a string representing a path found by A*
 */
std::string PathFinding::rebuild_path(const Node* final_node) {
	const Node* current_node = final_node;
	std::string p = "";
	while(current_node->direction != ' ') {
		p = current_node->direction + p;
		current_node = &closed_list[current_node->parent_index];
		//std::cout << "current_node: " << current_node->index << ", path = " << p << std::endl;
	}
	return p;
}

bool PathFinding::is_move_valid(Node& starting_node, int direction) {
	Rectangle collision_box = neighbours_locations[direction];
	collision_box.move_xy(starting_node.location);

	return !map.test_collision_with_obstacles(collision_box, source);
}