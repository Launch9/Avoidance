#include "stdafx.h"
#include "AniT.h"


AniT::AniT(sf::IntRect Rectangle)
{
	rect = Rectangle;
}

const sf::IntRect& AniT::getRect() {
	return rect;
}

AniT::AniT() {

}

void AniT::operator=(const AniT &I) {
	rect = I.rect;
}