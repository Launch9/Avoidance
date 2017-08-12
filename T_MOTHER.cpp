#include "stdafx.h"
#include "T_MOTHER.h"
#include <iostream>
#include "GF.h"
T_MOTHER::T_MOTHER()
{
	position = sf::Vector2f(0, 0);
}


T_MOTHER::~T_MOTHER()
{
	if (isSetup == true) {
		for (unsigned int i = 0; i < TileMap::selected_Textures[type_of_texture].To_BeDrawn.size(); i++) {
			if (&tile[0] == TileMap::selected_Textures[type_of_texture].To_BeDrawn[i]) {
				for (unsigned int b = 0; b < 4; b++) {
					TileMap::selected_Textures[type_of_texture].To_BeDrawn.erase(TileMap::selected_Textures[type_of_texture].To_BeDrawn.begin() + i);
				}
				break;
			}
		}
	}
}

void T_MOTHER::setup() {
	
	if (isSetup == false && type_of_texture != -1) {
		for (unsigned int i = 0; i < tile.getVertexCount(); i++) {
			TileMap::AddPointer(&tile[i], type_of_texture);
		}
		isSetup = true;
	}
	
}

void T_MOTHER::setTexture(unsigned int type) {
	if (isSetup == false) {
		type_of_texture = type;
	}
}

void T_MOTHER::setColor(const sf::Color &new_color) {
	color = new_color;
	if (isActive == true) {
		for (unsigned int i = 0; i < tile.getVertexCount(); i++) {
			tile[i].color = color;
		}
	}
}

const sf::Color &T_MOTHER::getColor() {
	return color;
}


void T_MOTHER::deactivate() {
	isActive = false;
	for (unsigned int i = 0; i < tile.getVertexCount(); i++) {
		tile[i].color.a = 0;
	}
}

void T_MOTHER::activate() {
	isActive = true;
	setColor(color);
}

std::vector<sf::Vertex *> T_MOTHER::getVertices() {
	std::vector<sf::Vertex *> v;
	v = { &tile[0],&tile[1],&tile[2],&tile[3] };
	return v;
}

bool T_MOTHER::get_is_Active() {
	return isActive;
}