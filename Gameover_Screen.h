#pragma once
#include "Screen_MOTHER.h"
class Gameover_Screen : public Screen_MOTHER
{
private:
	bool is_first = true;
	//This is the image of what was on the screen before you paused.
	sf::Texture preRender_Tex;
	//This is the sprite that is drawn to show what happened before the game was paused.
	sf::RectangleShape preRender;
	//This is the object that allows a choice to be made once paused.
	Choice C;
	//This draws everything.
	void render(sf::RenderWindow &win);
public:
	Gameover_Screen();
	bool main(sf::RenderWindow &win, TileMap &TM, sf::Event &s_event);
};

