#include "stdafx.h"
#include "NPC_Spawner.h"
#include "Projectile.h"
#include "TileMap.h"
#include "Sub_NPC_A.h"
#include "Skeleton.h"
#include "Sound.h"
#include "random2.h"
#define max_number_of_spawns 10
NPC_Spawner::NPC_Spawner(int Type, int x_pos, int y_pos, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	Tmap = &TM;
	typeID = 23; //This identifies this kind of derived object as a something different than the rest of them.
	max_ticks = 0.1; //Normal 0.1 ~how long is takes to get to the next frame of the animation.
	sprite.setTexture(0); //This tells the computer when to draw the sprite. Background, Character, or Foreground.
	sprite.setPosition(x, y); //This is for setting the position of the sprite to the x and y coordinates.
	sprite.setup(); //This is telling the computer that the sprite is ready to be drawn.
	isSIMPLELIGHTING = false; //If this is set to true, it will always be as bright as possible; Otherwise, it will lit by the surrounding light.
	SavedParameters = {type, x_pos, y_pos}; //These are the parameters that are saved when loading the tile.
	Sprites = All_Sprites[TM.getTextureID()][typeID][0];
	sprite *= Sprites[0];
	damage_text.setPosition(x, y);
	damage_text.setMax_Health(max_damage);
	dead_ani = All_Sprites[TM.getTextureID()][typeID][1];
	NonColAniTiles_FORE.push_back(this);
}

void NPC_Spawner::spawn() {
	if (total_spawns < max_number_of_spawns) {
		bool should_make = true;
		for (unsigned int i = 0; i < Sub_NPC_A::Object_Cache.size(); i++) {
			if (x == Sub_NPC_A::Object_Cache[i]->get_C_position().x && y == Sub_NPC_A::Object_Cache[i]->get_C_position().y && Sub_NPC_A::Object_Cache[i]->get_is_dead() == false) {
				should_make = false;
				break;
			}

		}
		if (should_make == true) {

			total_spawns++;
			switch (type) {
			case 0:

				new Skeleton(1, x, y, *Tmap);
				break;
			}

		}
	}
	else {
		die();
	}
	
	
}

void NPC_Spawner::damage(Projectile &P) {
	if (is_Dead == false) {
		total_damage += P.getVoltage();
		P.kill(2);
		damage_text.setDamage(total_damage);
		Sound::Play(67, 0, 0, random2::randomrange(1, 6));
		damage_text.display();
		if (total_damage >= max_damage) {
			die();
		}
	}
	
}

void NPC_Spawner::die() {
	ParticleSettings s(x + 16, y + 16, 1, 100, 5, 1);
	s.color = sf::Color::Red;
	ParticleSystem::create(s);
	Sound::Play(66, 0, 0, random2::randomrange(1, 6));
	Sprites = dead_ani;
	is_Dead = true;
}
///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-~VIRTUAL FUNCTIONS~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
///These are functions are overwritten virtual functions of the mother class Basic_Tile_MOTHER.
///Write in these if you want something to happen depending on the function;
///Otherwise, you can leave them empty, and nothing will happen.
///-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void NPC_Spawner::animate() {
	int collisionint = Projectile::DynamicCheckCollisionHeavy(x, y, 32, 32, 0, 0);
	if (collisionint != -1) {
		damage(Projectile::VP[collisionint]);
	}
	ticks += GF::getDelta();
	if (ticks >= max_ticks) {
		svectorindex += 1;
		if (svectorindex >= Sprites.size()) {
			if (is_Dead == false) {
				spawn();
			}
			svectorindex = 0;
			//Setting the texture rectangle to the correct position for proper animation.
		}
		sprite *= Sprites[svectorindex];
		ticks -= max_ticks;
	}
}

//This tells the computer what to do if the player stepped on the tile.
bool NPC_Spawner::ifCollision(int PlayerChannel) {
	return false;
}

//This tells the computer what to do if the player collides with the tile before he/she lands on it.
bool NPC_Spawner::ifCollisionBefore(bool isPlayer) {
	return true;
}

//This tells the computer what to do if the player is not colliding with the tile.
bool NPC_Spawner::elseCollisionBefore(int PlayerChannel) {
	return true;
}

//This tells the computer what to do if a projectile is colliding with the tile.
//Will return false if not no collision occured.
//Will return true if a collision occured.
void NPC_Spawner::ifProjectileCollision(Projectile &P, int direction) {

}

