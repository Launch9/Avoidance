#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
class Font
{
private:
	static std::vector<sf::Font> Font::Fonts;
public:
	//This function will initiate all the fonts.
	static void init();
	//This function gives you the isocpeur font.
	static const sf::Font &Get_isocpeur();
	//This function gives you the arial font.
	static const sf::Font &Get_arial();
	//This function gives you the smalle font.
	static const sf::Font &Get_smalle();
};

