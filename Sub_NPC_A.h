#pragma once
#include "NPC_MOTHER.h"

///This class should be inherited if you want an NPC that has the movement of a player.
///Moving up,down,left, and right, tile by tile.
///This inherits the NPC_MOTHER class.

class Sub_NPC_A : public NPC_MOTHER
{
private:
	

	
	struct Move_Data {
	public:
		int direction = -1;
		int spaces = 0;
		bool is_ready = false;
		float remainder = 0;
		int Speed = 0;
		Move_Data() {

		};
	};
	
	//This contains the information sent by the player's movement.
	static Move_Data Sub_NPC_A::M_Data;
	//This checks to see if one NPC is going to move on top of another NPC assocaited with this class.
	//returns true if found a collision with another NPC.
	//returns false if it did not find a collision with another NPC.
	static bool Check_C(int sx_pos, int sy_pos);
	//This is the speed at which the sprite moves at.
	float speed = 0;
	//This is how far the sprite has moved relative to last time a move function has been called and activated.
	float howMuchDone = 0;
	
	//This tells which direction the inherited NPC is going.
	int movingdirection = -1;
	//This tells how far the inherited NPC is suppost to go.
	int movingamount = 0;
protected:
	//This will stop the animation.
	void stop_ani();
	//This will look for any open doors
	//This is the object that holds the position of the NPC for collision detection with all the NPCs in this class.
	sf::Vector2i C_position;
	//Checks to see which way it should go.
	//If it finds that a path has a wall collision, then it will try all the other directions.
	bool checkLoop(int distance, int startingdirection, int speed, float remainder);
	//This is what happens when you need the NPC to go back to its original position.
	void reset();
	
	//This gets the collision detection position for NPCs ascociated with this class.
	/*This is called when the A_tick function is called.
	It should be overwritten, only if the NPC needs to know when the player moved.*/
	virtual void ifPlayerMoved(int speed, int direction, int spaces, float remainder);
	//Default Constructor
	Sub_NPC_A();
	//Default Deconstructor
	virtual ~Sub_NPC_A();
	//This returns the quadrant the given cordiantes are relative to, in accordance to the NPC's.
	//If the are greater/less than.
	//1 = top_right, 2 = top_left, 3 = bottom_left, 4 = bottom_right.
	int findQuadrant(float x_pos, float y_pos);
	//This returns the direction the given cordinates are relative to, in accordance to the NPC's.
	//If they are equal.
	//-1 = equal_points, 0 = top, 1 = right, 2 = bottom, 3 = left.
	int findDirection(float x_pos, float y_pos);
	
	//This moves the NPC up the given amount.
	//return 0 = already moving, so did nothing.
	//return 1 = hit wall, but possibly still moving.
	//return 2 = hit no wall, continue given length.
	int moveup(int amount, float new_speed, float remainder);
	//This moves the NPC down the given amount.
	//return 0 = already moving, so did nothing.
	//return 1 = hit wall, but possibly still moving.
	//return 2 = hit no wall, continue given length.
	int movedown(int amount, float new_speed, float remainder);
	//This moves the NPC left the given amount.
	//return 0 = already moving, so did nothing.
	//return 1 = hit wall, but possibly still moving.
	//return 2 = hit no wall, continue given length.
	int moveleft(int amount, float new_speed, float remainder);
	//This moves the NPC right the given amount.
	//return 0 = already moving, so did nothing.
	//return 1 = hit wall, but possibly still moving.
	//return 2 = hit no wall, continue given length.
	int moveright(int amount, float new_speed, float remainder);
	//This moves the sprite according to the variables inherited by this class. Refer to Sub_NPC_A.
	//This is virtual and can be overwritten.
	virtual void m_tick();
	//This is called once when the class has completed its movement and is waiting for more commands.
	virtual void next();
	//This returns true or false depending on if you are moving or not.
	//returns true if you are moving.
	//returns false if you are not moving.
	bool get_isMoving();
public:
	//This is a vector full of pointers to the objects made with this class specifically.
	//These objects will be erased from the vector from the deconstructor given by this class.
	//So don't worry about getting rid of these.
	static std::vector<Sub_NPC_A *> Sub_NPC_A::Object_Cache;
	//This gets the collision detection cordinates.
	const sf::Vector2i &get_C_position();
	/*This is called whenever the player moves.
	It will call a virtual function that allows inherited member classes do specific things.*/
	static void set_moved(int speed, int direction, int num_of_spaces, float remainder);
	/*This function will run the "ifPlayerMoved" virtual function to all NPC Objects in the cache, only if
	the set_moved function was called before this call.*/
	static void A_tick();
	//This statically checks for collision. Like as: if x == x && y == y then, return index.
	//This is a faster method of checking for collision than dynamic collision detection.
	//Will return the index of the object in the Object_Cache if collision has been detected; otherwise, will return -1.
	static int StaticCheckCollision(const sf::Vector2f &position);
	//This dynamicly checks for collision. Checking if a point is within the given rectangle.
	//This one checks only a point at the center of the NPC.
	//Will return the index of the object in the Object_Cache if collision has been detected; otherwise, will return -1.
	static int DynamicCheckCollision(const sf::FloatRect &rect);


};

