#include "stdafx.h"
#include "Laser.h"
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include "Player.h"
#include "Debug.h"
#include "Sound.h"
#define RenderDist 3
#define Extra 100
#define ES 0.8
Laser::Laser(int startx, int starty, int startingdirection, TileMap &TM, int distance, int color, int movementspeed)
{
	bool should_spawn = true;
	
	switch(Player::PlayerObjects[0]->get_difficulty()) {
	case 0:
		should_spawn = false;
		break;
	case 1:
		should_spawn = false;
		break;
	case 2:
		should_spawn = true;
		if (movementspeed != 0) {
			movementspeed += 2;
		}
		break;
	}

	if (should_spawn == true) {
		x = startx;
		y = starty;
		GF::CheckTile_OverLap(x, y);
		typeID = 0;
		initx = startx;
		inity = starty;
		delx = startx;
		dely = starty;
		x2 = startx;
		y2 = starty;
		dist = distance;
		direction = startingdirection;
		startdirection = startingdirection;
		max_ticks = 0.05;
		speed = movementspeed * Extra;
		svectorindex = 0;
		sprite.setPosition(x, y);
		sprite.setTexture(2);
		sprite.setup();
		switch (direction) {
		case 0:
			lambda = [&]() {
				switch (direction) {
				case 2:
					y += speed * GF::getDelta() * getGlobalSpeed();
					if (y >= y2) {
						y = y2;
						//Sending it back the other way.
						direction = 0;
					}
					break;
				case 0:
					y -= speed * GF::getDelta() * getGlobalSpeed();
					if (y <= opcalcdist) {
						y = opcalcdist;
						//Sending it back the other way.
						direction = 2;
					}

				}
				sprite.setPosition(x, y);
			};
			break;
		case 1:
			lambda = [&]() {
				switch (direction) {
				case 1:
					x += speed * GF::getDelta() * getGlobalSpeed();
					if (x >= calcdist) {
						x = calcdist;
						//Sending it back the other way.
						direction = 3;
					}
					break;
				case 3:
					x -= speed * GF::getDelta() * getGlobalSpeed();
					if (x <= x2) {
						x = x2;
						//Sending it back the other way.
						direction = 1;
					}
				}
				sprite.setPosition(x, y);
			};
			break;
		case 2:
			lambda = [&]() {
				switch (direction) {
				case 2:
					y += speed * GF::getDelta() * getGlobalSpeed();
					if (y >= calcdist) {
						y = calcdist;
						//Sending it back the other way.
						direction = 0;
					}
					break;
				case 0:
					y -= speed * GF::getDelta() * getGlobalSpeed();
					if (y <= y2) {
						y = y2;
						//Sending it back the other way.
						direction = 2;
					}
				}
				sprite.setPosition(x, y);
			};
			break;
		case 3:
			lambda = [&]() {
				switch (direction) {
				case 1:
					x += speed * GF::getDelta() * getGlobalSpeed();
					if (x >= x2) {
						x = x2;
						//Sending it back the other way.
						direction = 3;
					}
					break;
				case 3:
					x -= speed * GF::getDelta() * getGlobalSpeed();
					if (x <= opcalcdist) {
						x = opcalcdist;
						//Sending it back the other way.
						direction = 1;
					}
				}
				sprite.setPosition(x, y);
			};


		}

		//This is used to flip the sprite when going horizontal.
		if (direction == 1 || direction == 3) {



			SavedParameters = { typeID, initx, inity, direction, dist, color, movementspeed };
			//This is for readjusting the position of the NPC because it changed Origin.

			calcdist = x2 + (base32 * dist);
			opcalcdist = x2 + (base32 * -dist);

			RoughHeightB = 2;
			RoughHeightT = 2;
			RoughWidthL = 16;
			RoughWidthR = 15;
			//h = 16
			//V is the basic animation.
			anisprites = All_Sprites[TM.getTextureID()][typeID][1];
		}
		//This happens if it is going vertically(DEFAULT).
		else {

			SavedParameters = { typeID, initx, inity, direction, dist, color, movementspeed };
			calcdist = y2 + (base32 * dist);
			opcalcdist = y2 + (base32 * -dist);
			RoughHeightB = 16;
			RoughHeightT = 15;
			RoughWidthL = 2;
			RoughWidthR = 2;
			//V is the basic animation.
			anisprites = All_Sprites[TM.getTextureID()][typeID][0];
		}


		OVERRIDE_ANI = true;
		sprite *= anisprites[0];
		switch (color) {
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
			SetSpriteColor(255, 0, 255, 255);
			break;
		case 7:
			SetSpriteColor(0, 255, 255, 255);
			break;

		}
		//setWholePos(x, y);
		NPC_Cache.push_back(this);
	}
	
	
}

void Laser::tick(bool render) {
	//This will animate the object on the screen.
	//This also is where the drawing happens.
	
	if (CheckPlayerSliding() == false) {
		if (DynamicCheckPlayerCollision(x - horizontalint, y - horizontalint, 32, 32) == true) {
			//This happens when you collide into the laser and die.
			KillPlayer();

		}
		/*switch (direction) {
		case 0:
			std::cout << "direction: up" << std::endl;
			if (DynamicCheckPlayerCollision2(x, y + 15, 1, 1) == true) {
				//This happens when you collide into the laser and die.
				KillPlayer();

			}
			break;
		case 1:
			std::cout << "direction: right" << std::endl;
			if (DynamicCheckPlayerCollision2(x + 15, y, 1, 1) == true) {
				//This happens when you collide into the laser and die.
				KillPlayer();

			}
			break;
		case 2:
			std::cout << "direction: down" << std::endl;
			if (DynamicCheckPlayerCollision2(x, y + 15, 1, 1) == true) {
				//This happens when you collide into the laser and die.
				KillPlayer();

			}
			break;
		case 3:
			std::cout << "direction: left" << std::endl;
			if (DynamicCheckPlayerCollision2(x + 15, y, 1, 1) == true) {
				//This happens when you collide into the laser and die.
				KillPlayer();

			}
		}*/
		
	}
		
	
	
	if (isPaused == false) {
		lambda();
	}
	
}


