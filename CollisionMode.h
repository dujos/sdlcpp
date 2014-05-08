#ifndef COLLISION_MODE_H
#define COLLISION_MODE_H

enum CollisionMode {
	
	COLLISION_NONE = 0x0000,                 /** No collision detected. Detector detects no activity */
	COLLISION_RECTANGLE = 0x0001,            /** Collision if entity's rectangle overlaps detector's rectangle */
	COLLISION_INSIDE = 0x0002,               /** Collision if entity's rectangle is inside  detectors rectangle */
	COLLISION_ORIGIN_POINT = 0x0004,         /** Collision if entity's origin point is inside detectors rectangle */
	COLLISION_FACING_POINT = 0x0008,         /** Collision if entity's center is inside detectors rectangle */
	COLLISION_CENTER = 0x0010
};

#endif