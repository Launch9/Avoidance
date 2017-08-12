#pragma once
#include "BackSplash_MOTHER.h"

class Space : public BackSplash_MOTHER
{
private:
	//This tells if the credits should fade in or out.
	bool should_fade_in = true;
	//This is the color object that has its alpha constantly changing.
	sf::Color fade_color;
	//This tells if it should be displayin the credits.
	bool should_display_credits = false;
	//This tells if the screen should fade out and go to the main menu.
	bool should_fade_out = false;
	//These are used for the fading out of the screen.
	float screenfade_ticks = 0;
	//This is how many screenfade_ticks are needed to make the screen completely black.
	int max_screenfade_ticks = 2;
	//This tells how long it has been waiting for the fading of a text in the credits.
	float cfade_ticks = 0;
	//This tells how long it should take to fade the credits in and out.
	int max_cfade_ticks = 4;
	//This is the index of the credits vector that should be drawn.
	int ci = 0;
	//This rectangle is used for fading the screen out.
	sf::RectangleShape fade_rect;
	//This contains all the credits.
	std::vector<sf::Text> credits;
	//This boolean tells if you have arrived into space yet.
	bool has_made_it = false;
	//This is how long it has been since fading in.
	float fade_ticks = 0;
	//This is how long it should take when fading in.
	float max_fade_ticks = 2;
	//This is how many ticks that have gone by before the rocket actually gets to space.
	float w_ticks = 0;
	//This is how many w_ticks needed to arrive to space.
	float max_w_ticks = 7;
	//This float keeps track of how far the ship has gone.
	float distance = 0;
	//This is the speed at which the rocket moves.
	float speed = 0;
	//These are the clouds in the background.
	sf::Sprite backdrop;
	//This is the planet in the background.
	sf::Sprite planet;
	void draw_FORE(sf::RenderWindow &win);
	void draw(sf::RenderWindow &win);
	void tick();
	//This resets all the variables and makes it ready for opening this screen up again later.
	void reset();
public:
	Space();
	
};

