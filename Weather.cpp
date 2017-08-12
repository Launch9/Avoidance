#include "stdafx.h"
#include "Weather.h"
#include "random2.h"
#include <iostream>
random2::RandomStorage Weather::rand_numbers;
random2::RandomStorage Weather::rand_numbers2;
#define how_many_numbers_to_generate 5000
#define deviation 10
#define max_T 2
#define max_T_deviation 3
Weather::Weather(int type, int x_pos, int y_pos, int y_end_in_blocks, TileMap &TM)
{
	typeID = 9;
	x = x_pos;
	y = y_pos;
	y_ground = y_end_in_blocks * 32;
	switch (type) {
	case 0:
		max_t = rand_numbers.getNum();
		ani = All_Sprites[TM.getTextureID()][typeID][0];
		x_M = -100;
		y_M = 100;
		x_D = -100;
		y_D = 100;
		break;
	case 1:
		max_t = rand_numbers.getNum();
		ani = All_Sprites[TM.getTextureID()][typeID][1];
		break;
	case 2: //These go sideways.
		max_t = random2::randomrange(1,4);
		ani = All_Sprites[TM.getTextureID()][typeID][0];
		x_M = -300;
		y_M = random2::randomrange_complex(-15,15);
		x_D = -300;
		y_D = random2::randomrange_complex(-15, 15);
		break;
	}
	for (unsigned int i = 0; i < 5; i++) {
		int mo_add = rand_numbers.getNum();
		R_Objects.push_back(new FO(ani, sf::Vector2i(x, y), sf::Vector2f(x_M + mo_add, y_M + mo_add), type, y_ground));
	}
	switch(type) {
	case 2:
		//This spreads some of the objects that were meant to go into the R_Objects, so that you don't have to wait for the objects to get there.
		for (unsigned int i = 0; i < 5; i++) {
			float rand_dist = random2::randomrange_complex(x_pos, y_ground - 2);
			float dist = rand_dist - x_pos;
			Objects.push_back(new FO(ani, sf::Vector2i(x - dist, y), sf::Vector2f(x_M, y_M), type, y_ground));
		}
		break;
	default:
		//This spreads some of the objects that were meant to go into the R_Objects, so that you don't have to wait for the objects to get there.
		for (unsigned int i = 0; i < 5; i++) {
			float rand_dist = random2::randomrange_complex(y_pos, y_ground - 2);
			float dist = rand_dist - y_pos;
			float x_add = x_M - (y_ground - rand_dist);
			Objects.push_back(new FO(ani, sf::Vector2i(x + x_add, y + dist), sf::Vector2f(x_M, y_M), type, y_ground));
		}
	}
	
	real_max_t = max_t;
	SavedParameters = { type, x, y, y_end_in_blocks };
	setup(sf::Color::Blue, x, y, "Weather");
	NonCol_InvisibleObjects.push_back(this);
}


Weather::~Weather()
{
	for (unsigned int i = 0; i < Objects.size(); i++) {
		delete Objects[i];
	}
	Objects.clear();
	for (unsigned int i = 0; i < R_Objects.size(); i++) {
		delete R_Objects[i];
	}
	R_Objects.clear();
}

void Weather::tick() {
	
	t += GF::getDelta();
	
	if (t >= real_max_t) {

		real_max_t = rand_numbers2.getNum();

		
			for (unsigned int i = 0; i < random2::randomrange(1,2); i++) {
				if (GF::does_exist(0, R_Objects.size()) == true) {
					Objects.push_back(R_Objects[0]);
					R_Objects.erase(R_Objects.begin());
				}
			}
			

		t = 0;
	}
	
	for (unsigned int i = 0; i < Objects.size(); i++) {
		Objects[i]->tick();
	}
	
	for (unsigned int i = 0; i < Objects.size(); i++) {
		if (Objects[i]->is_ready_to_delete() == true) {
			Objects[i]->reset(sf::Vector2i(x + 16, y + 16), sf::Vector2f(x_M, y_M), y_ground);
			R_Objects.push_back(Objects[i]);
			Objects.erase(Objects.begin() + i);
			//i--;
		}
	}
	
}

void Weather::init() {
	rand_numbers.setup(how_many_numbers_to_generate, -deviation, deviation);
	rand_numbers2.setup(how_many_numbers_to_generate, max_T, max_T + max_T_deviation);
}