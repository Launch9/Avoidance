#include "stdafx.h"
#include "DText.h"
#include "GF.h"
#define offset_x 16
#define offset_y 16

DText::DText()
{
	position = sf::Vector2f(0, 0);
	color = sf::Color::Black;
	type = 1;
}

void DText::setPosition(float x_pos, float y_pos) {
	position.x = x_pos;
	position.y = y_pos;
	//text().setPosition(position.x + offset_x, position.y + offset_y);
}

void DText::setPosition(const sf::Vector2f &Position) {
	position = Position;
	//text().setPosition(position.x + offset_x, position.y + offset_y);
}

void DText::setMax_Health(int Max_health) {
	max_health = Max_health;
}

void DText::setDamage(int New_damage) {
	damage_done = New_damage;
}

void DText::display() {
	text().setPosition(position.x + offset_x, position.y + offset_y);
	text().setString(GF::str(damage_done) + "/" + GF::str(max_health));
}

TempText& DText::text() {
	static TempText* ans = new TempText();
	return *ans;
}

void DText::clear() {
	text().vanish();
}