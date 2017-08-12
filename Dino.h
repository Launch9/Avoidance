#pragma once
#include "TileMap.h"
#include "Sub_NPC_A.h"
#include "Sub_NPC_CD.h"
#include "DText.h"
class Dino : public Sub_NPC_A, public Sub_NPC_CD
{
private:
	//This is how much damage needs to be done to defeat the enemy.
	int damage_needed = 0;
	//This is how much damage has been done.
	int damage_done = 0;
	//This is a pointer to the tilemap object that is passed to the dino from the constructor.
	TileMap *t_ptr;
	//This is how many spaces the player has to move before the dino breathes fire.
	int moves_needed = 5;
	//This is how many moves the player has made since the dino has breathed fire.
	int moves_since = 0;
	//This tells the object if it is standing still or not.
	bool standing_toggle = false;
	//This shows how much health the NPC has.
	DText damage_text;
	//This is called when the NPC takes damage.
	void damage(Projectile &P);
public:
	Dino(int type, int x_pos, int y_pos, TileMap &TM);
	//This is called if the player has moved a tile.
	void ifPlayerMoved(int speed, int direction, int spaces, float remainder);
	//Called every frame.
	void tick(bool render);
	//This is called when the NPC dies.
	void when_dead();
	~Dino();
};

