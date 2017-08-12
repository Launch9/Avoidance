#pragma once
#include <vector>
#include "Misc_Sprites.h"
#include "ST.h"
class Flame : public Misc_Sprites
{
private:
	//These are the raw cordinates given by the constructor.
	sf::Vector2i pos0;
	//These are the cordinates of the top left of the flame sprite.
	sf::Vector2i pos;
	//This is the second position of the frame, this is used for checking collision.
	//Since the flame box is two tiles long, it must check on both tiles.
	//This is the top left of the second tile.
	sf::Vector2i pos2;
	//These are the sprites that are going to be animated through.
	std::vector<AniT> anisprites;
	//This is the sprite that the flame uses.
	ST sprite;
	//This animates the flame.
	void animate();
	//This is the frame of the animation that it is currently on.
	int svectorindex = 0;
	//This is the max_tick variable.
	float max_ticks = 5;
	//This is the animation tick variable.
	float ani_ticks = 0;
	//This tells the tick function if the object is ready to be deleted or not.
	bool ready_to_be_deleted = false;
	//This contains all the objects that are going to be ticked.
	static std::vector<Flame *> Flame::Objects;
	//This is the tick function of the object.
	void tick();
public:
	Flame(int type, int x_pos, int y_pos, int direction, TileMap &TM);
	//This clears all the flames in the game.
	static void clear_all();
	//This ticks all the objects.
	static void maintick();
};

