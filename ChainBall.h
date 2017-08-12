#pragma once
#include "NPC_MOTHER.h"
class ChainBall: public NPC_MOTHER
{
private:
	//0 = ball
	//1 = chain
	//These are the sprites that are being used.
	std::vector<CT> S;
	//This is the size of the ball at the end of the chain.
	int ballsize = 0;
	//This is the degree of rotation of the chain.
	float rotation = 0;
	//This tells the computer how fast the Chainball swings.
	int speed = 0;
	//This is pretty much a given...
	int startdirection = -1;
	//This is the length of the chain.
	int tan = 0;
public:
	ChainBall(int type, int startx, int starty, TileMap &TM, int distance_from_center = 2, int color = 0, int movementspeed = 1);
	void tick(bool render);
	void animate();
	void reset();
	void draw(sf::RenderWindow &win);
};

