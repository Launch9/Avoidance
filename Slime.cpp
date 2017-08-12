#include "stdafx.h"
#include "Slime.h"
#include "GF.h"
#include "Player.h"
#include "Sound.h"
#include "random2.h"
#define max_spaces 4
#define AniSpeed_Walk 0.0005
#define AniSpeed_Stand 0.13
Slime::Slime(int type, int x_pos, int y_pos, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	typeID = 5;
	SavedParameters = { typeID, type, x_pos, y_pos };
	GF::CheckTile_OverLap(x, y);
	OVERRIDE_ANI = true;
	max_ticks = 0.13;//0.03;
	svectorindex = 0;
	Sprites = All_Sprites[TM.getTextureID()][typeID];
	anisprites = Sprites[0];
	sprite.setPosition(x_pos, y_pos);
	sprite.setTexture(0);
	sprite.setup();
	switch (type) {
	case 0:
		max_damage = 30;
		break;
	}
	sprite *= Sprites[0][0];
	damage_text.setMax_Health(max_damage);
	C_position.x = x;
	C_position.y = y;
	initx = x;
	inity = y;
	delx = x;
	dely = y;
	x2 = x;
	y2 = y;

	//setWholePos(x, y);
	NPC_Cache.push_back(this);
}



void Slime::ifPlayerMoved(int speed, int direction, int spaces, float remainder) {
	if (sprite.get_is_Active() == true) {
		if (spaces_moved_since > max_spaces) {
			Sound::Play(34, 0, 0, random2::randomrange(1, 5));
			int Q = findQuadrant(Player::PlayerObjects[0]->getx(), Player::PlayerObjects[0]->gety());
			if (Q == -1) {
				Q = findDirection(Player::PlayerObjects[0]->getx(), Player::PlayerObjects[0]->gety());
				if (checkLoop(2, Q, speed * 2, remainder) == true) {
					Aniset(1, AniSpeed_Walk);
					standing_toggle = false;
				}
			}
			else {
				switch (Q) {
				case 1:
					if (checkLoop(2, 0, speed * 2, remainder) == true) {
						Aniset(1, AniSpeed_Walk);
						standing_toggle = false;
					};
					break;
				case 2:
					if (checkLoop(2, 3, speed * 2, remainder)) {
						Aniset(1, AniSpeed_Walk);
						standing_toggle = false;
					};
					break;
				case 3:
					if (checkLoop(2, 2, speed * 2, remainder) == true) {
						Aniset(1, AniSpeed_Walk);
						standing_toggle = false;
					};
					break;
				case 4:
					if (checkLoop(2, 1, speed * 2, remainder) == true) {
						Aniset(1, AniSpeed_Walk);
						standing_toggle = false;
					}

				}
			}
			spaces_moved_since = 0;
		}
		else {
			spaces_moved_since++;
		}
	}
	
		
}

void Slime::tick(bool render) {
	if (did_delete_self == false) {
		if (C_position.x == Player::PlayerObjects[0]->getcx() && C_position.y == Player::PlayerObjects[0]->getcy()) {
			Player::PlayerObjects[0]->Die();
		}
		int collisionint = Projectile::DynamicCheckCollisionHeavy(x, y, 32, 32, 0, false);
		if (collisionint != -1) {
			damage(Projectile::VP[collisionint]);
		}
		if (get_isMoving() == false) {

			if (standing_toggle == false) {

				Aniset(0, AniSpeed_Stand);
				standing_toggle = true;
			}
		}
		m_tick();
	}
}

void Slime::animate() {

	ticks += GF::getDelta();

	//This is used to check to see if the ticks have reached the amount given.
	//This will add a spriteindex if conditions are met.
	if (ticks >= max_ticks) {
		ticks = 0;


		//This is used to check to see if the animation has reached the last frame in the vector full of sprites.
		if (svectorindex >= anisprites.size() - 1) {
			if (standing_toggle == false) {
				Aniset(0, AniSpeed_Stand);
			}
			svectorindex = 0;
		}
		else {
			svectorindex++;
		}
		//Setting the sprite texture to the cordinates of the AniT in the Sprites vector according to animation variables.
		sprite *= anisprites[svectorindex];

	}

}

void Slime::damage(Projectile &P) {
	Sound::Play(33, 0, 0, random2::randomrange(1, 4));
	damage_done += P.getVoltage();
	damage_text.setPosition(x, y);
	damage_text.setDamage(damage_done);
	damage_text.display();
	Player::PlayerObjects[0]->addPower(1);
	P.kill(2);
	if (damage_done >= max_damage) {
		Sound::Play(32, 0, 0, random2::randomrange(1, 4));
		delete_self(this);
		ParticleSettings s(x + 16, y + 16, 2, 30, 1, 0);
		s.color = sf::Color::White;
		s.ac1 = 0;
		s.ac2 = 360;
		ParticleSystem::create(s);
	}
}

void Slime::when_dead() {
	call_when_dead();
	sprite.deactivate();
	damage_done = 0;
}

void Slime::reset() {
	x = initx;
	y = inity;
	spaces_moved_since = 0;
	C_position.x = initx;
	C_position.y = inity;
	stop_ani();
	sprite.setPosition(x, y);
}