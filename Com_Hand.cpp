#include "stdafx.h"
#include "Com_Hand.h"
#include "GF.h"
#include "Editor.h"
#include "Player.h"
#include <cmath>
#include "Sound.h"
#include "random2.h"
#include "Projectile.h"
#include "P_Switch_MAIN.h"
#define Pi 3.14159265

Com_Hand::Com_Hand(int Type, int x_pos, int y_pos, int Switchchannel, TileMap &TM)
{
	type = Type;
	x = x_pos;
	y = y_pos;
	channel = Switchchannel;
	GF::CheckTile_OverLap(x, y); //This checks to see if the tile is overlapping another tile.
	typeID = 15; //This is what distinguishes the NPC from all the other ones when being referred to.
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
	switch (Type) {
	case 0:
		sprite.setColor(sf::Color::Magenta);
		WTicks = max_WTicks;
		break;
	case 1:
		sprite.setColor(sf::Color::Blue);
		break;
	}
	distance = 0;
	chain *= All_Sprites[TM.getTextureID()][typeID][0][0];
	chain.setTexture(2);
	chain.setPosition(x + 16, y + 16);
	chain.setOrigin(16, 0);
	chain.setup();
	max_hits = 100;
	no_blink_ani = { All_Sprites[TM.getTextureID()][typeID][0][1] };
	blink_ani = { All_Sprites[TM.getTextureID()][typeID][0][1], All_Sprites[TM.getTextureID()][typeID][0][2] };
	max_ticks = 0.1; //Normal 0.1 //These are the max ticks needed for a frame of animation to go by.
	sprite.setPosition(x + 32, y + (96 / 2)); //This sets the position of the sprite to the given x and y coordinates.
	sprite.setOrigin(32, (96 / 2));
	damage_text_block.setMax_Health(max_hits);
	sprite.setTexture(2); //This sets when the sprite should be drawn. 0: Background, 1: Character, 2: Foreground
	sprite.setup(); //This tells the sprite that it is ready to be drawn.
	SavedParameters = { typeID, type, Switchchannel, x_pos, y_pos }; //These are the parameters that are used when you load up the NPC. refer to World.cpp for details.
	anisprites = no_blink_ani; //What kind of animation you want to use.
	OVERRIDE_ANI = true; //If this is true, then the animation will still occur even when offscreen; Otherwise, it will stop animation when not rendered.
	sprite *= anisprites[0]; //Setting the sprite to the AniT of zero index.
	Sprites = { { no_blink_ani },{ blink_ani } };
	NPC_Cache.push_back(this); //Pushing it into the cache to allow ticking.
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-~MAIN TICK~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//This function is an overwritten virtual function, but this is a very important function
//So, this is placed seperate from the less important ones.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void Com_Hand::tick(bool render) {
	if (isPaused == false && get_is_dead() == false) {
		if (did_delete_self == false) {
			//Checking to see if you should be dead or not.
			if (render == true) {
				if (DynamicCheckPlayerCollision(x + 32, y + (96 / 2), 1, 1) == true) {
					KillPlayer();
				}
			}
		}
		int p_int = Projectile::DynamicCheckCollisionHeavy(initx, inity, 32, 32, 0, false);
		if (p_int != -1) {
			if (distance != 0) {
				damageBlock(Projectile::VP[p_int]);
			}
			else {
				Sound::Play(51, 0, 0, random2::randomrange(1, 5));
			}

		}
		int p_int2 = Projectile::DynamicCheckCollisionHeavy2(x - 16, y - 16, 32, 32, 0, false);
		if (p_int2 != -1) {
			Projectile::VP[p_int2].kill(2);
			Sound::Play(51, 0, 0, random2::randomrange(1, 5));
		}
		switch (currentEvent) {
		case 0:
			WTicks += GF::getDelta();
			if (WTicks >= max_WTicks * 2) {
				WTicks = 0;
				currentEvent = 1;
				Sound::Play(59, 0, 0, random2::randomrange(1, 5));
				Aniset(1, 0.03);
			}
			break;
		case 1:
			WTicks += GF::getDelta();
			if (svectorindex == 1) {
				Sound::Play(60, 0, 0, random2::randomrange(1, 5));
			}
			if (WTicks >= max_WTicks) {
				Aniset(0, 5);
				WTicks = 0;
				should_point = false;
				currentEvent = 2;
			}
			break;
		case 2:
			LTicks += GF::getDelta();
			distance = -(LaunchDistance * (LTicks / max_LTicks));
			if (LTicks >= max_LTicks) {
				Sound::Play(63, 0, 0, random2::randomrange(1, 5));
				currentEvent = 3;
			}
			break;
		case 3:
			WTicks += GF::getDelta();

			if (WTicks >= max_WTicks) {
				WTicks = 0;
				currentEvent = 4;
			}
			break;
		case 4:
			LTicks -= GF::getDelta();
			distance = -(LaunchDistance * (LTicks / max_LTicks));
			if (LTicks <= 0) {
				LTicks = 0;
				distance = 0;
				should_point = true;
				currentEvent = 0;
			}
		}

		if (should_point == true) {
			degree = atan2(inity - Player::PlayerObjects[0]->gety(), initx - Player::PlayerObjects[0]->getx());
		}


		if (distance != 0) {

			x = (initx + 16) + (cos(degree) * distance);
			y = (inity + 16) + (sin(degree) * distance);
			chain.setScale(sf::Vector2f(1, distance / 32));
			sprite.setPosition(x, y);
		}
		else {
			x = initx;
			y = inity;
			chain.setScale(1, 1);
			sprite.setPosition(x, y);
		}
		if (should_point == true) {
			//This is the hypotenuse of the right triangle we are using for the triganometry of the player to the hand.
			//float hypot = GF::getDistance_Pixels(sf::Vector2f(Player::PlayerObjects[0]->getvx(), Player::PlayerObjects[0]->getvy()), sf::Vector2f(x + 32, y + 96 / 2));		
			chain.setRotation((degree * 180 / Pi) - 90);
			sprite.setRotation((degree * 180 / Pi) + 90);
		}
	}
	
	
	

	


}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-~VIRTUAL FUNCTIONS~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//These are functions that overwrite the virtual functions in NPC_MOTHER.
//You may change these functions, but it is not necessary.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//This function is called when the NPC is revived.
void Com_Hand::when_revive() {
	//did_delete_self = false;
	//sprite.activate();
//	chain.deactivate();
	
}
//This function is called when the NPC is killed or deleted_self.
void Com_Hand::when_dead() {
	sprite.deactivate();
	chain.deactivate();
	hits = 0;
	P_Switch_MAIN::Switches[channel] = true;
}

//This is called when the player dies, the editor starts, etc.
//Its purpose is to place everything back to where it started.
void Com_Hand::reset() {
	
	distance = 0;
	LTicks = 0;
	sprite.setPosition(initx + 32, inity + (96 / 2));
	should_point = true;
	Aniset(0);
	//chain.setScale(0, 0);
	switch (type) {
	case 0:
		
		WTicks = max_WTicks;
		break;
	case 1:
		WTicks = 0;
		LTicks = 0;
		break;
	}
	currentEvent = 0;
	x = initx;
	y = inity;
}

void Com_Hand::damageBlock(Projectile &P) {
	hits += P.getVoltage();
	P.kill(2);
	Sound::Play(61, 0, 0, random2::randomrange(1, 5));
	damage_text_block.setDamage(hits);
	damage_text_block.setPosition(initx, inity);
	damage_text_block.display();
	if (hits >= max_hits) {
		Sound::Play(62, 0, 0, random2::randomrange(1, 5));
		delete_self(this);
		ParticleSettings s(initx + 16, inity + 16, 1, 100, 1, 1);
		ParticleSystem::create(s);
	}
}