#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
class T_MOTHER;

class TileMap: public sf::Drawable, public sf::Transformable
{
private:
	//This sprite doesn't get deleted when changing the texture.
	static std::vector<sf::Vertex *> TileMap::PlayerSprite; 
	//This erases all the textures in the selected_Textures vector.
	void erase_all();
	int TextureID = 0;
	struct texture {
		std::vector<sf::Vertex *> texture::To_BeDrawn; //Background, things behind the foreground.
		//std::vector<sf::Vertex *> texture::To_BeDrawn_Fore; //Foreground, things drawn over the main drawing.
		sf::Texture *texture::tex = NULL;
		//Clears all the vertices in the texture.
		void texture::clear() {
			To_BeDrawn.clear();
		};
	};
	
public:
	//This takes in a vertex pointer and puts in the vector to draw later.
	static void AddPointer(sf::Vertex * verticeptr, int textureID);
	//These are full of the textures that are being used.
	static std::vector<texture> TileMap::selected_Textures;
	//These are the textures that are loaded up.
	static std::vector<sf::Texture *> TileMap::loaded_Textures;
	//Default Tilemap constructor
	TileMap(sf::Texture *character_texture);
	//This gets the TextureID being used in the TileMap.
	int getTextureID();
	//This will draw the ST to the screen; With texture and all.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//This loads in the tilemap texture for the gameplay.
	void load(sf::Texture *Tilemap);
	//This sets the texture that is being used for the world loaded.
	//0 = lobby texturemap.
	void setTexture(int textureID);
	//This clears the entire To_BeDrawn vector.
	//This clears all the vertices inside the given index texture.
	void clear(const int &index);
	//This goes though all the textures and cleans up all the vertices.
	void clear_all();
	//This erases all the selected textures, but it keeps the player's sprite.
	//Which is texture 1, index zero.
	void erase_almost_all();
	//This sets the player sprite to the tile given.
	void setPlayerSprite(T_MOTHER &Tile);
};

