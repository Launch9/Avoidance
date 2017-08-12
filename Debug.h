#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "TileMap.h"
class Debug
{
private:
	//This is the last command you entered in.
	//This can be used again by calling the uselastcommand function.
	static std::string Debug::lastCommand;
	//This will convert the given string into a float and return it.
	static float StringtoFloat(std::string string);
	//This will convert the given string into an integer and return it.
	static int StringtoInt(std::string string);
	//This will convert the given string into an unsigned int and return it.
	static unsigned int StringtoUnint(std::string string);
	//This will loop through and find the characters you want.
	//The integer given will be the amount of times it will pass one of the characters specified until it gives the index.
	//If the number of passes is not given, it will give the first character it finds that matches.
	static int FindChar(char c, int NumberofPasses = 0);
	//This will give the number of characters in the Command.
	static int FindNumChars(char c);
	//This will loop through the command and determine what needs to be the RootCommand and whats the parameters.
	static void DecipherCommand();
	//This is a function that is used during Debug Menu time.
	//It will clear everything command bases and give an error in the Menu.
	//THIS DOES NOT THROW AN ERROR. IT GIVES IT IN GAME.
	static void ThrowError(std::string ErrorReport);
	static sf::Font Debug::Font;
	static bool Debug::isMenuOpen;
	static std::string Debug::Command;
	static std::string Debug::RootCommand;
	static std::vector<std::string> Debug::Parameters;
	static std::vector<sf::Text> Debug::PermText;
	static std::vector<sf::Text> Debug::Texts;
	static std::vector<sf::VertexArray> Debug::Lines;
	static std::vector<sf::RectangleShape> Debug::PermRects;
	static std::vector<sf::RectangleShape> Debug::Rects;
	static sf::Text Debug::CommandText;
public:
	//This will setup the last command given in the debug menu.
	static void setlastcommand();
	//This will immediately use the last command given in the debug menu.
	//The Menu does not even have to be open for this to have an effect.
	static void uselastcommand(sf::RenderWindow &win, TileMap &TM);
	//This function will clear the command window.
	static void Clearcommand();
	//This gives the option of opening or closing the Debug menu.
	static void SetDebugMenu(sf::RenderWindow &win, bool TF);
	//This function returns true if the Debug Menu is open. False otherwise.
	static bool GetMenuOpen();
	//This will add a character to the command vector.
	static void AddCommandChar(char c);
	//This will delete that last letter of the string in the command.
	static void Backspace();
	//This will initiate the command in the vector at the given moment.
	static void UseCommand(sf::RenderWindow &win, TileMap &TM);
	//This function draws a rectangle at the given position.
	//This is used for determining where x and y positions are and other things.
	static void SquareDraw(float x_pos, float y_pos, int width = 10, int height = 10);
	//This function draws a line given the two points.
	static void LineDraw(const sf::Vector2f point1, const sf::Vector2f &point2, const sf::Color &color);
	//This function makes the decision to open the debug menu or not.
	//This function also moves the positions of all the text and rectangles to be used for debugging later on.
	static void tick();
	//This function draws all the text and rectangles.
	static void draw(sf::RenderWindow &win);
	static void init(sf::Font f);
};

