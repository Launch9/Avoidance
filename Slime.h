#pragma once
#include "Sub_NPC_A.h"
#include "DText.h"
#include "Sub_NPC_CD.h"
class Slime : public Sub_NPC_A, public Sub_NPC_CD
{
private:
	//This is for locking it for safer threading.
	sf::Mutex mtx;
	//This is how much damage has been to the slime.
	int damage_done = 0;
	//This is the max amount of damage you can do to the slime.
	int max_damage = 20;
	//This is the text that appears when you hurt the slime.
	DText damage_text;
	//These are the number of spaces the player has moved since the slime has last moved.
	unsigned int spaces_moved_since = 0;
	//Tells if it should be setting the animation for standing still.
	//If it has already set it before moving again, then it won't keep setting it.
	bool standing_toggle = false;
	//This damages the slime.
	void damage(Projectile &P);
	void reset();
public:
	Slime(int type, int x_pos, int y_pos, TileMap &TM);
	void ifPlayerMoved(int speed, int direction, int spaces, float remainder);
	//Called every frame.
	void tick(bool render);
	void animate();
	//This is what is called when the enemy dies.
	void when_dead();
};

