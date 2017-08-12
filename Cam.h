#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Choice.h"
class Cam
{
private:
	static bool Cam::ready_to_take_screenshot;
	float x = 0;
	float y = 0;
	sf::View view;
	static float displayheight;
	static float displaywidth;
	static float displayheight_fac;
	static float displaywidth_fac;
	//This is the number of pictures you have taken so far.
	static int Cam::num_of_pics;
	inline float getx();
	inline float gety();
	//For faster speeds.
	//These give the adress of the cordinates.
	inline float &getax();
	inline float &getay();
	//This will zoom the camera in or out.
	//Give negative for out. Give positive for in.
	void zoom(float offset);
	//This is used for moving the camera.
	void scroll(float offset1, float offset2);
	//This is used to set the window's view.
	void setview(sf::RenderWindow &win);
	//This is for setting the view port.
	void setviewport(float f1, float f2, float f3, float f4);
	//This is used for setting the x and y cordinates.
	//If center is sent as true. Then it will put the center of the camera to this position.
	//If not, then the top left of the camera will be put into that position.
	void setxy(float x_pos, float y_pos, bool center);
	//This is used to draw GUI.
	void drawGUI(sf::RenderWindow &win, const sf::Drawable &drawable);
	static std::vector <Cam> Cam::CamObjects;

public:
	//This is for getting the x cordinate of the camera.(Not the center of the camera!)
	static float getx_chan(int channel);
	//This is for getting the y cordinate of the camera.(Not the center of the camera!)
	static float gety_chan(int channel);
	//This will zoom the camera in or out.
	//Give negative for out. Give positive for in.
	static void zoom_chan(int channel, float offset);
	//This is used for getting the display's height.
	static int getdisplayheight();
	//This is used for getting the display's width.
	static int getdisplaywidth();
	//INITALIZE BEFORE YOU MAKE OBJECTS!
	static void init();
	//This is for setting the viewport of the view object.
	static void setviewport_chan(int channel, float f1, float f2, float f3, float f4);
	//This is used to move the camera.
	static void scroll_chan(int channel, float offset1, float offset2);
	//This is used to set the view of a window to a camera on a specific channel.
	static void setview_chan(int channel, sf::RenderWindow &win);
	//This is used to draw a drable object to the screen that doesn't move relative to the camera.
	static void drawGUI_chan(const int &channel, sf::RenderWindow &win, const sf::Drawable &drawable);
	//This gets the <is_ready_to_take_screenshot> boolean.
	static bool get_is_ready();
	//This makes an image of the current contents on the screen, and puts it into a .png file.
	static void takeScreenShot(sf::RenderWindow &win);
	//This readies the screenshot.
	static void readyScreenShot();
	//Make sure you have initalized the static variables in this class with Cam::init().
	//You have three channels to make views on: 1,2,3, and 4
	Cam();
	//Will return true if the block lies inside the screen boundarys.
	//Will return false otherwise.
	static bool RenderBasic(int x, int y, int CamChannel = 0, unsigned int Size = 32);
	//This will set the x and y cordinates of the camera view.
	static void setxy_chan(int channel, float x, float y, bool center);

};

