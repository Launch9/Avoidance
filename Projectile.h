#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "ParticleSettings.h"
#include <functional>
#include <mutex>
//#include "Sub_NPC_A.h"

class Projectile
{
private:
	
	bool b1 = false;
	bool b2 = false;
	bool b3 = false;
	bool b4 = false;
	//This actually kills the projectile.
	void actually_kill();
	//This checks all directions to see if there are any enemies around.
	//This is used for the green projectile.
	void check_direction_green();
	static int Projectile::Rindex;
	
	struct rect: public sf::Drawable {
	private:
		//This tells the computer to see if the rectangle is expanding or not.
		//If it is expanding, it cannot be deleted by the rectangle deleter thing; Yeah.
		bool isDoneExpanding = false;
		//This tells the computer if the rectangle has made a collision or not, at all in its life time.
		bool hasMadeCollision = false;
		float lengthofrect = 0;
		float x = 0;
		float y = 0;
		float width = 0;
		float height = 0;
		sf::VertexArray vertices;
		void rect::mapCords() {
			vertices[0].position = sf::Vector2f(x,y);
			vertices[1].position = sf::Vector2f(x + width, y);
			vertices[2].position = sf::Vector2f(x + width, y + height);
			vertices[3].position = sf::Vector2f(x, y + height);

		}
	public:
		
		float sx = 0;
		float sy = 0;
		float cx = 0;
		float cy = 0;
		bool ParticleProducing = false;
		//Default constructor
		rect() {
			vertices = sf::VertexArray(sf::Quads, 4);
		}
		void rect::setPosition(const sf::Vector2f &p) {
			x = p.x;
			y = p.y;
			vertices[0].position = p;
			vertices[1].position = sf::Vector2f(p.x + width, p.y);
			vertices[2].position = sf::Vector2f(p.x + width, p.y + height);
			vertices[3].position = sf::Vector2f(p.x, p.y + height);
		}
		void rect::setPosition(const float &x_pos, const float &y_pos) {
			x = x_pos;
			y = y_pos;
			mapCords();
		}
		const bool &rect::getisDoneExpanding() {
			return isDoneExpanding;
		}
		void rect::DoneExpanding() {
			isDoneExpanding = true;
		}
		const bool &rect::gethasMadeCollision() {
			return hasMadeCollision;
		}
		void rect::MadeCollision() {
			hasMadeCollision = true;
		}
		const float &rect::getlength() {
			return lengthofrect;
		}
		void rect::setlength(const float &new_length) {
			lengthofrect = new_length;
		}	
		void rect::setSize(sf::Vector2f v) {
			width = v.x;
			height = v.y;
			mapCords();
		}
		float rect::getWidth() {
			return width;
		}
		float rect::getHeight() {
			return height;
		}
		float rect::getX() {
			return x;
		}
		float rect::getY() {
			return y;
		}
		std::vector<sf::Vector2f> rect::getGlobalBounds() {
			return{ sf::Vector2f(vertices[0].position.x,vertices[0].position.y),sf::Vector2f(vertices[1].position.x,vertices[1].position.y)
			,sf::Vector2f(vertices[2].position.x,vertices[2].position.y),sf::Vector2f(vertices[3].position.x,vertices[3].position.y) };
		}
		virtual void rect::draw(sf::RenderTarget& target, sf::RenderStates states) const {
			states.texture = NULL;
			target.draw(vertices);
		};
		void setColor(sf::Color c) {
			vertices[0].color = c;
			vertices[1].color = c;
			vertices[2].color = c;
			vertices[3].color = c;
		}
		
	};
	float speed = 0;
	bool rectsubtract = 1;
	float rounddif = 0;
	float rectshrinkdif = 0;
	//This is the sound that is played whenever the projectile hits an NPC.
	sf::Sound sound;
	//This tells how many enemies the projectile has made collision with.
	int HowManyEnemies = 0;
	int type = 0;
	//Tells the computer whether or not the projectile is ready to die.
	bool isDead = false;
	//Tells the computer whether or not to break from a switch statement after checking for collision.
	bool SHOULDBREAK = false;
	//Tells the computer whether or not to keep going an extra 16 pixels for a nice smooth curve.
	bool extra16 = false;
	//Tells the computer whether or not to start the projectile lower closer to the center of the block before changing direction.
	//made true after extra16 is done.
	bool extra16done = false;
	//This holds the direction that needs to held for the extra16 curve.
	int reservedirection = 0;
	//X pos
	float x = 0;
	//Y pos
	float y = 0;
	//This tells where the rectangle started.
	float x2 = 0;
	//This tells where the rectangle started.
	float y2 = 0;
	//This tells where the rectangle should extend to.
	float x3 = 0;
	//This tells where the rectangle should extend to.
	float y3 = 0;
	
	float voltage = 0;
	//This tells what the setting for the particles should be once it hits a wall.
	ParticleSettings PSet;
	//This is the default PSet if you choose not to have any particles.
	static ParticleSettings Projectile::Default_PSet; //This is initialized in the init() function.
	//This tells where the projectile collision cordinates are.
	//This is used for static collision! Not dynamic.
	int cx = 0;
	//This tells where the projectile collision cordinates are.
	//This is used for static collision! Not dynamic.
	int cy = 0;
	//This tells to see how many times the projectile has passed 32 pixels.
	//Important for collision detection.
	int passed = 0;
	//This is the length of the bullet.
	//float length = 0;
	//This is the max length of the bullet.
	float max_length = 50;
	//Vector full of the rectangles that make up the projectile.
	std::vector<rect> Rectangles;
	//Vector full of directions.
	std::vector<int> directions;
	//The color that the rectangles are.
	sf::Color color;
	//This is the base color. (Color that it started as.)
	sf::Color base_color;
	//Sprite at the tip of the projectile.
	sf::Sprite tip;
	//This is the width of the projectile.
	int width = 5;
	//This is the middle of the projectile.
	float middle = (32 / 2) - (width / 2);
	//This checks to see if there is collision between the parameters given, and any rectangles the projectile object owns.
	//This checks in the center of the given parameters.
	
	bool CheckCollisionLight(float x_pos, float y_pos, float w, float h, bool should_add_enemy);
	//This checks to see if there is collision between the parameters given, and any rectangles the projectile object owns.
	//This checks in the (rightmiddle,topmiddle,leftmiddle,bottommiddle) points of the given parameters.
	//Will return -1 if did not find collision.
	//Will return index of collided projectile did collide.
	bool CheckCollisionHeavy(float x_position, float y_position, float w, float h, float threshold, bool should_add_enemy);
	//This checks if any vertices of the projectile are within the box of the given parameters.
	//Will return -1 if did not find collision.
	//Will return index if collided projectile did collide.
	bool CheckCollisionHeavy2(float x_position, float y_position, float w, float h, float threshold, bool should_add_enemy);
	//This does all the calculations to the projectile.
	void tick(int index);
	//This draws the projectile.
	void draw(sf::RenderWindow &win);
	//This tells the program if the projectile is ready to be deleted or not.
	bool ready_to_delete = false;
	//These are booleans that tell what special effects each projectile has.
	bool is_ghost = false; //If this is true, then the projectile will go through all walls, but once it has reached a given distance, it will be killed.
	bool is_piercing = false; //If this is true, then the projectile will go through all NPCs, but it will still hurt them.
	//This loops through and checks to see which projectiles need to be deleted.
	static void check_all();
public:
	
	static std::vector<Projectile> Projectile::VP;
	//This gets the direction the projectile is going.
	int getDirection();
	//This returns the collision x cordinate for static collision detection.
	int getcx();
	//This returns the collision y cordinate for static collision detection.
	int getcy();
	//This sets the x cordinate.
	void setx(int new_x);
	//This sets the y cordinate.
	void sety(int new_y);
	//This gets the type of the projectile.
	int gettype();
	//Changes direction of the projectile.
	//Making extra true, will make it have a smooth curve.
	//Making extra false, will make it change directions and have an empty block inbetween changing.
	void changedirection(const int &new_direction, const bool &extra, const bool &particles);
	//The given parameters is telling why you killed the projectile.
	//The reason for this is for example, if it were a peirciing projectile, then it would not stop if the reason for destroying it was because of an NPC.
	//If it was a ghost projectile then it would pass through walls.
	//0 = Went too far away from the character
	//1 = Wall
	//2 = NPC
	void kill(unsigned int reason);
	//This tells if the projectile is piercing or not. (Able to go through enemies without the projectile dying).
	bool get_is_piercing();
	//This tells if the projectile is a ghost or not. (Able to go through walls.)
	bool get_is_ghost();
	//This is called when 32 pixels have been surrpassed by the laser.
	void call32();
	//This is a constructor.
	//A projectile is a colored laser that goes in a direction and hits other objects in the map.
	Projectile(const int &type_of_projectile, const int &startx, const int &starty, const int &Direction, bool should_make_particles = true);
	//This function ticks all the projectiles in the program.
	static void tickall();
	//This function will draw all the projectiles to the given window.
	static void drawall(sf::RenderWindow &win);
	//This adds one enemy collision.
	void addEnemy(int how_many);
	//This gets the voltage of the projectile.
	//The higher the voltage, the more damage it does to whatever it is colliding to.
	float getVoltage();
	//This sets the voltage of the projectile.
	void setVoltage(float new_voltage);
	//This dynamicly checks for collision.
	//Will return -1 if did not find collision.
	//Will return index of collided projectile if did collide.
	//2-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	//This checks to see if there is collision between the parameters given, and any rectangles the projectile object owns.
	//This checks in the (rightmiddle,topmiddle,leftmiddle,bottommiddle) points of the given parameters.
	static int DynamicCheckCollisionHeavy(float x_pos, float y_pos, float widthofrect, float heightofrect, float threshold, bool should_add_enemy);
	//This checks if any vertices of the projectile are within the box of the given parameters.
	//Will return -1 if did not find collision.
	//Will return index if collided projectile did collide.
	static int DynamicCheckCollisionHeavy2(float x_pos, float y_pos, float widthofrect, float heightofrect, float threshold, bool should_add_enemy);
	//This dynamicly checks for collision.
	//Will return -1 if did not find collision.
	//Will return index of collided projectile if did collide.
	//2-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	//This checks to see if there is collision between the parameters given, and any rectangles the projectile object owns.
	//This checks in the center of the given parameters.
	static int DynamicCheckCollisionLight(float x_pos, float y_pos, float widthofrect, float heightofrect, bool should_add_enemy);
	//This clears the world of all projectiles.
	static void clear_all();
	
	//This initializes everything.
	static void init();
};

