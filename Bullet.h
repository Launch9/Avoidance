#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
/*The bullet class used its own animation system.*/
class Bullet
{
private:
	//This is the sound buffer for all the sounds the bullets will be making.
	static sf::SoundBuffer Bullet::SBuffer;
	//This vector stores all the sprites that are built into this class(When you call for a bullet id).
	static std::vector<std::vector<sf::Sprite>> Bullet::s;
	//This vector stores all the sounds that the projectile makes.
	static std::vector<std::vector<sf::SoundBuffer>> Bullet::sound;
	static std::vector<Bullet> Bullet::BObjects;
	//This is the vector full of sprites that the bullet is going to loop through.
	std::vector<sf::Sprite> sprites;
	//This is the direction the bullet is going.
	unsigned int direct;
	//This is the speed of the bullet.
	int speed;
	//These are the x and y cordinates.
	int x;
	int y;
	//This variable is used for the animation purposes.
	int spriteindex = 0;
	//This variable is used for determining when to change the sprite index.
	unsigned int ticks = 0;
	//This variable is used to tell how many ticks is required to change the sprite.
	unsigned int tick_limit = 0;
	//These functions get variables from the objects.
	//They get the adress of the variable. Not a copy!
	int &getx();
	int &gety();
	int &getspeed();
	unsigned int &getdirection();
	int &getspriteindex();
	unsigned int &getticks();
	unsigned int &gettick_limit();
	std::vector<sf::Sprite>& getsprites();
public:
	//This is how you create a projectile on the screen.
	//Leave the speed to default if you want the default of what ever bullet you used.
	//Giving a speedchange integer will change the bullet speed relative to whatever the default is for that bullet.
	//Giving a speed integer will change the bullet speed not relative to the default. 
	//The direction integer you choose goes like so.[0 = Right, 1 = Down, 2 = Left, 3 = Up]
	Bullet(int bulletx, int bullety, unsigned int direction, unsigned int bulletid, int bulletspeed = -1, int speedchange = 0);
	//This is used to make all the sprites for all the built in bullets.
	static void init(sf::Texture &tex);
	//This function moves all the bullet sprites.
	static void tick();
	//This function will draw all the bullet sprites.
	static void draw(sf::RenderWindow &win);
};

