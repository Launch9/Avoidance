#pragma once
#include "NPC_MOTHER.h"
///This class is suppost to be inherited by an NPC derived class.
///This allows the NPC to use static collision. Such as, a player walking into the NPC and not being able to walk through it.
///Basicly, when using this class, you can make it a collidable. Collision is checked in Basic_Tile_MOTHER.cpp
///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-
///When using this class, be sure to make the should_check boolean true, and also make sure that the scx and scy variables are according to where you wish the collision should take place.
///Otherwise, it will not do much of anything.
class Sub_NPC_StaticCollision
{
private:
	
	static std::vector<Sub_NPC_StaticCollision *> Sub_NPC_StaticCollision::Objects;
protected:
	//This is a boolean that tells if it should check for staticcollision.
	//If this boolean is equal to true, then it will check for static collision.
	//Otherwise, it will not check for static collision.
	bool should_check = false;
	//x position of static_collision.
	int scx = 0;
	//y position of static_collision.
	int scy = 0;
	//Constructor to put object into Objects vector for collision detection.
	Sub_NPC_StaticCollision();
	//Deconstructor called to clean up.
	virtual ~Sub_NPC_StaticCollision();
	//This staticly checks all the collision. Its basic playerx == characterx && playery == charactery.
	//This acts as a wall to the player.
	virtual bool checkCollision_over(int x_pos, int y_pos);
public:
	static bool checkCollision(int x_pos, int y_pos);
};

