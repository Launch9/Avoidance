#include "stdafx.h"
#include "Skeleton.h"
#include "GF.h"
#include <iostream>
#include "Projectile.h"
#include "ParticleSystem.h"
#include "ParticleSettings.h"
#include "Player.h"
#define AniSpeed_Walk 0.0008
#define AniSpeed_Stand 0.13
Skeleton::Skeleton(int Type, int x_pos, int y_pos, TileMap &TM)
{

	x = x_pos;
	y = y_pos;
	type = Type;
	SavedParameters = { 4, type, x_pos, y_pos };
	GF::CheckTile_OverLap(x, y);
	OVERRIDE_ANI = true;
	max_ticks = 0.13;//0.03;
	svectorindex = 0;
	
	x = x_pos;
	y = y_pos;
	Sprites = All_Sprites[TM.getTextureID()][4];
	anisprites = Sprites[0];
	sprite.setPosition(x_pos, y_pos);
	sprite.setTexture(0);
	sprite.setup();
	bool should_put = true;
	sprite *= Sprites[0][0];
	switch (type) {
	case 0:
		SetSpriteColor(255, 255, 255, 255);
		break;
	case 1:
		I_Del = true;
		SetSpriteColor(255, 0, 0, 255);
		break;
	case 2:
		SetSpriteColor(0, 255, 0, 255);
		break;
	case 3:
		SetSpriteColor(0, 0, 255, 255);
		break;
	case 4:
		SetSpriteColor(0, 0, 0, 255);
		break;
	case 5:
		SetSpriteColor(255, 255, 0, 255);
		break;
	case 6:
		SetSpriteColor(0, 255, 255, 255);
		break;
	case 7:
		SetSpriteColor(255, 0, 255, 255);
		break;
	}
	C_position.x = x_pos;
	C_position.y = y_pos;
	initx = x;
	inity = y;
	delx = x;
	dely = y;
	x2 = x;
	y2 = y;
	
	//setWholePos(x, y);
	
	NPC_Cache.push_back(this);
	
}

void Skeleton::ifPlayerMoved(int speed, int direction, int spaces, float remainder) {
	if (isPaused == false && toggle == true) {
		
			
			int Q = findQuadrant(Player::PlayerObjects[0]->getx(), Player::PlayerObjects[0]->gety());
			if (Q == -1) {
				Q = findDirection(Player::PlayerObjects[0]->getx(), Player::PlayerObjects[0]->gety());
				if(checkLoop(1, Q, speed, remainder) == true) {
					Aniset(1, AniSpeed_Walk);
					standing_toggle = false;
				}
			}
			else {
				switch (Q) {
				case 1:
					if (checkLoop(1, 0, speed, remainder) == true) {
						Aniset(1, AniSpeed_Walk);
						standing_toggle = false;
					};
					break;
				case 2:
					if (checkLoop(1, 3, speed, remainder)) {
						Aniset(1, AniSpeed_Walk);
						standing_toggle = false;
					};
					break;
				case 3:
					if (checkLoop(1, 2, speed, remainder) == true) {
						Aniset(1, AniSpeed_Walk);
						standing_toggle = false;
					};
					break;
				case 4:
					if (checkLoop(1, 1, speed, remainder) == true) {
						Aniset(1, AniSpeed_Walk);
						standing_toggle = false;
					}

				}

			}
		
	}
	
	if (toggle == true) {
		toggle = false;
	}
	else {
		toggle = true;
	}
	
	
	

}

void Skeleton::tick(bool render) {
	if (did_delete_self == false) {
		if (C_position.x == Player::PlayerObjects[0]->getcx() && C_position.y == Player::PlayerObjects[0]->getcy()) {
			KillPlayer();
		}
		
		

		if (get_isMoving() == false) {
			if (Projectile::DynamicCheckCollisionLight(get_C_position().x, get_C_position().y, 32, 32, true) != -1) {
				delete_self(this);

			}
			if (standing_toggle == false) {

				Aniset(0, AniSpeed_Stand);
				standing_toggle = true;
			}
		}
		else {
			if (Projectile::DynamicCheckCollisionHeavy(get_C_position().x, get_C_position().y, 32, 32, 0, true) != -1) {
				delete_self(this);
			}
		}

		m_tick();
	}
	
	
}

void Skeleton::when_dead() {
	
	Player::PlayerObjects[0]->addPower(1);
	sprite.deactivate();
	call_when_dead();
	ParticleSettings s(get_C_position().x + 16, get_C_position().y + 16, 2, 30, 1, 0);
	s.color = sf::Color::White;

	s.ac1 = 0;
	s.ac2 = 360;
	ParticleSystem::create(s);
}

void Skeleton::when_revive() {
	switch (type) {
	case 0:
		did_delete_self = false;
		sprite.activate();
		break;
	case 1:
		break;
	}
	
}

void Skeleton::reset() {
	switch (type) {
	case 0:
		x = initx;
		y = inity;
		toggle = false;
		C_position.x = initx;
		C_position.y = inity;
		stop_ani();
		sprite.setPosition(x, y);
		break;
	case 1:
		delete_self(this);
	}
	
}

