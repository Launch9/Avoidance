#include "stdafx.h"
#include "Room.h"
#include <iostream>
std::vector<Room *> Room::Objects;
class Basic_Tile_MOTHER;
class NPC_MOTHER;
Room::Room(int Type, int Channel, int x_pos, int y_pos, int width_in_blocks, int height_in_blocks)
{
	type = Type;
	channel = Channel;
	x = x_pos;
	y = y_pos;
	typeID = 6;
	size.x = (width_in_blocks - 1) * 32;
	size.y = (height_in_blocks - 1) * 32;
	bounding.setSize(sf::Vector2f(size.x + 32, size.y + 32));
	bounding.setPosition(x, y);
	bounding.setFillColor(sf::Color(0, 0, 0, 0));
	bounding.setOutlineThickness(3);
	bounding.setOutlineColor(sf::Color::Cyan);
	SavedParameters = { Type, Channel, x_pos, y_pos, width_in_blocks, height_in_blocks };
	Objects.push_back(this);
	NonCol_InvisibleObjects.push_back(this);
	update();
	deactivate();
}

Room::~Room() {
	activate();
	for (unsigned int i = 0; i < Objects.size(); i++) {
		if (this == Objects[i]) {
			Objects.erase(Objects.begin() + i);
			break;
		}
	}
}

void Room::update() {
	
	for (unsigned int b = 0; b < Objects.size(); b++) {
		Objects[b]->NPCs.clear();
		Objects[b]->Tiles.clear();
		for (unsigned int i = 0; i < Basic_Tile_MOTHER::ColTiles.size(); i++) {
			if (((Basic_Tile_MOTHER::ColTiles[i]->getx() >= Objects[b]->x) && (Basic_Tile_MOTHER::ColTiles[i]->getx() <= Objects[b]->x + Objects[b]->size.x)) &&
				((Basic_Tile_MOTHER::ColTiles[i]->gety() >= Objects[b]->y) && (Basic_Tile_MOTHER::ColTiles[i]->gety() <= Objects[b]->y + Objects[b]->size.y))) {
				Objects[b]->Tiles.push_back(Basic_Tile_MOTHER::ColTiles[i]->getSpritePointer());
			}
		}
		for (unsigned int i = 0; i < Basic_Tile_MOTHER::ColAniTiles.size(); i++) {
			if (((Basic_Tile_MOTHER::ColAniTiles[i]->getx() >= Objects[b]->x) && (Basic_Tile_MOTHER::ColAniTiles[i]->getx() <= Objects[b]->x + Objects[b]->size.x)) &&
				((Basic_Tile_MOTHER::ColAniTiles[i]->gety() >= Objects[b]->y) && (Basic_Tile_MOTHER::ColAniTiles[i]->gety() <= Objects[b]->y + Objects[b]->size.y))) {
				Objects[b]->Tiles.push_back(Basic_Tile_MOTHER::ColAniTiles[i]->getSpritePointer());
			}
		}
		for (unsigned int i = 0; i < Basic_Tile_MOTHER::NonColAniTiles.size(); i++) {
			if (((Basic_Tile_MOTHER::NonColAniTiles[i]->getx() >= Objects[b]->x) && (Basic_Tile_MOTHER::NonColAniTiles[i]->getx() <= Objects[b]->x + Objects[b]->size.x)) &&
				((Basic_Tile_MOTHER::NonColAniTiles[i]->gety() >= Objects[b]->y) && (Basic_Tile_MOTHER::NonColAniTiles[i]->gety() <= Objects[b]->y + Objects[b]->size.y))) {
				Objects[b]->Tiles.push_back(Basic_Tile_MOTHER::NonColAniTiles[i]->getSpritePointer());
			}
		}
		for (unsigned int i = 0; i < Basic_Tile_MOTHER::NonColAniTiles_FORE.size(); i++) {
			if (((Basic_Tile_MOTHER::NonColAniTiles_FORE[i]->getx() >= Objects[b]->x) && (Basic_Tile_MOTHER::NonColAniTiles_FORE[i]->getx() <= Objects[b]->x + Objects[b]->size.x)) &&
				((Basic_Tile_MOTHER::NonColAniTiles_FORE[i]->gety() >= Objects[b]->y) && (Basic_Tile_MOTHER::NonColAniTiles_FORE[i]->gety() <= Objects[b]->y + Objects[b]->size.y))) {
				Objects[b]->Tiles.push_back(Basic_Tile_MOTHER::NonColAniTiles_FORE[i]->getSpritePointer());
			}
		}
		for (unsigned int i = 0; i < Basic_Tile_MOTHER::NonColTiles.size(); i++) {
			if (((Basic_Tile_MOTHER::NonColTiles[i]->getx() >= Objects[b]->x) && (Basic_Tile_MOTHER::NonColTiles[i]->getx() <= Objects[b]->x + Objects[b]->size.x)) &&
				((Basic_Tile_MOTHER::NonColTiles[i]->gety() >= Objects[b]->y) && (Basic_Tile_MOTHER::NonColTiles[i]->gety() <= Objects[b]->y + Objects[b]->size.y))) {
				Objects[b]->Tiles.push_back(Basic_Tile_MOTHER::NonColTiles[i]->getSpritePointer());
			}
		}
		for (unsigned int i = 0; i < Basic_Tile_MOTHER::NonColTiles_FORE.size(); i++) {
			if (((Basic_Tile_MOTHER::NonColTiles_FORE[i]->getx() >= Objects[b]->x) && (Basic_Tile_MOTHER::NonColTiles_FORE[i]->getx() <= Objects[b]->x + Objects[b]->size.x)) &&
				((Basic_Tile_MOTHER::NonColTiles_FORE[i]->gety() >= Objects[b]->y) && (Basic_Tile_MOTHER::NonColTiles_FORE[i]->gety() <= Objects[b]->y + Objects[b]->size.y))) {
				Objects[b]->Tiles.push_back(Basic_Tile_MOTHER::NonColTiles_FORE[i]->getSpritePointer());
			}
		}
		for (unsigned int i = 0; i < Basic_Tile_MOTHER::ColProjectiles.size(); i++) {
			if (((Basic_Tile_MOTHER::ColProjectiles[i]->getx() >= Objects[b]->x) && (Basic_Tile_MOTHER::ColProjectiles[i]->getx() <= Objects[b]->x + Objects[b]->size.x)) &&
				((Basic_Tile_MOTHER::ColProjectiles[i]->gety() >= Objects[b]->y) && (Basic_Tile_MOTHER::ColProjectiles[i]->gety() <= Objects[b]->y + Objects[b]->size.y))) {
				Objects[b]->Tiles.push_back(Basic_Tile_MOTHER::ColProjectiles[i]->getSpritePointer());
			}
		}
		for (unsigned int i = 0; i < NPC_MOTHER::NPC_Cache.size(); i++) {
			if (((NPC_MOTHER::NPC_Cache[i]->getinitx() >= Objects[b]->x) && (NPC_MOTHER::NPC_Cache[i]->getinitx() <= Objects[b]->x + Objects[b]->size.x)) &&
				((NPC_MOTHER::NPC_Cache[i]->getinity() >= Objects[b]->y) && (NPC_MOTHER::NPC_Cache[i]->getinity() <= Objects[b]->y + Objects[b]->size.y))) {
				Objects[b]->NPCs.push_back(NPC_MOTHER::NPC_Cache[i]);
			}
		}
		for (unsigned int i = 0; i < Objects[b]->Tiles.size(); i++) {
			Objects[b]->Tiles[i]->deactivate();
		}
		for (unsigned int i = 0; i < Objects[b]->NPCs.size(); i++) {
			Objects[b]->NPCs[i]->deactivate();
		}
	}
	for (unsigned int i = 0; i < Objects.size(); i++) {
		Objects[i]->deactivate();
	}
}

void Room::draw(sf::RenderWindow &win) {
	
	win.draw(Rect);
	win.draw(Information);
	win.draw(bounding);

}

void Room::tick() {
	
}

void Room::activate() {
	if (is_active == false) {
		is_active = true;

		for (unsigned int i = 0; i < NPCs.size(); i++) {
			NPCs[i]->activate();
		}
		for (unsigned int i = 0; i < Tiles.size(); i++) {
			Tiles[i]->activate();
		}
	}
	
}

void Room::deactivate() {
	if (is_active = true) {
		is_active = false;
		for (unsigned int i = 0; i < NPCs.size(); i++) {
			NPCs[i]->deactivate();
		}
		for (unsigned int i = 0; i < Tiles.size(); i++) {
			Tiles[i]->deactivate();
		}
	}
	
}

void Room::activate_room(unsigned int channel) {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		if (Objects[i]->channel == channel) {
			
			Objects[i]->activate();
		}
	}
}

void Room::deactivate_room(unsigned int channel) {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		if (Objects[i]->channel == channel) {
			Objects[i]->deactivate();
		}
	}
}