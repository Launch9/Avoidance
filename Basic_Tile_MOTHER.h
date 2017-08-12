#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "GF.h"
#include "World.h"
#include "Ani_MOTHER.h"
#include "ST.h"
#include <memory>
#include "AniT.h"
#include "Projectile.h"
#include "Room.h"
///This class is meant for inheritance.
///Please inherit this class. Nobody else wants it.
///This gives basic tile functions and variables.
///If you are making a tile class, inherit this class please.
class Room;
class Basic_Tile_MOTHER
{
private:

	
	//This gets the object's typeID.
	//(The distinguishing variable for determining wether or not it is a wall or background, etc.
	unsigned int gettypeID();
	//This gets the object's spriteid.
	//(The distinguishing variable for determining what sprite to use.
	unsigned int getspriteID();
	//This is for getting the SavedParameters.
	std::vector<int> getSavedParameters();
	//This is for resetting the lighting in the collision tiles.
	static void RL0();
	//This is for resetting the lighting in the noncollision tiles.
	static void RL1();
	//This is for checking for collision in the first half of the total amount of Col tiles.
	static int CC0(int x, int y);
	//This is for checking for collision in the second half of the total amount of Col tiles.
	static int CC1(int x, int y);
	inline void ResetLighting();
	friend Room;
	//This function will update the lighting in the animation objects.
	void ResetLighting_ANI();
	
	//This is a function meant to draw the sprite.
	void Draw(sf::RenderWindow &win);
	//This is a function meant to draw the ani sprite.
	void Draw_Ani(sf::RenderWindow &win);
protected:
	
	//This safely changes the animation.
	void changeAni(std::vector<AniT> new_Ani);
	//Advanced booleans.
	bool isSIMPLELIGHTING = false;
	//Advanced boolean getter functions.
	bool getSIMPLELIGHTING();
	//This can be overwritten, but most of the time, its not necessary.
	virtual bool CheckCollision_Over(int Your_xpos, int Your_ypos);
	//This is the color for lighting.
	sf::Color color;
	
	//This tells the computer what to do if the player collides with the tile.
	//This should be over written if you want your tile to do something special once landed on.
	virtual bool ifCollision(int PlayerChannel);
	//This tells the computer what to do if the player collides with the tile before he/she lands on it.
	virtual bool ifCollisionBefore(bool isPlayer);
	//This tells the computer what to do if the player is not colliding with the tile.
	virtual bool elseCollisionBefore(int PlayerChannel);
	//This tells the computer what to do if a projectile is colliding with the tile.
	//Will return false if not no collision occured.
	//Will return true if a collision occured.
	virtual void ifProjectileCollision(Projectile &P, int direction);
	//This tells the computer which sprite to draw.
	virtual void animate();
	int x;
	int y;
	int typeID;
	int spriteID;
	//This is used if you want to just draw a single sprite. Or when using animation, this is the one sprite that is drawn.
	//It just changes the texture rectangle each animation change.
	ST sprite;
	//This gets a pointer to the sprite object.
	ST *getSpritePointer();
	//Only use this if it is a Animation.
	std::vector<AniT> Sprites;
	virtual ~Basic_Tile_MOTHER();
	Basic_Tile_MOTHER();
	//This is all the animation variables.
	float ticks = 0;
	float max_ticks = 0.5;
	int svectorindex = 0;
	
	//This is the vector that holds all the extra parameters that need to be saved in a file.
	std::vector<int> SavedParameters;
	unsigned int lightingint;
public:
	float getx();
	float gety();
	//This will delete a tile with the given x and y cordiantes.
	//It will return false if no tile was found with the given cordinates.
	//It will return true if a tile was found.
	static bool deletetile(int x, int y);
	//This will delete all the tiles contained in this class.
	static void deleteAll();
	
	//This holds all the pointers to the tile objects that are collidable.
	static std::vector<Basic_Tile_MOTHER *> Basic_Tile_MOTHER::ColTiles;
	//This holds all the pointers to the tile objects that are collidable and have an animation to them.
	static std::vector<Basic_Tile_MOTHER *>  Basic_Tile_MOTHER::ColAniTiles;
	//This holds all the pointers to the tile objects that are not collidable.
	static std::vector<Basic_Tile_MOTHER *> Basic_Tile_MOTHER::NonColTiles;
	//This holds all the pointers to the tile objects that are not collidable also are in the foreground.(Drawn after everything else.)
	static std::vector<Basic_Tile_MOTHER *> Basic_Tile_MOTHER::NonColTiles_FORE;
	//This holds all the pointers to the tile objects that are not collidable BUT they have an animation to them.
	static std::vector<Basic_Tile_MOTHER *> Basic_Tile_MOTHER::NonColAniTiles;
	//This holds all the pointers to the tile objects that are not collidable BUT they have an animation to them.
	static std::vector<Basic_Tile_MOTHER *> Basic_Tile_MOTHER::NonColAniTiles_FORE;

	//This holds all the pointers to the projectile collidables.
	static std::vector<Basic_Tile_MOTHER *> Basic_Tile_MOTHER::ColProjectiles;
	//These are all the sprites, in the entire game.
	//first index = type of texture you are using.
	//second index = type of sprite it is.(like for a wall?, or a background?).
	//third index = type of animation it is.
	//fourth index = type of AniT it is.
	static std::vector<std::vector<std::vector<std::vector<AniT>>>> Basic_Tile_MOTHER::All_Sprites; 
	//This holds all the sprite objects for the Walls.
	/*static std::vector<ST> Basic_Tile_MOTHER::WallSprites;
	//This holds all the sprite objects for the Backgrounds.
	static std::vector<ST> Basic_Tile_MOTHER::BackgroundSprites;
	//This holds all the sprite objects for the Shops.
	static std::vector<ST> Basic_Tile_MOTHER::ShopSprites;
	//This holds all the sprite objects for the Stairs.
	static std::vector<ST> Basic_Tile_MOTHER::StairSprites;
	//This holds all the sprite objects for the AniBgs.
	static std::vector<std::vector<AniT>> Basic_Tile_MOTHER::AniBgSprites;
	//This holds all the sprite objects for the SaveStations.
	static std::vector<AniT> Basic_Tile_MOTHER::SaveStationSprites;
	//This holds all the sprite objects for the Door.
	static std::vector<ST> Basic_Tile_MOTHER::DoorSprites;
	//This holds all the sprite objects for the Foregrounds.
	static std::vector<ST> Basic_Tile_MOTHER::ForegroundSprites;
	//This holds all the sprite objects for the chests.
	static std::vector<std::vector<AniT>> Basic_Tile_MOTHER::ChestSprites;
	//This holds all the sprite objects for the corners.
	static std::vector<std::vector<AniT>> Basic_Tile_MOTHER::CornerSprites;
	//This holds all the sprite objects for the PSwitchs.
	static std::vector<std::vector<AniT>> Basic_Tile_MOTHER::PSwitchSprites;
	//This holds all the sprtie objects for the Seals.
	static std::vector<ST> Basic_Tile_MOTHER::SealSprites;
	//This holds all the sprite objects for the RTiles.
	static std::vector<std::vector<AniT>> Basic_Tile_MOTHER::RTileSprites;
	//This holds all the sprite objects for the P_Spawner_Consts.
	static std::vector<std::vector<AniT>> Basic_Tile_MOTHER::P_Spawner_ConstSprites;
	//This holds all the sprite objects for the PTiles.
	static std::vector<std::vector<AniT>> Basic_Tile_MOTHER::PTileSprites;*/
	
	//This is for making all the sprites for walls and backgrounds.
	static void init(sf::Texture &tex);
	//This function will loop through all the basic tile objects and reset all the lighting.
	//Might take a bit of time to do. It is RECOMMENDED that you thread this function.
	static void ResetAllLighting();
	//This will draw all of the sprites to the window given.
	static void Drawall(sf::RenderWindow &win);
	//This will draw all the foreground sprites.
	static void DrawForeGround(sf::RenderWindow &win);
	//This will check all the special collision types.
	//The ones that directly modify the player's variables.
	//Returns true if it has found a special tile.
	//Returns false if you have stepped on something like a Background tile.
	static bool CheckSpecialCollision(int PlayerChannel);
	//This checks to see if a projectile has hit a projectile affecting tile.
	static bool CheckProjectileCollision(Projectile &P, int direction);
	//This checks to see if you have collided with anything at the given cordinates.
	static bool CheckCollision(int Your_xpos, int Your_ypos, bool isPlayer = false, bool isProjectile = false);
	//This checks to see if you have a tile over lapping another tile.
	static bool Check_Overlap(int Yourx_pos, int Youry_pos);
	//This gets the string nessasary for saving the world to a text file.
	static std::string GetSave();
	//This loops through the animation section to change dem all.
	static void mainanimate();
	
};

