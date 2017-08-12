#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp> 
class AniT
{
private:
	sf::IntRect rect;
public:
	//Default Constructor
	AniT();
	AniT(sf::IntRect Rectangle);
	const sf::IntRect& getRect();
	void operator=(const AniT &I);
};