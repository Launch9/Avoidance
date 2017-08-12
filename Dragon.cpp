#include "stdafx.h"
#include "Dragon.h"
#include <iostream>
#include "Player.h"
#include <cmath>
#include "Debug.h"
#include "P_Switch_MAIN.h"
#include "Editor.h"
#include "random2.h"
#define Pi 3.14159265
#define Extra 8
#define Default_X_Speed 10000
#define terminalvelocity 9000
//#define dist 28
Dragon::Dragon(int Type, int x_pos, int y_pos, int how_long, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	initx = x;
	inity = y;
	delx = x;
	dely = y;
	x2 = x;
	y2 = y;
	type = Type;
	typeID = 7;
	How_long = how_long;
	if (Editor::GetStatus() == true) {
		setPause(true);
	}
	else {
		setPause(false);
	}
	number_of_eye_balls = 4;
	SavedParameters = { typeID, Type, x_pos, y_pos, how_long };
	acceleration = 50 * Extra;
	sprite.setOrigin(16, 16);
	sprite.setPosition(x_pos, y_pos);
	
	switch (type) {
	case 1:
		Switch = 0;
		break;
	}
	for (unsigned int i = 0; i < how_long + 3; i++) {
		P_Data.push_back(new Data(sf::Vector2f(x,y), 0, 0));
	}
	sprite.setTexture(2);
	Sprites = All_Sprites[TM.getTextureID()][typeID];
	sprite *= Sprites[0][0];
	Ani_Sprites = All_Sprites[TM.getTextureID()][typeID][0];
	sprite.setup();
	create_parts();

	for (unsigned int i = 0; i < how_long + 3; i++) {
		R_Data.push_back(new RData(0, 0));
	}
	
	//y_speed = 0.5;
	x_speed = Default_X_Speed;
	NPC_Cache.push_back(this);
}

Dragon::~Dragon()
{
	//Deleting pointers to prevent memory leaks.
	for (unsigned int i = 0; i < Parts.size(); i++) {
		delete Parts[i];
	}
	for (unsigned int i = 0; i < P_Data.size(); i++) {
		delete P_Data[i];
	}
	for (unsigned int i = 0; i < R_Data.size(); i++) {
		delete R_Data[i];
	}
	//Erasing nullptrs
	Parts.clear();
	R_Data.clear();
	P_Data.clear();
}

void Dragon::tick(bool render) {
	
	if (is_active == true && isPaused == false) {
		drop_ticks += GF::getDelta();
		if (drop_ticks >= max_drop_ticks) {
			drop_in();
			drop_ticks = 0;
		}
		drop_in_color.b = 255 * ((max_drop_ticks - drop_ticks) / max_drop_ticks);
		drop_in_color.g = 255 * ((max_drop_ticks - drop_ticks) / max_drop_ticks);
		sprite.setColor(drop_in_color);
		for (unsigned int i = 0; i < Parts.size(); i++) {
			Parts[i]->Sprite.setColor(drop_in_color);
		}
		//t += GF::getDelta();
		//Checking projectile collision.
		int col_var = 0; //Collision variable
		for (unsigned int i = 0; i < Parts.size(); i++) {
			for (int b = i - 1; b < i + 2; b++) {
				if (GF::does_exist(b, Parts.size()) == true) {
					col_var = Projectile::DynamicCheckCollisionHeavy2(Parts[b]->getPosition().x - 16, Parts[b]->getPosition().y - 16, 32, 32, 0, false);
					if (col_var != -1) {
						Parts[i]->damage(Projectile::VP[col_var], this);
						break;
					}
				}
			}

		}

		//Making sure that all the parts get put in their corresponding spot. Using previous data.
		tan = atan2(-y_speed, -x_speed);
		float degree = atan2(-y_speed, -x_speed);
		degree = degree * 180 / Pi;
		sprite.setRotation(degree);
		Parts[0]->setRotation(degree);
		//Calculating the direction that it needs to fly in.
		x_speed -= (acceleration * (x - Player::PlayerObjects[0]->getvx())) * GF::getDelta() * getGlobalSpeed();
		y_speed -= (acceleration * (y - Player::PlayerObjects[0]->getvy())) * GF::getDelta() * getGlobalSpeed();
		
		if (x_speed >= terminalvelocity) {
			x_speed = terminalvelocity;
		}
		else if (x_speed <= -terminalvelocity) {
			x_speed = -terminalvelocity;
		}
		if (y_speed >= terminalvelocity) {
			y_speed = terminalvelocity;
		}
		else if (y_speed <= -terminalvelocity) {
			y_speed = -terminalvelocity;
		}
		/*if (x > Player::PlayerObjects[0]->getvx()) {
		x_speed -= acceleration * GF::getDelta() * getGlobalSpeed();
		}
		else {
		x_speed += acceleration * GF::getDelta() * getGlobalSpeed();
		}
		if (y > Player::PlayerObjects[0]->getvy()) {
		y_speed -= acceleration * GF::getDelta() * getGlobalSpeed();
		}
		else {
		y_speed += acceleration * GF::getDelta() * getGlobalSpeed();
		}*/

		//Setting the older positions to the one before this frame.
		old_position.x = x;
		old_position.y = y;
		//Moving the sprite according to the speed cordinates.
		x += x_speed * GF::getDelta() * getGlobalSpeed();
		y += y_speed * GF::getDelta() * getGlobalSpeed();
		sprite.setPosition(x, y);
		//t += x_speed * GF::getDelta() * getGlobalSpeed() + y_speed * GF::getDelta() * getGlobalSpeed();

		if (distance >= max_distance) {
			float dist_dif = distance - max_distance;
			float y_save = 0;
			float x_save = 0;
			y_save = old_position.y + (sin(tan) * dist_dif);
			x_save = old_position.x + (cos(tan) * dist_dif);
			P_Data.push_back(new Data(sf::Vector2f(x_save, y_save), sprite.getRotation(), tan));
			R_Data.push_back(new RData(degree, tan));
			delete R_Data[0];
			R_Data.erase(R_Data.begin());
			t -= maxtick;
			delete P_Data[0];
			P_Data.erase(P_Data.begin());
		}


		float r_y_pos = 0;
		float r_x_pos = 0;
		float r2_y_pos = 0;
		float r2_x_pos = 0;
		for (unsigned int i = P_Data.size() - 1; i > 0; i--) {
			float dist = 32 - (32 * (distance / max_distance));
			bool should_change = false;
			if (i == P_Data.size() - 1) {
				r_x_pos = P_Data[P_Data.size() - 1]->position.x;
				r_y_pos = P_Data[P_Data.size() - 1]->position.y;
				r2_y_pos = (sin(R_Data[R_Data.size() - 1]->tangent) * dist);
				r2_x_pos = (cos(R_Data[R_Data.size() - 1]->tangent) * dist);
				should_change = true;
			}
			else {
				r_x_pos = P_Data[i + 1]->position.x;
				r_y_pos = P_Data[i + 1]->position.y;
				r2_y_pos = sin(R_Data[i + 1]->tangent) * dist;// *(dist + (i * dist));
				r2_x_pos = cos(R_Data[i + 1]->tangent) * dist;// *(dist + (i * dist));
			}

			if (should_change = false) {
				Parts[i]->setPosition(sf::Vector2f(r_x_pos + r2_x_pos, r_y_pos + r2_y_pos));
				//P_Data[i]->position = sf::Vector2f(r_x_pos + r2_x_pos, r_y_pos + r2_y_pos);
				Parts[i]->setRotation(R_Data[i]->rotation);
			}
			else {
				Parts[i - 1]->setPosition(sf::Vector2f(r_x_pos + r2_x_pos, r_y_pos + r2_y_pos));
				//P_Data[i]->position = sf::Vector2f(r_x_pos + r3_x_pos, r_y_pos + r3_y_pos);
				Parts[i - 1]->setRotation(R_Data[i]->rotation);
			}


		}
		distance = GF::getDistance_Pixels(sf::Vector2f(x, y), sf::Vector2f(P_Data[P_Data.size() - 1]->position.x, P_Data[P_Data.size()
			- 1]->position.y));
		for (unsigned int i = 0; i < Parts.size(); i++) {
			if (DynamicCheckPlayerCollision(Parts[i]->getPosition().x - 10, Parts[i]->getPosition().y - 10, 26, 26) == true) {
				KillPlayer();
			}
		}
	}
	
}

void Dragon::animate() {

}

int Dragon::check_parts_how_many() {
	int total = 0;
	for (unsigned int i = 0; i < Parts.size(); i++) {
		if (Parts[i]->type == 1) {
			total++;
		}
	}
	return total;
}

int Dragon::check_parts_how_many_closed() {
	int total = 0;
	for (unsigned int i = 0; i < Parts.size(); i++) {
		if (Parts[i]->type == 1) {
			if (Parts[i]->is_closed == true) {
				total++;
			}
			
		}
	}
	return total;
}

void Dragon::die() {
	if (Switch != -1) {
		P_Switch_MAIN::Switches[Switch] = true;
		P_Switch_MAIN::update();
	}
	
	delete_self(this);
}

void Dragon::when_revive() {
	did_delete_self = false;
	
	sprite.activate();
	for (unsigned int i = 0; i < Parts.size(); i++) {
		Parts[i]->revive();
	}
}

void Dragon::when_dead() {
	Sound::Play(28, 0, 0, random2::randomrange(1, 5));
	if (type == 1) {
		Player::PlayerObjects[0]->setStep(1); //This is for the time you defeat the boss in dungeon one.
	}
	did_delete_self = true;
	if (Switch != -1) {
		P_Switch_MAIN::Switches[Switch] = true;
	}
	sprite.deactivate();
	for (unsigned int i = 0; i < Parts.size(); i++) {
		Parts[i]->Die();
	}

	sprite.deactivate();
	x_speed = 0;
	y_speed = 0;
	x = initx;
	y = inity;
	
}

void Dragon::reset() {
	if (did_delete_self == false) {
		x = initx;
		y = inity;
		sprite.activate();
		create_parts();
		for (unsigned int i = 0; i < P_Data.size(); i++) {
			delete P_Data[i];
		}
		for (unsigned int i = 0; i < R_Data.size(); i++) {
			delete R_Data[i];
		}
		P_Data.clear();
		R_Data.clear();
		for (unsigned int i = 0; i < How_long + 3; i++) {
			P_Data.push_back(new Data(sf::Vector2f(x, y), 0, 0));
		}
		for (unsigned int i = 0; i < How_long + 3; i++) {
			R_Data.push_back(new RData(0, 0));
		}
		x_speed = Default_X_Speed;
		y_speed = 0;
	}
	
	
	
}

void Dragon::create_parts() {
	for (unsigned int i = 0; i < Parts.size(); i++) {
		delete Parts[i];
	}
	Parts.clear();
	//Making the tail.
	Parts.push_back(new Body(2, initx, inity, this));
	Parts.push_back(new Body(0, initx + (32 * (How_long + 1)), inity, this));
	std::vector<unsigned int> indices;
	bool should_reroll = false;
	unsigned int i_var = 0;
	bool exit = false;
	for (unsigned int i = 0; i < number_of_eye_balls + 1; i++) {
		exit = false;
		while (exit == false) {
			
			i_var = random2::randomrange(2, How_long - 2);
			for (unsigned int b = 0; b < indices.size(); b++) { //Checking to make sure that it does not have two of the same numbers in the vector.
				if (i_var == indices[b]) {
					should_reroll = true;
					break;
				}
			}
			if (should_reroll == false) {
				indices.push_back(i_var);
				exit = true;
			}
			else {
				should_reroll = false;
			}
		}

	}
	
	
	should_reroll = false;
	for (unsigned int i = 0; i < How_long; i++) {
		for (unsigned int b = 0; b < indices.size(); b++) {
			if (indices[b] == i) {
				Parts.push_back(new Body(1, initx + (32 * (i + 1)), inity, this));
				should_reroll = true; //Actually not rerolling, just making sure that it does not make a hard shell body.
			}
		}
		if (should_reroll == false) {
			Parts.push_back(new Body(0, initx + (32 * (i + 1)), inity, this));
		}
		else {
			should_reroll = false;
		}
	}
	
}

void Dragon::drop_in() {
	x_speed = 0;
	y_speed = 0;
	Sound::Play(70, 0, 0, random2::randomrange(1, 6));
}