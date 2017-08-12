#pragma once
#include "Screen_MOTHER.h"
class Screen_Credits: public Screen_MOTHER
{
public:
	Screen_Credits();
	bool main(sf::RenderWindow &win, TileMap &TM, sf::Event &s_event);
};

