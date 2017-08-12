#include "stdafx.h"
#include "HomingSkull.h"
#include "GF.h"
#include <iostream>
#include "Player.h"
#include <cmath>
#include "Sound.h"
#include "Debug.h"
#include "Editor.h"
#include "GF.h"
#include "Projectile.h"
#include "ParticleSettings.h"
#include "ParticleSystem.h"
#include "random2.h"
#define Pi 3.14159265
#define base32 32
#define Terminalvelocity 10000000000
#define Extra 1000
HomingSkull::HomingSkull(int type, int start_x, int start_y, int color, int Speed, TileMap &TM)
{
	
	
	GF::CheckTile_OverLap(x, y);
	OVERRIDE_ANI = true;
	speed = Speed * Extra;
	max_ticks = 0.1;
	svectorindex = 0;
	typeID = 1;
	sprite.setTexture(0);
	
	s.setBuffer(Sound::GetSoundBuffer(8));
	s.setAttenuation(0);
	
	x = start_x;
	y = start_y;
	SavedParameters = { typeID, type, start_x, start_y, color, Speed };
	switch (type) {
		case 0:
			anisprites = All_Sprites[TM.getTextureID()][typeID][0];
	}
	sprite *= anisprites[0];
	sprite.setOrigin(sf::Vector2f(base32 / 2, base32 / 2));
	initx = x;
	inity = y;
	delx = start_x;
	dely = start_y;
	x2 = x;
	y2 = y;
	s.setPosition(x, 0, y);
	
	
	switch (color) {
	case 1:
		SetSpriteColor(255, 0, 0, 255);
		break;
	case 2:
		SetSpriteColor(0, 255, 0, 255);
		break;
	case 3:
		SetSpriteColor(0, 0, 255, 255);
		break;

	}
	sprite.setPosition(x, y);
	
	sprite.setup();
	
	
	NPC_Cache.push_back(this);
}



//This rotates all the sprites a certain degree.
void HomingSkull::rotate(int degree) {
	sprite.rotate(degree);
}
//This will set the rotation of all the sprites in the animation.
void HomingSkull::setrotation(int degree) {
	sprite.setRotation(degree);
}
void HomingSkull::tick(bool render) {
	if (render == true) {

		if (Editor::GetStatus() == false) {
			isActive = true;
		}
		
	}
	//If you have seen the skull at least once.
	if (isActive == true) {
		
		
		if (render == true) {
			if (DynamicCheckPlayerCollision(x - 15, y - 15, 30, 30) == true){
				KillPlayer();
			}
		}
		
		if (Projectile::DynamicCheckCollisionHeavy(x - 16, y - 16, 32, 32, 20, true) == true) {
			
			kill();
			
		}
		t += 1;
		if (t >= maxtick) {
			float degree = atan2(y - Player::PlayerObjects[0]->gety(), x - Player::PlayerObjects[0]->getx());

			degree = degree * 180 / Pi;

			setrotation(degree);

			
			t = 0;
		}
		if (x > Player::PlayerObjects[0]->getvx()) {
			xvelocity += -speed * GF::getDelta() * getGlobalSpeed();
			
		}					  
		else {
			xvelocity += speed * GF::getDelta() * getGlobalSpeed();
			
		}
		if (y > Player::PlayerObjects[0]->getvy()) {
			yvelocity += -speed * GF::getDelta() * getGlobalSpeed();
			
		}
		else {
			yvelocity += speed * GF::getDelta() * getGlobalSpeed();
			
		}
		
		//This set of code block checks to see if the skull is going too fast.
		if (xvelocity > Terminalvelocity) {
			xvelocity = Terminalvelocity;
		}
		else if (xvelocity < -Terminalvelocity) {
			xvelocity = -Terminalvelocity;
		}
		if (yvelocity > Terminalvelocity) {
			yvelocity = Terminalvelocity;
		}
		else if (yvelocity < -Terminalvelocity) {
			yvelocity = -Terminalvelocity;
		}
		
		x += (xvelocity) * GF::getDelta() * getGlobalSpeed();
		y += (yvelocity) * GF::getDelta() * getGlobalSpeed();
		
	}
	
}

void HomingSkull::animate() {
	
	ticks += GF::getDelta();
	//This is used to check to see if the ticks have reached the amount given.
	//This will add a spriteindex if conditions are met.
	if (ticks >= max_ticks) {
		ticks = 0;

		//This is used to check to see if the animation has reached the last frame in the vector full of sprites.
		if (spriteindex >= anisprites.size() - 1) {
			s.setPitch(random2::randomrange(1, 5));
			s.setPosition(x, 0, y);
			
			s.play();
			spriteindex = 0;
		}
		else {
			spriteindex++;
		}
		sprite *= anisprites[spriteindex];
	}
	sprite.setPosition(sf::Vector2f(x, y));
}

void HomingSkull::reset() {
	x = initx;
	y = inity;
	xvelocity = 0;
	yvelocity = 0;
	isActive = false;
	
}

void HomingSkull::kill() {
	
	ParticleSettings s;
	s.ac1 = sprite.getRotation() - 30;
	s.ac2 = 60;
	s.max_speed = xvelocity + yvelocity;
	s.color = sprite.getColor();
	s.x = x;
	s.y = y;
	s.num_of_particle = 50;
	s.out_type = 0;
	s.time_to_last = 2;
	ParticleSystem::create(s);
	
	delete_self(this); //Deleting itself.
	
}

HomingSkull::~HomingSkull() {
	
}