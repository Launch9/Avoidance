#include "stdafx.h"
#include "Flame.h"
#include "TileMap.h"
#include "GF.h"
#include "Player.h"
#include "Sound.h"
#include "random2.h"
std::vector<Flame *> Flame::Objects;
Flame::Flame(int type, int x_pos, int y_pos, int direction, TileMap &TM)
{
	Sound::Play(43, 0, 0, random2::randomrange(1, 6));
	switch (direction) {
	case 0:
		pos = sf::Vector2i(x_pos, y_pos - 64);
		pos2 = sf::Vector2i(x_pos, y_pos - 32);
		sprite.setPosition(pos);
		break;
	case 1:
		pos = sf::Vector2i(x_pos + 64, y_pos);
		pos2 = sf::Vector2i(x_pos + 32, y_pos);
		sprite.setPosition(pos2);
		break;
	case 2:
		pos = sf::Vector2i(x_pos, y_pos + 64);
		pos2 = sf::Vector2i(x_pos, y_pos + 32);
		sprite.setPosition(pos2);
		break;
	case 3:
		pos = sf::Vector2i(x_pos - 64, y_pos);
		pos2 = sf::Vector2i(x_pos - 32, y_pos);
		sprite.setPosition(pos);
		break;
	}
	pos0 = sf::Vector2i(x_pos, y_pos);
	switch (random2::randomrange(1, 5)) {
	case 0:
		max_ticks = 0.05;
		break;
	case 1:
		max_ticks = 0.02;
		break;
	case 2:
		max_ticks = 0.06;
		break;
	case 3:
		max_ticks = 0.03;
		break;
	case 4:
		max_ticks = 0.07;
		break;
	default:
		max_ticks = 0.05;
	}
	
	anisprites = All_Sprites[TM.getTextureID()][0][direction];
	sprite *= anisprites[0];
	
	sprite.setTexture(2);
	sprite.setup();
	Objects.push_back(this);
}

void Flame::tick() {
	animate();
	if (ready_to_be_deleted == false) {
		if (pos.x == Player::PlayerObjects[0]->getcx() && pos.y == Player::PlayerObjects[0]->getcy() || 
			pos2.x == Player::PlayerObjects[0]->getcx() && pos2.y == Player::PlayerObjects[0]->getcy()) {
			Player::PlayerObjects[0]->Die();
		}

	}
}

void Flame::maintick() {
	
	for (unsigned int i = 0; i < Objects.size(); i++) {
		Objects[i]->tick();
		if (Objects[i]->ready_to_be_deleted == true) {
			delete Objects[i];
			Objects.erase(Objects.begin() + i);
			i--;
		}
	}
	

}

void Flame::animate() {
	if (ready_to_be_deleted == false) {
		ani_ticks += GF::getDelta();
		if (ani_ticks >= max_ticks) {
			svectorindex++;
			ani_ticks -= max_ticks;
			
			if (svectorindex >= anisprites.size()) {
				ready_to_be_deleted = true;
			}
			else {
				sprite *= anisprites[svectorindex];
			}
			
			
		}
	}
	
}

void Flame::clear_all() {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		delete Objects[i];
	}
	Objects.clear();
}