#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Color.hpp>
#include <thread>
#include "Temporarytxt.h"
#include <vector>
#include "Wall.h"
#include "ChoiceRTEXT.h"
#include "Basic_Tile_MOTHER.h"
#include "Cam.h"
#include <functional>
#include "CT.h"
#include "TempText.h"
#include <atomic>
#include "Scoring.h"
using namespace std;
class Player
{
private:
	//This is the difficulty level.
	//-1 = has not made slot yet.
	//0 = easy
	//1 = normal
	//2 = hard
	int difficulty = -1;
	//This is the scoring object that keeps track of how many points you have and the time you have been in a dungeon.
	Scoring scoring;
	//This is the base distance. This variable does not change while you are walking.
	int basedist = 0;
	//This resets the bounce variables.
	void resetBounce();
	//This is how high you have bounced so far.
	//current_bounce_height
	float c_bounce_height = 0;
	//last_bounce_height
	float l_bounce_height = 0;
	//This is how far into the movement the player is.
	//This is reset everytime the player calls the move function.
	float how_far = 0;
	//This is the bounce animation reserve number.
	float b_ani_r = 0;
	//This determines if the bouncing animation is moving up, or moving down.
	bool is_bounce_moving_down = false;
	//This tells if the player is in a bouncing form of movement.
	bool isBounce = false;
	
	//This is a text that appears when you gained an item or something of the sort.
	TempText text;
	int lives = 3; //These are how many lives you have.
	//This is the pickaxe sprite that is used when mining something.
	CT pickaxe;
	//This is how much you can shoot.
	//Once this runs out, you are no longer able to shoot projectiles.
	int fuel = 100;
	std::vector<std::function<void(Player *)>> Player::AEF;
	//This is the type of gauntlet you are using.
	int Gtype = -1;
	//These are the gauntlet ids that are allowed to be used by the player.
	std::vector<int> ObtainedGauntlets = {};
	//These are the gauntlet ids that are displayed.
	std::vector<int> DisplayedGauntlets = {};
	//This is the iterator used for determining what gauntlet you are going to be using.
	int OGindex = 0;
	//This tells the animate function if it is doing a "doAnimation".
	bool isdAni = false;
	//This tells the animate function what function to call after being done with the animation.
	int d_index = 0;
	//0 = up, 1 = right, 2 = down, 3 = left.
	std::vector<bool> Controls = { false, false, false, false };
	//This is a vector that holds the sprites that are being animated right now.
	std::vector<AniT> CurrentAni;
	//This is a vector that holds the sprites that can be put into the CurrentAni vector.
	std::vector<std::vector<AniT>> AniSprites;
	//This is a vector that holds the sprites that can be used in the doAnimation function.
	//Animations that consist of standing still whilst doing.
	static std::vector<std::vector<AniT>> Player::doAniSprites;
	//These are the sprites that are used for unclassified things. They just don't fit well with the other vectors.
	static std::vector<std::vector<AniT>> Player::extraAnisprites;
	//ANIMATION VARAIBLES-=-=-=-=-==-=-=-==-=-//
	int svectorindex = 0;
	float tick = 0;
	float max_tick = 0;
	//-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-//
	//This function sets the variables that are responsible for the animation of the player sprite.
	void animate();
	//This function sets all the current animation sprites to the desired cordinates.
	void Aniset_XY(const float &x_cordinate, const float &y_cordinate);
	//This function changes all the current animation sprites to the desired vector.
	void changeAni(const int &index);
	//This function stops the animation of walking sliding etc, and it resets a whole bunch of variables.
	//If should_check_special_collision is true, then it will check for special collision... obviously.
	void stop_ani(bool should_check_special_collision = true);
	//This function is used to determine if the player is waiting to shoot.
	//Should be called every tile completion.
	//If returned true, then the player did want to fire a projectile, and it has been fired.
	//If returned false, then the player did not want to fire a projectile.
	bool check_pending_shoot();
	//This function will make all the lambda functions needed for proper animation treatment.
	//Call this function once you have made a player object.
	void make_lambda_functions();
	//This is the Floor you are on.
	int Floor = 0;
	//This is the type of dungeon you are in.
	int Dungeon = 0;
	//This is the story step that the player is on.
	int Step = 0;
	unsigned int deathtick = 0;
	unsigned int deathtickmax = 20;
	unsigned int bulletid = 0;
	//These are variables that tell what is currently happening to the player.
	bool isSliding = false;
	bool isDead = false;
	int slidingrep = 1; //How manys times you have passed a tile while sliding.
	int slideamount = 2 * 32;
	int slideamountbase = 2 * 32;
	int walkamount = 32;
	//This is the time that is kept hold for informational purposes.
	float Time = 0;
	//GROUP-SPEEDS=========================================
	//This is the walking speed.
	float speed = 300;
	//This is the REAL walking speed. The one that you can modify right here.
	float RealWalkSpeed = 3;
	//This is the sliding speed.
	//The slide speed is a multiplication/division of the walking speed.
	int slidespeed;
	//END-SPEEDS
	void continuemoving();

	//The font
	sf::Font font;
	//The x and y cordinates are for where the collision detection happen.
	int x;
	int y;
	//vx and vy stand for visual x and visual y. They are the position the image is drawn.
	float vx;
	float vy;
	//These are for the starting position of the player. He goes back here if he dies.
	int xstartp;
	int ystartp;
	float sx = 0;
	float sy = 0;
	
	bool isstartmoving = false;
	int distance = 0;
	int spacestraveled = 0;
	//This tells you how many dungeons you have passed in the game so far.
	int how_manyDungeons = 0;
	float movinganitick;
	int movingdirection;
	//This is how much powerfuel you have.
	//This is made atomic because it is used in a thread for the NPCs.
	std::atomic<float> powerfuel = 0;
	//This is how much powerfuel you need to be able to use your power shot.
	float max_powerfuel = 20;
	//These are a players stats.
	int health;
	float pick_angle = 0;
	//This is the type of pickaxe animation that is going.
	int pickaxe_ani_type = 0;
	//PSprite stands for what the players sprite is.
	ST PSprite;
	//This is what is called when you first start the pickaxe animation.
	void start_pickaxe(int type);
	//This is what is called for the pickaxe animation, it determines where the pickaxe is suppost to be and how it should be rotated according to the frame.
	void update_pickaxe();
	//This is called when the pickaxe animation is done.
	void stop_pickaxe();
	//This sets the pickaxe's position and rotation based on the given parameters relative to the player's cordinates.
	void set_pickaxe_position(float pick_angle, float distance_from_player, float pickaxe_degree);
	//Controls
	int buttonlayout;
	int anisetnum;
	//This is for determining if you are currently shopping at a shop.
	bool Shoppingtog = false;
	//Colors
	int white[3] = { 255,255,255 };
	int black[3] = { 0,0,0 };
	int blue[3] = { 0,0,255 };
	int red[3] = { 255,0,0 };
	//This is for locking the players controls.
	bool CLock = false;
	//Inventory variables
	vector<int> inventory = {};
	//This is a boolean for if the inventory is suppost to be open or not.
	bool inventorytog = false;
	static sf::Sprite Player::s321;
	sf::Sprite s123;
	//This is the sound that plays everytime you slide.
	sf::Sound SlideSound;
	//This is the sound that plays when you die.
	sf::Sound DeathSound;
	//This is the choice object.
	ChoiceRTEXT Co;
	//This tells the computer whether or not the NPC is ready to stop moving.
	bool readystop = false;
	//This is the waiting to shoot direction integer.
	//If you are moving and want to shoot, then it keep the direction you shot while moving and do the action once stoped.
	int shootingdirection_r = -1;
	//This tells that you should be stationary and it should run the constanimation walk routine even if the movingdirection == -1.
	bool const_ani_override = false;
	//This is for checking sliding collisions.
	//If it gives true then it is having a collision.
	static bool Checkslidingcollision(const int &your_x_position, const int &your_y_position);
	//This makes sure that the displayed gauntlets are displaying what they should.
	//This should be called whenever changing the obtained guantlets.
	void updateGauntlets();
	//This stops the current dAni.
	void stop_Dani();
	//This tells if you are ready to shoot your powershot.
	//This is a toggle that is switched on and off by a keyboard button.
	bool is_ready_for_powershot = false;

	//This calculates the bounce mechanism.
	void calculate_bounce(int direction);
	//This integer is used to tell what part of the story you are in.
	int storyID = 0;
public:
	//This will return true if the the player is in a dungeon.
	//Otherwise, this will return false.
	bool get_is_in_dungeon();
	//This gets the scoring object in a read only fashion.
	Scoring &getScoring();
	//This sets the storyID to the given integer.
	void setStoryID(int new_ID);
	//This gets the storyID.
	int getStoryID();
	//This tells the computer whether or not you have shot something since changing gauntlets.
	bool hasShot = false;
	//This holds all the player objects for the channels.
	static vector<Player *> Player::PlayerObjects;

	static std::vector<std::vector<std::vector<AniT>>> Ani_Sets;
	//0 = W,A,S,D
	//1 = Up,Down,Left,Right
	//The walkspeed variable must be given a number divisorable by 2 or it will give a default integer or 4.
	Player(const int &xstart, const int &ystart, const int &hlth, const int &walkspeed, const int &animationset, const sf::Font &fon, const int &buttoncontrols);
	//Adding a new difficulty will set the player's difficulty to said integer.
	//Otherwise, it will keep it at it's normal difficulty.
	//However, if the difficulty is -1 in the file, as if you haven't ever loaded up the file before, then the action is undefined.
	//Most likely crash.
	Player(string SavedFile, TileMap &TM, int new_difficulty = -1);
	//This function returns the diffculty integer.
	int get_difficulty();
	//This function will look at the player file given, and will return the difficulty integer.
	static int get_difficulty_from_file(const std::string &playerFile);
	void set_Ready();
	//This function adds fuel to the player, so that the player can shoot projectiles again.
	void addFuel(const int &howMuch);
	//This will decrease one of the player's lives without calling the Die function.
	//This will return true if the player's lives can't go down anymore.
	//Otherwise, this will return false.
	//The lowest_Life_limit parameter tells when it should stop going down.
	bool loseLife(int lowest_Life_limit);
	//This will set the player's lives to the desired amount.
	void setLife(int new_life_amount);
	//retruns x cordinate(cordinate used for collision).
	int getx();
	//retruns y cordinate(cordinate used for collision).
	int gety();
	//returns visual x cordiante(cordinate that the sprite is at).
	float getvx();
	//returns visual y cordiante(cordinate that the sprite is at).
	float getvy();
	//This will set the listen to the player's vx and vy cordinates
	void snapListener();
	//Collision detection happens here!
	unsigned int moveup(const int &amount);
	//Collision detection happens here!
	unsigned int movedown(const int &amount);
	//Collision detection happens here!
	unsigned int moveleft(const int &amount);
	//Collision detection happens here!
	unsigned int moveright(const int &amount);
	//Collision detection happens here!
	//This bounces the player in one direction.
	unsigned int bounceup(const int &amount);
	//Collision detection happens here!
	//This bounces the player in one direction.
	unsigned int bouncedown(const int &amount);
	//Collision detection happens here!
	//This bounces the player in one direction.
	unsigned int bounceleft(const int &amount);
	//Collision detection happens here!
	//This bounces the player in one direction.
	unsigned int bounceright(const int &amount);
	//Collision detection happens here!
	//The slide speed is a multiplication of the walkspeed.
	//amount is converted to spaces, instead of pixels.
	void slideup(const int &amount);
	//Collision detection happens here!
	//The slide speed is a multiplication of the walkspeed.
	//amount is converted to spaces, instead of pixels.
	void slidedown(const int &amount);
	//Collision detection happens here!
	//The slide speed is a multiplication of the walkspeed.
	//amount is converted to spaces, instead of pixels.
	void slideleft(const int &amount);
	//Collision detection happens here!
	//The slide speed is a multiplication of the walkspeed.
	//amount is converted to spaces, instead of pixels.
	void slideright(const int &amount);
	//This is for shooting right.
	void shootright();
	//This is for shooting down.
	void shootdown();
	//This is for shooting left.
	void shootleft();
	//This is for shooting up.
	void shootup();
	//This gets the collision detection variable of x cordinate.
	//It will calculate the position the player will be in after the animation for walking is done.
	int getcx();
	//This gets the collision detection variable of y cordinate.
	//It will calculate the position the player will be in after the animation for walking is done.
	int getcy();
	//This is for changing the type of gauntlet the player is using.
	void addGtype(const unsigned int &addition);
	//This is for changing the type of gauntlet the player is using.
	void subGtype(const unsigned int &subtraction);
	//This adds a gauntlet to the players list.
	void addGauntlet(int ID);
	//This is used for animation and smooth movement.
	//Camera movement happens here!
	void constanimation(const int &camera_channel, bool camlock = false);
	void drawPSprite(sf::RenderWindow &win);
	void setXY(const float &xf, const float &yf);
	bool getSliding();
	void changeaniset(const int &index);
	int getdirection();
	//This adds power to the powerfuel variable.
	void addPower(float how_Much);
	//This function gets the amount of fuel the playerh has.
	float getPower();
	bool GetShoppingtog();
	//This is for when you get close to a shop.
	void Shop(const int &PlayerChannel);
	//This is for opening the inventory and using things.
	void Openinventory();
	std::vector<int> getinventory();
	void addinventoryitem(const int &itemid);
	void useitem(const int &itemindex);
	//This gives the player an item by ID.
	void giveItem(int ID);
	//This sets the ChoiceText to its proper place.
	void SnapChoice();
	//This gets the amount of fuel the player has left.
	int getFuel();
	//This gets the sx variable from the player object.
	float getsx();
	//This gets the sy variable from the player object.
	float getsy();
	//This gets the amount of lives the player has.
	int getLives();
	//This gets the max amount of fuel the player can have.
	int get_maxFuel();
	//This gets the max amount of power the player can have.
	float get_maxPower();
	//This gets the obtained gauntlet vector.
	const std::vector<int> &get_Obtained_Gauntlets();
	//This is for adding lives.
	void addLives(int amount);
	//This makes the player stand still.
	//This is a special function used very rarely.
	//Mostly just for the world animations.
	void StandStill();
	//These functions set variables within the object to the desired amount.
	void setinventorytog(const bool &TF);
	void setCLock(const bool &TF);
	void setShoppingtog(const bool &TF);
	std::vector<int> const &getDisplayGauntlets();
	void Die();
	bool GetDeath();
	//This gets the integer telling you how many dungeons the player has gone through in the game.
	int get_how_manyDungeons();
	//This tells the player object that it has completed another dungeon.
	void add_dungeon();
	void SnapCam();
	void setFloor(const int &New_Floor);
	void setDungeon(const int &New_Dungeon);
	int getFloor();
	int getDungeon();
	void doAnimation(const int &type, bool should_overwrite);
	//This function will load up a player file and set the x and y cordinates and other variables accordingly.
	void LoadPlayerFile(string File);
	//This function will save the variables of a player onto a file to be used later.
	void SavePlayerFile(std::string File);
	static void init(sf::Texture &tex);
	//This will delete the player object from the world.
	//Only use this if you know what you are doing!
	static void deleteALL();
	//This function gets the walk_speed of the player object.
	float getWalk_Speed();
	//This tells you if the player is doing an doAnimation animation.
	//Will return true, if the are doing a doAnimation animation; Otherwise, it will return false.
	bool is_DoingAnimation();
	//This will return true if the player is ready to fire the special shot.
	//This is only true of the player's choice, it may be true but the player may not be able to shoot it because he lacks required power fuel.
	bool is_powershot_ready();
	//This tells you what story step the player is on.
	int getStep();
	//This sets the story step.
	void setStep(int new_Step);
};

