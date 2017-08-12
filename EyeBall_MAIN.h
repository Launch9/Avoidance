#pragma once
#include "NPC_MOTHER.h"
#include "DText.h"
//Item name: EyeBall_MAIN
//Date made 12/4/2016 1:19:05 AM
//Made by Josh

class EyeBall_MAIN : public NPC_MOTHER
{
private:
	//These are the switches that all need to be on in order for it to be active.
	std::vector<int> switches;
	//This tells if it accepts collisions by projectiles.
	bool can_be_hit = false;
	//This tells if the object is active or not.
	bool is_act = false;
	//This tells if it is about to fire a projectile.
	bool about_to_fire = false;
	void animate();
	//This is the tick that checks to see if it is ready to fire a projectile.
	float FTicks = 0;
	//This is how many ticks it needs to have to fire a projectile.
	int max_FTicks = 10;
	//This is a sound that is played when it is charging up its shot.
	sf::Sound charge_sound;
	//This is the type of EyeBall_MAIN it is.
	int type = 0;
	//This is how much damage has been done to the NPC.
	int how_much_done = 0;
	//This is how much needs to be done to defeat him.
	int how_much_needed = 0;
	//This is the text that appears when the NPC is damaged.
	DText damage_text;
	//This is called when the NPC is damaged.
	void damage(Projectile &P);
	//This checks the switches an looks to see what it can do with that.
	void update_over();
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

	static std::vector<EyeBall_MAIN *> EyeBall_MAIN::Objects;
public:

	static void update();
	EyeBall_MAIN(int type, int x_pos, int y_pos, const std::vector<int> &Switches, TileMap &TM);
	~EyeBall_MAIN();
	
	
	

	

};

