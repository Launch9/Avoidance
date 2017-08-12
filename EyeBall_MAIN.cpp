#include "stdafx.h"
#include "EyeBall_MAIN.h"
#include "GF.h"
#include "Editor.h"
#include "Player.h"
#include "P_Switch_MAIN.h"
#include "Sound.h"
#include "random2.h"
std::vector<EyeBall_MAIN *> EyeBall_MAIN::Objects;
EyeBall_MAIN::EyeBall_MAIN(int Type, int x_pos, int y_pos, const std::vector<int> &Switches, TileMap &TM)
{
	type = Type;
	x = x_pos;
	y = y_pos;
	switches = Switches;
	GF::CheckTile_OverLap(x, y); //This checks to see if the tile is overlapping another tile.
	typeID = 13; //This is what distinguishes the NPC from all the other ones when being referred to.
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
	charge_sound.setBuffer(Sound::GetSoundBuffer(53));
	charge_sound.setLoop(true);
	charge_sound.setRelativeToListener(false);
	how_much_needed = 100;
	damage_text.setMax_Health(how_much_needed);
	max_ticks = 0.07; //Normal 0.1 //These are the max ticks needed for a frame of animation to go by.
	sprite.setPosition(x, y); //This sets the position of the sprite to the given x and y coordinates.
	sprite.setTexture(2); //This sets when the sprite should be drawn. 0: Background, 1: Character, 2: Foreground
	sprite.setup(); //This tells the sprite that it is ready to be drawn.
	SavedParameters = { typeID, Type, x_pos, y_pos }; //These are the parameters that are used when you load up the NPC. refer to World.cpp for details.
	for (unsigned int i = 0; i < Switches.size(); i++) {
		SavedParameters.push_back(Switches[i]);
	}
	Sprites = All_Sprites[TM.getTextureID()][typeID]; //What kind of animation you want to use.
	max_FTicks = 2;
	anisprites = Sprites[0];
	about_to_fire = false;
	is_act = true;
	Aniset(0);
	OVERRIDE_ANI = true; //If this is true, then the animation will still occur even when offscreen; Otherwise, it will stop animation when not rendered.
	sprite *= anisprites[0]; //Setting the sprite to the AniT of zero index.
	Objects.push_back(this);
	NPC_Cache.push_back(this); //Pushing it into the cache to allow ticking.
	
}

EyeBall_MAIN::~EyeBall_MAIN() {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		if (Objects[i] == this) {
			Objects.erase(Objects.begin() + i);
			break;
		}
	}
}
void EyeBall_MAIN::damage(Projectile &P) {
	how_much_done += P.getVoltage();
	damage_text.setDamage(how_much_done);
	damage_text.setPosition(x, y);
	damage_text.display();
	Player::PlayerObjects[0]->addPower(2);
	Sound::Play(56, 0, 0, random2::randomrange(1, 6));
	P.kill(2);
	if (how_much_done >= how_much_needed) {
		P_Switch_MAIN::Switches[0] = true;
		Sound::Play(54, 0, 0, random2::randomrange(1, 6));
		delete_self(this);
		is_act = false;
		Aniset(0);
		charge_sound.stop();
		ParticleSettings s;
		s.color = sf::Color::Blue;
		s.max_speed = 2;
		s.num_of_particle = 500;
		s.out_type = 0;
		s.time_to_last = 4;
		s.x = x + 32;
		s.y = y + 16;
		ParticleSystem::create(s);
		P_Switch_MAIN::update();
	}
}

void EyeBall_MAIN::update() {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		Objects[i]->update_over();
	}
}

void EyeBall_MAIN::update_over() {
	int how_many_done = 0;
	for (unsigned int i = 0; i < switches.size(); i++) {
		if (P_Switch_MAIN::Switches[switches[i]] == true) {
			how_many_done++;
		}
	}
	if (how_many_done == switches.size()) {
		
		can_be_hit = true;
		if (about_to_fire == false) {
			anisprites = Sprites[1];
			ani_set_index = 1;
		}
		else {
			anisprites = Sprites[2];
			ani_set_index = 2; 
		}
		
	}
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-~MAIN TICK~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//This function is an overwritten virtual function, but this is a very important function
//So, this is placed seperate from the less important ones.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void EyeBall_MAIN::tick(bool render) {
	if (is_act == true) {
		if (did_delete_self == false) {
			if (about_to_fire == false) {
				
				FTicks += GF::getDelta();
				if (FTicks >= max_FTicks) {
					charge_sound.play();
					about_to_fire = true;
					max_ticks = 1;
					if (can_be_hit == false) {
						Aniset(3);
					}
					else {
						Aniset(2);
					}
					
					FTicks = 0;
				}
			}

			//Checking to see if you should be dead or not.
			if (render == true) {
				if (DynamicCheckPlayerCollision(x, y, 32, 32) == true) {
					KillPlayer();
				}
			}
			
				int CI = Projectile::DynamicCheckCollisionHeavy2(x, y, 64, 32, 0, 1);
				if (CI != -1) {
					if (can_be_hit == true) {
						damage(Projectile::VP[CI]);
					}
					else {
						Projectile::VP[CI].kill(2);
						Sound::Play(51, 0, 0, random2::randomrange(1, 6));
					}
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
void EyeBall_MAIN::when_revive() {
	did_delete_self = false;
	sprite.activate();
}
//This function is called when the NPC is killed or deleted_self.
void EyeBall_MAIN::when_dead() {
	
	sprite.deactivate();
}

//This is called when the player dies, the editor starts, etc.
//Its purpose is to place everything back to where it started.
void EyeBall_MAIN::reset() {
	x = initx;
	y = inity;
}

void EyeBall_MAIN::animate() {
	ticks += GF::getDelta();

	//This is used to check to see if the ticks have reached the amount given.
	//This will add a spriteindex if conditions are met.
	if (ticks >= max_ticks) {
		ticks = 0;


		//This is used to check to see if the animation has reached the last frame in the vector full of sprites.
		if (svectorindex >= anisprites.size() - 1) {
			if (about_to_fire == true) {
				charge_sound.stop();
				Sound::Play(55, 0, 0, random2::randomrange(1, 6));
				new Projectile(3, x, y + 32, 2, false);
				new Projectile(3, x + 32, y + 32, 2, false);
				about_to_fire = false;
				max_ticks = 0.1;
				if (can_be_hit == false) {
					Aniset(0);
				}
				else {
					Aniset(1);
				}
				
			}
			svectorindex = 0;
		}
		else {
			svectorindex++;
		}
		//Setting the sprite texture to the cordinates of the AniT in the Sprites vector according to animation variables.
		sprite *= anisprites[svectorindex];

	}
};

