#include "stdafx.h"
#include "Choice.h"
#include "App.h"
#include <iostream>
#include "Sound.h"
#include "random2.h"
//How many pixels are between each text object when displayed.
#define TextDisplacement 10
sf::Sprite Choice::globalSprite;
Choice::Choice()
{
	Cursor = globalSprite;
	mapCCords();
}

void Choice::moveindexup(const unsigned int &amount) {
	Sound::Play(0, 0, 0, random2::randomrange(1,5));
	if (index + amount > TextVector.size() - 1) {
		index = TextVector.size() - 1;
	}
	else {
		index += amount;
	}
	mapCCords();
}

void Choice::moveindexdown(const int &amount) {
	Sound::Play(0, 0, 0, random2::randomrange(1, 5));
	if (index - amount < 0) {
		index = 0;
	}
	else {
		index -= amount;
	}
	mapCCords();
}

void Choice::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (unsigned int i = 0; i < TextVector.size(); i++) {
		target.draw(TextVector[i]);
	}
	target.draw(Cursor);
}

void Choice::mapTCords() {
	for (unsigned int i = 0; i < TextVector.size(); i++) {
		TextVector[i].setPosition(x, y + ((TextVector[0].getLocalBounds().height + TextDisplacement) * i));
	}
}
int Choice::check() {
	
	//-=-
	//Checking ups and downs
	//-=-
	//If pressing W
	if (App::P_Controls[0] == true) {
		moveindexup(1);
	}
	//If pressing S
	else if (App::P_Controls[2] == true) {
		moveindexdown(1);
	}

	//-=-
	//Checking left and rights.
	//-=-
	if (App::P_Controls[1] == true) {
		Sound::Play(31, 0, 0, random2::randomrange(1, 5));
		return -5;
	}
	else if (App::P_Controls[3] == true) {
		Sound::Play(31, 0, 0, random2::randomrange(1, 5));
		return -6;
	}
	
	return index;
}

void Choice::setPosition(float x_pos, float y_pos) {
	x = x_pos;
	y = y_pos;
	mapTCords();
	mapCCords();
}

void Choice::setText(const std::vector<sf::Text> &txt, bool should_reset_index) {
	if (should_reset_index == true) {
		index = txt.size() - 1;
	}
	TextVector = txt;
	
	mapTCords();
	mapSCCords();
}

void Choice::init(sf::Texture &tilemap_tex) {
	globalSprite.setTexture(tilemap_tex);
	globalSprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
}

void Choice::mapCCords() {
	if (TextVector.size() != 0) {
		Cursor.setPosition(x - Cursor.getGlobalBounds().width, (y + ((-index + TextVector.size() - 1) * (TextVector[0].getLocalBounds().height + TextDisplacement))) - Cursor.getGlobalBounds().height / 5);
	}
	
}

int Choice::getIndex() {
	return index;
}

void Choice::setColor(const sf::Color &Color_to_be_changed_to) {
	for (unsigned int i = 0; i < TextVector.size(); i++) {
		TextVector[i].setColor(Color_to_be_changed_to);
	}
}

void Choice::mapSCCords() {
	Cursor.setScale(sf::Vector2f(TextVector[0].getCharacterSize() / 12, TextVector[0].getCharacterSize() / 12));
	mapCCords();
}

void Choice::setColorCursor(const sf::Color &new_color) {
	Cursor.setColor(new_color);
}