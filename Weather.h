#pragma once
#include "ST.h"
#include "GF.h"
#include <iostream>
#include "Invisible_MOTHER.h"
#include "random2.h"
class Weather : public Invisible_MOTHER
{
private: 
	//This stores all the random numbers that the rain would need for offset of mom
	//If it runs out, the random numbers given will just loop back to the first one.
	static random2::RandomStorage Weather::rand_numbers;
	//This stores all the random numbers that are used for deviation of max_tick time.
	static random2::RandomStorage Weather::rand_numbers2;
	//This is the animation given to the objects created.
	std::vector<AniT> ani;
	//This is how much deviation there is when spawning a FO.
	//deviation = offset by random numbers.
	int deviation = 0;
	//This is the amount of ticks the weather object has.
	float t = 0;
	//This is how many ticks you need before it makes another FO.
	//This is used just for a reference.
	float max_t = 0;
	//This is the real max_t that is used.
	float real_max_t = 0;
	//This tells how fast the FO should be.
	float x_M = 0;
	float y_M = 0;
	//This tells the object how far the drops should be made when creating preliminary ones.
	float x_D = 0;
	float y_D = 0;
	//This is the y cordinate line cut off. (the ground level)
	int y_ground = 0;
	//This is the type of weather that is happeneing right now.
	int type = 0;
	//This is a falling object.
	struct FO {
	private:
		//This is the animation that runs when the object is detroyed.
		std::vector<AniT> end_ani;
		//This is the sprite that is drawn for the falling object.
		ST sprite;
		//These are momentum of the object.
		float x_mom = 0;
		float y_mom = 0;
		//This is the x position of the object.
		float x = 0;
		//This is the y position of the object.
		float y = 0;
		//This is the y cordinate line that tells when the Falling object should delete_self.
		int ground_line = 0;
		//This is the type of falling object that it is. rain, snow, cats?
		int type = 0;
		//This says that the object is dead.
		bool is_dead = false;
		//This says that the object is ready to be deleted.
		bool ready_to_delete = false;
		//These are the ticks for the animation at the end of its life time.
		float ticks = 0;
		//These are the max_ticks that the ticks variable needs to reach to change the sprite.
		float max_ticks = 0;
		//This is the index the sprite is currently on.
		int svectorindex = 0;
	public:
		
		FO(std::vector<AniT> animation, const sf::Vector2i &starting_position, const sf::Vector2f &momentum, int Type, int Ground_line) {
			type = Type;
			/*float dif = Ground_line - starting_position.y;
			int rand = random2::randomrange_complex(-dif, dif);
			ground_line = starting_position.y + rand;
			x = starting_position.x;
			y = starting_position.y;
			x_mom = momentum.x;
			y_mom = momentum.y;*/
			end_ani = animation;
			reset(starting_position, momentum, Ground_line);
			//sprite *= end_ani[0];
			//sprite.setPosition(x, y);
			sprite.setTexture(2);
			sprite.setup();
			max_ticks = 0.04;
			
			
		}
		void tick() {
			if (is_dead == true) {
				ticks += GF::getDelta();
				if (ticks >= max_ticks) {
					svectorindex++;
					sprite *= end_ani[svectorindex];
					ticks = 0;
					if (svectorindex >= end_ani.size() - 1) {
						delete_self();
					}

				}
				
			}
			else {
				x += x_mom * GF::getDelta();
				y += y_mom * GF::getDelta();
				switch (type) {
				case 2:
					if (x <= ground_line) {
						die();
					}
					break;
				default:
					if (y >= ground_line) {
						die();
					}
					break;
				}
				
				
			}
			sprite.setPosition(x, y);
		}
		inline bool is_ready_to_delete() {
			return ready_to_delete;
		}
		void die() {
			is_dead = true;
		}
		void delete_self() {
			ready_to_delete = true;
		}
		//This function resets the rain drop, it will not delete it, it will bring it back to its spawner and start over with different variables.
		//The x and y positions are where the rain drop should spawn again.
		void reset(const sf::Vector2i &spawning_position, const sf::Vector2f &momentum, int Ground_line) {
			ready_to_delete = false;
			x = spawning_position.x;
			y = spawning_position.y;
			x += rand_numbers.getNum();
			y += rand_numbers.getNum();
			x_mom = momentum.x;
			y_mom = momentum.y;
			x_mom += rand_numbers.getNum();
			y_mom += rand_numbers.getNum();
			is_dead = false;
			svectorindex = 0;
			ticks = 0;
			sprite *= end_ani[0];
			switch (type) {
			case 2:
				ground_line = Ground_line;
				break;
			default:
				float dif = (Ground_line - spawning_position.y) / 2;
				int rand = random2::randomrange(0, ceil(dif));
				ground_line = (spawning_position.y + dif) + rand;
			}
			
			sprite.setPosition(x, y);
		}
	};
	//Reserved Objects
	//These are taken out and put into objects when the weather tile needs more drops.
	std::vector<FO *> R_Objects; 
	//These are the objects that are being ticked currently.
	std::vector<FO *> Objects;
public:
	Weather(int type, int x_pos, int y_pos, int y_end_in_blocks, TileMap &TM);
	~Weather();
	//This is called every frame.
	void tick();
	//This initializes everything.
	static void init();
};

