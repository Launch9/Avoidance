#pragma once
#include "Basic_Tile_MOTHER.h"
#include "DText.h"
//Item name: NPC_Spawner
//Date made 1/3/2017 5:45:21 PM
//Made by Josh

class NPC_Spawner : public Basic_Tile_MOTHER
{
private:
	//This is the total number of times it has spawned something.
	int total_spawns = 0;
	//This tells if the spawner is dead or not.
	bool is_Dead = false;
	//This is the animation that happens when the spawner is dead.
	std::vector<AniT> dead_ani;
	//This is what happens when the spawner dies.
	void die();
	//This is how many times you hit the spawner.
	int total_damage = 0;
	//This is how much damage needs to be done to defeat the spawner.
	int max_damage = 30;
	//This is the damage_text that appears when it gets hurt.
	DText damage_text;
	//This is a tilemap pointer.
	TileMap *Tmap;
	//This is the animation function.
	void animate();
	//This is called when the spawner gets hurt.
	void damage(Projectile &P);
	//This is the type of spawner that it is.
	int type = 0;
	//This tells the computer what to do if the player stepped on the tile.
	bool ifCollision(int PlayerChannel);
	//This tells the computer what to do if the player collides with the tile before he/she lands on it.
	bool ifCollisionBefore(bool isPlayer);
	//This tells the computer what to do if the player is not colliding with the tile.
	bool elseCollisionBefore(int PlayerChannel);
	//This tells the computer what to do if a projectile is colliding with the tile.
	//Will return false if not no collision occured.
	//Will return true if a collision occured.
	void ifProjectileCollision(Projectile &P, int direction);
	//This spawns an enemy.
	void spawn();
public:
	/*Put description here.*/
	NPC_Spawner(int Type, int x_pos, int y_pos, TileMap &TM);

};

