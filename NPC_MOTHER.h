#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "CT.h"
#include "AniT.h"
#include "TileMap.h"
#include "Room.h"
#define base32 32
class Room;
class NPC_MOTHER
{
private:
	//This loops through the objects_to_be_put vector and moves everything into the objects_to_be_deleted vector properly.
	static void check_OTBP();
	static float NPC_MOTHER::GlobalSpeed; //This is the speed magnifier of all NPCs.
	unsigned int PlayerChan = 0;
	
	static std::vector<NPC_MOTHER *> NPC_MOTHER::Objects_to_be_deleted; //This is a vector full of pointers that should be deleted when the level changes, or the delete_ready function is called.
	static std::vector<NPC_MOTHER *> NPC_MOTHER::Objects_to_be_put; //This is a vector full of pointers that should be put in the 
	//This is a function that ticks the upper half of the NPC_Cache.
	static void Tick2();
	//This is a function that ticks the lower half of the NPC_Cache.
	static void Tick1();
protected:
	//This boolean tells the class to delete the object from the cache once dead. It will not be revived, the delete object is gone forever.
	bool I_Del = false;
	//This tells what index of sprites you are using.
	int ani_set_index = 0;
	bool pause_lock = false; //If this is true, you can not change whether or not the NPC is paused.
	bool is_active = true; //This tells if the NPC is active or not.
	void deactivate(); //This deactivates the NPC. And will not activate until told to do so.
	void activate(); //This activates the NPC. And will not deactivate until told to do so.
	//THIS VARIABLE IS VERY IMPORTANT!
	//This variable is used for reading the type of npc you are using.
	//This must be given a number.
	int typeID = 1;
	//This tells the computer whether or not the object has been called to be deleted yet.
	bool did_delete_self = false;
	//These are the collision integers. These are used for rough edge collision.
	//Making sure when you hit the object it looks like you actually hit the object.
	//B = Bottom
	//T = Top
	//L = Left
	//R = Right
	int RoughHeightB = 0;
	int RoughHeightT = 0;
	int RoughWidthL = 0;
	int RoughWidthR = 0;
	//This determines if the player is suppost to be killed on this tick or not.
	static bool ISPD;
	//This is a set of advanced booleans to be turned on and off.
	//ONLY USE THIS IF YOU ARE SURE YOU KNOW WHAT THEY DO.
	bool OVERRIDE_ANI = false;
	
	//These functions get the variables to see if the are on or off.
	bool getOVERRIDE_ANI();
	
	//This vector holds all the parameters that are of an NPC that need to be put into the file and read later.
	//Please insert the typeID before anything else!
	//e.g. SavedParameters = {typeID, direction, color, taste};
	//Organization does matter when placing parameters into this container!
	std::vector<int> SavedParameters;
	//This determines wether or not the npc is moving.
	bool isPaused = false;
	//This will return the distance the player and the NPC are apart.(In blocks!)
	//You decide in your tick function how far you need to be to do certain things.
	int Render(int NPCxpos, int NPCypos);
	//This changes the isPaused boolean to whatever you put in.
	//This will only work if the pause_lock boolean is equal to false.
	void setPause(bool TF);
	//This will set the x and y cordinates back to their initial state.
	//x = initx, y = inity
	virtual void reset();
	//This will set the animation set you are using the proper way.
	//You are allowed to supply a new_max_ticks, but if you do not, it will not change the max_ticks.
	void Aniset(int aniset, float new_max_ticks = -1);
	//This checks to see if the Player is sliding.
	bool CheckPlayerSliding();
	/*Use this when you want to check for collision pixel by pixel.
	This is used for something that moves around smoothly and you want to check all possible collisions.
	This takes more CPU time then static collision detection.*/
	bool DynamicCheckPlayerCollision(float NPCxpos, float NPCypos, float NPCwidth, float NPCheight);
	/*Use this when you want to check to see if a point is within the block of the player.
	This takes more CPU time then static collision detection.*/
	bool DynamicCheckPlayerCollision2(float NPCxpos, float NPCypos, float NPCwidth, float NPCheight);
	/*Use this when you want to check if the NPC is right on top of the Player.
	This will return true if the player is half way or less or higher on the sprite.
	This takes less CPU time then dynamic collision detection.*/
	bool StaticCheckPlayerCollision(int NPCxpos, int NPCypos);
	/*This is used to check to see if the is anything staticaly placed at the inital x and y cordinates of the npc.
	This is mainly used for checking tile over lap while editing.*/
	bool initStaticCheckPlayerCollision(int Yourxpos, int Yourypos);
	

	//These are a list of common functions that the derived classes would use.
	void SetSpriteColor(unsigned int Red, unsigned int Green, unsigned int Blue, unsigned int alpha);
	//This is used when you want to kill the player.
	void KillPlayer();
	//This is used to set all the sprites in the given vector to the desired position.
	void setWholePos(float x_pos, float y_pos);
	
	//These are the sprites for the lasers.
	/*static std::vector<std::vector<AniT>> NPC_MOTHER::LaserSprites;
	//These are the sprites that are used for the homingskulls.
	static std::vector<std::vector<AniT>> NPC_MOTHER::HomingSkullSprites;
	//These are the sprites for the chainballs.
	static std::vector<std::vector<AniT>> NPC_MOTHER::Chainballsprites;
	//These are the sprites for the Europa character.
	static std::vector<std::vector<std::vector<AniT>>> NPC_MOTHER::EuropaSprites;
	//These are the sprites for the skeletons.
	static std::vector<std::vector<std::vector<AniT>>> NPC_MOTHER::SkeletonSprites;*/
	//These are all the sprites, in the entire game.
	//first index = type of texture you are using.
	//second index = type of sprite it is.(like for a skeleton?, or a character?).
	//third index = type of animation it is.
	//fourth index = type of AniT it is.
	static std::vector<std::vector<std::vector<std::vector<AniT>>>> NPC_MOTHER::All_Sprites;
	
	//This is a vector full of AniT objects that can be switched back a forth depending on what animation you want to use.
	std::vector<std::vector<AniT>> Sprites;
	//This is the vector full of AniSprites that are actually animating at the moment.
	std::vector<AniT> anisprites;
	//This is the CT sprite that is actually setup.
	CT sprite;
	//This determines whether or not you can slide under the NPC.
	bool HIGH = false;
	//This is the inital x cordinate that the NPC starts at.
	int initx = 0;
	//This is the inital y cordinate that the NPC starts at.
	int inity = 0;
	//This is where the cursor needs to be to delete the NPC.
	int delx = 0;
	//This is where the cursor needs to be to delete the NPC.
	int dely = 0;
	//X cordinate of the sprite.
	float x = 0;
	//Y cordinate of the sprite.
	float y = 0;
	//This is a cordinate to use for determining how much to move the npc.
	int x2 = 0;
	//This is a cordinate to use for determining how much to move the npc.
	int y2 = 0;
	//These are for rendering purposes.
	
	//This returns the SavedParameters vector.
	std::vector<int> getSavedParameters();
	//This is used for determining direction.
	//0 = right, 1 = down, 2 = left, 3 = up.
	int direction = 0;
	//This is the current amount of ticks for the animation.
	float ticks = 0;
	//This is the number of ticks it needs to reach for the spriteindex to add an extra number.
	float max_ticks = 0.5;
	//This shows the computer what sprite to display when animating an NPC.
	int spriteindex = 0;
	//This is the index number of the vector full of sprites.
	int svectorindex = 0;
	//This function loops through all the sprites in your animation and moves the index accordingly.
	//You may redefine it if you wish.
	virtual void animate();
	//This function is called when the NPC is revived.
	virtual void when_revive();
	//This function is called when the NPC is killed or deleted_self.
	virtual void when_dead();
	//This function will draw the NPC to the screen.
	virtual void draw(sf::RenderWindow &win);
	//This is just a function that should be remade in an NPC derived class.
	virtual void tick(bool render);
	
	//This is a virtual deconstructor.
	virtual ~NPC_MOTHER();
	//This returns the a pointer to the sprite(CT).
	CT *getSpritePointer();

	friend Room;
public:
	//This returns the x integer.
	float getx();
	//This returns the y integer.
	float gety();
	//This returns the initx integer.
	int getinitx();
	//This returns the inity integer.
	int getinity();
	//This returns the delx integer.
	int getdelx();
	//This returns the dely integer.
	int getdely();
	//This returns the typeID integer.
	int gettypeID();
	//This gets the sprite's x coordinate and sprite's y coordinate.
	const sf::Vector2f &getPosition();
	//This is a static class that holds pointers to any derived class of the NPC_MOTHER class.
	static std::vector<NPC_MOTHER *> NPC_MOTHER::NPC_Cache;
	//This will delete the npc you are on.
	//Only the delx and dely will line up with them!
	//This will return true if it has deleted something.
	//It will return false if it couldn't find anything to delete.
	static bool deleteNPC(int x, int y);
	//This deletes all the tiles contained in this class.
	static void deleteAll();
	//This is what is called when you want to delete the object.
	virtual void delete_self(NPC_MOTHER * Object);
	//This revives all the npcs in the level that have not been officially "deleted".
	//This is normally called right after you die and go back to the start of the level.
	static void revive_NPCs();
	//This command will make all the npcs "pause".
	//They will go back to their original location of spawn and stop moving.
	static void PauseAllNPC();
	//This command will make all the npcs go back to moving.
	//They will starting moving from their starting location.
	static void UnPauseAllNPC();
	//This should be used outside the main game loop.
	//This will loop through all the objects and make all the sprites for them.
	//tex = enemies, ctex = characters
	static void maininit(sf::Texture &tex, sf::Texture &ctex);
	//This is the main tick function that loops through all the NPCs and ticks them.
	//This must be placed in the main loop.
	static void maintick();
	//This function returns the string required for putting it to a file.
	static std::string GetSave();
	//This function checks for the over lap of tiles.
	//This looks at the initx and inity positions of the npcs.
	static bool Check_Overlap(int Yourxpos, int Yourypos);
	//This functions takes in a window object and will draw all the NPCs to the screen.
	static void maindraw(sf::RenderWindow &win);
	//This function puts resets all the npcs and puts them back to their original locations.
	static void resetall();
	//This function pretty much tells the NPCs to go back to their origin cleanly.
	//It will reset all the npcs in a neat fashion once this class has run the tick function.
	static void setISPD();
	//This function sets the GlobalSpeed float variable of all NPCs.
	static void setGlobalSpeed(float new_speed);
	//This function gets the GlobalSpeed float variable of all NPCs.
	static float getGlobalSpeed();
	//This function deletes all the enemies that want to be deleted.
	static void delete_ready();
	//This gets the boolean telling you if the enemy is dead or not.
	bool get_is_dead();
};

