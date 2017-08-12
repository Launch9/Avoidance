#include "stdafx.h"
#include "Break_Spawner.h"
#include "Player.h"
#include "Sound.h"
#include "random2.h"
Break_Spawner::Break_Spawner(int Type, int x_pos, int y_pos, int pattern, int type_of_projectile, int max_health, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	initx = x;
	inity = y;
	delx = x;
	dely = y;
	PS = ParticleSettings(x + 16, y + 16, 1, 100, 2, 1);
	PS.color = sf::Color::Yellow;
	type = Type;

	max_damage = max_health;
	typeID = 8;
	SavedParameters = { typeID, Type, x_pos, y_pos, pattern, type_of_projectile, max_health };
	Damage_Text.setMax_Health(max_health);
	Damage_Text.setDamage(0);
	Damage_Text.setPosition(x, y);
	anisprites = All_Sprites[TM.getTextureID()][typeID][0];
	sprite.setTexture(0);
	sprite.setPosition(x, y);
	sprite *= anisprites[0];
	sprite.setup();
	switch (pattern) {
	case 0:
		for (unsigned int i = 0; i < 4; i++) {
			Cannons.push_back(new Cannon(x,y,type_of_projectile,i,0,1));
		}
		break;
	case 1:
		for (unsigned int i = 0; i < 4; i++) {
			Cannons.push_back(new Cannon(x, y, type_of_projectile, i, 0.25 * i, 1));
		}
		break;
	case 2:
		for (unsigned int i = 0; i < 4; i++) {
			switch (i) {
			case 0:
				Cannons.push_back(new Cannon(x, y, type_of_projectile, i, 0, 1));
				break;
			case 1:
				Cannons.push_back(new Cannon(x, y, type_of_projectile, i, 0.5, 1));
				break;
			case 2:
				Cannons.push_back(new Cannon(x, y, type_of_projectile, i, 0, 1));
				break;
			case 3:
				Cannons.push_back(new Cannon(x, y, type_of_projectile, i, 0.5, 1));
				break;

			}
		}
	}
	NPC_Cache.push_back(this);
	
}

void Break_Spawner::tick(bool render) {
	if (Player::PlayerObjects[0]->getx() == x && Player::PlayerObjects[0]->gety() == y) {
		Player::PlayerObjects[0]->Die();
	}
	int collisionint = Projectile::DynamicCheckCollisionHeavy(x, y, 32, 32, 0, true);
	if (collisionint != -1) {
		damage(Projectile::VP[collisionint]);
	}
	for (unsigned int i = 0; i < Cannons.size(); i++) {
		Cannons[i]->update();
	}
}

void Break_Spawner::damage(Projectile &P) {
	total_damage += P.getVoltage();
	P.kill(2);
	Damage_Text.setDamage(total_damage);
	Damage_Text.display();
	if (total_damage >= max_damage) {
		die();
	}

}

void Break_Spawner::die() {
	Sound::Play(29, 0, 0, random2::randomrange(1, 5));
	ParticleSystem::create(PS);
	delete_self(this);
}