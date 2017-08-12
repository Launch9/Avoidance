#pragma once
#include "Basic_Tile_MOTHER.h"
#include "Player.h"
class Stair: public Basic_Tile_MOTHER
{
private:
	//This is the normal stair sprite without the red_X on it.
	AniT normal_sprite;
	
	int Floorv = 0;
	int Dungeonv = 0;
	//This tells whether or not you can go down the stairs.
	bool is_allowed = false;
	//This is the type of stair you want.
	int Type = 0;
	//This is a vector full of the stair objects.
	static std::vector<Stair *> Stair::Objects;
public:
	Stair(int x_pos, int y_pos, int Floor, int Dungeon, int type, TileMap &TM);
	~Stair();
	bool ifCollision(int PlayerChannel);
	//This checks to see if you have killed all the enemies or not.
	static void update();
};

