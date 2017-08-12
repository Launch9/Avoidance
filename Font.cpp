#include "stdafx.h"
#include "Font.h"
#include <iostream>
std::vector<sf::Font> Font::Fonts;

void Font::init() {
	sf::Font f0;
	if (!f0.loadFromFile("R/Fonts/isocpeur.ttf")) {
		std::cout << "Error loading isocpeur.ttf font." << std::endl;
		throw("Errorz");
	}
	sf::Font f1;
	if (!f1.loadFromFile("R/Fonts/arial.ttf")) {
		std::cout << "Error loading arial.ttf font" << std::endl;
	}
	sf::Font f2;
	if (!f2.loadFromFile("R/Fonts/ARDESTINE.ttf")) {
		std::cout << "Error loading smalle.fon font" << std::endl;
	}
	Fonts = { f0, f1, f2 };
}

const sf::Font &Font::Get_isocpeur() {
	return Fonts[0];
}

const sf::Font &Font::Get_arial() {
	return Fonts[1];
}

const sf::Font &Font::Get_smalle() {
	return Fonts[2];
}