#include "stdafx.h"
#include "Cloud.h"
#include <iostream>
std::vector<Cloud *> Cloud::Objects;
std::vector<std::vector<sf::Vector2i>> Cloud::Transforms;
Cloud::Cloud(int start_x_pos, int start_y_pos, int end_x_position, float x_Speed, float y_Speed) {
	x = start_x_pos;
	y = start_y_pos;
	start_x = start_x_pos;
	start_y = start_y_pos;
	end_x = end_x_position * 32;
	x_speed = x_Speed;
	y_speed = y_Speed;
	srand(GF::getTSS().asMicroseconds());
	sf::Color color;
	color.a = rand() % (150 + 30);
	color.g = 255;
	color.b = 255;
	color.r = 255;
	std::vector<sf::Vector2i> trans; //Transformations to be used.
	trans = Transforms[rand() % (Transforms.size() + 0)];
	for (unsigned int i = 0; i < trans.size(); i++) {
		sf::CircleShape c;
		c.setFillColor(color);
		c.setRadius(30);
		c.setPosition(x + trans[i].x, y + trans[i].y);
		Circles.push_back(c);
	}

	Objects.push_back(this);
}

void Cloud::tick() {
	x += x_speed * GF::getDelta();
	y += y_speed * GF::getDelta();
	for (unsigned int i = 0; i < Circles.size(); i++) {
		
		Circles[i].move(x_speed * GF::getDelta(), y_speed * GF::getDelta());
		
	}
	
}

void Cloud::maintick() {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		Objects[i]->tick();
		if (Objects[i]->end_x > Objects[i]->start_x) {
			if (Objects[i]->x > Objects[i]->end_x) {
				delete Objects[i];
				Objects.erase(Objects.begin() + i);
			}
		}
		else if(Objects[i]->end_x < Objects[i]->start_x) {
			if (Objects[i]->x < Objects[i]->end_x) {
				delete Objects[i];
				Objects.erase(Objects.begin() + i);
			}
		}
		else {
			delete Objects[i];
			Objects.erase(Objects.begin() + i);
		}
		
	}
}

void Cloud::draw(sf::RenderWindow &win) {
	for (unsigned int i = 0; i < Circles.size(); i++) {
		win.draw(Circles[i]);
	}
}

void Cloud::draw_all(sf::RenderWindow &win) {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		Objects[i]->draw(win);
	}
}

void Cloud::init() {
	Transforms = { {sf::Vector2i(30,50), sf::Vector2i(60,65), sf::Vector2i(100,80), sf::Vector2i(95,40)},
	{sf::Vector2i(0,0), sf::Vector2i(-50, 20), sf::Vector2i(-36,10), sf::Vector2i(-80,3), sf::Vector2i(-100,0) },
	{sf::Vector2i(0,0), sf::Vector2i(40, 20), sf::Vector2i(35, 16)},
	{sf::Vector2i(0,0), sf::Vector2i(-30, 10), sf::Vector2i(-40, -24), sf::Vector2i(25,5)},
	{sf::Vector2i(4,7),sf::Vector2i(24,10), sf::Vector2i(-20,6), sf::Vector2i(-40,15)} };
}

void Cloud::clear_all() {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		delete Objects[i];
	}
	Objects.clear();
}