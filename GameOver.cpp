#include "GameOver.h"
#include "Game.h"
#include "Hero.h"
#include "Sprite.h"
#include "Map.h"
#include "Surface.h"
#include "System.h"
#include "Equipment.h"
#include "TargetMovement.h"

GameOver::GameOver(Game& game, int hero_direction) :
  game(game),
  game_over_surface("game_over_menu.png"),
  state(GameOver::State::WAIT_START),
  date_interval(100),
  fade_away("game_over_fade.txt"),
  fairy("fairy.txt"),
  hero_dead("tunic.txt"),
  fairy_movement(NULL) {
	fairy.set_current_animation("fairy");
	hero_dead.set_current_animation("damage");

	const Rectangle& camera_position = game.get_map().get_camera_position();
	const Rectangle& hero_xy = game.get_hero_xy();
	this->hero_dead_x = hero_xy.get_x() - camera_position.get_x();
	this->hero_dead_y = hero_xy.get_y() - camera_position.get_y();

	next_state_date = System::now() + date_interval;
}

GameOver::~GameOver() {
	delete fairy_movement;
}

bool GameOver::is_state_finished() {
	return state == GameOver::State::RESUME;
}

void GameOver::update() {
	uint32_t now = System::now();
	hero_dead.update();

	switch(state) {
		case GameOver::State::WAIT_START:
			if(now >= next_state_date) {
				std::cout << now << " " << next_state_date << std::endl;
			}
			if(now >= next_state_date) {
				std::cout << state << "asd" << std::endl;
				state = State::DYING;
				//fade_away.restart_animation();
			}
			break;
		case GameOver::State::DYING:
			//fade_away.update();
			//if(fade_away.is_animation_finished()) {
			//state = GameOver::State::RED_SCREEN;
			hero_dead.set_current_animation("dying");
			hero_dead.set_current_direction(0);
			next_state_date = now + 2000;
			//}
			break;

		/*
		case GameOver::State::RED_SCREEN:
			hero_dead.update();
			if(hero_dead.is_animation_finished() && now >= next_state_date) {
				state = GameOver::State::BLACK_SCREEN;
				fade_away.set_current_animation("open");
			}
			break;
			case GameOver::State::BLACK_SCREEN:
				fade_away.update();
				if(fade_away.is_animation_finished()) {
					Equipment& equipment = game.get_equipment();
					if(equipment.has_item("fairy")) {
						state = GameOver::State::FAIRY;
						this->fairy_x = hero_dead_x + 12;
						this->fairy_y = hero_dead_y + 12;
						fairy_movement = new TargetMovement(240, 22, 96);
						fairy_movement->set_xy(fairy_x, fairy_y);
						equipment.notify_item_used("fairy");
					} else {
						state = GameOver::State::MENU;
					}
				}
			break;
		case GameOver::State::FAIRY:
			fairy.update();
			fairy_movement->update();
			fairy_x = fairy_movement->get_x();
			fairy_y = fairy_movement->get_y();
			if(fairy_movement->is_finished()) {
				state = GameOver::State::WAIT_END;
				next_state_date = now + date_interval;
			}
			break;
		case GameOver::State::WAIT_END:
			if(now >= next_state_date) {
				state = GameOver::State::RESUME;
				game.get_hero_dead();
			}
			break;
		case GameOver::State::RESUME:
			break;
		case GameOver::MENU:
			fairy.update();
			break;
		*/
	}
}

void GameOver::display(Surface& dst_surface) {
	hero_dead.raw_display(dst_surface, hero_dead_x, hero_dead_y);
}

/*
void GameOver::display(Surface& dst_surface) {
	//if(state >= GameOver::State::DYING)
	//	dst_surface.fill_with_color(Color::get_black());
	
	if(state <= GameOver::State::BLACK_SCREEN) {
		if(state == GameOver::State::RED_SCREEN) {
			dst_surface.fill_with_color(Color::get_red());
		} else {
			fade_away.raw_display(dst_surface, hero_dead_x, hero_dead_y);
		}
	}
	if(state <= GameOver::State::WAIT_END) {
		hero_dead.raw_display(dst_surface, hero_dead_x, hero_dead_y);
		if(state == GameOver::State::FAIRY) {
			fairy.raw_display(dst_surface, fairy_x, fairy_y);
		}
	} else if(state == GameOver::State::MENU) {
		game_over_surface.display(dst_surface);
		fairy.raw_display(dst_surface, fairy_x, fairy_y);
	}
}
*/