#pragma once
#include "NPC_MOTHER.h"
#include "DText.h"
//Item name: Com_MAIN
//Date made 12/31/2016 11:47:38 PM
//Made by Josh

class Com_MAIN : public NPC_MOTHER
{
private:
	//This boolean tells if the jaw is open or not.
	bool is_jaw_open = false;
	//This tells if the object is dead or not.
	bool is_dead = false;
	//This is the damage done.
	int damage_done = 0;
	//This is the damage that needs to be done.
	int max_damage = 100;
	//This is the damage text.
	DText damage_text;
	
	//This boolean tells if it should count cticks or not.
	bool should_count_cticks = true;
	//This is a pointer to the tilemap given in the constructor.
	//This is used for creating blast objects.
	TileMap *Tmap;
	//This tells when the eye should do its next command.
	float cticks = 0;
	//This is the command ID which is activated when the cticks reach the max_cticks.
	int c_event = 0;
	//This is the max number of cticks needed to call a command.
	float max_cticks = 3;
	//This is the type of Com_MAIN it is.
	int type = 0;
	//This is the number of ticks that have gone by since opening or closing the mouth.
	float pticks = 0;
	//This is the max number of ticks needed to get to its destination.
	float max_pticks = 0.5;
	//This integer tells whether it is opening, closing, or not doing anything with its mouth.
	//-1 == do nothing.
	//0 == open.
	//1 == close.
	int m_event = -1;
	//This integer tells whether its eyeball is opening or closing.
	//-1 == do nothing.
	//0 == opening.
	//1 == closing.
	int e_event = -1;
	//This is the eyeball sprite.
	ST eye;
	//These are the mouth pieces.
	std::vector<ST> jaws;
	//This contains all the sprites for the eyeball closing.
	std::vector<AniT> closing_ani;
	//This contains all the sprites for the eyeball opening.
	std::vector<AniT> opening_ani;
	//This is the switch that activates when dead.
	int channel = 2;
	//This function opens the eyeball.
	void open_eye();
	//This function closes the eyeball.
	void close_eye();
	//This function opens the mouth.
	void open_jaw();
	//This function closes the mouth.
	void close_jaw();
	//This fires the blasts.
	void fire_blasts();
	//This damages the object.
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
	//This overwrites the animation function.
	void animate();

	//} ~Virtual functions
	
public:

	
	Com_MAIN(int type, int x_pos, int y_pos, int SwitchChannel, TileMap &TM);
	
	
	
	

	

};

