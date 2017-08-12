#include "stdafx.h"
#include "CT.h"
#include "Debug.h"
#include <iostream>




CT::CT() {
	tile = sf::VertexArray(sf::Quads, 4);
	origin = sf::Vector2f(0, 0);
	scale_factors = sf::Vector2f(1, 1);
	
	//Adding the vertexes to the vertex array that will be holding all the vertexs in one place to be drawn.
	tile[0].position = sf::Vector2f(position.x, position.y);
	tile[1].position = sf::Vector2f(position.x + 32, position.y);
	tile[2].position = sf::Vector2f(position.x + 32, position.y + 32);
	tile[3].position = sf::Vector2f(position.x, position.y + 32);
}

void CT::mapCords() {
	tile[0].position = transform.transformPoint(position.x, position.y);
	tile[1].position = transform.transformPoint(position.x + texrect.width, position.y);
	tile[2].position = transform.transformPoint(position.x + texrect.width, position.y + texrect.height);
	tile[3].position = transform.transformPoint(position.x, position.y + texrect.height);
}

void CT::translate() {
	
}

void CT::setTextureRect(const sf::IntRect &rect) {
	texrect = rect;
	tile[0].texCoords = sf::Vector2f(rect.left + off, rect.top + off);
	tile[1].texCoords = sf::Vector2f((rect.left + rect.width) - off, rect.top + off);
	tile[2].texCoords = sf::Vector2f((rect.left + rect.width) - off, (rect.top + rect.height) - off);
	tile[3].texCoords = sf::Vector2f(rect.left + off, (rect.top + rect.height) - off);
}

void CT::operator=(const CT &I) {
	this->texrect = I.texrect;
	this->setTextureRect(texrect);
	this->position.x = I.position.x;
	this->position.y = I.position.y;
	this->type_of_texture = I.type_of_texture;
	this->isSetup = I.isSetup;
	mapCords();
}

void CT::operator*=(AniT &I) {
	setTextureRect(I.getRect());
	mapCords();
}

void CT::setOrigin(const sf::Vector2f &Origin) {

	position.x = -Origin.x; position.y = -Origin.y;
	mapCords();
}

void CT::setOrigin(float x_offset, float y_offset) {
	position.x = -x_offset; position.y = -y_offset;
	mapCords();
}

void CT::setRotation(float degree) {
	transform.scale(1 / scale_factors.x, 1 / scale_factors.y);
	transform.rotate(-rotation).rotate(degree);
	transform.scale(scale_factors.x, scale_factors.y);
	rotation = checkDegree(degree);
	mapCords();
	
}

void CT::rotate(float degree) {
	transform.scale(1 / scale_factors.x, 1 / scale_factors.y);
	transform.rotate(degree);
	transform.scale(scale_factors.x, scale_factors.y);
	rotation = checkDegree(rotation + degree);
	mapCords();
}

void CT::setPosition(const sf::Vector2f &Position) {
	transform.rotate(-rotation);
	transform.translate(-origin.x, -origin.y);
	origin = Position;
	transform.translate(origin.x, origin.y);
	transform.rotate(rotation);
	mapCords();
}

void CT::setPosition(float x_pos, float y_pos) {
	transform.rotate(-rotation);
	transform.translate(-origin.x, -origin.y);
	origin = sf::Vector2f(x_pos, y_pos);
	transform.translate(origin.x, origin.y);
	transform.rotate(rotation);
	mapCords();
}

float CT::getRotation() {
	return rotation;
}

void CT::setScale(const sf::Vector2f &factors) {
	transform.scale(1/scale_factors.x,1/scale_factors.y).scale(factors);
	scale_factors = factors;
	mapCords();
}

void CT::setScale(float x_factor, float y_factor) {
	transform.scale(1/scale_factors.x, 1/scale_factors.y).scale(x_factor, y_factor);
	scale_factors = sf::Vector2f(x_factor, y_factor);
	mapCords();
}

void CT::scale(float x_factor, float y_factor) {
	scale_factors.x += x_factor; scale_factors.y += y_factor;
	transform.scale(x_factor, y_factor);
	mapCords();
}

void CT::scale(const sf::Vector2f &factors) {
	scale_factors += factors;
	transform.scale(factors);
	mapCords();
	
}

float CT::checkDegree(float degree) {
	if (degree >= 360) {
		while (degree >= 360) {
			degree -= 360;
		}

	}
	else if (degree <= -360) {
		while (degree <= -360) {
			degree += 360;
		}
	}
	return degree;
}

void CT::move(float x_offset, float y_offset) {
	setPosition(origin.x + x_offset, origin.y + y_offset);
}

void CT::move(const sf::Vector2f &offset) {
	setPosition(origin.x + offset.x, origin.y + offset.y);
}

const sf::Vector2f &CT::getPosition() {
	return origin;
}
