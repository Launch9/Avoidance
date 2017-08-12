#pragma once
#include "Sub_NPC_A.h"
#include "Projectile.h"
#include <iostream>
#include "DText.h"
#include "Sound.h"
#include "Sub_NPC_CD.h"
#include "random2.h"
#define TID 6
class Shielder;
class Shielder : public Sub_NPC_A, public Sub_NPC_CD
{
private:
	//This is a pointer to the tilemap object passed to the constructor.
	TileMap *Tmap;
	void reset();
	struct shield {
		private:
			
			//These contain all the good condition shield sprites.
			std::vector<AniT> GoodShieldSprites;
			//These contain all the bad condition shield sprites.
			std::vector<AniT> BadShieldSprites;
			//This tells the player how much health the shield has left.
			DText Damage_Text;
		public:
			
			//This is the type of sprite the shield uses.
			int type = 0;
			//X cordinate position.
			float x = 0;
			//Y cordinate position.
			float y = 0;
			//This tells the direction that the shield is in.
			int direction = 0;
			//This tells the direction that the projectile needs to be going in order to hurt the shield.
			int reversedirection = 0;
			//shield sprite that is drawn.
			ST Sprite;
			//This tells if the shield object is dead or not.
			int is_dead = false;
			//This is the max number of hits the shield can take before it is destroyed.
			//Make this -1 for the shield to last forever.
			int max_damage = 0;
			//This is the total amount of hits the shield has taken during its life time.
			int totaldamage = 0;
			//This tells if the shield is damaged or not.
			bool is_damaged = false;
			//This this is what is called when the shield has taken a hit by a projectile.
			void damage(Projectile &p) {
				Player::PlayerObjects[0]->addPower(0.5);
				//Playing the sound
				Sound::Play(23, 0, 0, random2::randomrange(1,5), 1,1);
				p.kill(2);
				totaldamage += p.getVoltage();
				Damage_Text.setDamage(totaldamage);
				Damage_Text.display();
				if (totaldamage > max_damage / 2 && is_damaged == false) {
					Sound::Play(24, 0, 0, random2::randomrange(1,5), 1, 1);
					Sprite *= BadShieldSprites[direction];
					is_damaged = true;
				}
				if (totaldamage >= max_damage) {
					is_dead = true;
					Sprite.deactivate();
				}
			}

			//This function is called to revive the shield.
			void revive() {
				totaldamage = 0;
				Sprite *= GoodShieldSprites[direction];
				Sprite.activate();
				is_dead = false;
				is_damaged = false;
			}

			//This function is used to kill the shield.
			void kill() {
					totaldamage = max_damage;
					is_dead = true;
					is_damaged = true;
					Sprite.deactivate();
			}

			void setPosition(const sf::Vector2f &Position) {
				x = Position.x;
				y = Position.y;
				Sprite.setPosition(Position.x, Position.y);
				Damage_Text.setPosition(Position.x, Position.y);
			}
			
			void setPosition(float x_pos, float y_pos) {
				x = x_pos;
				y = y_pos;
				Sprite.setPosition(x_pos, y_pos);
				Damage_Text.setPosition(x_pos, y_pos);
			}
			//Constructor
			shield(int x_pos, int y_pos, int direction_to_start_in, int Max_hits, std::vector<AniT> &sprites) {
				direction = direction_to_start_in;
				max_damage = Max_hits;
				x = x_pos; y = y_pos;
				Damage_Text.setPosition(x, y);
				Damage_Text.setMax_Health(Max_hits);
				switch (direction) {
				case 0:
					reversedirection = 2;
					break;
				case 1:
					reversedirection = 3;
					break;
				case 2:
					reversedirection = 0;
					break;
				case 3:
					reversedirection = 1;
					break;
				}
				for (unsigned int i = 1; i < 5; i++) {
					GoodShieldSprites.push_back(sprites[i]);
				}
				for (unsigned int i = 5; i < sprites.size(); i++) {
					BadShieldSprites.push_back(sprites[i]);
				}
				Sprite.setTexture(0);
				setPosition(x_pos, y_pos);
				Sprite *= GoodShieldSprites[direction];
				Sprite.setup();
			}
			
				
			
	};
	//This is a toggle used for the every other move deal.
	bool toggle = false;
	//This is the type of shielder that it is.
	int type = 0;
	//These contain the shields that are being used currently.
	std::vector<shield *> shields;
public:

	//These enemies will have shields around them, that will break, given the amount of hits needed.
	//Otherwise, you can just shoot around them and hit them in their sides.
	Shielder(int Type, int x_pos, int y_pos, int how_Many_hits, TileMap &TM, std::vector<int> Shields);
	//This is the tick function.
	void tick(bool render);
	//Overwritting animate function, because it doesn't need to animate anything.
	void animate();
	//This happens when the shielder dies.
	void when_dead();
	//This happens when the shielder gets revived.
	void when_revive();
	//If the player moved, then call this function.
	void ifPlayerMoved(int speed, int direction, int spaces, float remainder);
	//Deconstructor
	~Shielder();
};

