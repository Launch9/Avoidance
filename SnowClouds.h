#pragma once
#include "BackSplash_MOTHER.h"
class SnowClouds : public BackSplash_MOTHER
{
private:
	//These are the clouds in the background.
	sf::Sprite backdrop;
	void draw(sf::RenderWindow &win);
	void tick();
public:
	SnowClouds();
	
};

