#include "stdafx.h"
#include "Com_MAIN.h"
#include "GF.h"
#include "Editor.h"
#include <iostream>
#include "Blast.h"
#include "P_Switch_MAIN.h"
#include "Sub_NPC_A.h"
#include "Skeleton.h"
#include "Sound.h"
#include "random2.h"
#define jaw_width 25
#define jaw_height 46
#define body_width 128
#define body_height 82
#define jaw_dist 39
#define half_body_width body_width / 2

Com_MAIN::Com_MAIN(int Type, int x_pos, int y_pos, int SwitchChannel, TileMap &TM)
{
	type = Type;
	x = x_pos;
	y = y_pos;
	Tmap = &TM;
	GF::CheckTile_OverLap(x, y); //This checks to see if the tile is overlapping another tile.
	typeID = 16; //This is what distinguishes the NPC from all the other ones when being referred to.
	initx = x_pos; //This stores the initial x coordinate of creation.
	inity = y_pos; //This stores the initial y coordinate of creation.
	delx = x_pos; //This stores the x coordinate of where the editor needs to be to delete it.
	dely = y_pos; //This stores the y coordinate of where the editor needs to be to delete it.
	x2 = x_pos; //Extra x variable used for calculations.
	y2 = y_pos; //Extra y variable used for calculations.
	channel = SwitchChannel;
	ST jaw1;
	ST jaw2;
	jaw1.setPosition(x + (half_body_width - jaw_width), y + 83);
	jaw2.setPosition(x + (half_body_width), y + 83);
	jaw1.setTexture(2);
	jaw2.setTexture(2);
	jaw1 *= All_Sprites[TM.getTextureID()][typeID][0][1];
	jaw2 *= All_Sprites[TM.getTextureID()][typeID][0][2];
	
	jaws = { jaw1,jaw2 };
	jaws[0].setup();
	jaws[1].setup();
	if (Editor::GetStatus() == true) {
		setPause(true);
	}
	else {
		setPause(false);
	}
	//m_event = -1;
	max_ticks = 0.1; //Normal 0.1 //These are the max ticks needed for a frame of animation to go by.
	sprite.setPosition(x, y); //This sets the position of the sprite to the given x and y coordinates.
	sprite.setTexture(2); //This sets when the sprite should be drawn. 0: Background, 1: Character, 2: Foreground
	sprite.setup(); //This tells the sprite that it is ready to be drawn.
	opening_ani = All_Sprites[TM.getTextureID()][typeID][2];
	closing_ani = All_Sprites[TM.getTextureID()][typeID][1];
	
	eye *= opening_ani[0];
	open_eye();
	eye.setTexture(2);
	eye.setPosition(x + 16, y);
	eye.setup();
	SavedParameters = { typeID, Type, x_pos, y_pos, SwitchChannel }; //These are the parameters that are used when you load up the NPC. refer to World.cpp for details.
	c_event = 0;
	damage_text.setMax_Health(max_damage);
	OVERRIDE_ANI = true; //If this is true, then the animation will still occur even when offscreen; Otherwise, it will stop animation when not rendered.
	sprite *= All_Sprites[TM.getTextureID()][typeID][0][0]; //Setting the sprite to the AniT of zero index.
	NPC_Cache.push_back(this); //Pushing it into the cache to allow ticking.
}

void Com_MAIN::open_eye() {
	e_event = 0;
	anisprites = opening_ani;
	svectorindex = 0;
	ticks = 0;
}

void Com_MAIN::close_eye() {
	e_event = 1;
	anisprites = closing_ani;
	svectorindex = 0;
	ticks = 0;
}

void Com_MAIN::open_jaw() {
	m_event = 0;
	pticks = 0;
	jaws[0].setPosition(x + (half_body_width - jaw_width), y + 83);
	jaws[1].setPosition(x + (half_body_width), y + 83);
}
//This function closes the mouth.
void Com_MAIN::close_jaw() {
	m_event = 1;
	pticks = max_pticks;
	jaws[0].setPosition(x, y + body_height + 1);
	jaws[1].setPosition(x + (body_width - jaw_width), y + body_height + 1);
}

void Com_MAIN::fire_blasts() {
	new Blast(3, x + 32, y + 32, *Tmap);
	new Blast(3, x + 64, y + 32, *Tmap);
	
}



void Com_MAIN::damage(Projectile &P) {
	P.kill(2);
	
	if (P_Switch_MAIN::Switches[0] == true && P_Switch_MAIN::Switches[1] == true && is_dead == false) {
		Sound::Play(64, 0, 0, random2::randomrange(1, 6));
		damage_done += P.getVoltage();
		damage_text.setDamage(damage_done);
		damage_text.setPosition(x + 32, y + body_height);
		damage_text.display();
		if (damage_done >= max_damage) {
			Sound::Play(63, 0, 0, random2::randomrange(1, 6));
			is_dead = true;
			sprite.setColor(sf::Color::Magenta);
			P_Switch_MAIN::Switches[channel] = true;
			P_Switch_MAIN::update();
			e_event = -1;
			ParticleSettings v;
			v.color = sf::Color::Magenta;
			v.max_speed = 1;
			v.num_of_particle = 1000;
			v.out_type = 0;
			v.time_to_last = 3;
			v.x = x + half_body_width;
			v.y = y + (body_height / 2);
			ParticleSystem::create(v);
			eye *= opening_ani[0];

		}
	}
	else {
		Sound::Play(51, 0, 0, random2::randomrange(1, 5));
	}
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-~MAIN TICK~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//This function is an overwritten virtual function, but this is a very important function
//So, this is placed seperate from the less important ones.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void Com_MAIN::tick(bool render) {
	
	
	//Checking to see if you should be dead or not.
	if (render == true) {
		if (DynamicCheckPlayerCollision2(x + 1, y + 1, body_width - 2, body_height + jaw_height - 2) == true) {
			KillPlayer();
		}
	}
	
	
		int Pcollision;
		if (is_jaw_open == false) {
			Pcollision = Projectile::DynamicCheckCollisionHeavy2(x + 32, y, 64, body_height + jaw_height, 0, 0);
		}
		else {
			Pcollision = Projectile::DynamicCheckCollisionHeavy2(x + 32, y, 64, body_height, 0, 0);
		}

		int Pcollision2 = Projectile::DynamicCheckCollisionHeavy2(x, y, 32, body_height + jaw_height, 0, 0);
		int Pcollision3 = Projectile::DynamicCheckCollisionHeavy2(x + 96, y, 32, body_height + jaw_height, 0, 0);
		if (Pcollision != -1) {
			damage(Projectile::VP[Pcollision]);
		}
		if (Pcollision2 != -1) {
			Projectile::VP[Pcollision2].kill(2);
		}
		if (Pcollision3 != -1) {
			Projectile::VP[Pcollision3].kill(2);
		}
	if (is_dead == false) {
		if (should_count_cticks == true) {
			cticks += GF::getDelta();
			if (cticks >= max_cticks) {
				cticks = 0;
				switch (c_event) {
				case 0:
					should_count_cticks = false;
					open_jaw();
					break;
				case 1:

					fire_blasts();
					c_event = 2;
					break;
				case 2:
					should_count_cticks = false;
					close_jaw();
					break;
				}
			}
		}


		switch (m_event) {
		case -1:
			break;
		case 0:
			pticks += GF::getDelta();
			jaws[0].setPosition((x + (half_body_width - jaw_width)) - (jaw_dist * (pticks / max_pticks)), y + (body_height + 1));
			jaws[1].setPosition((x + half_body_width) + (jaw_dist * (pticks / max_pticks)), y + (body_height + 1));
			if (pticks >= max_pticks) {
				pticks = max_pticks;
				m_event = -1;
				jaws[0].setPosition(x, y + body_height + 1);
				jaws[1].setPosition(x + (body_width - jaw_width), y + body_height + 1);
				is_jaw_open = true;
				Sound::Play(65, 0, 0, random2::randomrange(1, 6));
				switch (c_event) {
				case 0:
					fire_blasts();
					should_count_cticks = true;
					c_event = 1;
					break;
				}
			}
			break;
		case 1:
			pticks -= GF::getDelta();
			jaws[0].setPosition((x + (half_body_width - jaw_width)) - (jaw_dist * (pticks / max_pticks)), y + (body_height + 1));
			jaws[1].setPosition((x + half_body_width) + (jaw_dist * (pticks / max_pticks)), y + (body_height + 1));
			if (pticks <= 0) {
				pticks = 0;
				m_event = -1;
				jaws[0].setPosition(x + (half_body_width - jaw_width), y + 83);
				jaws[1].setPosition(x + (half_body_width), y + 83);
				is_jaw_open = false;
				Sound::Play(65, 0, 0, random2::randomrange(1, 6));
				switch (c_event) {
				case 2:
					should_count_cticks = true;
					c_event = 0;
					break;
				}
			}
			break;
		}
	}
	
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-~VIRTUAL FUNCTIONS~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//These are functions that overwrite the virtual functions in NPC_MOTHER.
//You may change these functions, but it is not necessary.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//This function is called when the NPC is revived.
void Com_MAIN::when_revive() {
	did_delete_self = false;
	sprite.activate();
}
//This function is called when the NPC is killed or deleted_self.
void Com_MAIN::when_dead() {
	sprite.deactivate();
}

//This is called when the player dies, the editor starts, etc.
//Its purpose is to place everything back to where it started.
void Com_MAIN::reset() {
	x = initx;
	y = inity;
}

//This overwrites the animation function.
void Com_MAIN::animate() {
	if (e_event != -1) {
		ticks += GF::getDelta();

		//This is used to check to see if the ticks have reached the amount given.
		//This will add a spriteindex if conditions are met.
		if (ticks >= max_ticks) {
			ticks = 0;


			//This is used to check to see if the animation has reached the last frame in the vector full of sprites.
			if (svectorindex >= anisprites.size() - 1) {
				switch (e_event) {
				case 0:
					close_eye();
					break;
				case 1:
					open_eye();
					break;
				}
				svectorindex = 0;
			}
			else {
				svectorindex++;
			}
			//Setting the sprite texture to the cordinates of the AniT in the Sprites vector according to animation variables.
			eye *= anisprites[svectorindex];

		}
	}
	
}