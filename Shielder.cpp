#include "stdafx.h"
#include "Shielder.h"
#include <iostream>
#include "random2.h"
#include "Shielder.h"
#include "Blast.h"
Shielder::Shielder(int Type, int x_pos, int y_pos, int how_Many_hits, TileMap &TM, std::vector<int> Shields)
{
	//Setting positions.
	x = x_pos;
	y = y_pos;
	initx = x;
	inity = y;
	delx = x;
	dely = y;
	x2 = x;
	y2 = y;
	C_position.x = x;
	C_position.y = y;
	Tmap = &TM;
	typeID = 6;
	type = Type;
	SavedParameters = { typeID, type, x_pos, y_pos, how_Many_hits };
	//Saving the shield directions in the SavedParameters vector.
	for (unsigned int i = 0; i < Shields.size(); i++) {
		SavedParameters.push_back(Shields[i]);
	}
	//Making shields around the enemy.
	for (unsigned int i = 0; i < Shields.size(); i++) {
		shields.push_back(new shield(x, y, Shields[i], how_Many_hits, All_Sprites[TM.getTextureID()][typeID][0]));
	}
	switch (type) {
	case 1:
		sprite.setColor(sf::Color::Red);
		break;
	case 2:
		sprite.setColor(sf::Color::Blue);
		break;
	}
	sprite.setTexture(0);
	sprite.setPosition(x, y);
	sprite *= All_Sprites[TM.getTextureID()][typeID][0][0];
	sprite.setup();
	NPC_Cache.push_back(this);
}


Shielder::~Shielder()
{
	for (unsigned int i = 0; i < shields.size(); i++) {
		delete shields[i];
	}
	shields.clear();
}


void Shielder::tick(bool render) {
	if (did_delete_self == false) {
		if (C_position.x == Player::PlayerObjects[0]->getcx() && C_position.y == Player::PlayerObjects[0]->getcy()) {
			KillPlayer();
		}
		int collision_int = Projectile::DynamicCheckCollisionHeavy(x, y, 32, 32, 4, false);
		if (collision_int != -1) {
			int direction = Projectile::VP[collision_int].getDirection();
			for (unsigned int i = 0; i < shields.size(); i++) {
				if (shields[i]->reversedirection == direction) {
					if (shields[i]->is_dead == false) {
						shields[i]->damage(Projectile::VP[collision_int]);
						direction = -1;
						break;
					}

				}
			}
			if (direction != -1) {
				ParticleSettings c(x + 16, y + 16, 100, 100, 1, 1);
				c.color = sf::Color::Red;
				ParticleSystem::create(c);
				Sound::Play(25, x, y, random2::randomrange(1, 5), 1, 1);
				delete_self(this);
			}
		}
		//Calculating the movement of the sprite.
		m_tick();
		for (unsigned int i = 0; i < shields.size(); i++) {
			shields[i]->setPosition(sprite.getPosition());
		}
	}
	
}

void Shielder::animate() {

}

void Shielder::when_dead() {
	Player::PlayerObjects[0]->addFuel(2);
	call_when_dead();
	sprite.deactivate();
	for (unsigned int i = 0; i < shields.size(); i++) {
		shields[i]->kill();
	}
	switch (type) {
	case 1:
		Projectile(2, x, y, 0, true);
		Projectile(2, x + 32, y, 1, true);
		Projectile(2, x, y + 32, 2, true);
		Projectile(2, x, y, 3, true);
		break;
	case 2:
		new Blast(2, x, y, *Tmap);
		break;
	}
}

void Shielder::when_revive() {
	did_delete_self = false;
	sprite.activate();
	for (unsigned int i = 0; i < shields.size(); i++) {
		shields[i]->revive();
	}
}

void Shielder::ifPlayerMoved(int speed, int direction, int spaces, float remainder) {
	if (isPaused == false && toggle == true) {
		int Q = findQuadrant(Player::PlayerObjects[0]->getx(), Player::PlayerObjects[0]->gety());
		if (Q == -1) {
			Q = findDirection(Player::PlayerObjects[0]->getx(), Player::PlayerObjects[0]->gety());
			checkLoop(1, Q, speed, remainder);
		}
		else {
			switch (Q) {
			case 1:
				checkLoop(1, 0, speed, remainder);
				break;
			case 2:
				checkLoop(1, 3, speed, remainder);
				break;
			case 3:
				checkLoop(1, 2, speed, remainder);
				break;
			case 4:
				checkLoop(1, 1, speed, remainder);
			}
		}
		toggle = false;
	}
	else {
		toggle = true;
	}
	
}

void Shielder::reset() {
	x = initx;
	y = inity;
	toggle = false;
	C_position.x = initx;
	C_position.y = inity;
	stop_ani();
	sprite.setPosition(x, y);
}