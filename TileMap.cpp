#include "stdafx.h"
#include "TileMap.h"
#include "Cam.h"
#include <iostream>
#include "Player.h"
std::vector<sf::Vertex *> TileMap::PlayerSprite;
std::vector<TileMap::texture> TileMap::selected_Textures;
std::vector<sf::Texture *> TileMap::loaded_Textures;
TileMap::TileMap(sf::Texture *character_texture)
{
	load(character_texture); //Loading the character texture map.
	texture t;
	t.tex = loaded_Textures[0];
	texture t2;
	t2.tex = loaded_Textures[0];
	texture t3;
	t3.tex = NULL;
	erase_all();
	selected_Textures.push_back(t);
	selected_Textures.push_back(t2);
	selected_Textures.push_back(t);
	selected_Textures.push_back(t3);
	
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	for (unsigned int i = 0; i < selected_Textures.size(); i++) {
		
		
		// apply the texture
		states.texture = selected_Textures[i].tex;
		
		
		

		// draw the vertex array
		for (unsigned int b = 0; b < selected_Textures[i].To_BeDrawn.size(); b += 4) {
			//if (selected_Textures[i].To_BeDrawn[b]->color.a != 0) {
			target.draw(selected_Textures[i].To_BeDrawn[b], 4, sf::Quads, states);
			//}
			
		}
		// draw the vertex array in front of the other one.
		/*for (unsigned int b = 0; b < Textures[i].To_BeDrawn_Fore.size(); b += 4) {
			target.draw(Textures[i].To_BeDrawn_Fore[b], 4, sf::Quads, states);
		}*/
		
	}
	
	
}

void TileMap::AddPointer(sf::Vertex * verticeptr, int textureID) {
	selected_Textures[textureID].To_BeDrawn.push_back(verticeptr);
}

void TileMap::load(sf::Texture *Tilemap) {
	loaded_Textures.push_back(Tilemap);
}

void TileMap::clear(const int &index) {
	selected_Textures[index].To_BeDrawn.clear();
}

void TileMap::erase_all() {
	selected_Textures.clear();
}

void TileMap::clear_all() {
	PlayerSprite.clear();
	TextureID = 0;
	texture t;
	t.tex = loaded_Textures[0];
	texture t2;
	t2.tex = loaded_Textures[0];
	texture t3;
	t3.tex = NULL;
	erase_all();
	selected_Textures.push_back(t);
	selected_Textures.push_back(t2);
	selected_Textures.push_back(t);
	selected_Textures.push_back(t3);
}

void TileMap::erase_almost_all() {
	
}

void TileMap::setTexture(int textureID) {
	textureID += 1;
		
		texture t;
		t.tex = loaded_Textures[textureID];
		texture t2;
		t2.tex = loaded_Textures[0];
		t2.To_BeDrawn = PlayerSprite;
		texture t3;
		t3.tex = NULL;
		erase_all();
		selected_Textures.push_back(t);
		selected_Textures.push_back(t2);
		selected_Textures.push_back(t);
		selected_Textures.push_back(t3);
		TextureID = textureID;
	
	
}

int TileMap::getTextureID() {
	return TextureID;
}

void TileMap::setPlayerSprite(T_MOTHER &Tile){
	if (Tile.isSetup == false) {
		
		for (unsigned int i = 0; i < Tile.getVertices().size(); i++) {
			PlayerSprite.push_back(Tile.getVertices()[i]);
		}
		
		Tile.isSetup = true;
	}
	
}