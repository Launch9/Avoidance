#pragma once
#include "NPC_MOTHER.h"
#include "DText.h"
//Item name: Squisher
//Date made 11/15/2016 1:58:44 AM
//Made by Josh

class Squisher : public NPC_MOTHER
{
private:
	//This is the ticking sound that plays when moving.
	sf::Sound sound;
	//This is how much damage you need to do to kill the enemy.
	int max_damage = 30;
	//This is how much damage you have done to the NPC.
	int total_damage = 0;
	//This is the type of Squisher it is.
	int type = 0;
	//This is the velocity of the squisher object.
	float vel = 0;
	//This is direction that the squisher object squishes.
	int direction = 0;
	//This is the distance the block is from the starting point.
	float distance = 0;
	//This is the max_distance the block goes before coming back.
	float max_distance = 0;
	//This tells whether or not the squisher is going forward or backward.
	//If this is equal to -1, then it is not active.
	//If this is equal to 0, then it is going backward.
	//If this is equal to 1, then it is going forward.
	int isForward = -1;
	//This is the speed that the block accelerates at.
	float speed = 0;
	//This is the spring sprite.
	CT spring;
	//This is the switch that the spring activates by.
	int Switch = -1;
	//This updates all the squishers in the game.
	void update();
	//This is the text that shows how much health the NPC has.
	DText damage_text;
	//This is called every time the NPC gets hurt.
	void damage(Projectile &P);
	
	
	//Virtual functions{

	//This function is called when the NPC is revived.
	void when_revive();
	//This function is called when the NPC is killed or deleted_self.
	void when_dead();
	//This is called when the player dies, the editor starts, etc.
	//Its purpose is to place everything back to where it started.
	void reset();
	//This is the tick function that is overwritten.
	//This is called every frame.
	void tick(bool render);

	//} ~Virtual functions
	//This contains all the squisher objects.
	static std::vector<Squisher *> Squisher::Objects;
	
public:

	//Deconstructor
	~Squisher();
	//Constructor
	Squisher(int type, int x_pos, int y_pos, int Direction, int distance_in_blocks, int Speed, int SwitchChannel, TileMap &TM);
	//This updates all the squishers.
	static void update_all();
	
	
	

	

};

