#include "stdafx.h"
#include "SnowClouds.h"
#include "Cam.h"
#include "Player.h"
SnowClouds::SnowClouds()
{
	
	//This sets the backdrop to the apropriate sprite.
	backdrop = All_sprites[0][0][0];
	//Setting the main object equal to this object.
	Object = this;
}

void SnowClouds::draw(sf::RenderWindow &win) {
	Cam::drawGUI_chan(0, win, backdrop);
}

void SnowClouds::tick() {
	backdrop.setPosition((-Cam::getdisplaywidth() / 2) - (Player::PlayerObjects[0]->getvx() / 4), (-Cam::getdisplayheight() / 2) - (Player::PlayerObjects[0]->getvy() / 4));
}