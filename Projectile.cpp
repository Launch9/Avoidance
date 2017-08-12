#include "stdafx.h"
#include "Projectile.h"
#include "GF.h"
#include <iostream>
#include "Debug.h"
#include "ParticleSettings.h"
#include "ParticleSystem.h"
#include "Gauntlets.h"
#include "Sound.h"
#include "Sub_NPC_A.h"
#include "random2.h"
#include <mutex>
//#include "Sub_NPC_A.h"
//class Sub_NPC_A;
//This is to be used for safer threads.
std::mutex mtx;
#define SAS 70//Shooting Angle Size
#define Max_distance 32 * 30
std::vector<Projectile> Projectile::VP;
int Projectile::Rindex;
ParticleSettings Projectile::Default_PSet;

Projectile::Projectile(const int &type_of_projectile, const int &startx, const int &starty, const int &Direction, bool should_make_particles)
{	
	
	type = type_of_projectile;
	switch (type_of_projectile) {
	case 0:
		color = sf::Color::Blue;
		base_color = color;
		speed = 500;//500
		max_length = 32;//50
		width = 2;
		middle = (32 / 2) - (width / 2);
		voltage = 2;
		PSet = Gauntlets::GetParticleSettings(0);
		PSet.num_of_particle = 50;
		sound.setBuffer(Sound::GetSoundBuffer(11));
		sound.setRelativeToListener(false);
		break;
	case 1:
		color = sf::Color::Magenta;
		base_color = color;
		speed = 50;
		max_length = 100;
		width = 6;
		middle = (32 / 2) - (width / 2);
		voltage = 4;
		
		PSet = Gauntlets::GetParticleSettings(1);
		PSet.num_of_particle = 5;
		sound.setBuffer(Sound::GetSoundBuffer(11));
		sound.setRelativeToListener(false);
		break;
	case 2:
		color = sf::Color::Yellow;
		base_color = color;
		speed = 300;
		max_length = 64;
		width = 2;
		middle = (32 / 2) - (width / 2);
		voltage = 6;
		PSet.num_of_particle = 1;
		PSet.color = sf::Color::Yellow;
		PSet.max_speed = 2;
		PSet.out_type = 0;
		PSet.x = 0;
		PSet.y = 0;
		sound.setBuffer(Sound::GetSoundBuffer(11));
		sound.setRelativeToListener(false);
		break;
	case 3:
		color = sf::Color::Blue;
		is_piercing = true;
		base_color = color;
		speed = 600;//500
		max_length = 50;//50
		width = 32;
		middle = (32 / 2) - (width / 2);
		voltage = 5;
		PSet = Gauntlets::GetParticleSettings(0);
		PSet.num_of_particle = 150;
		sound.setBuffer(Sound::GetSoundBuffer(11));
		sound.setRelativeToListener(false);
		break;
	case 4:
		color = sf::Color::Magenta;
		is_piercing = true;
		is_ghost = true;
		base_color = color;
		speed = 600;//500
		max_length = 200;//50
		width = 96;
		middle = (32 / 2) - (width / 2);
		voltage = 3;
		PSet = Gauntlets::GetParticleSettings(0);
		PSet.num_of_particle = 150;
		sound.setBuffer(Sound::GetSoundBuffer(11));
		sound.setRelativeToListener(false);
		break;
	
	case 5:
		color = sf::Color::Green;
		base_color = color;
		speed = 500;
		max_length = 16;
		width = 4;
		voltage = 2.5;
		middle = (32 / 2) - (width / 2);
		PSet = Gauntlets::GetParticleSettings(3);
		sound.setBuffer(Sound::GetSoundBuffer(11));
		sound.setRelativeToListener(false);
		break;
	case 6:
		color = sf::Color::Green;
		base_color = color;
		is_piercing = true;
		speed = 500;
		max_length = 500;
		width = 16;
		voltage = 2;
		middle = (32 / 2) - (width / 2);
		PSet = Gauntlets::GetParticleSettings(3);
		sound.setBuffer(Sound::GetSoundBuffer(11));
		sound.setRelativeToListener(false);
		break;
	}

	if (should_make_particles == false) {
		PSet = Default_PSet;
	}
	directions.push_back(Direction);
	x = startx;
	y = starty;
	x2 = startx;
	y2 = starty;
	cx = startx;
	cy = starty;
	x3 = startx;
	y3 = starty;
	rect r;
	r.sx = x3;
	r.sy = y3;
	r.setColor(color);
	switch (Direction) {
	case 0:
		r.setPosition(startx + middle, starty);
		break;
	case 1:
		r.setPosition(startx, starty + middle);
		break;
	case 2:
		r.setPosition(startx + middle, starty);
		break;
	case 3:
		r.setPosition(startx, starty + middle);
		break;
	}
	Rectangles.push_back(r);
	VP.push_back(*this);

}




void Projectile::tickall() {
	for (unsigned int i = 0; i < VP.size(); i++) {
		VP[i].tick(i);
	}
	check_all();
}

int Projectile::gettype() {
	return type;
}
void Projectile::tick(int index) {
	
		//This checks to see if the projectile has gone too far from the player.
		//If so, then it will be deleted.
		if (GF::getDistance_Pixels(sf::Vector2f(x, y), sf::Vector2f(Player::PlayerObjects[0]->getx(), Player::PlayerObjects[0]->gety())) >= Max_distance) {
			kill(0);
		}
		//Setting colors
		for (unsigned int i = 0; i < Rectangles.size(); i++) {
			Rindex = i;
			bool b1 = Rectangles[i].getisDoneExpanding();
			bool b2 = Rectangles[i].gethasMadeCollision();
			if (!(b1 == true && b2 == true) ) {
				switch (directions[i]) {
				case 0:
					if (Rectangles[i].gethasMadeCollision() == false) {
						y = y - (speed * GF::getDelta());
					}
					if (Rectangles[i].gethasMadeCollision() == true) {
						Rectangles[i].setlength(Rectangles[i].getlength() - (speed * GF::getDelta()));
					}
					else {
						Rectangles[i].setlength(y - y3);
					}
									
					if (Rectangles[i].getlength() <= -max_length) {
						
						Rectangles[i].setlength(-max_length);
						Rectangles[i].DoneExpanding();
					}

					if (y <= y2 - (passed * 32)) {
						call32();
						if (extra16done == true) {

							if (passed == 2) {
								extra16done = false;
							}

						}
						if (extra16 == true) { //Completed the extra 16 pixels.

							rounddif = Rectangles[i].getY() - (cy + 16);
							Rectangles[i].setlength(Rectangles[i].getlength() - rounddif);
							Rectangles[i].setPosition(x + middle, cy + 16);
							
							changedirection(reservedirection, false, true);
							Rectangles[i].MadeCollision();
							Rectangles[i].cx = x;
							Rectangles[i].cy = y;							
							extra16 = false;
							extra16done = true;
							switch (reservedirection) {
							case 1:
								x3 -= 16;						
								x -= 16;
								break;
							case 3:
								x3 += 16;																
								x += 16;
								break;
							}
							Rectangles[i].sx = x3;
							Rectangles[i].sy = y3;
							break;
						}
						if (Rectangles[i].gethasMadeCollision() == false) {
							passed++;
							cy = y2 - ((passed)* 32);

							if (Basic_Tile_MOTHER::CheckProjectileCollision(VP[index], directions[i]) == false) {
								if (Basic_Tile_MOTHER::CheckCollision(cx, cy, false, true) == true) {
									kill(1);
								};
							};
							if (SHOULDBREAK == true) {
								SHOULDBREAK = false;
								break;
							}

							if (extra16 == true) {
								y2 += 16;
							}
						}
																		
					}
					
					if (Rectangles[i].gethasMadeCollision() == false) {
						
						//Moving the rectangle
						Rectangles[i].setPosition(x + middle, y);
						//Extending the rectnagle
						Rectangles[i].setSize(sf::Vector2f(width, -Rectangles[i].getlength()));
					}

					break;
				case 1:
					if (Rectangles[i].gethasMadeCollision() == false) {
						x = x + (speed * GF::getDelta());
					}
					if (Rectangles[i].gethasMadeCollision() == true) {
						Rectangles[i].setlength(Rectangles[i].getlength() + (speed * GF::getDelta()));
					}
					else {
						Rectangles[i].setlength(x - x3);
					}
					

					if (Rectangles[i].getlength() >= max_length) {
						Rectangles[i].setlength(max_length);
						Rectangles[i].DoneExpanding();
					}

					if (x >= x2 + (passed * 32)) {
						call32();
						if (extra16done == true) {

							if (passed == 2) {
								extra16done = false;
							}

						}
						if (extra16 == true) {
							rounddif = Rectangles[i].getX() - (cx + 16);
							Rectangles[i].setlength(Rectangles[i].getlength() + rounddif);
							Rectangles[i].setPosition(cx + 16, y + middle);
							//Completed the extra 16 pixels.
							changedirection(reservedirection, false, true);
							Rectangles[i].MadeCollision();
							Rectangles[i].cx = x;
							Rectangles[i].cy = y;							
							extra16 = false;
							extra16done = true;
							switch (reservedirection) {
							case 0:								
								y3 += 16;								
								y += 16;
								break;
							case 2:
								y3 -= 16;
								y -= 16;
								break;
							}
							
							Rectangles[i].sx = x3;
							Rectangles[i].sy = y3;
							break;

						}
						if (Rectangles[i].gethasMadeCollision() == false) {
							passed++;
							cx = x2 + ((passed - 1) * 32);
							if (Basic_Tile_MOTHER::CheckProjectileCollision(VP[index], directions[i]) == false) {
								if (Basic_Tile_MOTHER::CheckCollision(cx, cy, false, true) == true) {
									kill(1);
								};
							};
							if (SHOULDBREAK == true) {
								SHOULDBREAK = false;
								break;
							}
							if (extra16 == true) {
								x2 -= 16;
							}
						}
						
						
					}
					if (Rectangles[i].gethasMadeCollision() == false) {
						
						//Moving the rectangle
						Rectangles[i].setPosition(x, y + middle);
						//Extending the rectnagle
						Rectangles[i].setSize(sf::Vector2f(-Rectangles[i].getlength(), width));
					}
					break;
				case 2:
					if (Rectangles[i].gethasMadeCollision() == false) {
						y = y + (speed * GF::getDelta());
					}
					if (Rectangles[i].gethasMadeCollision() == true) {
						Rectangles[i].setlength(Rectangles[i].getlength() + (speed * GF::getDelta()));
					}
					else {
						Rectangles[i].setlength(y - y3);
					}
					
					
					if (Rectangles[i].getlength() >= max_length) {
						Rectangles[i].setlength(max_length);
						Rectangles[i].DoneExpanding();
					}
					if (y >= y2 + (passed * 32)) {
						call32();
						if (extra16done == true) {

							if (passed == 2) {
								extra16done = false;
							}

						}
						if (extra16 == true) {
							//Completed the extra 16 pixels.
							rounddif = Rectangles[i].getY() - (cy + 16);
							Rectangles[i].setlength(Rectangles[i].getlength() + rounddif);
							Rectangles[i].setPosition(x + middle, cy + 16);
							changedirection(reservedirection, false, true);
							Rectangles[i].MadeCollision();
							Rectangles[i].cx = x;
							Rectangles[i].cy = y;
							
							extra16 = false;
							extra16done = true;
							switch (reservedirection) {
							case 1:
								x3 -= 16;
								x -= 16;
								break;
							case 3:
								x3 += 16;
								x += 16;
								break;
							}
							
							Rectangles[i].sx = x3;
							Rectangles[i].sy = y3;
							break;
						}
						if (Rectangles[i].gethasMadeCollision() == false) {
							passed++;
							cy = y2 + ((passed - 1) * 32);
							if (Basic_Tile_MOTHER::CheckProjectileCollision(VP[index], directions[i]) == false) {
								if (Basic_Tile_MOTHER::CheckCollision(cx, cy, false, true) == true) {
									kill(1);
								};
							};
							if (SHOULDBREAK == true) {
								SHOULDBREAK = false;
								break;
							}
							if (extra16 == true) {
								y2 -= 16;
							}
						}
						
					}
					if (Rectangles[i].gethasMadeCollision() == false) {
						
						//Moving the rectangle
						Rectangles[i].setPosition(x + middle, y);
						//Extending the rectnagle
						Rectangles[i].setSize(sf::Vector2f(width, -Rectangles[i].getlength()));
					}
					
					break;
				case 3:
					if (Rectangles[i].gethasMadeCollision() == false) {
						x = x - (speed * GF::getDelta());
					}
					if (Rectangles[i].gethasMadeCollision() == true) {
						Rectangles[i].setlength(Rectangles[i].getlength() - (speed * GF::getDelta()));
					}
					else {
						Rectangles[i].setlength(x - x3);
					}
					
					
					if (Rectangles[i].getlength() <= -max_length) {
						Rectangles[i].setlength(-max_length);
						Rectangles[i].DoneExpanding();
					}
					if (x <= x2 - (passed * 32)) {
						call32();
						if (extra16done == true) {

							if (passed == 2) {
								extra16done = false;
							}

						}
						if (extra16 == true) { //Completed the extra 16 pixels.
							rounddif = Rectangles[i].getX() - (cx + 16);
							Rectangles[i].setlength(Rectangles[i].getlength() - rounddif);
							Rectangles[i].setPosition(cx + 16, y + middle);
							
							changedirection(reservedirection, false, true);
							Rectangles[i].MadeCollision();
							Rectangles[i].cx = x;
							Rectangles[i].cy = y;
							extra16 = false;
							extra16done = true;
							switch (reservedirection) {
							case 0:
								y3 += 16;
								y += 16;
								break;
							case 2:
								y3 -= 16;
								y -= 16;
								break;
							}
							Rectangles[i].sx = x3;
							Rectangles[i].sy = y3;
							break;
						}
						if (Rectangles[i].gethasMadeCollision() == false) {
							passed++;
							cx = x2 - ((passed)* 32);
							if (Basic_Tile_MOTHER::CheckProjectileCollision(VP[index], directions[i]) == false) {
								if (Basic_Tile_MOTHER::CheckCollision(cx, cy, false, true) == true) {
									kill(1);
								};
							};
							if (SHOULDBREAK == true) {
								SHOULDBREAK = false;
								break;
							}
							if (extra16 == true) {
								x2 += 16;
							}
						}
						
					}
					if (Rectangles[i].gethasMadeCollision() == false) {
						//Moving the rectangle
						Rectangles[i].setPosition(x, y + middle);
						//Extending the rectnagle
						Rectangles[i].setSize(sf::Vector2f(-Rectangles[i].getlength(), width));
					}
					
					break;
				}
			}
		}
			
		
	switch (directions[directions.size() - 1]) { //Checking to see if the leading rectangle is colliding with a object. (If so; make particles).
	case 0:
		if (Rectangles[directions.size() - 1].ParticleProducing == true) {
			
			PSet.x = cx + 16;
			PSet.y = cy + 32;
			PSet.ac1 = 90 + (-(SAS / 2));
			PSet.ac2 = SAS;
			ParticleSystem::create(PSet);
		}
		break;
	case 1:
		if (Rectangles[directions.size() - 1].ParticleProducing == true) {
			
			PSet.x = cx;
			PSet.y = cy + 16;
			PSet.ac1 = 180 + (-(SAS / 2));
			PSet.ac2 = SAS;
			ParticleSystem::create(PSet);
		}
		break;
	case 2:
		if (Rectangles[directions.size() - 1].ParticleProducing == true) {
			
			PSet.x = cx + 16;
			PSet.y = cy;
			PSet.ac1 = 270 + (-(SAS / 2));
			PSet.ac2 = SAS;
			ParticleSystem::create(PSet);
		}
		break;
	case 3:
		if (Rectangles[directions.size() - 1].ParticleProducing == true) {
			
			PSet.x = cx + 32;
			PSet.y = cy + 16;
			PSet.ac1 = 0 + (-(SAS / 2));
			PSet.ac2 = SAS;
			ParticleSystem::create(PSet);
		}
		break;
	}

	//Checking to see if there are any rectangles behind the main one; If so, then it should finish shrinking the proper way.	
	if (Rectangles.size() > rectsubtract) {

		if (Rectangles[0].getisDoneExpanding() == true && Rectangles[0].gethasMadeCollision() == true) {

			switch (directions[0]) {
			case 0:
				
				if (rectshrinkdif != 0) {
					Rectangles[0].setSize(sf::Vector2f(Rectangles[0].getWidth(), Rectangles[0].getHeight() - rectshrinkdif));
					rectshrinkdif = 0;
				}
				Rectangles[0].setSize(sf::Vector2f(Rectangles[0].getWidth(), Rectangles[0].getHeight() - (speed * GF::getDelta())));
				if (Rectangles[0].getHeight() <= 0) {
					rectshrinkdif = abs(Rectangles[0].getHeight());
					Rectangles.erase(Rectangles.begin());
					directions.erase(directions.begin());
				}
				break;

			case 1:
				
				if (rectshrinkdif != 0) {
					Rectangles[0].setSize(sf::Vector2f(Rectangles[0].getWidth() + rectshrinkdif, Rectangles[0].getHeight()));
					rectshrinkdif = 0;
				}
				Rectangles[0].setSize(sf::Vector2f(Rectangles[0].getWidth() + (speed * GF::getDelta()), Rectangles[0].getHeight()));
				if (Rectangles[0].getWidth() >= 0) {
					rectshrinkdif = abs(Rectangles[0].getWidth());
					Rectangles.erase(Rectangles.begin());
					directions.erase(directions.begin());
				}
				break;
			case 2:
				
				if (rectshrinkdif != 0) {
					Rectangles[0].setSize(sf::Vector2f(Rectangles[0].getWidth(), Rectangles[0].getHeight() + rectshrinkdif));
					rectshrinkdif = 0;
				}
				Rectangles[0].setSize(sf::Vector2f(Rectangles[0].getWidth(), Rectangles[0].getHeight() + (speed * GF::getDelta())));
				if (Rectangles[0].getHeight() >= 0) {
					rectshrinkdif = abs(Rectangles[0].getHeight());
					Rectangles.erase(Rectangles.begin());
					directions.erase(directions.begin());


				}
				break;
			case 3:
				
				if (rectshrinkdif != 0) {
					Rectangles[0].setSize(sf::Vector2f(Rectangles[0].getWidth() - rectshrinkdif, Rectangles[0].getHeight()));
					rectshrinkdif = 0;
				}
				Rectangles[0].setSize(sf::Vector2f(Rectangles[0].getWidth() - (speed * GF::getDelta()), Rectangles[0].getHeight()));
				if (Rectangles[0].getWidth() <= 0) {
					rectshrinkdif = abs(Rectangles[0].getWidth());
					Rectangles.erase(Rectangles.begin());
					directions.erase(directions.begin());

				}
				break;
			}

		}
	}
	
	if (Rectangles.size() == 0) {
		ready_to_delete = true;
		
	}
	
}

void Projectile::drawall(sf::RenderWindow &win) {
	for (unsigned int i = 0; i < VP.size(); i++) {
		VP[i].draw(win);
	}
}

void Projectile::draw(sf::RenderWindow &win) {
	for (unsigned int i = 0; i < Rectangles.size(); i++) {
		win.draw(Rectangles[i]);
	}
}

void Projectile::changedirection(const int &new_direction, const bool &extra, const bool &particles) {
	if (extra == true) {
		//Making it so that the projectile must go another 16 pixels before changing direction.
		extra16 = true;
		reservedirection = new_direction;
	}
	else {
		SHOULDBREAK = true;
		x = cx;
		y = cy;
		x2 = cx;
		y2 = cy;
		x3 = cx;
		y3 = cy;
		if (particles == true) {
			switch (gettype()) {
			case 0:
			{ ParticleSettings f(x + 16, y + 16, 2, 20, 4, 1); f.color = sf::Color::Blue; f.ac1 = 0; f.ac2 = 360; ParticleSystem::create(f); }
			break;
			case 1:
			{ParticleSettings f1(x + 16, y + 16, 2, 20, 4, 1); f1.color = sf::Color::Magenta; f1.ac1 = 0; f1.ac2 = 360; ParticleSystem::create(f1); }
			break;
			}
		}
		rect r;
		r.setColor(color);
		switch (new_direction) {
		case 0:
			
			r.setPosition(x + middle, y);
			break;
		case 1:
			
			//These switch statements add/subtract 32 in the direction necessary.
			switch (directions[directions.size() - 1]) {
			case 2:				
				x += 32 + rounddif;
				x3 += 32;
				x2 += 32;			
				break;
			case 0:				
				x += 32 + rounddif;
				x3 += 32;
				x2 += 32;
				break;
			}
			
			r.setPosition(x, y + middle);
			break;
		case 2:
		
			//These switch statements add/subtract 32 in the direction necessary.
			switch (directions[directions.size() - 1]) {
			case 1:				
				y += 32 + rounddif;
				y3 += 32;
				y2 += 32;				
				break;
			case 3:				
				y += 32 + rounddif;
				y3 += 32;
				y2 += 32;				
				break;
			}			

			r.setPosition(x + middle, y);
			break;
		case 3:

			r.setPosition(x, y + middle);
			break;
		}

		r.sx = x3;
		r.sy = y3;
		passed = -1;
		directions.push_back(new_direction);
		Rectangles.push_back(r);
	}
	
}

int Projectile::getcx() {
	return cx;
}

int Projectile::getcy() {
	return cy;
}

void Projectile::setx(int new_x) {
	x = new_x;
}

void Projectile::sety(int new_y) {
	y = new_y;
}

bool Projectile::CheckCollisionLight(float x_pos, float y_pos, float w, float h, bool should_add_enemy) {
	
	
	for (unsigned int i = 0; i < Rectangles.size(); i++) {
		float rx = Rectangles[i].getX();
		float ry = Rectangles[i].getY();
		float rw = Rectangles[i].getWidth();
		float rh = Rectangles[i].getHeight();
		bool has_x = false;
		bool has_y = false;
		
		x_pos += w / 2;
		y_pos += h / 2;
		if (rw < 0) {
			if (((x_pos) < rx) && ((x_pos) > rx + rw)){ 
				has_x = true;
			}
		}
		else if (rw > 0) {
			if (((x_pos) > rx && (x_pos) < rx + rw)) { 
				has_x = true;
			}
		}
		if (rh > 0) {
			
			if (((y_pos) > ry && (y_pos) < ry + rh)){
				has_y = true;
			}
		}
		else if (rh < 0) {
			
			if (((y_pos) < ry && (y_pos) > ry + rh)){
				has_y = true;
			}
		}
		
		if (has_x == true && has_y == true) {
			
			if (should_add_enemy == true) {
				mtx.lock();
				HowManyEnemies += 1;
				Player::PlayerObjects[0]->getScoring().add_score(2 * HowManyEnemies);
				sound.setPitch(HowManyEnemies + 1);
				sound.play();
				mtx.unlock();
			}
			return true;
		}
	}
	
	return false;
}

bool Projectile::CheckCollisionHeavy(float x_position, float y_position, float w, float h, float threshold, bool should_add_enemy) {
	
	for (unsigned int i = 0; i < Rectangles.size(); i++) {
		
		float rx = Rectangles[i].getX();
		float ry = Rectangles[i].getY();
		float rw = Rectangles[i].getWidth();
		float rh = Rectangles[i].getHeight();
		if (rw > rh) {
			ry -= threshold;
			rh += threshold;
		}
		else if (rh > rw) {
			rx -= threshold;
			rw += threshold;
			
		}
		float x_pos = x_position;
		float y_pos = y_position;
		
		for (unsigned int b = 0; b < 4; b++) {
			bool has_x = false;
			bool has_y = false;
			switch (b) {
			case 0:
				x_pos = x_position + (w / 2);
				y_pos = y_position + 1;
				break;
			case 1:
				x_pos = x_position + (w - 1);
				y_pos = y_position + (h / 2);
				break;
			case 2:
				x_pos = x_position + (w / 2);
				y_pos = y_position + (h - 1);
				break;
			case 3:
				y_pos = y_position + (h / 2);
				x_pos = x_position + 1;
				break;

			}
			if (rw < 0) {
				if (((x_pos) < rx) && ((x_pos) > rx + rw)) {
					has_x = true;
				}
			}
			else if (rw > 0) {
				if (((x_pos) > rx && (x_pos) < rx + rw)) {
					has_x = true;
				}
			}
			if (rh > 0) {

				if (((y_pos) > ry && (y_pos) < ry + rh)) {
					has_y = true;
				}
			}
			else if (rh < 0) {

				if (((y_pos) < ry && (y_pos) > ry + rh)) {
					has_y = true;
				}
			}
			if (has_x == true && has_y == true) {
				
				if (should_add_enemy == true) {
					mtx.lock();
					HowManyEnemies += 1;
					Player::PlayerObjects[0]->getScoring().add_score(2 * HowManyEnemies);
					sound.setPitch(HowManyEnemies + 1);
					sound.play();
					mtx.unlock();
				}
				return true;
			}
		}
		
	
	}

	return false;
}

bool Projectile::CheckCollisionHeavy2(float x_position, float y_position, float w, float h, float threshold, bool should_add_enemy) {
	std::vector<sf::Vector2f> Bounds;
	for (unsigned int i = 0; i < Rectangles.size(); i++) {
		Bounds = Rectangles[i].getGlobalBounds();
		for (unsigned int b = 0; b < Bounds.size(); b++) {
			if ((Bounds[b].x > x_position && Bounds[b].x < x_position + w) && (Bounds[b].y > y_position && Bounds[b].y < y_position + h)) {

				//At least one of the vertices are inside the collision bounds.
				return true;
			}
		}
	}
	return false;
}

int Projectile::DynamicCheckCollisionHeavy(float x_pos, float y_pos, float widthofrect, float heightofrect, float threshold, bool should_add_enemy) {
	for (unsigned int i = 0; i < VP.size(); i++) {
		
		if (VP[i].CheckCollisionHeavy(x_pos, y_pos, widthofrect, heightofrect, threshold, should_add_enemy) == true) {
			return i;
		}
	}
	return -1;
}

int Projectile::DynamicCheckCollisionHeavy2(float x_pos, float y_pos, float widthofrect, float heightofrect, float threshold, bool should_add_enemy) {
	for (unsigned int i = 0; i < VP.size(); i++) {
		if (VP[i].CheckCollisionHeavy2(x_pos, y_pos, widthofrect, heightofrect, threshold, should_add_enemy) == true) {
			return i;
		}
	}
	return -1;
}

int Projectile::DynamicCheckCollisionLight(float x_pos, float y_pos, float widthofrect, float heightofrect, bool should_add_enemy) {
	for (unsigned int i = 0; i < VP.size(); i++) {
		if (VP[i].CheckCollisionLight(x_pos, y_pos, widthofrect, heightofrect, should_add_enemy) == true) {
			return i;
		}
	}
	return -1;
}

void Projectile::addEnemy(int how_many) {
	HowManyEnemies += how_many;
}

void Projectile::kill(unsigned int reason) {
	mtx.lock();
	switch (reason) {
	case 0: //Too far away from player.
		actually_kill();
		break;
	case 1: //Hit wall
		if (is_ghost == false) {
			actually_kill();
		}
		break;
	case 2: //Hit NPC
		if (is_piercing == false) {
			actually_kill();
		}
		break;
	}
	mtx.unlock();
}

void Projectile::clear_all() {
	VP.clear();
}

int Projectile::getDirection() {
	return directions[0];
}

float Projectile::getVoltage() {
	return voltage;
}

void Projectile::setVoltage(float new_voltage) {
	voltage = new_voltage;
}

void Projectile::init() {
	
	Default_PSet = ParticleSettings(0, 0, 0, 0, 0, 0);
}

void Projectile::actually_kill() {
	rectsubtract = 0;
	Rectangles[Rectangles.size() - 1].ParticleProducing = true;
	Rectangles[Rectangles.size() - 1].MadeCollision();
}
	
void Projectile::call32() {
	switch (type) {
	case 5:
		check_direction_green();
		break;
	case 6:
		check_direction_green();
		
	}
}

void Projectile::check_all() {
	if (VP.size() != 0) {
		for (std::vector<Projectile>::iterator iter = VP.begin(); iter != VP.end();) {
			if (iter->ready_to_delete == true) {
				iter = VP.erase(iter);
			}
			else {
				iter++;
			}
		}
	}
	
}

void Projectile::check_direction_green() {
	if (b1 == false) {
		for (unsigned int i = 0; i < Sub_NPC_A::Object_Cache.size(); i++) {
			if (Sub_NPC_A::Object_Cache[i]->get_is_dead() == false) {
				float Ny = Sub_NPC_A::Object_Cache[i]->get_C_position().y;
				float Nx = Sub_NPC_A::Object_Cache[i]->get_C_position().x;
				if (Ny == getcy()) {
					if (Nx <= getcx()) {
						if (getDirection() != 1) {
							bool should_turn = true;
							for (unsigned int i = 0; i < Basic_Tile_MOTHER::ColTiles.size(); i++) {
								//if (Basic_Tile_MOTHER::ColTiles[i]->gety() == y && Basic_Tile_MOTHER::ColTiles[i]->getx() < x) {
								//	pos_of_wall = sf::Vector2f(Basic_Tile_MOTHER::ColTiles[i]->getx(), Basic_Tile_MOTHER::ColTiles[i]->gety());
								//}
								if(Basic_Tile_MOTHER::ColTiles[i]->gety() == Ny &&
									Basic_Tile_MOTHER::ColTiles[i]->getx() > Nx &&
									Basic_Tile_MOTHER::ColTiles[i]->getx() < x){
									should_turn = false;
								}
							}
							if (should_turn == true) {
								Sound::Play(40, 0, 0, random2::randomrange(1, 6));
								b1 = true;
								changedirection(3, true, false);
							}
							
						}


						break;
					}
					else {
						if (getDirection() != 3) {
							bool should_turn = true;
							for (unsigned int i = 0; i < Basic_Tile_MOTHER::ColTiles.size(); i++) {
								//if (Basic_Tile_MOTHER::ColTiles[i]->gety() == y && Basic_Tile_MOTHER::ColTiles[i]->getx() < x) {
								//	pos_of_wall = sf::Vector2f(Basic_Tile_MOTHER::ColTiles[i]->getx(), Basic_Tile_MOTHER::ColTiles[i]->gety());
								//}
								if (Basic_Tile_MOTHER::ColTiles[i]->gety() == Ny &&
									Basic_Tile_MOTHER::ColTiles[i]->getx() > x &&
									Basic_Tile_MOTHER::ColTiles[i]->getx() < Nx) {
									should_turn = false;
								}
							}
							if (should_turn == true) {
								Sound::Play(40, 0, 0, random2::randomrange(1, 6));
								b1 = true;
								changedirection(1, true, false);
							}
							
						}
						break;
					}
				}
				else if (Nx == getcx()) {
					if (Ny <= getcy()) {
						if (getDirection() != 2) {
							bool should_turn = true;
							for (unsigned int i = 0; i < Basic_Tile_MOTHER::ColTiles.size(); i++) {
								//if (Basic_Tile_MOTHER::ColTiles[i]->gety() == y && Basic_Tile_MOTHER::ColTiles[i]->getx() < x) {
								//	pos_of_wall = sf::Vector2f(Basic_Tile_MOTHER::ColTiles[i]->getx(), Basic_Tile_MOTHER::ColTiles[i]->gety());
								//}
								if (Basic_Tile_MOTHER::ColTiles[i]->getx() == Nx &&
									Basic_Tile_MOTHER::ColTiles[i]->gety() < y &&
									Basic_Tile_MOTHER::ColTiles[i]->gety() > Ny) {
									should_turn = false;
								}
							}
							if (should_turn == true) {
								Sound::Play(40, 0, 0, random2::randomrange(1, 6));
								b1 = true;
								changedirection(0, true, false);
							}
							
						}
						break;
					}
					else {
						if (getDirection() != 0) {
							bool should_turn = true;
							for (unsigned int i = 0; i < Basic_Tile_MOTHER::ColTiles.size(); i++) {
								//if (Basic_Tile_MOTHER::ColTiles[i]->gety() == y && Basic_Tile_MOTHER::ColTiles[i]->getx() < x) {
								//	pos_of_wall = sf::Vector2f(Basic_Tile_MOTHER::ColTiles[i]->getx(), Basic_Tile_MOTHER::ColTiles[i]->gety());
								//}
								if (Basic_Tile_MOTHER::ColTiles[i]->getx() == Nx &&
									Basic_Tile_MOTHER::ColTiles[i]->gety() > y &&
									Basic_Tile_MOTHER::ColTiles[i]->gety() < Ny) {
									should_turn = false;
								}
							}
							if (should_turn == true) {
								Sound::Play(40, 0, 0, random2::randomrange(1, 6));
								b1 = true;
								changedirection(2, true, false);
							}
							
						}
						break;
					}
				}
			}
		}
	}
}

bool Projectile::get_is_piercing() {
	return is_piercing;
}

bool Projectile::get_is_ghost() {
	return is_ghost;
}