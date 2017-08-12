#pragma once
#include "NPC_MOTHER.h"
#include "Sub_NPC_A.h"
#include "Sub_NPC_StaticCollision.h"
///This is the tutorial character that tells you all the rules of the game.
///Giving the different type will define how she moves.
class Character: public Sub_NPC_A, public Sub_NPC_StaticCollision
{
private:
	void setCheck(bool TF);
	//void moveup(int distance);
	//void movedown(int distance);
	//void moveleft(int distance);
	//void moveright(int distance);
	void iterate();
	//This is the most recent number you put into the setAni function.
	int last_num = -1;
	//Old animation number.
	int last_doAninum = -1;
	//This tells what number to use after the doAnimation is done.
	int last_enddoAninum = -1;
	//This tells if a doAnimation animation is currently happening.
	bool is_doAnimation = false;
	//This tells if the character is standing still or not. If it is standing still, then the player can collide with the character.
	bool is_standingstill = false;
	//This tells the animate function if you are ready for random blinking.
	bool boolean_telling_if_it_is_ready_for_random_blinking_in_the_animate_function_because_I_want_the_character_to_blink_randomly = false;
	//These are the booleans that are used when making a character.
	bool check0 = false;
	bool check1 = false;
	bool check2 = false;
	bool check3 = false;
	bool check4 = false;
	// These is used for keeping a direction.
	int direction0 = -1;
	int direction1 = -1;
	int direction2 = -1;
	//This is used for making boundary boxes.
	sf::IntRect boundary0;
	//This is used for keeping time.
	float w_ticks0 = 0;
	float max_w_ticks0 = 1;
	//Ready ani change, Is the character ready to stop walking?
	bool ReadyAC = true;
	//These tell where the character was at.
	int x3 = 0;
	int y3 = 0;
	//This does the desired animation, then goes back to the animation index given.
	//doNum = the animation that is done.
	//endNum = the animation that it is set to after the doNum is finished.
	void doAnimation(int doNum, int endNum);
	//This sets up the animation that you want.
	void setAni(int num);
	//This tells the tick function what animation to set up and do.
	int Animation = -1;
	//This tells how many animation sequences have gone by.
	int AniN = 0;
	//This tells which direction she is walking.
	int direction = 0;
	//This tells how fast the character moves.
	int speed = 0;
	//This is how far the character needs to walk.
	int dist = 0;
	//This is the amount of ticks that have gone by since the character has started moving a direction.
	int movinganitick = 0;
	//This tells what kind of movement pattern the character should do.
	int Type = 0;
public:
	Character(int startx, int starty, int type, TileMap &TM);
	void tick(bool render);
	void reset();
	void next();
	void animate();
};

