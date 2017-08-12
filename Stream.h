#pragma once
#include "Basic_Tile_MOTHER.h"
class Stream : Basic_Tile_MOTHER
{
private:
	int type = 0; //This is the type of sprite being used.
	float howFar = 0; //This is how far in the slide it is.
	sf::IntRect rect; //This is the bounding rectangle of the slide that should be used. Like the lava slide.
	sf::IntRect texrect; //This is the rectangle that is set to the sprite every frame.
	bool is_left = 0; //This tells if it flowing left, or right.
	float speed = 0; //This tells how fast it is flowing.
public:
	//This class makes a stream of something. e.g: lava, water.
	//Type: kind of sprite to be used.
	//is_flowing_left: whether or not it flows left or flows right.
	//Speed: how fast it flows.
	Stream(int Type, bool is_flowing_left, float Speed, int x_pos, int y_pos, TileMap &TM);
	void animate();
};

