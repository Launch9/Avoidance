#pragma once
#include "NPC_MOTHER.h"

class HomingSkull: public NPC_MOTHER
{
private:
	//This is the sound that plays everytime the teeth close.
	sf::Sound s;
	//This tells how fast the skull should accelerate.
	float speed = 0;
	//This tells how fast the skull is going in the x axis.
	float xvelocity = 0;
	//This tells how fast the skull is going in the y axis.
	float yvelocity = 0;
	//This determines if it has been activated.
	bool isActive = false;
	int t = 0;
	int maxtick = 5;
	int airresistance = 2;
	//This will kill the homingskull.
	void kill();
public:
	//This rotates all the sprites a certain degree.
	void rotate(int degree);
	//This will set the rotation of all the sprites in the animation.
	void setrotation(int degree);
	HomingSkull(int type, int start_x, int start_y, int color, int Speed, TileMap &TM);
	~HomingSkull();
	void tick(bool render);
	void animate();
	void reset();
	
};

