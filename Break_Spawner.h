#pragma once
#include "NPC_MOTHER.h"
#include "Sub_NPC_StaticCollision.h"
#include <iostream>
#include "DText.h"
#include "Gauntlets.h"
#include "Sound.h"
#include "random2.h"
class Break_Spawner : public NPC_MOTHER
{
private:
	//These are the settings for the particles that come out when you kill the Break_Spawner.
	ParticleSettings PS; //Particle Settings
	//These are the settings for the particles that come out when it shoots a projectile.
	ParticleSettings PSP; //Particle Settings for Projectile
	//This is the total amount of damage that has been done to the Break_Spawner.
	int total_damage = 0;
	//This is the max amount of damage that you can do to the Break_Spawner before it dies.
	int max_damage = 100;
	struct Cannon {
	private:
		//This is the direction that is shoots the projectile.
		int direction = 0;
		//This is the type of projectile that gets shot out.
		int type_of_projectile = 0;
		//This is the x cordinate.
		float x = 0;
		//This is the y cordiante.
		float y = 0;
		//This tells how long until it fires that cannon.
		float ticks = 0;
		//This tells how many ticks need to be reached before it is ready to fire.
		float max_ticks = 0;
	public:
		

		Cannon(int x_pos, int y_pos, int type_of_Projectile, int Direction, float starting_ticks, float max_tick) {
			max_ticks = max_tick;
			direction = Direction;
			ticks = starting_ticks;
			type_of_projectile = type_of_Projectile;
			x = x_pos;
			y = y_pos;
		}
		void update() {
			ticks += GF::getDelta();
			if (ticks >= max_ticks) {
				ticks -= max_ticks;
				fire();
			}
		}
		void fire() {
			Sound::Play(30, 0, 0, random2::randomrange(1, 5));
			Gauntlets::Shoot(type_of_projectile, x, y, direction);
		}
	};
	//This function is called whenever the Break_Spawner gets hurt.
	void damage(Projectile &P);
	//This is the text that shows up when the Break_Spawner gets hurt.
	DText Damage_Text;
	int type = 0;
	std::vector<Cannon *> Cannons;
	//This is called when the NPC dies.
	void die();
public:
	Break_Spawner(int Type, int x_pos, int y_pos, int pattern, int type_of_projectile, int max_health, TileMap &TM);
	void tick(bool render);
	
};

