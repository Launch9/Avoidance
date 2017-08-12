#include "stdafx.h"
#include "BackSplash_MOTHER.h"
#include "SnowClouds.h"
#include "Space.h"
#include <iostream>
std::vector<std::vector<std::vector<sf::Sprite>>> BackSplash_MOTHER::All_sprites;
BackSplash_MOTHER * BackSplash_MOTHER::Object;

void BackSplash_MOTHER::init(sf::Texture &tex) {
	
	for (unsigned int i = 0; i < 10; i++) {
		All_sprites.push_back({});
	}
	//Type 0 backsplash, consists of snowy clouds.
	sf::Sprite s1;
	s1.setTexture(tex);
	s1.setTextureRect(sf::IntRect(0, 0, 2048, 1280));
	//Type 1 backsplash, consists of space and planets.
	sf::Sprite s2;
	s2.setTexture(tex);
	s2.setTextureRect(sf::IntRect(0, 1280, 2048, 1280));
	//Planet
	sf::Sprite s3;
	s3.setTexture(tex);
	s3.setTextureRect(sf::IntRect(0, 2560, 96, 96));
	All_sprites[0].push_back({ s1 });
	All_sprites[1].push_back({ s2,s3 });
}

void BackSplash_MOTHER::draw_all(sf::RenderWindow &win) {
	if (Object != nullptr) {
		
		Object->draw(win);
	}
	
}

void BackSplash_MOTHER::draw(sf::RenderWindow &win) {

}

int BackSplash_MOTHER::getSave() {
	if (Object != nullptr) {
		return Object->typeID;
	}
	
}

void BackSplash_MOTHER::clear() {
	delete Object;
	Object = nullptr;
}

void BackSplash_MOTHER::tick() {

}

void BackSplash_MOTHER::draw_FORE(sf::RenderWindow &win) {

}

void BackSplash_MOTHER::create(int type) {
	switch (type) {
	case 0:
		new SnowClouds();
		break;
	case 1:
		new Space();
		break;
	}
}

void BackSplash_MOTHER::tick_all() {
	if (Object != nullptr) {
		
		Object->tick();
	}
	
	
}

void BackSplash_MOTHER::draw_all_fore(sf::RenderWindow &win) {
	if (Object != nullptr) {
		Object->draw_FORE(win);
	}
}