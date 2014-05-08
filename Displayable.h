#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

#include <iostream>

#include <SDL.h>
#include "SDL_image.h"

#include "Type.h"
#include "Rectangle.h"

class Displayable {

protected:
	Displayable() {};

public:
	virtual ~Displayable() {};

	//display
	virtual void raw_display(Surface& dst_surface, const Rectangle& dst_position) = 0;
};

#endif