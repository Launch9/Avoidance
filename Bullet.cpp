#include "stdafx.h"
#include "Bullet.h"
#include "Wall.h"
#include <iostream>
std::vector<std::vector<sf::Sprite>> Bullet::s;
std::vector<Bullet> Bullet::BObjects;
sf::SoundBuffer Bullet::SBuffer;
std::vector<std::vector<sf::SoundBuffer>> Bullet::sound;

Bullet::Bullet(int bulletx, int bullety, unsigned int direction, unsigned int bulletid, int bulletspeed, int speedchange)
{
	direct = direction;
	x = bulletx;
	y = bullety;
	//This is used to determine what the sprite and default speed is for the bullet id you choose.
	switch (bulletid) {
	case 0:
		sprites = s[0];
		//This checks to see if you actually put in a number for the speed.
		//If not it will give default for the bullet.
		if (bulletspeed == -1) {
			speed = 16 + speedchange;
		}
		tick_limit = 6;
		break;
	
	}
	BObjects.push_back(*this);
}


void Bullet::init(sf::Texture &tex) {
	
	sf::Sprite Standardb0;
	sf::Sprite Standardb1;
	sf::Sprite Standardb2;
	Standardb0.setTexture(tex);
	Standardb1.setTexture(tex);
	Standardb2.setTexture(tex);
	Standardb0.setTextureRect(sf::IntRect(64, 96, 32, 32));
	Standardb1.setTextureRect(sf::IntRect(64, 128, 32, 32));
	Standardb2.setTextureRect(sf::IntRect(64, 160, 32, 32));
	std::vector<sf::Sprite> StandardbV = { Standardb0, Standardb1, Standardb2 };
	s.push_back(StandardbV);
}

void Bullet::tick() {
	
	for (unsigned int i = 0; i < BObjects.size(); i++) {
		
		bool b = Wall::CheckCollision(BObjects[i].getx(), BObjects[i].gety());
		if (b == true) {
			BObjects.erase(BObjects.begin() + i);
			continue;
		}
		
		/*This checks the direction and then adds the speed integer to whatever cordinate needs it.*/
		switch (BObjects[i].getdirection()) {
			//case right
		case 0:
			BObjects[i].getx() += BObjects[i].getspeed();
			break;
			//case down
		case 1:
			BObjects[i].gety() += BObjects[i].getspeed();
			break;
			//case left
		case 2:
			BObjects[i].getx() -= BObjects[i].getspeed();
			break;
			//case up
		case 3:
			BObjects[i].gety() -= BObjects[i].getspeed();
			break;
		}
		
		//This sets the position of the sprite that will be drawn.
		for (unsigned int b = 0; b < BObjects[i].getsprites().size(); b++) {
			BObjects[i].getsprites()[b].setPosition(BObjects[i].getx(), BObjects[i].gety());
		}
		
		//This is used to tell wether or not to change the sprite in the animation.
		if (BObjects[i].getticks() >= BObjects[i].gettick_limit()) {
			//Checking to see if the animation index has reached the end of the vector of sprites.
			if (BObjects[i].getspriteindex() >= BObjects[i].getsprites().size() - 1) {
			
				BObjects[i].getspriteindex() = 0;
			}
			else {
				BObjects[i].getspriteindex() += 1;
			}
		}
		//This is adding one tick to the total.
		BObjects[i].getticks() += 1;

	
		


	}
}

int &Bullet::getx() {
	return x;
}
int &Bullet::gety() {
	return y;
}

int &Bullet::getspeed() {
	return speed;
}
unsigned int &Bullet::getdirection() {
	return direct;
}
std::vector<sf::Sprite> &Bullet::getsprites() {
	return sprites;
}
int &Bullet::getspriteindex() {
	return spriteindex;
}
unsigned int &Bullet::getticks() {
	return ticks;
}
unsigned int &Bullet::gettick_limit() {
	return tick_limit;
}

void Bullet::draw(sf::RenderWindow &win) {

	for (unsigned int i = 0; i < BObjects.size(); i++) {
		win.draw(BObjects[i].getsprites()[BObjects[i].getspriteindex()]);
	}
	
}