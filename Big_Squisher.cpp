#include "stdafx.h"
#include "Big_Squisher.h"
#include "GF.h"
#include "Editor.h"
#include <iostream>
#include "Sound.h"
#include "random2.h"
#include "Debug.h"
#include "Sub_NPC_A.h"
#define back_add 2 //How many extra tiles to create when making the big_squisher.
Big_Squisher::Big_Squisher(int Type, int x_pos, int y_pos, int Distance, int Direction, TileMap &TM)
{
	type = Type;
	x = x_pos;
	y = y_pos;
	distance = Distance * 32;
	direction = Direction;
	speed = 400;
	max_time = 2;
	
	stoggle = true;
	GF::CheckTile_OverLap(x, y); //This checks to see if the tile is overlapping another tile.
	typeID = 14; //This is what distinguishes the NPC from all the other ones when being referred to.
	initx = x_pos; //This stores the initial x coordinate of creation.
	inity = y_pos; //This stores the initial y coordinate of creation.
	delx = x_pos; //This stores the x coordinate of where the editor needs to be to delete it.
	dely = y_pos; //This stores the y coordinate of where the editor needs to be to delete it.
	x2 = x_pos; //Extra x variable used for calculations.
	y2 = y_pos; //Extra y variable used for calculations.
	if (Editor::GetStatus() == true) {
		setPause(true);
	}
	else {
		setPause(false);
	}
	
	s = sf::Vector2f(64, 32);
	max_ticks = 0.1; //Normal 0.1 //These are the max ticks needed for a frame of animation to go by.
	sprite.setPosition(x, y); //This sets the position of the sprite to the given x and y coordinates.
	//sprite.setSize(sf::Vector2f(64, 32));
	sprite.setTexture(2); //This sets when the sprite should be drawn. 0: Background, 1: Character, 2: Foreground
	sprite.setup(); //This tells the sprite that it is ready to be drawn.
	SavedParameters = { typeID, Type, x_pos, y_pos, Distance, Direction }; //These are the parameters that are used when you load up the NPC. refer to World.cpp for details.
	num_SQ = 0;
	max_num_SQ = 5;
	origin_direction = direction;
	add_ons[direction] = distance;
	db = distance + (back_add * 32);
	switch (type) {
	case 1:
		speed = 10;
		break;
	case 2:
		speed = 800;
		break;
	case 3:
		speed = 1200;
		break;
	}
	
	anisprites = All_Sprites[TM.getTextureID()][typeID][0]; //What kind of animation you want to use.
	for (unsigned int i = 0; i < Distance + back_add; i++) {
		ST *spr = new ST();
		spr->setPosition(x, y);
		*spr *= anisprites[4];
		spr->setTexture(0);
		spr->setup();
		
		blocks.push_back(spr);
	}
	OVERRIDE_ANI = true; //If this is true, then the animation will still occur even when offscreen; Otherwise, it will stop animation when not rendered.
	sprite *= anisprites[direction]; //Setting the sprite to the AniT of direction index.
	NPC_Cache.push_back(this); //Pushing it into the cache to allow ticking.
}

Big_Squisher::~Big_Squisher() {
	for (unsigned int i = 0; i < blocks.size(); i++) {
		delete blocks[i];
	}
	blocks.clear();
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-~MAIN TICK~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//This function is an overwritten virtual function, but this is a very important function
//So, this is placed seperate from the less important ones.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void Big_Squisher::tick(bool render) {
	
	
	if (isWaiting == true) {
		how_long += GF::getDelta();
		
		if (how_long >= max_time) {
			how_long -= max_time;
			isWaiting = false;
		}
	}
	else {
		switch (direction) {
		case 0:
			y -= speed * GF::getDelta();
			if (y <= inity - add_ons[0]) {
				y = inity - add_ons[0];
				direction = 2;
				if (stoggle == true) {
					Sound::Play(58, 0, 0, random2::randomrange(1, 5));
					stoggle = false;
				}
				else {
					stoggle = true;
				}
				if (num_SQ >= max_num_SQ) {
					num_SQ = 0;
					isWaiting = true;
				}
				else {
					num_SQ++;
				}
			}
			break;
		case 1:
			x += speed * GF::getDelta();
			if (x >= initx + add_ons[1]) {
				x = initx + add_ons[1];
				direction = 3;
				if (stoggle == true) {
					Sound::Play(58, 0, 0, random2::randomrange(1, 5));
					stoggle = false;
				}
				else {
					stoggle = true;
				}
				if (num_SQ >= max_num_SQ) {
					num_SQ = 0;
					isWaiting = true;
				}
				else {
					num_SQ++;
				}
			}
			break;
		case 2:
			y += speed * GF::getDelta();
			if (y >= inity + add_ons[2]) {
				y = inity + add_ons[2];
				direction = 0;
				if (stoggle == true) {
					Sound::Play(58, 0, 0, random2::randomrange(1, 5));
					stoggle = false;
				}
				else {
					stoggle = true;
				}
				if (num_SQ >= max_num_SQ) {
					num_SQ = 0;
					isWaiting = true;
				}
				else {
					num_SQ++;
				}
			}
			break;
		case 3:
			x -= speed * GF::getDelta();
			if (x <= initx - add_ons[3]) {
				x = initx - add_ons[3];
				direction = 1;
				if (stoggle == true) {
					Sound::Play(58, 0, 0, random2::randomrange(1, 5));
					stoggle = false;
				}
				else {
					stoggle = true;
				}
				if (num_SQ >= max_num_SQ) {
					num_SQ = 0;
					isWaiting = true;
				}
				else {
					num_SQ++;
				}
				
			}
			break;
		}

	}
	
	
	switch (origin_direction) {
	case 0:
		for (unsigned int i = 0; i < blocks.size(); i++) {
			blocks[i]->setPosition(x, y + ((i + 1) * 32));
		}
		
		break;
	case 1:
		for (unsigned int i = 0; i < blocks.size(); i++) {
			blocks[i]->setPosition(x - ((i + 1) * 32), y);
		}
		break;
	case 2:
		for (unsigned int i = 0; i < blocks.size(); i++) {
			blocks[i]->setPosition(x, y - ((i + 1) * 32));
		}
		break;
	case 3:
		for (unsigned int i = 0; i < blocks.size(); i++) {
			blocks[i]->setPosition(x + ((i + 1) * 32), y);
		}
		break;
		
	}
	sprite.setPosition(x, y);
	if (did_delete_self == false) {
		//Checking to see if you should be dead or not.
		//if (render == true) {
		int t = -1; //Used for projectile collision detection.
		int b = -1; //Used for Sub_NPC_A collision detection.
		switch (origin_direction) {
		case 0:
			t = Projectile::DynamicCheckCollisionHeavy2(x + 1, y + 1, 30, 30 + db, 0, false);
			if (t != -1) {
				Projectile::VP[t].kill(1);
			}
			b = Sub_NPC_A::DynamicCheckCollision(sf::FloatRect(x + 1, y + 1, 30, 30 + db));
			if (b != -1) {
				Sub_NPC_A::Object_Cache[b]->delete_self(Sub_NPC_A::Object_Cache[b]);
			}
			//Debug::SquareDraw(x + 1, y + 1, 30, 30 + db);
			if (DynamicCheckPlayerCollision2(x + 1, y + 1, 30, 30 + db) == true) {
				KillPlayer();
			}
			break;
		case 1:
			t = Projectile::DynamicCheckCollisionHeavy2(x + 31, y + 1, 30 - db, 30, 0, false);
			if (t != -1) {
				Projectile::VP[t].kill(1);
			}
			b = Sub_NPC_A::DynamicCheckCollision(sf::FloatRect(x + 31, y + 1, 30 - db, 30));
			if (b != -1) {
				Sub_NPC_A::Object_Cache[b]->delete_self(Sub_NPC_A::Object_Cache[b]);
			}
			//Debug::SquareDraw(x + 31, y + 1, 30 - db, 30);
			if (DynamicCheckPlayerCollision2(x + 31, y + 1, 30 - db, 30) == true) {
				KillPlayer();
			}
			break;
		case 2:
			t = Projectile::DynamicCheckCollisionHeavy2(x + 1, y + 1 - db, 30, 30 + db, 0, false);
			if (t != -1) {
				Projectile::VP[t].kill(1);
			}
			b = Sub_NPC_A::DynamicCheckCollision(sf::FloatRect(x + 1, y + 1 - db, 30, 30 + db));
			if (b != -1) {
				Sub_NPC_A::Object_Cache[b]->delete_self(Sub_NPC_A::Object_Cache[b]);
			}
			//Debug::SquareDraw(x + 1, y + 1 - db, 30, 30 + db);
			if (DynamicCheckPlayerCollision2(x + 1, y + 1 - db, 30, 30 + db) == true) {
				KillPlayer();
			}
			break;
		case 3:
			t = Projectile::DynamicCheckCollisionHeavy2(x + 1, y + 1, 30 + db, 30, 0, false);
			if (t != -1) {
				Projectile::VP[t].kill(1);
			}
			b = Sub_NPC_A::DynamicCheckCollision(sf::FloatRect(x + 1, y + 1, 30 + db, 30));
			if (b != -1) {
				Sub_NPC_A::Object_Cache[b]->delete_self(Sub_NPC_A::Object_Cache[b]);
			}
			//Debug::SquareDraw(x + 1, y + 1, 30 + db, 30);
			if (DynamicCheckPlayerCollision2(x + 1, y + 1, 30 + db, 30) == true) {
				KillPlayer();
			}
			break;
		}

		//}
	}
	
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-~VIRTUAL FUNCTIONS~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//These are functions that overwrite the virtual functions in NPC_MOTHER.
//You may change these functions, but it is not necessary.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//This function is called when the NPC is revived.
void Big_Squisher::when_revive() {
	did_delete_self = false;
	sprite.activate();
}
//This function is called when the NPC is killed or deleted_self.
void Big_Squisher::when_dead() {
	sprite.deactivate();
}

//This is called when the player dies, the editor starts, etc.
//Its purpose is to place everything back to where it started.
void Big_Squisher::reset() {
	x = initx;
	y = inity;
	how_long = 0;
	num_SQ = 0;
	isWaiting = true;
	stoggle = true;
	direction = origin_direction;
}

void Big_Squisher::animate() {

}