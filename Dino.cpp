#include "stdafx.h"
#include "Dino.h"
#include "Player.h"
#include "Flame.h"
#include "random2.h"
#include "Sound.h"
#define AniSpeed_Walk 0.0008
#define AniSpeed_Stand 0.13
Dino::Dino(int type, int x_pos, int y_pos, TileMap &TM)
{
	t_ptr = &TM;
	x = x_pos;
	y = y_pos;
	SavedParameters = { 9, type, x_pos, y_pos };
	GF::CheckTile_OverLap(x, y);
	OVERRIDE_ANI = true;
	max_ticks = 0.7;//0.03;
	svectorindex = 0;
	typeID = 9;
	Sprites = All_Sprites[TM.getTextureID()][typeID];
	anisprites = Sprites[0];
	sprite.setPosition(x_pos, y_pos);
	sprite.setTexture(2);
	sprite.setup();
	sprite *= Sprites[0][0];
	damage_needed = 40;
	damage_done = 0;
	damage_text.setMax_Health(damage_needed);
	switch (type) {
	case 0:
		SetSpriteColor(255, 255, 255, 255);
		break;
	case 1:
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
	NPC_Cache.push_back(this);
}


Dino::~Dino()
{
}

void Dino::ifPlayerMoved(int speed, int direction, int spaces, float remainder) {
	if (isPaused == false && get_is_dead() == false) {
		bool should_move = true;
		moves_since += spaces;
		if (moves_since == moves_needed - 1) {
			should_move = false;
			if (ani_set_index != 4) {
				Aniset(4, 0.1);
			}
		}
		else if (moves_since == moves_needed) {
			moves_since = 0;
			int R = findQuadrant(Player::PlayerObjects[0]->getx(), Player::PlayerObjects[0]->gety());
			
			if (R != -1) {
				if (R <= 3) {
					if (ani_set_index != 3) {
						Aniset(3, 0.2);
					}
					
				}
				else {
					if (ani_set_index != 2) {
						Aniset(2, 0.2);
					}
					
				}
				switch (R) {
				case 1: //top_right
					switch (random2::getBool()) {
					case 0:
						new Flame(0, x, y, 0, *t_ptr);
						Aniset(3, 0.2);
						break;
					case 1:
						new Flame(0, x, y, 1, *t_ptr);
						Aniset(3, 0.2);
					}
					break;
				case 2: //top_left
					switch (random2::getBool()) {
					case 0:
						new Flame(0, x, y, 3, *t_ptr);
						Aniset(2, 0.2);
						break;
					case 1:
						new Flame(0, x, y, 0, *t_ptr);
						Aniset(3, 0.2);
					}
					break;
				case 3: //bottom_left
					switch (random2::getBool()) {
					case 0:
						new Flame(0, x, y, 2, *t_ptr);
						Aniset(3, 0.2);
						break;
					case 1:
						new Flame(0, x, y, 3, *t_ptr);
						Aniset(2, 0.2);
					}
					break;
				case 4: //bottom_right
					switch (random2::getBool()) {
					case 0:
						new Flame(0, x, y, 1, *t_ptr);
						Aniset(3, 0.2);
						break;
					case 1:
						new Flame(0, x, y, 2, *t_ptr);
						Aniset(3, 0.2);
					}
					break;
				}
			}
			
			else {
				R = findDirection(Player::PlayerObjects[0]->getx(), Player::PlayerObjects[0]->gety());
				if (R <= 2) {
					if (ani_set_index != 3) {
						Aniset(3, 0.2);
					}

				}
				else {
					if (ani_set_index != 2) {
						Aniset(2, 0.2);
					}

				}
				
				if (R != -1) {
					new Flame(0, x, y, R, *t_ptr);
				}
				
			}
			should_move = false;
		
		}
		else if (moves_since == 0 || moves_since == 1) {
			if (ani_set_index != 0) {
				Aniset(0, 0.1);
			}
			should_move = false;
		}
		else {
			if (ani_set_index != 0) {
				Aniset(0, 0.1);
			}
		}
		if (should_move == true) {
			int Q = findQuadrant(Player::PlayerObjects[0]->getx(), Player::PlayerObjects[0]->gety());
			if (Q == -1) {
				Q = findDirection(Player::PlayerObjects[0]->getx(), Player::PlayerObjects[0]->gety());
				if (checkLoop(1, Q, speed, remainder) == true) {
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
		

	}

	




}

void Dino::tick(bool render) {
	if (did_delete_self == false) {
		if (C_position.x == Player::PlayerObjects[0]->getcx() && C_position.y == Player::PlayerObjects[0]->getcy()) {
			KillPlayer();
		}
		int p_index = Projectile::DynamicCheckCollisionHeavy(x, y, 32, 32, 0, true);
		if (p_index != -1) {
			damage(Projectile::VP[p_index]);
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

void Dino::when_dead() {
	Sound::Play(41, 0, 0, random2::randomrange(1, 6));
	damage_done = 0;
	moves_since = 0;
	Player::PlayerObjects[0]->addPower(3);
	sprite.deactivate();
	call_when_dead();
}

void Dino::damage(Projectile &P) {
	Sound::Play(42, 0, 0, random2::randomrange(1, 6));
	Player::PlayerObjects[0]->addPower(2);
	P.kill(2);
	damage_done += P.getVoltage();
	damage_text.setDamage(damage_done);
	damage_text.setPosition(x, y);
	damage_text.display();
	if (damage_done >= damage_needed) {
		
		delete_self(this);
		ParticleSettings s(get_C_position().x + 16, get_C_position().y + 16, 2, 30, 1, 0);
		s.color = sf::Color::White;
		s.ac1 = 0;
		s.ac2 = 360;
		ParticleSystem::create(s);
	}
}