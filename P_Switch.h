#pragma once
#include "Basic_Tile_MOTHER.h"
#include "TempText.h"
class P_Switch : public Basic_Tile_MOTHER
{
private:
	void animate();
	int dir = 0;
	int typec = 0;
	int channel = 0;
	TempText text;
	//This tells whether or not the switch is active.
	bool is_active = false;
	//This is the sound that plays when the switch is set to a timer.
	sf::Sound timer_Sound;
	//This is the timer's ticks.
	float timer_ticks = 0;
	//This is the amount of ticks the timer needs to perform a function.
	float max_timer_ticks = 10;
	std::vector<std::vector<AniT>> spr;
	void Active();
	//This deactivates the switch.
	void Deactive();
	//Happens if collision with something important.
	void ifProjectileCollision(Projectile &P, int direction);
	//This is what happens if a projectile has collided with it.
	void Collide(Projectile &P, const int &direction);
public:
	
	P_Switch(const int &type, const int &x_pos, const int &y_pos, const int &Direction, const int &Switch, TileMap &TM);
	
};

