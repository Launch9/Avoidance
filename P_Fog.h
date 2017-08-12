#pragma once
#include "Invisible_MOTHER.h"
#include "CT.h"
#include "random2.h"
#include <iostream>
//Item name: P_Fog
//Date made 2/4/2017 6:23:10 PM
//Made by Josh

class P_Fog : public Invisible_MOTHER
{
private:
	//This is for identification purposes within this class type.
	int type = 0;
	//This is the max number of times that the c_ticks can create more parts.
	int parts_left_create = 4;
	//These are ticks that are used to create the objects slowly.
	float c_ticks = 0;
	//Once the c_ticks reached these max_c_ticks, then it will create a new object.
	float max_c_ticks = 1;
	std::vector<AniT> tex_coords;
	struct part {
		std::vector<AniT> t_coords; //This should point to the tex_coords within the P_Fog object.
		float rot_speed; //Rotationary speed.
		sf::Vector2f position;
		sf::Vector2f spawn_position; //This is the coordinates where the particle was created in the first place.
		sf::Color color; //This is the color of the sprite.
		sf::Vector2f vels; //Velocities.
		float e_ticks = 0; //How long it has been existing.
		float max_e_ticks = 2; //How long until it gets destroyed.
		CT sprite; //This is what is drawn to the screen.
		part(int Type, float x_pos, float y_pos, std::vector<AniT> sprite_coords, float start_ticks) {
			spawn_position.x = x_pos;
			spawn_position.y = y_pos;
			e_ticks = max_e_ticks / start_ticks;
			t_coords = sprite_coords;
			sprite.setTexture(2);
			rot_speed = random2::randomrange_complex(-30, 30);
			sprite.setOrigin(16, 16);
			sprite.setPosition(x_pos + 16, y_pos + 16);
			position.x = x_pos;
			position.y = y_pos;
			vels.x = random2::randomrange_complex(-30, 30);
			vels.y = random2::randomrange_complex(-30, 30);
			color = sf::Color(255, 255, 255, 255);
			sprite *= t_coords[random2::randomrange(0, t_coords.size() - 1)];
			sprite.setup();
		}
		void tick() {
			sprite.rotate(rot_speed * GF::getDelta());
			position.x += vels.x * GF::getDelta();
			position.y += vels.y * GF::getDelta();
			sprite.setPosition(position);
			e_ticks += GF::getDelta();
			
			color.a = 255 * ((max_e_ticks - e_ticks) / max_e_ticks);
			if (e_ticks < 0) {
				color.a = 0;
			}
			sprite.setColor(color);
			if (e_ticks >= max_e_ticks) {
				reset();
			}

		}
		//This sets the particle to go back to it's original spawn coordinates.
		void reset() {
			e_ticks = 0;
			position = spawn_position;
			vels.x = random2::randomrange_complex(-30, 30);
			vels.y = random2::randomrange_complex(-30, 30);
			rot_speed = random2::randomrange_complex(-30, 30);
		}
	};
	std::vector<part *> particles;
	//Virtual functions {

	//This is called if the player lands on the tile.
	void if_landed_on();
	//This is called every frame.
	void tick();

	//}
public:
	/*insert constructor description here.*/
	P_Fog(int Type, int x_pos, int y_pos, TileMap &TM);
	~P_Fog();
	
};

