#ifndef PATH_FINDING_H
#define PATH_FINDING_H

#include <map>
#include <list>
#include "Rectangle.h"
#include "Type.h"

class PathFinding {
	
private:
	/** A node is a 16x16 location on the map */
	class Node {

	public:
		Rectangle location;			/** location of this node on the map */
		int index;					/** index of this square on the map*/

		// total_cost = last_cost + heuristic
		int last_cost;				/** cost of the best path that leads to this node */
		int heuristic;				/** estimation of remaining cost to the target node */
		int total_cost;				/** total cost of this node */
		int parent_index;			/** index containing the best node leading to this node */
		char direction;		/** direction from the parent node to this node 0-7 */

		bool operator<(Node& other);
	};

	Map& map;							/** map */
	MapEntity& source;					/** source entity*/
	MapEntity& target;						/** target entity */
	const int max_distance;				/** maximum distance to be checked between two entities */

	static const Rectangle neighbours_locations[];

	std::map<int, Node> closed_list;	/** closed list, indexed by node locations on map */
	std::map<int, Node> opened_list;	/** opened list, indexed by node locations on map */
	std::list<int> open_list_indices;	/** indices of the open list elements sorted by priority */

	int get_square_index(const Rectangle& location);
	int get_manhattan_distance(const Rectangle& point1, const Rectangle& point2);
	void add_index_sorted(Node* node);
	std::string rebuild_path(const Node* final_node);


public:
	PathFinding(Map& map, MapEntity& source, MapEntity& target);
	~PathFinding();

	bool is_move_valid(Node& starting_node, int direction);

	std::string compute_path();
};


#endif