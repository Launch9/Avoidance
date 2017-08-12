#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Ani_MOTHER
{
private:
	//X cordinate
	int x = 0;
	//Y cordinate
	int y = 0;
	//This is the amount of ticks that have gone by since it has drawn something.
	float tick = 0;
	//This is the max amount of ticks that need to happen before it draws a sprite and refreshes the tick integer(Sets it back to zero).
	float maxtick = 100;
	//This is the index of the sprite that the object is on.
	int index = 0;
	//This holds all the sprites that need to be looped through and drawn.
	std::vector<sf::Sprite> Sprites = {};

public:


	//This will draw the animation and also add the tick to it.
	//This should be called every tick of your main loop.
	void animate(sf::RenderWindow &win, const bool &isStatic);
	//The functions below set and get the desired variables.
	//CAUTION::The variables returned by the function may be an address, please watch for commments whilst using them.
	int getx();
	int gety();
	float gettick();
	float getmaxtick();
	//Returns the adress!
	std::vector<sf::Sprite> &getsprites();
	void setx(int x_pos);
	void sety(int y_pos);
	void settick(int newtick);
	void setmaxtick(int newmaxtick);
	void setsprites(std::vector<sf::Sprite> newsprites);
	//Once you have made an Ani_MOTHER object, please put it in a vector to be used in the animate function later on.
	Ani_MOTHER(int x_pos, int y_pos, std::vector<sf::Sprite> AnimationSprites, float requiredticks = 10);
	
	
};

