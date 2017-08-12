#include "stdafx.h"
#include "Squisher.h"
#include "GF.h"
#include "Editor.h"
#include <iostream>
#include "P_Switch_MAIN.h"
#include "Debug.h"
#include "Sound.h"
#include "random2.h"
#define Sound_Pitch_Limit 10
std::vector<Squisher *> Squisher::Objects;
Squisher::Squisher(int Type, int x_pos, int y_pos, int Direction, int distance_in_blocks, int Speed, int SwitchChannel, TileMap &TM)
{
	type = Type;
	x = x_pos;
	y = y_pos;
	direction = Direction;
	max_distance = distance_in_blocks * 32;
	distance = 1;
	speed = Speed;
	Switch = SwitchChannel;
	GF::CheckTile_OverLap(x, y); //This checks to see if the tile is overlapping another tile.
	typeID = 10; //This is what distinguishes the NPC from all the other ones when being referred to.
	initx = x_pos; //This stores the initial x coordinate of creation.
	inity = y_pos; //This stores the initial y coordinate of creation.
	delx = x_pos; //This stores the x coordinate of where the editor needs to be to delete it.
	dely = y_pos; //This stores the y coordinate of where the editor needs to be to delete it.
	x2 = x_pos; //Extra x variable used for calculations.
	y2 = y_pos; //Extra y variable used for calculations.
	if (Editor::GetStatus() == true) {
		setPause(true);
	}
	else {
		setPause(false);
	}

	switch (direction) {
	case 0:
		spring.setPosition(x, y);
		break;
	case 1:
		spring.setPosition(x, y);
		break;
	case 2:
		spring.setPosition(x, y);
		break;
	case 3:
		spring.setPosition(x, y);
		break;
	}
	sound.setBuffer(Sound::GetSoundBuffer(46));
	sound.setRelativeToListener(false);
	sound.setLoop(true);
	sound.setVolume(50);
	//All_Sprites[TM.getTextureID()][typeID][0][0];
	spring *= All_Sprites[TM.getTextureID()][typeID][1][direction];
	max_damage = 10;
	damage_text.setMax_Health(max_damage);
	spring.setTexture(2);
	spring.setup();
	max_ticks = 0; //Normal 0.1 //These are the max ticks needed for a frame of animation to go by.
	sprite.setPosition(x, y); //This sets the position of the sprite to the given x and y coordinates.
	sprite.setTexture(2); //This sets when the sprite should be drawn. 0: Background, 1: Character, 2: Foreground
	sprite.setup(); //This tells the sprite that it is ready to be drawn.
	SavedParameters = { typeID, type, x_pos, y_pos, direction,distance_in_blocks,Speed,SwitchChannel }; //These are the parameters that are used when you load up the NPC. refer to World.cpp for details.
	anisprites = All_Sprites[TM.getTextureID()][typeID][0]; //What kind of animation you want to use.
	OVERRIDE_ANI = true; //If this is true, then the animation will still occur even when offscreen; Otherwise, it will stop animation when not rendered.
	sprite *= anisprites[0]; //Setting the sprite to the AniT of zero index.
	NPC_Cache.push_back(this); //Pushing it into the cache to allow ticking.
	Objects.push_back(this);
}

void Squisher::damage(Projectile &P) {
	P.kill(2);
	total_damage += P.getVoltage();
	damage_text.setDamage(total_damage);
	damage_text.setPosition(x, y);
	damage_text.display();
	if (total_damage >= max_damage) {
		Sound::Play(45, 0, 0, random2::randomrange(1, 6));
		sound.stop();
		ParticleSettings s;
		s.x = x + 16;
		s.y = y + 16;
		s.color = sf::Color::Cyan;
		s.max_speed = 3;
		s.out_type = 1;
		s.time_to_last = 1;
		s.num_of_particle = 50;
		delete_self(this);
	}
}

void Squisher::update() {
	if (Switch != -1) {
		if (GF::does_exist(Switch, P_Switch_MAIN::Switches.size())) {
			if (P_Switch_MAIN::Switches[Switch] == true && isForward == -1) {
				if (did_delete_self == false) {
					sound.play();
				}
				
				isForward = 1;
				x = initx;
				y = inity;
				

			}
		}
		else {
			std::cout << "Squisher has invalid switch parameter." << std::endl;
			throw("errorz");
		}
		
	}
	
}

void Squisher::update_all() {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		Objects[i]->update();
	}
}

Squisher::~Squisher() {
	
	for (unsigned int i = 0; i < Objects.size(); i++) {
		if (Objects[i] == this) {
			Objects.erase(Objects.begin() + i);
			break;
		}
	}
	
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-~MAIN TICK~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//This function is an overwritten virtual function, but this is a very important function
//So, this is placed seperate from the less important ones.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void Squisher::tick(bool render) {

	if (did_delete_self == false && isPaused == false) {
		int Ci = Projectile::DynamicCheckCollisionHeavy(x, y, 32, 32, 0, true);
		if (Ci != -1) {
			damage(Projectile::VP[Ci]);
		}
		if (Switch == -1 && isForward == -1) {
			isForward = 1;
			sound.play();
		}
		if (isForward != -1){

			if (isForward == false) {
				sound.setPitch((distance / max_distance) * Sound_Pitch_Limit);
				vel = -(((speed / 2) * GF::getDelta()) * (distance / max_distance));
			}
			else {
				sound.setPitch((distance / max_distance) * Sound_Pitch_Limit);
				vel = (speed * GF::getDelta()) * (distance / max_distance);
			}
			switch (direction) {
			case 0:
				y -= vel;
				distance = inity - y;
				spring.setScale(1, -distance / 32);
				break;
			case 1:
				x += vel;
				distance = x - initx;
				spring.setScale(distance / 32, 1);
				break;
			case 2:
				y += vel;
				distance = y - inity;
				spring.setScale(1, distance / 32);
				break;
			case 3:
				x -= vel;
				distance = initx - x;
				spring.setScale(-distance / 32, 1);
			}
			
			
			if (distance >= max_distance && isForward == true) {
				
				switch (direction) {
				case 0:
					y = (inity - max_distance) + 1;
					break;
				case 1:
					x = (initx + max_distance) - 1;
					break;
				case 2:
					y = (inity + max_distance) - 1;
					break;
				case 3:
					x = (initx - max_distance) + 1;
				}

				vel = 0;
				isForward = false;
			}
			else if (distance <= 2 && isForward == false) {
				sound.stop();
				x = initx;
				y = inity;
				distance = 1;
				vel = 0;
				isForward = -1;
			}
			
		}
		
		sprite.setPosition(x, y);
			
		//Checking to see if you should be dead or not.
		if (render == true) {
			if (DynamicCheckPlayerCollision(x + 4, y + 4, 32 - 8, 32 - 8) == true) {
				KillPlayer();
			}
		}
	}
	
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-~VIRTUAL FUNCTIONS~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//These are functions that overwrite the virtual functions in NPC_MOTHER.
//You may change these functions, but it is not necessary.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//This function is called when the NPC is revived.
void Squisher::when_revive() {
	did_delete_self = false;
	sound.play();
	sprite.activate();
	spring.activate();
}
//This function is called when the NPC is killed or deleted_self.
void Squisher::when_dead() {
	total_damage = 0;
	spring.setScale(1, 1);
	spring.deactivate();
	sprite.deactivate();
}

//This is called when the player dies, the editor starts, etc.
//Its purpose is to place everything back to where it started.
void Squisher::reset() {
	isForward = -1;
	x = initx;
	y = inity;
}

