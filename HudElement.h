#ifndef HUD_ELEMENT_H
#define HUD_ELEMENT_H

#include "Rectangle.h"
#include "Surface.h"
#include "Equipment.h"

class HudElement {

protected:
	Game* game;
	Equipment* equipment;

	Surface surface_displayed;
	Rectangle dst_position;

	bool visible;
	int opacity;

	HudElement(Game& game, int x, int y, int width, int height);

public:
	virtual ~HudElement();

	void set_visible(bool visible);
	void set_position(int x, int y);
	void set_opacity(int opacity);

	bool is_visible();

	virtual void update();
	virtual void rebuild();
	void display(Surface& dst_surface);
};

#endif