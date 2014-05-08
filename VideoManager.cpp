#include "VideoManager.h"
#include "Surface.h"
#include "Globals.h"

VideoManager* VideoManager::instance = NULL;

const int VideoManager::surface_flags = SDL_SWSURFACE;

//Size of the screen in each video mode.
Rectangle VideoManager::default_mode_sizes[] = {
	Rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)
};

//Initializes the video system and creates the window.
void VideoManager::init() {
	instance = new VideoManager();
}

//close the video system.
void VideoManager::quit() {
	delete instance;
}

//Return video manager.
VideoManager* VideoManager::get_instance() {
	return instance;
}

VideoManager::VideoManager() : 
  screen_surface(NULL) {

	  const std::string title = "test";
	  SDL_WM_SetCaption(title.c_str(), NULL);

	  for(int i = 0; i < NB_MODES; i++)
		  mode_sizes[i] = default_mode_sizes[i];

	  int flags = SDL_SWSURFACE;

	  mode_sizes[WINDOW_NORMAL].set_size(SCREEN_WIDTH, SCREEN_HEIGHT);

	  set_default_video_mode();
}

VideoManager::~VideoManager() {
	delete screen_surface;
}

void VideoManager::set_default_video_mode() {

	VideoMode mode;
	mode = VideoMode::WINDOW_NORMAL;

	set_video_mode(mode);
}

//Sets video mode
void VideoManager::set_video_mode(VideoMode mode) {
	int flags = surface_flags;

	SDL_Surface* screen_internal_surface = 
		SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, flags);

	this->screen_surface = new Surface(screen_internal_surface);
	this->video_mode = mode;
}

VideoManager::VideoMode VideoManager::get_video_mode() {
	return video_mode;
}

//Blits a surface on a screen with the current video mode.
void VideoManager::display(Surface& src_surface) {
	switch(video_mode) {
	
	    case VideoMode::WINDOW_NORMAL:
			blit(src_surface, *screen_surface);
			break;
		default:
			break;
	}
	SDL_Flip(screen_surface->get_surface());
}

void VideoManager::blit(Surface& src_surface, Surface& dst_surface) {
	src_surface.display(dst_surface);
}