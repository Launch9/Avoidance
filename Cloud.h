#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "GF.h"
#define maxDetail 10
///This class belongs to the World.cpp class.
///It displays clouds float in the sky.
class Cloud
{
private:
	//This is the rate at which all the circles move in the x direction.
	float x_speed = 0;
	//This is the rate at which all the circles move in the y direction.
	float y_speed = 0;
	//This is where the cloud is deleted.
	int end_x = 0;
	//Contains all the Circles that make up the cloud.
	std::vector<sf::CircleShape> Circles;
	//This contains a nice big list of different transformations that can be applied to the different circles when making a cloud.
	static std::vector<std::vector<sf::Vector2i>> Cloud::Transforms;
	//X position
	float x = 0;
	//Y position
	float y = 0;
	//starting position for x
	int start_x = 0;
	//starting position for y
	int start_y = 0;
	//All the cloud objects are contained within this vector.
	static std::vector<Cloud *> Cloud::Objects; //This contains all the clouds.
	//This loops through all the circles and moves them the right distance from before.
	//Depending on x and y speeds.
	void tick();
	//This will draw all the circles to the window given.
	//It will draw the cloud.
	void draw(sf::RenderWindow &win);
	

public:
	//This is only run once.
	//At the beginning of your program.
	static void init();
	//This is a cloud, it will move in the direction provided by the x and y speeds.
	//It will disapear after reaching a given point.
	//The end_x_position is a line at a given x position. Any time the cloud goes above or below that x position, it will be deleted.
	//The end_x_position is multiplied by 32. So it is just how many blocks from zero you want it to be at.
	Cloud(int start_x_pos, int start_y_pos, int end_x_position, float x_Speed, float y_Speed);
	static void maintick();
	static void draw_all(sf::RenderWindow &win);
	//This clears all the clouds in the map.
	static void clear_all();
};

