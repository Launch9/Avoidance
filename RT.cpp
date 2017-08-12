#include "stdafx.h"
#include "RT.h"
#include "Debug.h"
#include <iostream>
#include "AniT.h"


RT::RT() {
	tile = sf::VertexArray(sf::Quads, 4);
	position.x = 0; position.y = 0;
	tile_size = sf::Vector2f(32, 32);
	//Adding the vertexes to the vertex array that will be holding all the vertexs in one place to be drawn.
	tile[0].position = sf::Vector2f(position.x, position.y);
	tile[1].position = sf::Vector2f(position.x + tile_size.x, position.y);
	tile[2].position = sf::Vector2f(position.x + tile_size.x, position.y + tile_size.y);
	tile[3].position = sf::Vector2f(position.x, position.y + tile_size.y);
}

RT::~RT() {

}

void RT::mapCords() {
	tile[0].position = sf::Vector2f(position.x, position.y);
	tile[1].position = sf::Vector2f(position.x + tile_size.x, position.y);
	tile[2].position = sf::Vector2f(position.x + tile_size.x, position.y + tile_size.y);
	tile[3].position = sf::Vector2f(position.x, position.y + tile_size.y);
	/*tile[0].position = sf::Vector2f(position.x - off, position.y - off);
	tile[1].position = sf::Vector2f(position.x + texrect.width + off, position.y - off);
	tile[2].position = sf::Vector2f(position.x + texrect.width + off, position.y + texrect.height + off);
	tile[3].position = sf::Vector2f(position.x - off, position.y + texrect.height + off);*/
}

void RT::setTextureRect(const sf::IntRect &rect) {
	texrect = rect;
	tile[0].texCoords = sf::Vector2f(rect.left + off, rect.top + off);
	tile[1].texCoords = sf::Vector2f((rect.left + rect.width) - off, rect.top + off);
	tile[2].texCoords = sf::Vector2f((rect.left + rect.width) - off, (rect.top + rect.height) - off);
	tile[3].texCoords = sf::Vector2f(rect.left + off, (rect.top + rect.height) - off);
}

void RT::operator=(const RT &I) {
	this->texrect = I.texrect;
	this->setTextureRect(texrect);
	this->position.x = I.position.x;
	this->position.y = I.position.y;
	this->type_of_texture = I.type_of_texture;
	this->isSetup = I.isSetup;
}

void RT::operator*=(AniT &I) {
	this->setTextureRect(I.getRect());
	this->mapCords();
}

void RT::setPosition(const sf::Vector2f &Position) {
	position.x = Position.x; position.y = Position.y;
	mapCords();
}

void RT::setPosition(float x_pos, float y_pos) {
	position.x = x_pos; position.y = y_pos;
	mapCords();
}

const sf::Vector2f &RT::getPosition() {
	return position;
}

void RT::setPosition(const sf::Vector2i &Position) {
	position.x = Position.x; position.y = Position.y;
	mapCords();
}

void RT::setSize(const sf::Vector2f &size) {
	tile_size = size;
	mapCords();
}

void RT::setSize(float width, float height) {
	tile_size.x = width;
	tile_size.y = height;
	mapCords();
}