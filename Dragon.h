#pragma once
#include "NPC_MOTHER.h"
#include <iostream>
#include "DText.h"
#include "Sound.h"
#include "random2.h"
class Dragon : public NPC_MOTHER
{
private:
	//This is the type of dragon that is being used.
	int type = 0;
	//This is how long the dragon is.
	int How_long = 0;
	//This makes a new set of parts.
	void create_parts();
	void when_revive();
	void when_dead();
	//This is the color that gets brighter and brighter that closer it is to doing a drop in.
	sf::Color drop_in_color = sf::Color(255, 255, 255, 255);
	//These are the number of ticks that have gone by since the last drop it did.
	float drop_ticks = 0;
	//This is the max number of drop_ticks needed to do a drop in.
	float max_drop_ticks = 3;
	//This will make the dragon perform a drop in.
	void drop_in();
	//This function loops through all the parts and checks to see how many are type 1.
	int check_parts_how_many();
	//This function loops through all the parts and checks to see how many are type 1, and closed.
	int check_parts_how_many_closed();
	int damage_done = 0;
	int max_damage = 100;
	//This is the ID for the switch that activates when you kill the dragon.
	//If this is -1, then it will do nothing.
	int Switch = -1;
	std::vector<AniT> Ani_Sprites;
	//These are the total number of eye balls that appear on the dragon.
	unsigned int number_of_eye_balls = 0;
	//These are used for the momentum of the main dragon head.
	float x_speed = 0; //X cordinate speed
	float y_speed = 0; //Y cordinate speed
	float acceleration = 0; //This is how much is added to the x and y speed variables.
	//This is the position of the front face a frame before the newest one.
	sf::Vector2f old_position;
	//This tells you how many frames have gone by since the last time it has taken a R_Data check.
	int frames = 0;
	//This is how many frames that it has to reach before taking an R_Data check.
	int max_frames = 0;
	//This is the tick variable that makes sure that it only updates the rotation every so many ticks.
	float t = 0;
	//This the distance that the skull has gone.
	float distance = 0;
	//This is how far the skull needs to go to make a new data object.
	float max_distance = 32;
	//This is the max amount of ticks that the tick variable needs to reach before checking rotation again.
	float maxtick = 0.06;
	//This is the tangent variable made for storing the tangent of the right triangle created by the x_speed and y_speed variables when moving the sprite.
	double tan = 0;
	//This is the slope of the hypotnuse.
	double slope = 0;
	//This is what is called when the dragon dies.
	void die();
	//This class contains the data from the previous max_tick frame.
	//This class is used for rotation data.
	struct RData {
	public:
		float rotation = 0;
		double tangent = 0;
		RData(float Rotation, double Tangent) {
			rotation = Rotation;
			tangent = Tangent;
		}
	};
	struct Data {
	public:
		sf::Vector2f position;
		float rotation = 0;
		double tangent = 0; //This is the tangent of the right triangle created when moving the head.
		double slope = 0;
		Data(const sf::Vector2f &Position, float degrees, double Tangent) {
			position = Position;
			rotation = degrees;
			tangent = Tangent;
		}
	};
	
	//This class is used for each body part of the dragon.
	struct Body {
		
	private:
		friend Dragon;
		sf::Vector2f pos;
		int type = 0;
		bool is_closed = false;
		CT Sprite; //This is the sprite of the body piece.
		DText Damage_Text; //This is what is displayed when you hurt the dragon.
	public:
		//Type = 0: Normal hard shell taco, not able to damage these ones. (If you  
		//Type = 1: Soft eyeball taco, this is where its at. (You can damage this one.)
		//Type = 2: Tail
		Body(int Type, int x_pos, int y_pos, Dragon *dragon_object) {
			type = Type;
			Sprite.setOrigin(16, 16);
			Sprite.setTexture(0);
			Sprite.setPosition(x_pos + 16, y_pos + 16);
			switch (Type) {
			case 0:
				Sprite *= dragon_object->Ani_Sprites[1];
				break;
			case 1:
				Sprite *= dragon_object->Ani_Sprites[3];
				break;
			case 2:
				Sprite *= dragon_object->Ani_Sprites[2];
				break;
			}
			Sprite.setup();
		}
		const sf::Vector2f &getPosition() {
			return pos;
		}
		void setPosition(const sf::Vector2f &position) {
			pos = position;
			Sprite.setPosition(position);
		}
		void move(const sf::Vector2f &position) {
			pos += position;
			Sprite.move(position);
		}
		void setRotation(float to_what_degree) {
			Sprite.setRotation(to_what_degree);
		}
		void Die() {
			ParticleSettings s(pos.x, pos.y, 10, 20, 1, 1);
			s.color = sf::Color::Cyan;
			ParticleSystem::create(s);
			Sprite.deactivate();
		}
		void revive() {
			Sprite.activate();
		}
		void damage(Projectile &P, Dragon *dragon_object) {
			if (type != 0 && is_closed == false) {
				
				is_closed = true;
				Sprite *= dragon_object->Ani_Sprites[4];
				Sound::Play(27, 0, 0, random2::randomrange(1, 5), 1, 1);
				dragon_object->damage_done = dragon_object->check_parts_how_many_closed();
				Damage_Text.setMax_Health(dragon_object->check_parts_how_many());
				Damage_Text.setDamage(dragon_object->damage_done);
				Damage_Text.setPosition(pos);
				Damage_Text.display();
				if (dragon_object->damage_done > dragon_object->number_of_eye_balls) {
					dragon_object->die();
				}
			}
			P.kill(2);
		}
	
	};
	friend Body;
	void reset();
	std::vector<Body *> Dragon::Parts; //Parts of the dragon.
	std::vector<Data *> Dragon::P_Data; //Previous max_tick frame data, for figuring out how the parts in the back of the dragon should move.
	std::vector<RData *> Dragon::R_Data; //Previous max_tick frame data, for figuring out the rotation and tangent of the parts.
public:
	//This is a dragon that spins around the player.
	Dragon(int type, int x_pos, int y_pos, int how_long, TileMap &TM);
	~Dragon();
	//This is the tick function that is overwritten.
	void tick(bool render);
	//This function is overwrites the on from NPC_MOTHER and is used for animating.
	void animate();
	//
	
};

