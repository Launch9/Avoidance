#pragma once
#include <string>
#include "TempText.h"
///This class is to be used for when you are taking damage and need to show how much health the enemy has left.
///This class just kind of standardizes the damage text.
class DText
{
	//This is relative position of the text.
	sf::Vector2f position;
	//This is the color of the text.
	sf::Color color;
	//This is the type of the text that it is.
	int type = 0;
	//This is the total health that the enemy has.
	int max_health = 0;
	//This is the damage done to the enemy in total.
	int damage_done = 0;
	//This is the text that is displayed when the monster gets hurt.
	static TempText& text();

public:
	DText();
	//This sets the cordinates of the text.
	//The texts has a default offset to the cordinates provided.
	void setPosition(float x_pos, float y_pos);
	//This sets the cordinates of the text.
	//The texts has a default offset to the cordinates provided.
	void setPosition(const sf::Vector2f &Position);
	//This sets the health that the enemy has.
	//The damaged that needs to be reached. e.g 50/max_health
	void setMax_Health(int Max_health);
	//This sets the damage you have done to the enemy.
	//The total damage that has been done to the enemy. e.g health/100
	void setDamage(int New_damage);
	//This function refreshes the string and sets it the text.
	//The text will be displayed by calling this function.
	//Call this to display the text.
	void display();
	//This will clear the DText that is currently on the screen.
	static void clear();
};

