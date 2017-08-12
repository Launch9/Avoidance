#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <sstream>
#include <SFML/Graphics/Color.hpp>
#include "Temporarytxt.h"
#include "Wall.h"
#include "Shop.h"
#include "Itemids.h"
#include "Sound.h"
#include "Wall.h"
#include "Bg.h"
#include "Light_MOTHER.h"
#include "Bullet.h"
#include "GF.h"
#include "Dia.h"
#include <future>
#include "ConstLight.h"
#include <fstream>
#include "GUI.h"
#include "Sound.h"
#include "Font.h"
#include "NPC_MOTHER.h"
#include <cmath>
#include "Projectile.h"
#include "Gauntlets.h"
#include "ParticleSystem.h"
#include "ParticleSettings.h"
#include "Sub_NPC_A.h"
#include "App.h"
#include "Debug.h"
#include "Screen_MOTHER.h"
#include "random2.h"
#include "Blast.h"
#include "Flame.h"
#define particlemultiplyer 2
#define DefaultPlayerSpeed 300
#define DefaultPlayerSlideSpeed 600
#define DefaultMaxPowerFuel 70
#define max_fuel 100
#define Pi 3.14159265
#define base32 32
#define bounceheight 32
#define SlidePitch 1
#define SlideVolume 100
#define DeathVolume 100
#define ProjOffset 32 //Projectile shooting offset from player. In Pixels!
//#define ob
#define SAS 30//Shooting angle size
using namespace std;
std::vector<std::vector<AniT>> Player::doAniSprites;
std::vector<std::vector<AniT>> Player::extraAnisprites;
vector<Player *> Player::PlayerObjects;
std::vector<std::vector<std::vector<AniT>>> Player::Ani_Sets;
sf::Sprite Player::s321;

Player::Player(const int &xstart, const int &ystart, const int &hlth, const int &walkspeed, const int &animationset, const sf::Font &fon, const int &buttoncontrols)
{
	speed = walkspeed;
	slidespeed = walkspeed * 2;
	SlideSound.setBuffer(Sound::GetSoundBuffer(1));
	SlideSound.setVolume(SlideVolume);
	SlideSound.setPitch(SlidePitch);
	DeathSound.setBuffer(Sound::GetSoundBuffer(3));
	x = xstart;
	y = ystart;
	SlideSound.setPosition(x, y, 0);
	DeathSound.setPosition(x, y, 0);
	vx = xstart;
	vy = ystart;
	xstartp = xstart;
	ystartp = ystart;
	anisetnum = animationset;
	
	switch (animationset) {
	case 1:
		AniSprites = Player::Ani_Sets[0];
		changeAni(1);
		break;
	}
	
	DeathSound.setVolume(DeathVolume);
	make_lambda_functions();
	movinganitick = 0;
	movingdirection = -1;
	health = hlth;
	font = fon;
	buttonlayout = buttoncontrols;
	Co.setstringlist(Itemids::rvstring(inventory));
	Co.setfont(font);
	Co.setPosition(x + 32, y);
	Co.setbuttonlayout(buttonlayout);
	Gtype = -1;
	SnapChoice();
	PSprite.setTexture(1);
	PSprite.setup();
	//Putting the object into a channel.
	PlayerObjects.push_back(this);
	GUI::update();
}


Player::Player(string SavedFile, TileMap &TM, int new_difficulty) {
	
	LoadPlayerFile(SavedFile);
	SlideSound.setBuffer(Sound::GetSoundBuffer(1));
	SlideSound.setVolume(SlideVolume);
	SlideSound.setPitch(SlidePitch);
	SlideSound.setPosition(x, y, 0);
	DeathSound.setVolume(DeathVolume);
	DeathSound.setBuffer(Sound::GetSoundBuffer(3));
	DeathSound.setPosition(x, y, 0);
	
	Cam::setxy_chan(0, x, y, true);
	s123 = s321;
	s123.setPosition(0, 0);
	
	PSprite.setTexture(1);
	if (new_difficulty != -1) {
		difficulty = new_difficulty;
	}
	PSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	PSprite.setPosition(0, 0);
	pickaxe *= extraAnisprites[0][0];
	pickaxe.setTexture(1);
//	pickaxe.setup();
	TM.setPlayerSprite(PSprite);
	TM.setPlayerSprite(pickaxe);
	pickaxe.deactivate();
	PlayerObjects.push_back(this);
	//World::setFile("Lob.txt");
	Dungeon = 1;
	Floor = 1;
	World::setDungeon(Dungeon);
	World::setFloor(Floor);
	World::setExtra(0);
	World::setAnimation(4);
	//World::setDungeon(3);
	//World::setFloor(1);
	//World::setExtra(0);
	//World::setAnimation(2);
	////World::LoadWorld("R/World Files/Dungeon 1/F1.txt", TM, true);
	
	GUI::update();
	
	//World::Files[Dungeon][Floor][0], true
}

Scoring &Player::getScoring() {
	return scoring;
}

int Player::get_how_manyDungeons() {
	return how_manyDungeons;
}

void Player::add_dungeon() {
	how_manyDungeons++;
}


void Player::make_lambda_functions() {

	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//LAMBDA FUNCTIONS FOR END OF ANIMATON CLEAN UP-=-
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	AEF.push_back([](Player * ob) {//end of turning to blue gauntlets
		ob->changeaniset(1);
		ob->hasShot = true;
	});

	AEF.push_back([](Player * ob) {//end of turning to purple gauntlets
		ob->changeaniset(2);
		ob->hasShot = true;
	});
	AEF.push_back([](Player * ob) {
		ob->changeaniset(0);
		ob->hasShot = true;
	});

	AEF.push_back([](Player * ob) {
		ob->changeaniset(0);
		ob->hasShot = true;
	});

}

void Player::snapListener() {
	sf::Listener::setPosition(float(vx), 0, float(vy));
	
}

void Player::useitem(const int &itemindex) {
	
	//Checking to see if the size of the inventory vector is large enough to be used without exceptions popping up.
	if (inventory.size() != 0) {
		string s("Used " + Itemids::rstring(inventory[itemindex]));
		
		//Making a temporary text appear when to use an item.
		Temporarytxt t(s, x - 32, y, 200, font, sf::Color::White, 1, 16);
		
		//Checking to see what kind of item was used.
		switch (inventory[itemindex]) {
		//If you used a potato of silence. 
		case 0:
			//erasing the item in the itemindex given.
			inventory.erase(inventory.begin() + itemindex);
			health += 50;
			break;
		//If you used blanket of mischeif.
		case 1:
			//erasing the item in the itemindex given.
			inventory.erase(inventory.begin() + itemindex);
			new ConstLight(x, y, 13, true, true, true);
			Basic_Tile_MOTHER::ResetAllLighting();
			break;
			
		}
		
	}
	GUI::update();
	
}
void Player::addinventoryitem(const int &itemid) {
	
	
	inventory.push_back(itemid);
	Co.setstringlist(Itemids::rvstring(inventory));
	
}
void Player::Openinventory() {

	CLock = true;
	
	
	
	int dn = Co.Choice();
	switch (dn) {
	case -6:
		inventorytog = false;
		CLock = false;
	
		break;
	case -5:
		useitem(Co.getindex());
		Co.setstringlist(Itemids::rvstring(inventory));
		Co.reset();
	}
	
}
void Player::Shop(const int &PlayerChannel){
	
	if (Shoppingtog == 1) {

		Shop::CommenceShop(PlayerChannel, buttonlayout);
	}
	
}
//This part of the file is full of the functions that get and set variables.
bool Player::GetShoppingtog() {
	return Shoppingtog;
}

float Player::getvx() {
	return vx;
}
float Player::getvy() {
	return vy;
}

int Player::getx() {
	return x;
}

int Player::gety() {
	return y;
}
void Player::setinventorytog(const bool &TF) {
	inventorytog = TF;
}

void Player::setXY(const float &xf, const float &yf) {
	x = xf;
	y = yf;
	vy = yf;
	vx = xf;
	Aniset_XY(xf, yf);
	SnapCam();
}

void Player::setCLock(const bool &TF) {
	CLock = TF;
}

void Player::setShoppingtog(const bool &TF) {
	Shoppingtog = TF;
}
int Player::getdirection() {
	return movingdirection;
}

bool Player::getSliding() {
	return isSliding;
}
bool Player::GetDeath() {
	return isDead;
}

void Player::Die() {
	if (isDead == false) {
		App::control_cache.clear();
		World::ClearSome();
		DeathSound.setPitch(random2::randomrange(1, 6));
		DeathSound.play();
		lives -= 1;
		ParticleSettings f;
		f.x = 16;
		f.y = 16;
		f.color = sf::Color::White;
		f.max_speed = 5;
		f.num_of_particle = 30;
		f.out_type = 0;
		f.time_to_last = 0.2;
		fuel = max_fuel;
		ParticleSystem::create(f);
		NPC_MOTHER::setISPD();
		isDead = true;
		x = 0;
		y = 0;
		if (lives <= 0) {
			scoring.setTimer(false);
			Screen_MOTHER::start(3);
			Floor = 0;
			lives = 3;
		}
		GUI::update();
	}
	
}

void Player::SnapCam() {
	Cam::setxy_chan(0, vx, vy, true);

}

void Player::SnapChoice() {
	Co.setPosition(x + (base32 * 2), y - (base32 * 2));
}

void Player::StandStill() {
	movingdirection = -1;
	movinganitick = 0;
	isSliding = false;
	stop_ani(false);
	vx = x;
	vy = y;
	changeAni(1);
}
unsigned int Player::moveup(const int &amount) {
	Controls[0] = true;
	if (movingdirection == -1) {
		how_far = 0;
		movingdirection = 0;
		bool toggle = Wall::CheckCollision(x, y - amount, true);
		if (toggle == true || CLock == true) {
			
			movingdirection = -1;
			return 1;
		}
		else {
			Sub_NPC_A::set_moved(speed, 0, amount / 32, 300 * GF::getDelta());
			changeAni(0);
			sx = x;
			sy = y;
			distance = amount;
			basedist = distance;
			movingdirection = 0;
			isstartmoving = true;
			return 2;
		}
		
		SnapCam();
		SnapChoice();
	}
	else {
		return 0;
	}

}

unsigned int Player::movedown(const int &amount) {
	Controls[2] = true;
	if (movingdirection == -1) {
		how_far = 0;
		movingdirection = 2;
		bool toggle = Wall::CheckCollision(x, y + amount, true);
		if (toggle == true || CLock == true) {
			movingdirection = -1;
			return 1;
		}
		else {
			Sub_NPC_A::set_moved(speed, 2, amount / 32, 300 * GF::getDelta());
			changeAni(0);
			sx = x;
			sy = y;
			distance = amount;
			basedist = distance;
			movingdirection = 2;
			isstartmoving = true;
			return 2;
		}
		SnapCam();
		SnapChoice();
	}
	else {
		return 0;
	}
	
}

unsigned int Player::moveleft(const int &amount) {
	Controls[3] = true;
	if (movingdirection == -1) {
		how_far = 0;
		movingdirection = 3;
		bool toggle = Wall::CheckCollision(x - amount, y, true);
		if (toggle == true || CLock == true) {
			
			movingdirection = -1;
			return 1;
		}
		else {
			Sub_NPC_A::set_moved(speed, 3, amount / 32, 300 * GF::getDelta());
			changeAni(0);
			sx = x;
			sy = y;
			distance = amount;
			basedist = distance;
			movingdirection = 3;
			isstartmoving = true;
			return 2;
		}
		SnapCam();
		SnapChoice();
	}
	else {
		return 0;
	}

}

unsigned int Player::moveright(const int &amount) {
	Controls[1] = true;
	if (movingdirection == -1) {
		how_far = 0;
		movingdirection = 1;
		bool toggle = Wall::CheckCollision(x + amount, y, true);
		if (toggle == true || CLock == true) {
			
			movingdirection = -1;
			return 1;
		}
		else {
			Sub_NPC_A::set_moved(speed, 1, amount / 32, 300 * GF::getDelta());
			changeAni(0);
			sx = x;
			sy = y;
			distance = amount;
			basedist = distance;
			movingdirection = 1;
			isstartmoving = true;
			return 2;
		}
		SnapCam();
		SnapChoice();
	}
	else {
		return 0;
	}
	
}


void Player::slideup(const int &amount) {
	
	//This checks to see if you are standing still, and if you are then it will set the sliding variable.
	if (movingdirection == -1) {
		
		int base = slideamountbase / 32;
		slideamount = slideamountbase;
		for (unsigned int i = 0; i < base; i++) {
			bool SC = Checkslidingcollision(x, y - (base32 * (i + 1)));


			if (SC == false) {
				if (i == base - 1) {
					Sub_NPC_A::set_moved(slidespeed, 0, 1, slidespeed * GF::getDelta());
					movingdirection = 0;
					changeAni(2);
					isSliding = true;
					SlideSound.setPitch(random2::randomrange(1, 4));
					SlideSound.play();
					sx = x;
					sy = y;
				}
				
			}
			else {
				//There is a wall right in front of the player.
				if (i == 0) {
					
					break;
				}
				else {
					
					slideamount = (32 * i);
					Sub_NPC_A::set_moved(slidespeed, 0, 1, slidespeed * GF::getDelta());
					movingdirection = 0;
					changeAni(2);
					isSliding = true;
					SlideSound.setPitch(random2::randomrange(1, 4));
					SlideSound.play();
					sx = x;
					sy = y;
				}
			}
		}
		
		
	}
	
}

void Player::slidedown(const int &amount) {
	
	if (movingdirection == -1) {
		//This checks to see if you are standing still, and if you are then it will set the sliding variable.
		int base = slideamountbase / 32;
		slideamount = slideamountbase;
		for (unsigned int i = 0; i < base; i++) {
			bool SC = Checkslidingcollision(x, y + (base32 * (i + 1)));


			if (SC == false) {
				if (i == base - 1) {
					Sub_NPC_A::set_moved(slidespeed, 2, 1, slidespeed * GF::getDelta());
					movingdirection = 2;
					changeAni(2);
					isSliding = true;
					SlideSound.setPitch(random2::randomrange(1, 4));
					SlideSound.play();
					sx = x;
					sy = y;
				}


			}
			else {
				//There is a wall right in front of the player.
				if (i == 0) {

					break;
				}
				else {
				
					slideamount = (32 * i);
					Sub_NPC_A::set_moved(slidespeed, 2, 1, slidespeed * GF::getDelta());
					movingdirection = 2;
					changeAni(2);
					isSliding = true;
					SlideSound.setPitch(random2::randomrange(1, 4));
					SlideSound.play();
					sx = x;
					sy = y;
				}
			}
		}
	}
	


}



void Player::slideleft(const int &amount) {
	if (movingdirection == -1) {
		int base = slideamountbase / 32;
		slideamount = slideamountbase;
		for (unsigned int i = 0; i < base; i++) {
			bool SC = Checkslidingcollision(x - (base32 * (i + 1)), y);


			if (SC == false) {
				if (i == base - 1) {
					Sub_NPC_A::set_moved(slidespeed, 3, 1, slidespeed * GF::getDelta());
					movingdirection = 3;
					changeAni(3);
					isSliding = true;
					SlideSound.setPitch(random2::randomrange(1, 4));
					SlideSound.play();
					sx = x;
					sy = y;
				}


			}
			else {
				//There is a wall right in front of the player.
				if (i == 0) {

					break;
				}
				else {
					slideamount = (32 * i);
					Sub_NPC_A::set_moved(slidespeed, 3, 1, slidespeed * GF::getDelta());
					movingdirection = 3;
					changeAni(3);
					isSliding = true;
					SlideSound.setPitch(random2::randomrange(1, 4));
					SlideSound.play();
					sx = x;
					sy = y;
				}

			}
		}
	}
	


}


void Player::slideright(const int &amount) {
	if (movingdirection == -1) {
		//This checks to see if you are standing still, and if you are then it will set the sliding variable.
		int base = slideamountbase / 32;
		slideamount = slideamountbase;
		for (unsigned int i = 0; i < base; i++) {
			bool SC = Checkslidingcollision(x + (base32 * (i + 1)), y);


			if (SC == false) {
				if (i == base - 1) {
					Sub_NPC_A::set_moved(slidespeed, 1, 1, slidespeed * GF::getDelta());
					movingdirection = 1;
					changeAni(2);
					isSliding = true;
					SlideSound.setPitch(random2::randomrange(1, 4));
					SlideSound.play();
					sx = x;
					sy = y;
				}


			}
			else {
				//There is a wall right in front of the player.
				if (i == 0) {

					break;
				}
				else {
					slideamount = (32 * i);
					Sub_NPC_A::set_moved(slidespeed, 1, 1, slidespeed * GF::getDelta());
					movingdirection = 1;
					changeAni(2);
					isSliding = true;
					SlideSound.setPitch(random2::randomrange(1, 4));
					SlideSound.play();
					sx = x;
					sy = y;
				}

			}
		}
	}
	


}




void Player::constanimation(const int &camera_channel, bool camlock) {
	scoring.tick();
	if (Projectile::DynamicCheckCollisionHeavy(vx, vy, 32, 32, 0, true) != -1) {
		Die();
	}

	if (isDead == false) {
		
		//This happens if you are not sliding.
		if (isSliding == false) {
			if (inventorytog == 1) {
				Openinventory();
			}
			else {
				Co.reset();
			}
			if (movingdirection != -1 || const_ani_override == true) {
				if (const_ani_override == false) {
					readystop = false;
				}

				switch (movingdirection) {
				case 0:
					calculate_bounce(movingdirection);
					//Scrolling the camera.
					if (camlock == false) {
						Cam::scroll_chan(camera_channel, 0, -(speed * GF::getDelta()));
					}
					vy = vy - (speed * GF::getDelta());
					
					if (how_far >= distance) {
						if (isBounce == true) {
							App::control_cache.clear();
						}
						sy = sy - distance;
						how_far -= distance;
						y -= distance;
						
						bool toggle = Wall::CheckCollision(x, y - 32, false);
						
						if (toggle == true || CLock == true) {
							movingdirection = -1;
							stop_ani();
						}
						else {
							//Sub_NPC_A::set_moved(movingdirection, 1);
						}
						Basic_Tile_MOTHER::CheckSpecialCollision(0);
						readystop = true;
					}
					break;
				case 1:
					calculate_bounce(movingdirection);
					//Scrolling the camera.
					if (camlock == false) {
						Cam::scroll_chan(camera_channel, speed * GF::getDelta(), 0);
					}
					vx = vx + (speed * GF::getDelta());
	
					if (how_far >= distance) {
						if (isBounce == true) {
							App::control_cache.clear();
						}
						sx = sx + distance;
						how_far -= distance;
						x += distance;
						bool toggle = Wall::CheckCollision(x + 32, y, false);
						if (toggle == true || CLock == true) {
							
							movingdirection = -1;
							stop_ani();
						}
						Basic_Tile_MOTHER::CheckSpecialCollision(0);
						readystop = true;
					}
					break;
				case 2:
					calculate_bounce(movingdirection);
					//Scrolling the camera.
					if (camlock == false) {
						Cam::scroll_chan(camera_channel, 0, speed * GF::getDelta());
					}
					vy = vy + (speed * GF::getDelta());
	
					if (how_far >= distance) {
						if (isBounce == true) {
							App::control_cache.clear();
						}
						sy = sy + distance;
						how_far -= distance;
						y += distance;
						
						bool toggle = Wall::CheckCollision(x, y + 32, false);
						
						if (toggle == true || CLock == true) {
							movingdirection = -1;
							stop_ani();
						}
						Basic_Tile_MOTHER::CheckSpecialCollision(0);
						readystop = true;
					}
					break;
				case 3:
					calculate_bounce(movingdirection);
					//Scrolling the camera.
					if (camlock == false) {
						Cam::scroll_chan(camera_channel, -(speed * GF::getDelta()), 0);
					}
					vx = vx - (speed * GF::getDelta());
		
					if (how_far >= distance) {
						if (isBounce == true) {
							App::control_cache.clear();
							
						}
						sx = sx - distance;
						how_far -= distance;
						x -= distance;
						
						bool toggle = Wall::CheckCollision(x - 32, y, false);
						
						if (toggle == true || CLock == true) {
							movingdirection = -1;
							stop_ani();
						}
						Basic_Tile_MOTHER::CheckSpecialCollision(0);
						readystop = true;
					}
					break;
				}
				how_far = how_far + (speed * GF::getDelta());
				/*if (readystop == true) {
					if (Controls[movingdirection] == false) {
						stop_ani();
					}
					else {
						Sub_NPC_A::A_tick();
					}
				}*/
				
					if (readystop == true) {
						if (shootingdirection_r == -1 && isBounce == false) {
							for (unsigned int i = 0; i < Controls.size(); i++) {
								if (i == movingdirection) {
									if ((Controls[i] == false)) {
										if (readystop == true) {
										//This is for moving the player back to the original position if he did not make it to the tile.
											stop_ani();
										}
									}
									else {
										switch (movingdirection) {
										case 0:
											Sub_NPC_A::set_moved(speed, movingdirection, 1, y - vy);
											break;
										case 1:
											Sub_NPC_A::set_moved(speed, movingdirection, 1, vx - x);
											break;
										case 2:
											Sub_NPC_A::set_moved(speed, movingdirection, 1, vy - y);
											break;
										case 3:
											Sub_NPC_A::set_moved(speed, movingdirection, 1, x - vx);
										}
									}
								}
							}
						}
						else {
							
							
								//CLock = true;
								readystop = true;
								for (unsigned int i = 0; i < Controls.size(); i++) {
									Controls[i] = false;
								}
								//if (const_ani_override == false) {
									stop_ani();
									switch (shootingdirection_r) {
									case 0:
										shootup();
										break;
									case 1:
										shootright();
										break;
									case 2:
										shootdown();
										break;
									case 3:
										shootleft();
									}
								//}
									
								//movingdirection = -1;
									App::control_cache.clear();
									shootingdirection_r = -1;
								
							
						}
				}
				
				
				
				
				
				snapListener();
				
				
					
				
			}
			

		}
		//This happens if you are Sliding.
		else if (isSliding = true) {
			
			switch (movingdirection) {
			case 0:
				////Scrolling the camera.
				//if (camlock == false) {
				//	Cam::scroll_chan(camera_channel, 0, -slidespeed * GF::getDelta());
				//}

				vy = vy - (slidespeed * GF::getDelta());
				
				if (vy <= sy - slideamount) {
					y = sy - slideamount;
					vy = y;
					if (check_pending_shoot() == false) {
						stop_ani();
					}
				}
				else {
					if (vy <= sy - (32 * slidingrep)) {
						y = sy - (32 * slidingrep);
						slidingrep++;
						Basic_Tile_MOTHER::CheckSpecialCollision(0);
						if (check_pending_shoot() == false) {
							Sub_NPC_A::set_moved(slidespeed, movingdirection, 1, (sy - 32) - vy); //Setting it so that the NPC_As should move one place.
						};
						
						
						
					}
				}
				
				break;
			case 1:
				//Scrolling the camera.
				//if (camlock == false) {
				//	Cam::scroll_chan(camera_channel, slidespeed * GF::getDelta(), 0);
				//}
				vx = vx + (slidespeed * GF::getDelta());
				if (vx >= sx + slideamount) {
					x = sx + slideamount;
					vx = x;
					if (check_pending_shoot() == false) {
						stop_ani();
					}
				}
				else {
					if (vx >= sx + (32 * slidingrep)) {
						
						x = sx + (32 * slidingrep);		
						slidingrep++;
						Basic_Tile_MOTHER::CheckSpecialCollision(0);
						if (check_pending_shoot() == false) {
							Sub_NPC_A::set_moved(slidespeed, movingdirection, 1, vx - (sx + 32)); //Setting it so that the NPC_As should move one place.
						};
						
						
						
					}
				}
				
				
				break;
			case 2:
				//Scrolling the camera.
				//if (camlock == false) {
				//	Cam::scroll_chan(camera_channel, 0, slidespeed * GF::getDelta());
				//}
				vy = vy + (slidespeed * GF::getDelta());
				if (vy >= sy + slideamount) {
					y = sy + slideamount;
					vy = y;
					if (check_pending_shoot() == false) {
						stop_ani();
					}
					
				}
				else {
					if (vy >= sy + (32 * slidingrep)) {
						y = sy + (32 * slidingrep);
						slidingrep++;
						Basic_Tile_MOTHER::CheckSpecialCollision(0);
						if (check_pending_shoot() == false) {
							Sub_NPC_A::set_moved(slidespeed, movingdirection, 1, vy - (sy + 32)); //Setting it so that the NPC_As should move one place.
						}
						
						
						
					}
				}
				
				break;
			case 3:
				//Scrolling the camera.
				//if (camlock == false) {
				//	Cam::scroll_chan(camera_channel, -slidespeed * GF::getDelta(), 0);
				//}
				vx = vx - (slidespeed * GF::getDelta());
				if (vx <= sx - slideamount) {
					x = sx - slideamount;
					vx = x;
					if (check_pending_shoot() == false) {
						stop_ani();
					}
				}
				else {
					if (vx <= sx - (32 * slidingrep)) {
						x = sx - (32 * slidingrep);
						slidingrep++;
						Basic_Tile_MOTHER::CheckSpecialCollision(0);
						if (check_pending_shoot() == false) {
							Sub_NPC_A::set_moved(slidespeed, movingdirection, 1, (sx - 32) - vx); //Setting it so that the NPC_As should move one place.
						}
						
						
						
					}
				}
				
				break;


			}
			SnapCam();
			snapListener();
			
		}
	}

	

	if (isDead == true) {
		deathtick += 1;
		x = 0;
		y = 0;
		vx = 0;
		vy = 0;
		CLock = true;
		movingdirection = -1;
		movinganitick = 0;
		changeAni(1);
		SnapCam();
		StandStill();
		//This is what happens when you are still dead.
		//This happens for a given amount of time.
		//Stops you from moving.
		//Why are you still reading this comment!
		if (deathtick >= deathtickmax) {
			deathtick = 0;
			isDead = false;
			CLock = false;

		}
	}
	
		
	
	text.setPosition(vx + 16, vy + 16);
	//PSprite.setPosition(vx, vy);
	//SnapCam();
	PSprite.setPosition(vx, vy);
	//s123.setPosition(vx, vy);
	//Debug::SquareDraw(vx + 32, vy + 32, 32, 32);
	Aniset_XY(vx, vy);
	animate();
	//Setting all the controls to false.
	for (unsigned int i = 0; i < Controls.size(); i++) {
		Controls[i] = false;
	}


}

bool Player::check_pending_shoot() {
	if (shootingdirection_r != -1) {
		stop_ani();
		switch (shootingdirection_r) {
		case 0:
			shootup();
			break;
		case 1:
			shootright();
			break;
		case 2:
			shootdown();
			break;
		case 3:
			shootleft();
		}
		App::control_cache.clear();
		shootingdirection_r = -1;
		return true;
	}
	else {
		return false;
	}
}

void Player::LoadPlayerFile(string File) {
	char CC; //Current character
	std::vector<int> Para;
	std::vector<int> VB;//Vector build
	std::vector<std::vector<int>> Vectors;
	std::string MEM = "";
	bool Start = false;
	bool isVector = false;
	ifstream f;
	f.open(File, ios::in);

	while (f.good()) {
		f.seekg(0, ios::cur);
		f >> CC;

		if (Start == true) {
			
			if (CC == *",") {
				if (isVector == false) {
					Para.push_back(GF::StringtoInt(MEM));
				}
				else {
					VB.push_back(GF::StringtoInt(MEM));
				}
				
				MEM = "";
			}
			else if (CC == *")") {
				Start = false;
				continue;
			}
			else if (CC == *":") {
				isVector = true;
				continue;
			}
			else if (CC == *";") {
				Vectors.push_back(VB);
				VB = {};
				isVector = false;
				continue;
			}
			else {
				MEM.push_back(CC);
			}
		}
		if (CC == *"(") {
			Start = true;
		}
		
		
	}
	
	
	x = Para[0];
	y = Para[1];
	
	vx = x;
	vy = y;
	xstartp = x;
	ystartp = y;
	
	lives = Para[2];
	Floor = Para[4];
	difficulty = Para[5];
	//Dungeon = Para[6];
	max_powerfuel = DefaultMaxPowerFuel;
	
	make_lambda_functions();
	anisetnum = 1;
	switch (anisetnum) {
	case 1:
		AniSprites = Player::Ani_Sets[0];
		max_tick = 2;
		break;
	}
	changeAni(1);
	Step = Para[3];
	speed = DefaultPlayerSpeed;
	slidespeed = DefaultPlayerSlideSpeed;
	//Floor = 0;
	Dungeon = 0;
	how_manyDungeons = Step;
	font = Font::Get_isocpeur();
	
	
	Co.setstringlist(Itemids::rvstring(inventory));
	Co.setfont(font);
	Co.setPosition(x + 32, y);
	Co.setbuttonlayout(buttonlayout);
	ObtainedGauntlets = Vectors[0];
	//Gtype = ObtainedGauntlets[OGindex];
	Gtype = -1;
	//pickaxe.deactivate();
	if (ObtainedGauntlets.size() > 0) {
		int v1;
		int v3;

		if (GF::does_exist(OGindex - 1, ObtainedGauntlets.size()) == false) {
			v1 = -1;
		}
		else {
			v1 = ObtainedGauntlets[OGindex - 1];
		}

		if (GF::does_exist(OGindex + 1, ObtainedGauntlets.size()) == false) {
			v3 = -1;
		}
		else {
			v3 = ObtainedGauntlets[OGindex + 1];
		}
		DisplayedGauntlets = { v1, ObtainedGauntlets[OGindex], v3 };

	}
	
	//ObtainedGauntlets = {};
	//DisplayedGauntlets = {-1,-1,-1};
	
	//GUI::update();
}

void Player::SavePlayerFile(std::string File) {
	std::string Save = "(";
	Save.append(std::to_string(x) + ",");
	Save.append(std::to_string(y) + ",");
	Save.append(std::to_string(lives) + ",");
	Save.append(std::to_string(Step) + ",");
	Save.append(std::to_string(Floor) + ",");
	Save.append(std::to_string(difficulty) + ",");
	//Save.append(std::to_string(Dungeon) + ",");
	
	Save.append(":");
	for (unsigned int i = 0; i < ObtainedGauntlets.size(); i++) {
		Save.append(std::to_string(ObtainedGauntlets[i]) + ",");
	}
	Save.append(";");
	Save.append(")");
	ofstream f;
	f.open(File, ios::out);
	f.clear();
	f << Save;
	f.close();
	std::cout << "Player file saved to " + File << std::endl;
}

void Player::init(sf::Texture &tex) {
	s321.setTexture(tex);
	s321.setTextureRect(sf::IntRect(0, 0, 32, 32));
	//No gauntlet
	AniT s0(sf::IntRect(0, 64 - 64, 32, 32));
	AniT s1(sf::IntRect(0, 96 - 64, 32, 32));
	AniT s2(sf::IntRect(0, 128 - 64, 32, 32));
	AniT s3(sf::IntRect(0, 160 - 64, 32, 32));
	AniT s_a0(sf::IntRect(0, 192 - 64, 32, 32));
	AniT s_a1(sf::IntRect(0, 224 - 64, 32, 32));
	AniT s_a2(sf::IntRect(0, 256 - 64, 32, 32));
	AniT s_b0(sf::IntRect(0, 288 - 64, 32, 32));
	AniT s_b1(sf::IntRect(0, 320 - 64, 32, 32));
	AniT s_c0(sf::IntRect(0, 352 - 64, 32, 32));
	AniT s_c1(sf::IntRect(0, 384 - 64, 32, 32));
	AniT s_d0(sf::IntRect(0, 416 - 64, 32, 32));
	AniT s_e0(sf::IntRect(0, 448 - 64, 32, 32));
	
	std::vector<AniT> v0 = { s0, s1, s2, s3 };
	std::vector<AniT> a = { s0, s_a0, s_a1, s_a2 };
	std::vector<AniT> b = { s_b0, s_b1 };
	std::vector<AniT> c = { s_c0, s_c1 };
	std::vector<AniT> d = { s_d0 };
	std::vector<AniT> e = { s_e0 };
	//Blue gauntlets-=-=-=-=-=-=-=-=-=-
	AniT sa0(sf::IntRect(32, 64 - 64, 32, 32));
	AniT sa1(sf::IntRect(32, 96 - 64, 32, 32));
	AniT sa2(sf::IntRect(32, 128 - 64, 32, 32));
	AniT sa3(sf::IntRect(32, 160 - 64, 32, 32));
	AniT sa_a0(sf::IntRect(32, 192 - 64, 32, 32));
	AniT sa_a1(sf::IntRect(32, 224 - 64, 32, 32));
	AniT sa_a2(sf::IntRect(32, 256 - 64, 32, 32));
	AniT sa_b0(sf::IntRect(32, 288 - 64, 32, 32));
	AniT sa_b1(sf::IntRect(32, 320 - 64, 32, 32));
	AniT sa_c0(sf::IntRect(32, 352 - 64, 32, 32));
	AniT sa_c1(sf::IntRect(32, 384 - 64, 32, 32));
	AniT sa_d0(sf::IntRect(32, 416 - 64, 32, 32));
	AniT sa_e0(sf::IntRect(32, 448 - 64, 32, 32));
	
	std::vector<AniT> a_v0 = { sa0, sa1, sa2, sa3 };
	std::vector<AniT> a_a = { sa0, sa_a0, sa_a1, sa_a2 };
	std::vector<AniT> a_b = { sa_b0, sa_b1 };
	std::vector<AniT> a_c = { sa_c0, sa_c1 };
	std::vector<AniT> a_d = { sa_d0 };
	std::vector<AniT> a_e = { sa_e0 };
	//Purple gauntlets
	AniT sb0(sf::IntRect(32 + 64, 64 - 64, 32, 32));
	AniT sb1(sf::IntRect(32 + 64, 96 - 64, 32, 32));
	AniT sb2(sf::IntRect(32 + 64, 128 - 64, 32, 32));
	AniT sb3(sf::IntRect(32 + 64, 160 - 64, 32, 32));
	AniT sb_a0(sf::IntRect(32 + 64, 192 - 64, 32, 32));
	AniT sb_a1(sf::IntRect(32 + 64, 224 - 64, 32, 32));
	AniT sb_a2(sf::IntRect(32 + 64, 256 - 64, 32, 32));
	AniT sb_b0(sf::IntRect(32 + 64, 288 - 64, 32, 32));
	AniT sb_b1(sf::IntRect(32 + 64, 320 - 64, 32, 32));
	AniT sb_c0(sf::IntRect(32 + 64, 352 - 64, 32, 32));
	AniT sb_c1(sf::IntRect(32 + 64, 384 - 64, 32, 32));
	AniT sb_d0(sf::IntRect(32 + 64, 416 - 64, 32, 32));
	AniT sb_e0(sf::IntRect(32 + 64, 448 - 64, 32, 32));
	
	std::vector<AniT> b_v0 = { sb0, sb1, sb2, sb3 };
	std::vector<AniT> b_a = { sb0, sb_a0, sb_a1, sb_a2 };
	std::vector<AniT> b_b = { sb_b0, sb_b1 };
	std::vector<AniT> b_c = { sb_c0, sb_c1 };
	std::vector<AniT> b_d = { sb_d0 };
	std::vector<AniT> b_e = { sb_e0 };

	//Green gauntlet
	AniT sc0(sf::IntRect(160, 64 - 64, 32, 32));
	AniT sc1(sf::IntRect(160, 96 - 64, 32, 32));
	AniT sc2(sf::IntRect(160, 128 - 64, 32, 32));
	AniT sc3(sf::IntRect(160, 160 - 64, 32, 32));
	AniT sc_a0(sf::IntRect(160, 192 - 64, 32, 32));
	AniT sc_a1(sf::IntRect(160, 224 - 64, 32, 32));
	AniT sc_a2(sf::IntRect(160, 256 - 64, 32, 32));
	AniT sc_b0(sf::IntRect(160, 288 - 64, 32, 32));
	AniT sc_b1(sf::IntRect(160, 320 - 64, 32, 32));
	AniT sc_c0(sf::IntRect(160, 352 - 64, 32, 32));
	AniT sc_c1(sf::IntRect(160, 384 - 64, 32, 32));
	AniT sc_d0(sf::IntRect(160, 416 - 64, 32, 32));
	AniT sc_e0(sf::IntRect(160, 448 - 64, 32, 32));

	std::vector<AniT> c_v0 = { sc0, sc1, sc2, sc3 };
	std::vector<AniT> c_a = { sc0, sc_a0, sc_a1, sc_a2 };
	std::vector<AniT> c_b = { sc_b0, sc_b1 };
	std::vector<AniT> c_c = { sc_c0, sc_c1 };
	std::vector<AniT> c_d = { sc_d0 };
	std::vector<AniT> c_e = { sc_e0 };
	//0 = Walking animation
	//1 = Standing still animation
	//2 = Sliding animation(Right)
	//3 = Sliding animation(Left)
	std::vector<std::vector<AniT>> vfull0 = { v0, a, b, c, d, e }; //No gauntlet
	std::vector<std::vector<AniT>> vfull1 = { a_v0, a_a, a_b, a_c, a_d, a_e }; //Blue gauntlet
	std::vector<std::vector<AniT>> vfull2 = { b_v0, b_a, b_b, b_c, b_d, b_e }; //Purple gauntlet
	std::vector<std::vector<AniT>> vfull3 = { c_v0, c_a, c_b, c_c, c_d, c_e }; //Green gauntlet
	Ani_Sets = { vfull0, vfull1, vfull2, vfull3 };
	//Putting on blue gauntlets
	AniT da0_0(sf::IntRect(64, (32 * 0), 32, 32));
	AniT da0_1(sf::IntRect(64, (32 * 1), 32, 32));
	AniT da0_2(sf::IntRect(64, (32 * 2), 32, 32));
	AniT da0_3(sf::IntRect(64, (32 * 3), 32, 32));
	AniT da0_4(sf::IntRect(64, (32 * 4), 32, 32));
	AniT da0_5(sf::IntRect(64, (32 * 5), 32, 32));
	AniT da0_6(sf::IntRect(64, (32 * 6), 32, 32));
	AniT da0_7(sf::IntRect(64, (32 * 7), 32, 32));
	AniT da0_8(sf::IntRect(64, (32 * 8), 32, 32));
	//Putting on purple gauntlets
	AniT da1_0(sf::IntRect(64 + 64, (32 * 0), 32, 32));
	AniT da1_1(sf::IntRect(64 + 64, (32 * 1), 32, 32));
	AniT da1_2(sf::IntRect(64 + 64, (32 * 2), 32, 32));
	AniT da1_3(sf::IntRect(64 + 64, (32 * 3), 32, 32));
	AniT da1_4(sf::IntRect(64 + 64, (32 * 4), 32, 32));
	AniT da1_5(sf::IntRect(64 + 64, (32 * 5), 32, 32));
	AniT da1_6(sf::IntRect(64 + 64, (32 * 6), 32, 32));
	AniT da1_7(sf::IntRect(64 + 64, (32 * 7), 32, 32));
	AniT da1_8(sf::IntRect(64 + 64, (32 * 8), 32, 32));
	//Putting on green gauntlets
	AniT da3_0(sf::IntRect(192, (32 * 0), 32, 32));
	AniT da3_1(sf::IntRect(192, (32 * 1), 32, 32));
	AniT da3_2(sf::IntRect(192, (32 * 2), 32, 32));
	AniT da3_3(sf::IntRect(192, (32 * 3), 32, 32));
	AniT da3_4(sf::IntRect(192, (32 * 4), 32, 32));
	AniT da3_5(sf::IntRect(192, (32 * 5), 32, 32));
	AniT da3_6(sf::IntRect(192, (32 * 6), 32, 32));
	AniT da3_7(sf::IntRect(192, (32 * 7), 32, 32));
	AniT da3_8(sf::IntRect(192, (32 * 8), 32, 32));
	
	//swing pickaxe right
	//Standard gloves
	AniT da2_0(sf::IntRect(0, 416 + (32 * 0), 32, 32));
	AniT da2_1(sf::IntRect(0, 416 + (32 * 1), 32, 32));
	AniT da2_2(sf::IntRect(0, 416 + (32 * 2), 32, 32));
	AniT da2_3(sf::IntRect(0, 416 + (32 * 3), 32, 32));
	AniT da2_4(sf::IntRect(0, 416 + (32 * 4), 32, 32));
	AniT da2_5(sf::IntRect(32, 416 + (32 * 0), 32, 32));
	//Blue gauntlets
	AniT da2_6(sf::IntRect(64, 416 + (32 * 0), 32, 32));
	AniT da2_7(sf::IntRect(64, 416 + (32 * 1), 32, 32));
	AniT da2_8(sf::IntRect(64, 416 + (32 * 2), 32, 32));
	AniT da2_9(sf::IntRect(64, 416 + (32 * 3), 32, 32));
	AniT da2_10(sf::IntRect(64, 416 + (32 * 4), 32, 32));
	AniT da2_11(sf::IntRect(96, 416 + (32 * 0), 32, 32));
	//Purple gauntlets
	AniT da2_12(sf::IntRect(128, 416 + (32 * 0), 32, 32));
	AniT da2_13(sf::IntRect(128, 416 + (32 * 1), 32, 32));
	AniT da2_14(sf::IntRect(128, 416 + (32 * 2), 32, 32));
	AniT da2_15(sf::IntRect(128, 416 + (32 * 3), 32, 32));
	AniT da2_16(sf::IntRect(128, 416 + (32 * 4), 32, 32));
	AniT da2_17(sf::IntRect(160, 416 + (32 * 0), 32, 32));
	//Green gauntlets
	AniT da2_36(sf::IntRect(224, 256 + (32 * 0), 32, 32));
	AniT da2_37(sf::IntRect(224, 256 + (32 * 1), 32, 32));
	AniT da2_38(sf::IntRect(224, 256 + (32 * 2), 32, 32));
	AniT da2_39(sf::IntRect(224, 256 + (32 * 3), 32, 32));
	AniT da2_40(sf::IntRect(224, 256 + (32 * 4), 32, 32));
	AniT da2_41(sf::IntRect(224 + 32, 256 + (32 * 0), 32, 32));
	//swing pickaxe left
	//Standard gloves
	AniT da2_18(sf::IntRect(192 + 32, 416 + (32 * 0), 32, 32));
	AniT da2_19(sf::IntRect(192 + 32, 416 + (32 * 1), 32, 32));
	AniT da2_20(sf::IntRect(192 + 32, 416 + (32 * 2), 32, 32));
	AniT da2_21(sf::IntRect(192 + 32, 416 + (32 * 3), 32, 32));
	AniT da2_22(sf::IntRect(192 + 32, 416 + (32 * 4), 32, 32));
	AniT da2_23(sf::IntRect(192, 416 + (32 * 0), 32, 32));
	//Blue gauntlets
	AniT da2_24(sf::IntRect(192 + 32 + 64, 416 + (32 * 0), 32, 32));
	AniT da2_25(sf::IntRect(192 + 32 + 64, 416 + (32 * 1), 32, 32));
	AniT da2_26(sf::IntRect(192 + 32 + 64, 416 + (32 * 2), 32, 32));
	AniT da2_27(sf::IntRect(192 + 32 + 64, 416 + (32 * 3), 32, 32));
	AniT da2_28(sf::IntRect(192 + 32 + 64, 416 + (32 * 4), 32, 32));
	AniT da2_29(sf::IntRect(192 + 96, 416 + (32 * 0), 32, 32));
	//Purple gauntlets
	AniT da2_30(sf::IntRect(192 + 32 + 128, 416 + (32 * 0), 32, 32));
	AniT da2_31(sf::IntRect(192 + 32 + 128, 416 + (32 * 1), 32, 32));
	AniT da2_32(sf::IntRect(192 + 32 + 128, 416 + (32 * 2), 32, 32));
	AniT da2_33(sf::IntRect(192 + 32 + 128, 416 + (32 * 3), 32, 32));
	AniT da2_34(sf::IntRect(192 + 32 + 128, 416 + (32 * 4), 32, 32));
	AniT da2_35(sf::IntRect(192 + 160, 416 + (32 * 0), 32, 32));
	//Green gauntlets
	AniT da2_42(sf::IntRect(320, 256 + (32 * 0), 32, 32));
	AniT da2_43(sf::IntRect(320, 256 + (32 * 1), 32, 32));
	AniT da2_44(sf::IntRect(320, 256 + (32 * 2), 32, 32));
	AniT da2_45(sf::IntRect(320, 256 + (32 * 3), 32, 32));
	AniT da2_46(sf::IntRect(320, 256 + (32 * 4), 32, 32));
	AniT da2_47(sf::IntRect(320 - 32, 256 + (32 * 0), 32, 32));

	doAniSprites = { {da0_0,da0_1,da0_2,da0_3,da0_4,da0_5,da0_6,da0_7,da0_8 },{ da1_0,da1_1,da1_2,da1_3,da1_4,da1_5,da1_6,da1_7,da1_8 },
	{da2_0,da2_1,da2_2,da2_3,da2_4,da2_5}, { da2_6,da2_7,da2_8,da2_9,da2_10,da2_11 }, { da2_12,da2_13,da2_14,da2_15,da2_16,da2_17 },
	{ da2_18,da2_19,da2_20,da2_21,da2_22,da2_23 },{ da2_24,da2_25,da2_26,da2_27,da2_28,da2_29 },{ da2_30,da2_31,da2_32,da2_33,da2_34,da2_35 },{
	da2_36,da2_37,da2_38,da2_39,da2_40,da2_41 }, { da2_42,da2_43,da2_44,da2_45,da2_46,da2_47 }, {da3_0,da3_1,da3_2,da3_3,da3_4,da3_5,da3_6,da3_7,da3_8, } };



	//Extra sprites
	//Pickaxe sprite
	AniT ex2_pick0(sf::IntRect(192, 385, 32, 32));
	extraAnisprites = { { ex2_pick0 } };

}
std::vector<int> const &Player::getDisplayGauntlets() {
	return DisplayedGauntlets;
}

void Player::doAnimation(const int &type, bool should_overwrite) {
	bool should_do = false;
	if (should_overwrite == true) {
		should_do = true;
	}
	else if (isdAni == false) {
		should_do = true;
	}

	if (should_do == true) {
		CLock = true;
		isdAni = true;
		d_index = type;
		stop_ani();
		tick = 0;
		svectorindex = 0;
		switch (type) {
		case 0://Putting on gloves, blue
			CurrentAni = doAniSprites[0];
			max_tick = 0.06;
			break;
		case 1://Putting on gloves purple
			CurrentAni = doAniSprites[1];
			max_tick = 0.06;
			break;
		case 2://Mining right

			switch (Gtype) {
			case -1:
				CurrentAni = doAniSprites[2];
				break;
			case 0:
				CurrentAni = doAniSprites[3];
				break;
			case 1:
				CurrentAni = doAniSprites[4];
				break;
			case 2:
				CurrentAni = doAniSprites[8];
				break;
			}

			start_pickaxe(0);
			max_tick = 0.03;
			break;
		case 3: //Mining left

			switch (Gtype) {
			case -1:
				CurrentAni = doAniSprites[5];
				break;
			case 0:
				CurrentAni = doAniSprites[6];
				break;
			case 1:
				CurrentAni = doAniSprites[7];
				break;
			case 2:
				CurrentAni = doAniSprites[9];
				break;
			}
			start_pickaxe(1);
			max_tick = 0.03;
			break;
		case 4: //Putting on gloves Green
			CurrentAni = doAniSprites[10];
			max_tick = 0.06;
			break;
		}

		Aniset_XY(vx, vy);
	}
	
}

void Player::addFuel(const int &howMuch) {
	if (fuel + howMuch > max_fuel) {
		fuel = max_fuel;
	}
	else {
		fuel += howMuch;
	}
	
}
void Player::shootright() {
	
	if (ObtainedGauntlets.size() > 0) {
		stop_Dani();
		if (movingdirection == -1) {
			if (hasShot == false) {
				if (isdAni == false) {
					Gtype = ObtainedGauntlets[OGindex];
					switch (Gtype) {
					case 0:
						doAnimation(0, true);
						break;
					case 1:
						doAnimation(1, true);
						break;
					case 2:
						doAnimation(4, true);
						break;
					}
					
				}

			}
			else {
				if (is_ready_for_powershot == true) {
					if (powerfuel >= max_powerfuel) {
						
						changeAni(5);
						powerfuel = 0;
						Gauntlets::PlayPowerSound(Gtype, x, y);
						set_Ready();
						Gauntlets::Shoot_Power(Gtype, x, y, 1);
						GUI::update();
					}
					else {
						Sound::Play(22, x, y, random2::randomrange(1, 5), 0, 0);
					}

				}
				else {
					if (Gauntlets::getFuel(Gtype) <= fuel) {
						changeAni(4);
						Gauntlets::PlaySound(Gtype, x, y);
						Gauntlets::Shoot_with_particles(Gtype, x, y, 1, SAS, true);


						//Decreasing the amount of fuel you have.
						fuel -= Gauntlets::getFuel(Gtype);
						GUI::update();
					}
					else {
						fuel = 0;
						Sound::Play(22, x, y, random2::randomrange(1, 5), 0, 0);
						GUI::update();
					}
				}
				
				changeAni(4);
				
			}
		}
		else {
			shootingdirection_r = 1;
		}
	}
	
	
	
}

void Player::shootdown() {
	if (ObtainedGauntlets.size() > 0) {
		stop_Dani();
		if (movingdirection == -1) {
			if (hasShot == false) {
				if (isdAni == false) {
					Gtype = ObtainedGauntlets[OGindex];
					switch (Gtype) {
					case 0:
						doAnimation(0, true);
						break;
					case 1:
						doAnimation(1, true);
						break;
					case 2:
						doAnimation(4, true);
						break;
					}
				}
			}
			else {
				if (is_ready_for_powershot == true) {
					if (powerfuel >= max_powerfuel) {
						changeAni(5);
						powerfuel = 0;
						Gauntlets::PlayPowerSound(Gtype, x, y);
						set_Ready();
						Gauntlets::Shoot_Power(Gtype, x, y, 2);
						GUI::update();
					}
					else {
						Sound::Play(22, x, y, random2::randomrange(1, 5), 0, 0);
					}

				}
				else {
					if (Gauntlets::getFuel(Gtype) <= fuel) {
						changeAni(4);
						Gauntlets::PlaySound(Gtype, x, y);
						Gauntlets::Shoot_with_particles(Gtype, x, y, 2, SAS, true);


						//Decreasing the amount of fuel you have.
						fuel -= Gauntlets::getFuel(Gtype);
						GUI::update();
					}
					else {
						fuel = 0;
						Sound::Play(22, x, y, random2::randomrange(1, 5), 0, 0);
						GUI::update();
					}
				}
				
				changeAni(4);
				
				
				
			}
		}
		else {
			shootingdirection_r = 2;
		}

	}
	
}

void Player::shootleft() {
	if (ObtainedGauntlets.size() > 0) {
		stop_Dani();
		if (movingdirection == -1) {
			if (hasShot == false) {
				if (isdAni == false) {
					Gtype = ObtainedGauntlets[OGindex];
					switch (Gtype) {
					case 0:
						doAnimation(0, true);
						break;
					case 1:
						doAnimation(1, true);
						break;
					case 2:
						doAnimation(4, true);
						break;
					}
				}
			}
			else {
				if (is_ready_for_powershot == true) {
					if (powerfuel >= max_powerfuel) {
						changeAni(5);
						powerfuel = 0;
						Gauntlets::PlayPowerSound(Gtype, x, y);
						set_Ready();
						Gauntlets::Shoot_Power(Gtype, x, y, 3);
						GUI::update();
					}
					else {
						Sound::Play(22, x, y, random2::randomrange(1, 5), 0, 0);
					}
					
				}
				else {
					if (Gauntlets::getFuel(Gtype) <= fuel) {
						changeAni(5);
						Gauntlets::PlaySound(Gtype, x, y);
						Gauntlets::Shoot_with_particles(Gtype, x, y, 3, SAS, true);


						//Decreasing the amount of fuel you have.
						fuel -= Gauntlets::getFuel(Gtype);
						GUI::update();
					}
					else {
						fuel = 0;
						Sound::Play(22, x, y, random2::randomrange(1, 5), 0, 0);
						GUI::update();
					}
					
				}
				changeAni(5);
				
				
			}
		}
		else {
			shootingdirection_r = 3;
		}

	}
}

void Player::shootup() {
	if (ObtainedGauntlets.size() > 0) {
		stop_Dani();
		if (movingdirection == -1) {
			if (hasShot == false) {
				if (isdAni == false) {
					Gtype = ObtainedGauntlets[OGindex];
					switch (Gtype) {
					case 0:
						doAnimation(0, true);
						break;
					case 1:
						doAnimation(1, true);
						break;
					case 2:
						doAnimation(4, true);
						break;
					}
				}
			}
			else {
				if (is_ready_for_powershot == true) {
					if (powerfuel >= max_powerfuel) {
						changeAni(5);
						powerfuel = 0;
						Gauntlets::PlayPowerSound(Gtype, x, y);
						set_Ready();
						Gauntlets::Shoot_Power(Gtype, x, y, 0);
						GUI::update();
					}
					else {
						Sound::Play(22, x, y, random2::randomrange(1, 5), 0, 0);
					}

				}
				else {
					if (Gauntlets::getFuel(Gtype) <= fuel) {
						changeAni(4);
						Gauntlets::PlaySound(Gtype, x, y);
						Gauntlets::Shoot_with_particles(Gtype, x, y, 0, SAS, true);
						//Decreasing the amount of fuel you have.
						fuel -= Gauntlets::getFuel(Gtype);
						GUI::update();
					}
					else {
						fuel = 0;
						Sound::Play(22, x, y, random2::randomrange(1, 5), 0, 0);
						GUI::update();
					}
					
				}
				changeAni(4);
				
			}
		}
		else {
			shootingdirection_r = 0;
		}

	}
}

void Player::addGtype(const unsigned int &addition) {

	if (ObtainedGauntlets.size() > 0) {
		
		hasShot = false;
		
		
		OGindex += addition;
		if (OGindex > ObtainedGauntlets.size() - 1) {
			OGindex = ObtainedGauntlets.size() - 1;
		}
		else {
			Sound::Play(20, x, y, random2::randomrange(1, 5), 0, 0);
			Gtype = ObtainedGauntlets[OGindex];
			int v1;
			int v3;

			if (GF::does_exist(OGindex - 1, ObtainedGauntlets.size()) == false) {
				v1 = -1;
			}
			else {
				v1 = ObtainedGauntlets[OGindex - 1];
			}
			if (GF::does_exist(OGindex + 1, ObtainedGauntlets.size()) == false) {
				v3 = -1;
			}
			else {
				v3 = ObtainedGauntlets[OGindex + 1];
			}

			DisplayedGauntlets = { v1, ObtainedGauntlets[OGindex], v3 };

			GUI::update();
		}
		
		
	}
	
		
	
}

void Player::changeaniset(const int &index) {
	
	AniSprites = Ani_Sets[index];
	changeAni(1);
	
}
void Player::subGtype(const unsigned int &subtraction) {
	if (ObtainedGauntlets.size() > 0) {
		
		hasShot = false;
		
		OGindex -= subtraction;
		if (OGindex < 0) {
			OGindex = 0;
		}
		else {
			Sound::Play(20, x, y, random2::randomrange(1, 5), 0, 0);
			Gtype = ObtainedGauntlets[OGindex];
			int v1;
			int v3;

			if (GF::does_exist(OGindex - 1, ObtainedGauntlets.size()) == false) {
				v1 = -1;
			}
			else {
				v1 = ObtainedGauntlets[OGindex - 1];
			}
			if (GF::does_exist(OGindex + 1, ObtainedGauntlets.size()) == false) {
				v3 = -1;
			}
			else {
				v3 = ObtainedGauntlets[OGindex + 1];
			}

			DisplayedGauntlets = { v1, ObtainedGauntlets[OGindex], v3 };

			GUI::update();
		}
		
		
	}
	
	
}

bool Player::Checkslidingcollision(const int &your_x_position, const int &your_y_position) {


	//This checks to see if any collision occured whilst sliding.
	if (Basic_Tile_MOTHER::CheckCollision(your_x_position, your_y_position, true) == true) {
		return true;
	}
	else {
		return false;
	}

}

void Player::setFloor(const int &New_Floor) {
	Floor = New_Floor;
}
void Player::setDungeon(const int &New_Dungeon) {
	Dungeon = New_Dungeon;
}
int Player::getFloor() {
	return Floor;
}
int Player::getDungeon() {
	return Dungeon;
}

void Player::stop_ani(bool should_check_special_collision) {
	if (isBounce == true) {
		resetBounce();
		
	}
	movinganitick = 0;
	movingdirection = -1;
	isSliding = false;
	sx = x;
	sy = y;
	vx = x;
	vy = y;
	slidingrep = 1;
	if (should_check_special_collision == true) {
		Basic_Tile_MOTHER::CheckSpecialCollision(0);
	}
	//Reseting the animations back to the default(Standing still).
	changeAni(1);
	SnapCam();
	snapListener();
	SnapChoice();
}

void Player::drawPSprite(sf::RenderWindow &win) {
	//win.draw(s123);
	//win.draw(CurrentAni[svectorindex]);
	if (Shoppingtog == true || inventorytog == true) {
		
		Co.draw(win);
	
	}
	
}

void Player::Aniset_XY(const float &x_cordinate, const float &y_cordinate) {
	PSprite.setPosition(x_cordinate, y_cordinate);
	/*for (unsigned int i = 0; i < CurrentAni.size(); i++) {
		CurrentAni[i].setPosition(x_cordinate, y_cordinate);
	}*/
}

void Player::animate() {

	tick += GF::getDelta();
	if (tick >= max_tick) {
		switch (d_index) {
			case 2:
				update_pickaxe();
				break;
			case 3:
				update_pickaxe();
				break;
			
		}
		PSprite *= CurrentAni[svectorindex];
		if (svectorindex >= CurrentAni.size() - 1) {
			if (isdAni == true) {
				
				CLock = false;
				isdAni = false;
				switch (d_index) {
				case 0:
					changeaniset(1);
					hasShot = true;
					break;
				case 1:
					changeaniset(2);
					hasShot = true;
					break;
				case 2:
					switch (Gtype) {
					case -1:
						changeaniset(0);
						break;
					case 0:
						changeaniset(1);
						break;
					case 1:
						changeaniset(2);
						break;
					case 2:
						changeaniset(3);
						break;
					}
					stop_pickaxe();
					break;
				case 3:
					switch (Gtype) {
					case -1:
						changeaniset(0);
						break;
					case 0:
						changeaniset(1);
						break;
					case 1:
						changeaniset(2);
						break;
					case 2:
						changeaniset(3);
						break;
					}
					stop_pickaxe();
					break;
				case 4:
					changeaniset(3);
					hasShot = true;
					break;
				
				default:
					changeaniset(0);
					

					
				}
				d_index = -1;
			}
			svectorindex = 0;
		}
		else {
			svectorindex++;
		}
		tick = 0;
	}
	
	
}

void Player::changeAni(const int &index) {
	tick = 0;
	svectorindex = 0;
	switch (index) {
	case 0:
		max_tick = 0.04;//Walk animation
		break;
	case 1:
		max_tick = 0.5;
		break;
	case 2:
		max_tick = 0.00000004;//slide animation
		break;
	case 3:
		max_tick = 0.00000004;//slide animation
		break;
	case 4:
		max_tick = 100000;
		break;
	case 5:
		max_tick = 100000;
		break;
	case 6:
		max_tick = 100000;
		break;
	}
	CurrentAni = AniSprites[index];
	PSprite *= CurrentAni[0];
	Aniset_XY(vx, vy);
	
	
}

std::vector<int> Player::getinventory() {
	return inventory;
}

int Player::getFuel() {
	return fuel;
}

float Player::getsx() {
	return sx;
}

float Player::getsy() {
	return sy;
}

int Player::getcx() {
	
	if (isSliding == true) {
		
		if (movingdirection == 1) {
			return sx + (32 * slidingrep);
		}
		else if (movingdirection == 3) {
			return sx - (32 * slidingrep);
		}
		else {
			return sx;
		}
	}
	else {
		
		if (movingdirection == 1) {
			return sx + 32;
		}
		else if (movingdirection == 3) {
			return sx - 32;
		}
		else {

			return sx;
		}
	}
	
}

int Player::getcy() {
	
	if (isSliding == true) {
		
		if (movingdirection == 0) {
			return sy - (32 * slidingrep);
		}
		else if (movingdirection == 2) {
			return sy + (32 * slidingrep);
		}
		else {
			return sy;
		}
	}
	else {
		
		if (movingdirection == 0) {
			return sy - 32;
		}
		else if (movingdirection == 2) {
			return sy + 32;
		}
		else {
			return sy;
		}
	}
	
}

void Player::deleteALL() {
	
	//Clearing all the player objects.
	for (unsigned int i = 0; i < PlayerObjects.size(); i++) {
		delete PlayerObjects[i];
	}
	PlayerObjects.clear();
	
}

int Player::getLives() {
	return lives;
}

void Player::addLives(int amount) {
	lives += amount;
}



void Player::giveItem(int ID) {
	switch (ID) {
	case 0:
		switch (difficulty) {
		case 0:
			addLives(2);
			text.setString("+2 Live");
			break;
		case 1:
			addLives(1);
			text.setString("+1 Live");
			break;
		case 2:
			addLives(1);
			text.setString("+1 Live");
		}
		
		break;
	case 1:
		switch (difficulty) {
		case 0:
			addLives(4);
			text.setString("+4 Live");
			break;
		case 1:
			addLives(2);
			text.setString("+2 Live");
			break;
		case 2:
			addLives(2);
			text.setString("+2 Live");
		}
		
		break;
	case 2:
		addFuel(30);
		text.setString("+30 Fuel");
		break;
	case 3:
		addGauntlet(0);
		text.setString("Acquired: Blue Tornado Gauntlet");
		break;
	case 4:
		addGauntlet(2);
		text.setString("Acquired: Green Vine Gauntlet");
		break;
	case 5:
		addGauntlet(1);
		text.setString("Acquired: Purple Skip Gauntlet");
		break;
	}
	GUI::update();
}

void Player::addGauntlet(int ID) {
	bool should_add = true;
	for (unsigned int i = 0; i < ObtainedGauntlets.size(); i++) {
		if (ObtainedGauntlets[i] == ID) {
			should_add = false;
			break;
		}
	}
	if (should_add == true) {
		ObtainedGauntlets.push_back(ID);
		updateGauntlets();
	}
	else {
	}
	
}

void Player::updateGauntlets() {
	Gtype = ObtainedGauntlets[OGindex];
	int v1;
	int v3;

	if (GF::does_exist(OGindex - 1, ObtainedGauntlets.size()) == false) {
		v1 = -1;
	}
	else {
		v1 = ObtainedGauntlets[OGindex - 1];
	}
	if (GF::does_exist(OGindex + 1, ObtainedGauntlets.size()) == false) {
		v3 = -1;
	}
	else {
		v3 = ObtainedGauntlets[OGindex + 1];
	}

	DisplayedGauntlets = { v1, ObtainedGauntlets[OGindex], v3 };

	GUI::update();
}

void Player::update_pickaxe() {
	int distance = 20;
	float angle = 0;
	float pickaxe_rotation = 0;

	switch (pickaxe_ani_type) {
	case 0:
		switch (svectorindex) {
		case 0:
			pick_angle = 230;
			pickaxe_rotation = -60;
			break;
		case 1:
			pick_angle = 250;
			pickaxe_rotation = -40;
			break;
		case 2:
			pick_angle = 270;
			pickaxe_rotation = -20;
			break;
		case 3:
			pick_angle = 290;
			pickaxe_rotation = 0;
			break;
		case 4:
			pick_angle = 310;
			pickaxe_rotation = 20;
			break;
		case 5:
			pick_angle = 330;
			pickaxe_rotation = 60;
			break;
		}
		break;
	case 1:
		switch (svectorindex) {
		case 0:
			pick_angle = 350 - 50;
			pickaxe_rotation = 150 - 90;
			break;
		case 1:
			pick_angle = 330 - 50;
			pickaxe_rotation = 110 - 90;
			break;
		case 2:
			pick_angle = 310 - 50;
			pickaxe_rotation = 90 - 90;
			break;
		case 3:
			pick_angle = 290 - 50;
			pickaxe_rotation = 70 - 90;
			break;
		case 4:
			pick_angle = 270 - 50;
			pickaxe_rotation = 50 - 90;
			break;
		case 5:
			pick_angle = 250 - 50;
			pickaxe_rotation = 30 - 90;
			break;
		}
	}
	angle = pick_angle * (Pi / 180);
	pickaxe.setPosition((x + 16) + (cos(angle) * distance), (y + 16) + (sin(angle) * distance));
	pickaxe.setRotation(pickaxe_rotation);

}

void Player::stop_pickaxe() {
	pickaxe.deactivate();
	Sound::Play(26, 0, 0, random2::randomrange(1,5));
}

void Player::start_pickaxe(int type) {
	pickaxe_ani_type = type;
	pickaxe.activate();
	pickaxe.setOrigin(16, 16);
	switch (type) {
	case 0:
		set_pickaxe_position(230, 20, -60);
		break;
	case 1:
		set_pickaxe_position(350, 20, 150);
	}
	
}

void Player::set_pickaxe_position(float pick_angle, float distance_from_player, float pickaxe_degree) {
	float angle = pick_angle * (Pi / 180);
	pickaxe.setPosition((x + 16) + (cos(angle) * distance_from_player), (y + 16) + (sin(angle) * distance_from_player));
	pickaxe.setRotation(pickaxe_degree);
}

float Player::getWalk_Speed() {
	return speed;
}

bool Player::is_DoingAnimation() {
	return isdAni;
}

void Player::stop_Dani() {
	if (isdAni == true) {
		CLock = false;
		pickaxe.deactivate();
		tick = max_tick + 1;
		isdAni = false;
	}
	

}

void Player::addPower(float how_Much) {
	
	powerfuel = powerfuel.load() + how_Much;
	if (powerfuel >= max_powerfuel) {
		powerfuel = max_powerfuel;
	}
	GUI::update();
}

void Player::set_Ready() {
	if (is_ready_for_powershot == false) {
		Sound::Play(37, 0, 0, random2::randomrange(1, 5));
		is_ready_for_powershot = true;
		text.setString("Active");
	}
	else {
		Sound::Play(38, 0, 0, random2::randomrange(1, 5));
		text.setString("Inactive");
		is_ready_for_powershot = false;
	}
	GUI::update();
}

float Player::getPower() {
	return powerfuel;
}

int Player::get_maxFuel() {
	return max_fuel;
}

float Player::get_maxPower() {
	return max_powerfuel;
}

bool Player::is_powershot_ready() {
	return is_ready_for_powershot;
}

int Player::getStep() {
	return Step;
}

void Player::setStep(int new_Step) {
	if (new_Step > Step) {
		Step = new_Step;
	}
	
}

unsigned int Player::bounceup(const int &amount) {
	App::control_cache.clear();
	movingdirection = -1;
	isSliding = false;
	sx = x;
	sy = y;
	vx = x;
	vy = y;
	distance = amount;
	slidingrep = 1;
	isBounce = true;
	is_bounce_moving_down = false;
	b_ani_r = 0;
	return moveup(amount);
}
unsigned int Player::bouncedown(const int &amount) {
	App::control_cache.clear();
	movingdirection = -1;
	isSliding = false;
	sx = x;
	sy = y;
	vx = x;
	vy = y;
	distance = amount;
	slidingrep = 1;
	isBounce = true;
	is_bounce_moving_down = false;
	b_ani_r = 0;
	return movedown(amount);
}
unsigned int Player::bounceleft(const int &amount) {
	App::control_cache.clear();
	movingdirection = -1;
	isSliding = false;
	sx = x;
	sy = y;
	vx = x;
	vy = y;
	distance = amount;
	slidingrep = 1;
	isBounce = true;
	is_bounce_moving_down = false;
	b_ani_r = 0;
	return moveleft(amount);
}
unsigned int Player::bounceright(const int &amount) {
	App::control_cache.clear();
	movingdirection = -1;
	isSliding = false;
	sx = x;
	sy = y;
	vx = x;
	vy = y;
	distance = amount;
	slidingrep = 1;
	isBounce = true;
	is_bounce_moving_down = false;
	b_ani_r = 0;
	return moveright(amount);
}

void Player::calculate_bounce(int direction) {
	
	if (isBounce == true) {
		
		
			if (is_bounce_moving_down == true) {
				float jdif = distance - how_far;// -(distance / 2);//((sx + (distance + b_ani_r)) - vx);
				l_bounce_height = c_bounce_height;
				c_bounce_height = ((jdif / ((distance))) * bounceheight);//((distance / 2 - ((x + (distance / 2)) - vx)) / (distance / 2);
				vy += l_bounce_height;
				vy -= c_bounce_height;
			}
			else {
				float jdif = how_far;//(distance / 2) - ((sx + (distance / 2)) - vx);
				l_bounce_height = c_bounce_height;
				c_bounce_height = ((jdif / (distance / 2)) * bounceheight);//((distance / 2 - ((x + (distance / 2)) - vx)) / (distance / 2);
				vy += l_bounce_height;
				vy -= c_bounce_height;
				if (how_far >= distance / 2) {
					is_bounce_moving_down = true;
					//b_ani_r = (sy - bounceheight) - vy;

				}
			}
		
	}
	
}

void Player::resetBounce() {
	isBounce = false;
	is_bounce_moving_down = false;
	b_ani_r = 0;
}

void Player::setStoryID(int new_ID) {
	storyID = new_ID;
}

int Player::getStoryID() {
	return storyID;
}

const std::vector<int> &Player::get_Obtained_Gauntlets() {
	return ObtainedGauntlets;
}

int Player::get_difficulty() {
	return difficulty;
}

int Player::get_difficulty_from_file(const std::string &playerFile) {
	char CC; //Current character
	std::vector<int> Para;
	std::vector<int> VB;//Vector build
	std::vector<std::vector<int>> Vectors;
	std::string MEM = "";
	bool Start = false;
	bool isVector = false;
	ifstream f;
	f.open(playerFile, ios::in);

	while (f.good()) {
		f.seekg(0, ios::cur);
		f >> CC;

		if (Start == true) {

			if (CC == *",") {
				if (isVector == false) {
					Para.push_back(GF::StringtoInt(MEM));
				}
				else {
					VB.push_back(GF::StringtoInt(MEM));
				}

				MEM = "";
			}
			else if (CC == *")") {
				Start = false;
				continue;
			}
			else if (CC == *":") {
				isVector = true;
				continue;
			}
			else if (CC == *";") {
				Vectors.push_back(VB);
				VB = {};
				isVector = false;
				continue;
			}
			else {
				MEM.push_back(CC);
			}
		}
		if (CC == *"(") {
			Start = true;
		}


	}


	f.close();
	return Para[5];
	

	
	
}

bool Player::get_is_in_dungeon() {
	switch (getDungeon()) {
	case 0:
		return false;
	case 1:
		return true;
	case 2:
		return true;
	case 3:
		return true;
	case 4:
		return false;
	case 5:
		return false;
	case 6:
		return false;
	}
}

bool Player::loseLife(int lowest_Life_limit) {
	if (lives > lowest_Life_limit) {
		lives -= 1;
		return false;
	}
	else {
		return true;
	}
	
	
}

void Player::setLife(int new_life_amount) {
	lives = new_life_amount;
}