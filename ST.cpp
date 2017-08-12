#include "stdafx.h"
#include "ST.h"
#include <iostream>
#include <memory>

int IDadd;
#define dif 0

ST::ST() {
	tile = sf::VertexArray(sf::Quads, 4);
	position.x = 0; position.y = 0;
	
	//Adding the vertexes to the vertex array that will be holding all the vertexs in one place to be drawn.
	tile[0].position = sf::Vector2f(position.x, position.y);
	tile[1].position = sf::Vector2f(position.x + 32, position.y);
	tile[2].position = sf::Vector2f(position.x + 32, position.y + 32);
	tile[3].position = sf::Vector2f(position.x, position.y + 32);
 
}

ST::~ST() {
	
}

void ST::mapCords() {
	tile[0].position = sf::Vector2f(position.x, position.y);
	tile[1].position = sf::Vector2f(position.x + texrect.width, position.y);
	tile[2].position = sf::Vector2f(position.x + texrect.width, position.y + texrect.height);
	tile[3].position = sf::Vector2f(position.x, position.y + texrect.height);
	/*tile[0].position = sf::Vector2f(position.x - off, position.y - off);
	tile[1].position = sf::Vector2f(position.x + texrect.width + off, position.y - off);
	tile[2].position = sf::Vector2f(position.x + texrect.width + off, position.y + texrect.height + off);
	tile[3].position = sf::Vector2f(position.x - off, position.y + texrect.height + off);*/
}

void ST::setTextureRect(const sf::IntRect &rect) {
	texrect = rect;
	tile[0].texCoords = sf::Vector2f(rect.left + off, rect.top + off);
	tile[1].texCoords = sf::Vector2f((rect.left + rect.width) - off, rect.top + off);
	tile[2].texCoords = sf::Vector2f((rect.left + rect.width) - off, (rect.top + rect.height) - off);
	tile[3].texCoords = sf::Vector2f(rect.left + off, (rect.top + rect.height) - off);
}

void ST::operator=(const ST &I) {
	this->texrect = I.texrect;
	this->setTextureRect(texrect);
	this->position.x = I.position.x;
	this->position.y = I.position.y;
	this->type_of_texture = I.type_of_texture;
	this->isSetup = I.isSetup;
}

void ST::operator*=(AniT &I) {
	setTextureRect(I.getRect());
	mapCords();
}

void ST::setPosition(const sf::Vector2f &Position) {
	position.x = Position.x; position.y = Position.y;
	mapCords();
}

void ST::setPosition(float x_pos, float y_pos) {
	position.x = x_pos; position.y = y_pos;
	mapCords();
}

const sf::Vector2f &ST::getPosition() {
	return position;
}

void ST::setPosition(const sf::Vector2i &Position) {
	position.x = Position.x; position.y = Position.y;
	mapCords();
}