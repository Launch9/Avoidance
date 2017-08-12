#include "stdafx.h"
#include "Space.h"
#include "Cam.h"
#include "Player.h"
#include "Font.h"
#include "App.h"
#define x_offset 300
Space::Space()
{
	typeID = 1;
	//This sets the backdrop to the apropriate sprite.
	backdrop = All_sprites[1][0][0];
	planet = All_sprites[1][0][1];
	planet.setPosition(128, 128);
	fade_rect.setPosition(0, 0);
	fade_rect.setSize(sf::Vector2f(Cam::getdisplaywidth(), Cam::getdisplayheight()));
	fade_color = sf::Color(255, 255, 255, 0);
	speed = 3;
	sf::Text t1("Made using SFML", Font::Get_isocpeur(), 30);
	t1.setPosition(Cam::getdisplaywidth() / 8, Cam::getdisplayheight() / 2);
	t1.setColor(fade_color);
	sf::Text t2("Much appreciation to: Nick for \ngreat support and awesome art.", Font::Get_isocpeur(), 30);
	t2.setPosition(Cam::getdisplaywidth() / 8, Cam::getdisplayheight() / 2);
	t2.setColor(fade_color);
	sf::Text t3("Jesse for the testing and \nconstant interest, for my work.", Font::Get_isocpeur(), 30);
	t3.setPosition(Cam::getdisplaywidth() / 8, Cam::getdisplayheight() / 2);
	t3.setColor(fade_color);
	sf::Text t5("Made by Joshua Schudt", Font::Get_isocpeur(), 30);
	t5.setPosition(Cam::getdisplaywidth() / 8, Cam::getdisplayheight() / 2);
	t5.setColor(fade_color);
	
	credits = { t1, t2, t3, t5 };
	sf::Color c(255, 255, 255, 0);
	backdrop.setColor(c);
	planet.setColor(c);
	//Setting the main object equal to this object.
	Object = this;
}


void Space::draw(sf::RenderWindow &win) {
	Cam::drawGUI_chan(0, win, backdrop);
	Cam::drawGUI_chan(0, win, planet);
	
}

void Space::draw_FORE(sf::RenderWindow &win) {
	Cam::drawGUI_chan(0, win, credits[ci]);
	if (should_fade_out == true) {
		Cam::drawGUI_chan(0, win, fade_rect);
	}
}

void Space::tick() {
	if (has_made_it == true) {
		distance += GF::getDelta() * speed;
	}
	//std::cout << "w_ticks: " << w_ticks << "fade_ticks: " << fade_ticks << std::endl;
	if (should_fade_out == true) {
		sf::Color fc(255, 255, 255, 255 * (screenfade_ticks / max_screenfade_ticks));
		screenfade_ticks += GF::getDelta();
		fade_rect.setFillColor(fc);
		if (screenfade_ticks >= max_screenfade_ticks) {
			App::goto_mainmenu();
			reset();
		}
	}
	else {
		if (should_display_credits == false) {
			if (w_ticks >= max_w_ticks) {
				has_made_it = true;
				fade_ticks += GF::getDelta();
				sf::Color cb(255, 255, 255, 255 * (fade_ticks / max_fade_ticks));
				backdrop.setColor(cb);
				planet.setColor(cb);
				if (fade_ticks >= max_fade_ticks) {
					should_display_credits = true;
					sf::Color c(255, 255, 255, 255);
					backdrop.setColor(c);
					planet.setColor(c);

				}
			}
			else {
				w_ticks += GF::getDelta();
			}
		}
		else {
			switch (should_fade_in) {
			case 0:
				cfade_ticks -= GF::getDelta();
				break;
			case 1:
				cfade_ticks += GF::getDelta();
				break;
			}

			fade_color.a = 255 * (cfade_ticks / max_cfade_ticks);

			switch (should_fade_in) {
			case 0:
				if (cfade_ticks <= 0) {
					fade_color.a = 0;
					cfade_ticks = 0;
					ci++;
					should_fade_in = 1;
					if (ci >= credits.size()) {
						should_display_credits = false;
						should_fade_out = true;
						ci = 0;
					}

				}
				break;
			case 1:
				if (cfade_ticks >= max_cfade_ticks) {
					fade_color.a = 255;
					should_fade_in = 0;
					cfade_ticks = max_cfade_ticks;
				}
				break;
			}
			credits[ci].setColor(fade_color);
		}
	}
	
	
	
	if (Player::PlayerObjects.size() != 0) {
		backdrop.setPosition(((-Cam::getdisplaywidth() / 2) - (Player::PlayerObjects[0]->getvx() / 4)) - x_offset, ((-Cam::getdisplayheight() / 2) - (Player::PlayerObjects[0]->getvy() / 4)) + distance);
		planet.setPosition((128 - (Player::PlayerObjects[0]->getvx() / 4)), (128 - (Player::PlayerObjects[0]->getvy() / 4)) + (distance / 4));
	
	}
}

void Space::reset() {
	fade_ticks = 0;
	distance = 0;
	should_fade_out = false;
	should_display_credits = false;
	ci = 0;
	cfade_ticks = 0;
	should_fade_in = 1;
	w_ticks = 0;
	has_made_it = false;
}