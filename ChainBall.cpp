#include "stdafx.h"
#include "ChainBall.h"
#include "GF.h"
#include <cmath>
#include <iostream>
#include "Debug.h"
#define Extra 100
ChainBall::ChainBall(int type, int startx, int starty, TileMap &TM, int distance_from_center, int color, int movementspeed)
{
	
	x = startx;
	y = starty;
	GF::CheckTile_OverLap(x, y);
	typeID = 2;
	initx = startx;
	inity = starty;
	delx = startx;
	dely = starty;
	x2 = startx;
	y2 = starty;
	max_ticks = 3;
	tan = distance_from_center * 32;
	speed = movementspeed * Extra;
	svectorindex = 0;
	
	switch (type) {
	case 0:

		//Red blade
		CT s1; s1 *= All_Sprites[TM.getTextureID()][typeID][0][0]; //Ball
		CT s2; s2 *= All_Sprites[TM.getTextureID()][typeID][0][1]; //Chain
		
		ballsize = 64;
		s2.setTexture(0);
		s1.setTexture(0);
		
		s2.setPosition(x + 16, y + 16);
		s1.setPosition((x + 16), (y + 16) * (32 * distance_from_center));
		s2.setScale(1, distance_from_center);
		s2.setOrigin(32 / 2, 0);
		s1.setOrigin((ballsize / 2) - 1.2, (ballsize / 2) - 1.2);
		
		S = { s1,s2 };
		S[0].setup();
		S[1].setup();
		break;
	}


	switch (color) {
	case 1:
		S[1].setColor(sf::Color(255, 0, 0, 255));
		S[0].setColor(sf::Color(255, 0, 0, 255));
		break;
	case 2:
		S[1].setColor(sf::Color(0, 255, 0, 255));
		S[0].setColor(sf::Color(0, 255, 0, 255));
		break;
	case 3:
		S[1].setColor(sf::Color(0, 0, 255, 255));
		S[0].setColor(sf::Color(0, 0, 255, 255));
		break;

	}

	SavedParameters = { typeID,type,startx,starty,distance_from_center,color,movementspeed };
	NPC_Cache.push_back(this);
}

void ChainBall::tick(bool render) {
	
	S[1].rotate((speed * GF::getDelta() * getGlobalSpeed()) + 90);
	rotation = S[1].getRotation();
	S[1].rotate(-90);
	S[0].rotate(1000 * GF::getDelta());
	//Sine
	float Sine = sin(GF::radians(rotation)) * tan;
	//Cosine
	float CoSine = cos(GF::radians(rotation)) * tan;
	
	x = (initx + 16) + CoSine;
	y = (inity + 16) + Sine;
	
	S[0].setPosition(x, y);


	//Checking to see if you should be dead or not.
	if (render == true) {
		
		if (DynamicCheckPlayerCollision(x - 16, y - 16, 32, 32) == true) {
			KillPlayer();
		}
	}
}

void ChainBall::animate() {

}

void ChainBall::draw(sf::RenderWindow &win) {
	//win.draw(S[0]);
	//win.draw(S[1]);
}

void ChainBall::reset() {
	rotation = 0;
	S[1].setRotation(rotation);
	S[0].setPosition((x + 16), (y + 16) * (tan));
}