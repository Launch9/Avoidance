#pragma once
#include "Basic_Tile_MOTHER.h"
#include <functional>
class PTile;
class PTile : public Basic_Tile_MOTHER
{
private:
	static std::vector<PTile *> PTile::Objects;
	//This is the lambda function to be used if you are stepping on to it.
	std::function <void(PTile *P)> lambda_geton;
	//This is the lambda function to be used if you are stepping off of it.
	std::function <void(PTile *P)> lambda_getoff;
	//These are the sprites that will be used during the life time of the PTile.
	std::vector<AniT> spr;
	//This tells the tile if the player has landed on the tile yet.
	bool has_landed = false;
	bool is_on = true;
	void animate();
	bool elseCollisionBefore(int PlayerChannel);
	void update();
public:
	friend PTile;
	//Deconstructor
	~PTile();
	//This updates all of the PTiles.
	static void update_all();
	//This function will turn the PTile off.
	void turn_off();
	//This function will turn the PTile on.
	void turn_on();
	//This is the switch channel.
	int SC = -1;
	//Constructor
	PTile(int type, int x_pos, int y_pos, int SwitchChannel, TileMap &TM);
	//This is a boolean that is an optional usage by a lambda.
	bool isSteppingon = false;
	//This tells the computer what to do if the player has landed on the tile.
	bool ifCollision(int PlayerChannel);
	
};

