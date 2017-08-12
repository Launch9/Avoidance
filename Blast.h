#pragma once
#include "Misc_Sprites.h"
#include "ST.h"
#include "GF.h"
class Blast : public Misc_Sprites
{
private:
	//This is a boolean used for the type 3 blast.
	bool made_new_blast = false;

	//This is a pointer to the tilemap.
	TileMap *Tmap;
	//This is used for a type three blast.
	//Used for knowing how long the lines needs to be.
	std::vector<int> dists = { 0,0,0,0 };
	//This is used for a type three blast.
	//Used for knowing how far the lines have gone so far.
	std::vector<int> iters = { 0,0,0,0 };
	//This is used for a type three blast.
	//Used for holding the sprite animation.
	std::vector<AniT> ani;
	//This is the initial x cordinate when created.
	int initx = 0;
	//This is the initial y cordinate when created.
	int inity = 0;
	//This is the position of the explosion.
	sf::IntRect c_rect;
	//This is the type of blast it is.
	int type = 0;
	struct B {
		B(int Type, const std::vector<AniT> &sprites, float Max_Ticks, int x_pos, int y_pos) {
			anisprites = sprites;
			
			x = x_pos;
			y = y_pos;
			sprite.setPosition(x_pos, y_pos);
			sprite.setTexture(2);
			sprite *= anisprites[0];
			switch (Type) {
			case 1:
				sprite.setColor(sf::Color::Red);
				break;
			}
			sprite.setup();
			max_ticks = Max_Ticks;
		}
		//This is a boolean to switch on or off for whatever you need to mark.
		bool toggle = false;
		//X coordinate
		int x = 0;
		//Y coordinate
		int y = 0;
		//This tells which frame the animation is on.
		int svectorindex = 0;
		//This is the max number of ticks required before the next frame is iterated.
		float max_ticks = 0;
		//This is how many ticks the animation currently.
		float ani_ticks = 0;
		//This is for animation.
		void animate() {
			ani_ticks += GF::getDelta();
			if (ani_ticks >= max_ticks) {
				svectorindex++;
				ani_ticks -= max_ticks;

				if (svectorindex >= anisprites.size()) {
					ready_to_be_deleted = true;
				}
				else {
					sprite *= anisprites[svectorindex];
				}


			}
		}
		//These are the sprites that are used for animation.
		std::vector<AniT> anisprites;
		//This is the sprite the blast uses.
		ST sprite;
		//This tells to see if the object is ready to be deleted.
		bool ready_to_be_deleted = false;
	};
	void check_Blasts_delete();
	//This contains all the B objects.
	std::vector<B *> Blasts = {};
	//This tells to see if the object is ready to be deleted.
	bool ready_to_be_deleted = false;
	//This contains all the objects that are created and still being used.
	static std::vector<Blast *> Blast::Objects;
	//This ticks the object.
	void tick();
	//This checks to see what objects are ready to be deleted. And deletes them.
	static void check_delete();
public:
	//Small explosion, kills anything inside the given tile including the player.
	Blast(int type, int x_pos, int y_pos, TileMap &TM);
	//Deconstructor
	~Blast();
	//Clears all blasts from the map.
	static void clear_all();
	//This ticks all the objects.
	static void tick_all();
};

