#ifndef PIXELS_H
#define PIXELS_H

#include "Surface.h"
#include "Rectangle.h"

class Pixels {

private:
	int width;								/** image width in pixels */
	int height;								/** image height in pixels */
	int nb_integers_per_row;				/** number of uint32_t required to store the bits of a row of an image*/
	uint32_t** bits;						/** 2d array representing the transparancy of each pixel */

public:
	Pixels(Surface& surface, const Rectangle& image_position);
	~Pixels();

	bool test_collision(const Pixels& other, const Rectangle& location1, const Rectangle& location2) const;

};

#endif