#ifndef VIDEO_MANAGER_H
#define VIDEO_MANAGER_H

#include "Type.h"
#include "Rectangle.h"

#include <list>
#include <string>

class VideoManager {

public:
	enum VideoMode {	
		WINDOW_NORMAL,										/** the game surface is displayed on a window of 
															  * the same size */
		NB_MODES											/** number of existing video modes */
	};

	static const int surface_flags;							/** SDL flags for surfaces */

private:
	static VideoManager* instance;							/** single object of VideoManager */
	static Rectangle default_mode_sizes[NB_MODES];			/** default size of surface for each video mode */

	Rectangle mode_sizes[NB_MODES];							/** size of surfaces for each video mode */

	VideoMode video_mode;									/** current video mode of the scrren */
	Surface* screen_surface;								/** screen surface */

	VideoManager();
	~VideoManager();

	void blit(Surface& src_surface, Surface& dst_surface);

public:

	static void init();
	static void quit();
	static VideoManager* get_instance();

	VideoMode get_video_mode();
	void set_video_mode(VideoMode mode);
	void set_default_video_mode();

	void display(Surface& src_surface);
};


#endif