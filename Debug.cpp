#include "stdafx.h"
#include "Debug.h"
#include "Cam.h"
#include <iostream>
#include "Player.h"
#include <string>
#include "Itemids.h"
#include "Editor.h"
#include "Laser.h"
#include "Light_MOTHER.h"
#include "World.h"
#include "Bg.h"
#include "Shop.h"
#include "ConstLight.h"
#include "FlickerLight.h"
#include "Stair.h"
#include "SoundBlock.h"
#include "HomingSkull.h"
#include "AniBg.h"
#include "ChainBall.h"
#include "Character.h"
#include "SaveStation.h"
#include "Door.h"
#include "Foreground.h"
#include "Chest.h"
#include "Corner.h"
#include "P_Switch.h"
#include "Seal.h"
#include "RTile.h"
#include "P_Spawner_Const.h"
#include "PTile.h"
#include "Skeleton.h"
#include "Cloud_Spawner.h"
#include "Cloud_Start.h"
#include "Teleporter.h"
#include "Slime.h"
#include "Sign.h"
#include "Hurts.h"
#include "Stream.h"
#include "Room.h"
#include "Entrance.h"
#include "Exit.h"
#include "TripleChest.h"
#include "Shielder.h"
#include "Dragon.h"
#include "Rock.h"
#include "Break_Spawner.h"
#include "Weather.h"
#include "Dino.h"
#include "Flame.h"
#include "BounceTile.h"
#include "Squisher.h"
#include "Blast.h"
#include "W_bomb.h"
#include "EyeBall.h"
#include "EBM.h"
#include "EyeBall_MAIN.h"
#include "Elevator.h"
#include "SnowClouds.h"
#include "Sub_NPC_Block.h"
#include "IPTile.h"
#include "FlameThrower.h"
#include "Big_Squisher.h"
#include "Com_Hand.h"
#include "Com_MAIN.h"
#include "NPC_Spawner.h"
#include "P_Fog.h"
#define PChannel 0
#define b32 32
#define WhitebarW 10
#define CommandTextHoverDif 5
#define CamChannel 0
sf::Font Debug::Font;
std::string Debug::lastCommand;
bool Debug::isMenuOpen;
sf::Text Debug::CommandText;
std::string Debug::Command;
std::string Debug::RootCommand;
std::vector<std::string> Debug::Parameters;
std::vector<sf::Text> Debug::PermText;
std::vector<sf::Text> Debug::Texts;
std::vector<sf::RectangleShape> Debug::Rects;
std::vector<sf::RectangleShape> Debug::PermRects;
std::vector<sf::VertexArray> Debug::Lines;
void Debug::SetDebugMenu(sf::RenderWindow &win, bool TF) {
	win.setKeyRepeatEnabled(TF);
	isMenuOpen = TF;
}
void Debug::SquareDraw(float x_pos, float y_pos, int width, int height) {
	sf::RectangleShape r(sf::Vector2f(x_pos, y_pos));
	r.setPosition(x_pos, y_pos);
	r.setSize(sf::Vector2f(width, height));
	Rects.push_back(r);
}

void Debug::LineDraw(const sf::Vector2f point1, const sf::Vector2f &point2, const sf::Color &color) {
	sf::VertexArray v;
	v.setPrimitiveType(sf::Lines);
	sf::Vertex c;
	c.position = point1;
	c.color = color;
	v.append(c);
	sf::Vertex c2;
	c2.position = point2;
	c2.color = color;
	v.append(c2);
	Lines.push_back(v);
	
}
void Debug::tick() {
	//This checks to see if the menu is open.
	if (isMenuOpen == true) {
		//This will display the debug menu.
		CommandText.setString(Command);
		
	}
	
}

void Debug::draw(sf::RenderWindow &win) {
	
	for (unsigned int i = 0; i < Rects.size(); i++) {
		win.draw(Rects[i]);
		//Erasing the sprite once it has been drawn.
		//Rects.erase(Rects.begin() + i);
	}
	
	Rects.clear();
	
	for (unsigned int i = 0; i < Lines.size(); i++) {
		win.draw(Lines[i]);
		
		//Lines.erase(Lines.begin() + i);
	}

	Lines.clear();
	
	if (isMenuOpen == true) {
		Cam::drawGUI_chan(0, win, PermText[0]);
		Cam::drawGUI_chan(0,win,PermRects[0]);
		Cam::drawGUI_chan(0,win,CommandText);
	}
	
		
}
void Debug::init(sf::Font f) {
	Font = f;
	isMenuOpen = false;
	//Creating the texts for 
	sf::Text t1;
	t1.setFont(Font);
	t1.setString(":>");
	t1.setColor(sf::Color::Magenta);
	sf::RectangleShape r1;
	r1.setSize(sf::Vector2f(Cam::getdisplaywidth(), WhitebarW));
	CommandText.setFont(Font);
	//This is for putting the texts that were just created into a permanent text vector(Will not get erased each tick).
	PermText.push_back(t1);
	PermRects.push_back(r1);
	PermText[0].setPosition(0, Cam::getdisplayheight() - (b32 + WhitebarW));
	PermRects[0].setPosition(0, Cam::getdisplayheight() - WhitebarW);
	CommandText.setPosition(b32, Cam::getdisplayheight() - (WhitebarW + b32 + CommandTextHoverDif));


	
}

bool Debug::GetMenuOpen() {
	return isMenuOpen;
}

void Debug::AddCommandChar(char c) {
	Command.push_back(c);
}

void Debug::UseCommand(sf::RenderWindow &win, TileMap &TM) {
	lastCommand = Command;
	DecipherCommand();
	bool Clearbool = true;
	//This is for checking to see how many parrentheses(Sorry about the bad spelling) are in the command.
	int totalparenth = FindNumChars(*")") + FindNumChars(*"(");
	int totalparameters = Parameters.size();
	//These are all the possible commands!
	//This will teleport the player to 0x 0y.
	if (RootCommand == "Teleport" && totalparenth == 0) {
		Player::PlayerObjects[PChannel]->setXY(0, 0);
		Player::PlayerObjects[PChannel]->SnapCam();
	}
	//This will teleport the player to the specifed x and y cordinates.
	//This converts the cordinates into blocks!
	else if (RootCommand == "Teleport" && totalparenth == 2) {
		//This checks for errors in the command.
		if (totalparameters >= 3) {
			ThrowError("Teleport(x,y)");
			Clearbool = false;
		}
		else if (totalparameters <= 1) {
			ThrowError("Teleport(x,y)");
			Clearbool = false;
		}
		else {
			//This moves the players x and y cordinates to the given position in the command given.
			Player::PlayerObjects[PChannel]->setXY(StringtoInt(Parameters[0]) * b32, StringtoInt(Parameters[1]) * b32);
			Player::PlayerObjects[PChannel]->SnapCam();
		}
	}
	//This will give the player an object.
	//Please give this command an object id to give to the player.
	else if (RootCommand == "Give" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Give(ItemId)");
			Clearbool = false;
		}
		else {
			Player::PlayerObjects[0]->addinventoryitem(StringtoInt(Parameters[0]));
		}
	}
	else if (RootCommand == "ZoomCam" && totalparenth == 2) {
		if(totalparameters != 1){
			ThrowError("ZoomCam(float)");
			Clearbool = false;
		}
		else {
			Cam::zoom_chan(CamChannel, StringtoFloat(Parameters[0]));
		}
		
	}
	else if (RootCommand == "setTexture" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("setTexture(int textureID)");
			Clearbool = false;
		}
		else {
			TM.setTexture(StringtoInt(Parameters[0]));
		}
	}
	else if (RootCommand == "EditorStart" && totalparenth == 0) {
		Editor::Start();
	}
	else if (RootCommand == "EditorStop" && totalparenth == 0) {
		Editor::Stop();
	}
	else if (RootCommand == "LoadWorld" && totalparenth == 2) {
		
		World::LoadWorld(Parameters[0], TM, true);
		
	}
	else if (RootCommand == "SaveWorld" && totalparenth == 2) {
		World::SaveWorld(Parameters[0], TM);
	}
	else if (RootCommand == "EditorSetWaitTick" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("EditorSetWaitTick(int amount)");
			Clearbool = false;
		}
		else {
			Editor::SetWaitTick(StringtoInt(Parameters[0]));
		}
		
	}
	else if (RootCommand == "SaveWorld" && totalparameters == 0) {
		World::OverwriteCurrentWorld(TM);
	}
	//All of these are for making NPCs.
	else if (RootCommand == "Editor_Make_Laser" && totalparenth == 2) {
		if (totalparameters != 4) {
			ThrowError("Editor_Make_Laser(unint strtdirection, int distance, unint color, int speed)");
			Clearbool = false;
		}
		else {
			new Laser(Editor::getx(), Editor::gety(), StringtoUnint(Parameters[0]), TM, StringtoInt(Parameters[1]), StringtoUnint(Parameters[2]), StringtoInt(Parameters[3]));
		}
			
	}
	else if (RootCommand == "Editor_Make_Rock" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Editor_Make_Rock(int type)");
			Clearbool = false;
		}
		else {
			new Rock(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), TM);
		}
	}
	else if (RootCommand == "Player_do_ani" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Player_do_ani(int type)");
			Clearbool = false;
		}
		else {
			Player::PlayerObjects[0]->doAnimation(StringtoInt(Parameters[0]), true);
		}
	}
	else if (RootCommand == "Editor_Make_EyeBall" && totalparenth == 2) {
		if (totalparameters != 3) {
			ThrowError("Editor_Make_EyeBall(int type, int Direction, int Switch)");
			Clearbool = false;
		}
		else {
			new EyeBall(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Flame" && totalparenth == 2) {
		if (totalparameters != 2) {
			ThrowError("Editor_Make_Flame(int type, int direction)");
			Clearbool = false;
		}
		else {
			new Flame(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_EBM" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Editor_Make_EBM(int type)");
			Clearbool = false;
		}
		else {
			new EBM(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Dino" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Editor_Make_Dino(int type)");
			Clearbool = false;
		}
		else {
			new Dino(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), TM);
		}
	}
	else if (RootCommand == "Editor_Make_NPC_Spawner" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Editor_Make_NPC_Spawner(int type)");
			Clearbool = false;
		}
		else {
			new NPC_Spawner(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Squisher" && totalparenth == 2) {
		if (totalparameters != 5) {
			ThrowError("Editor_Make_Squisher(int type, int direction, float distance_in_blocks, float Speed, int SwitchChannel");
			Clearbool = false;
		}
		else {
			new Squisher(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), StringtoFloat(Parameters[3]), StringtoInt(Parameters[4]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_BounceTile" && totalparenth == 2) {
		if (totalparameters != 3) {
			ThrowError("Editor_Make_BounceTile(int type, int distance, int direction)");
			Clearbool = false;
		}
		else {
			new BounceTile(StringtoInt(Parameters[0]), StringtoInt(Parameters[1]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[2]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Break_Spawner" && totalparenth == 2) {
		if (totalparameters != 4) {
			ThrowError("Editor_Make_Break_Spawner(int type, int pattern, int type_of_projectile, int how_much_health)");
			Clearbool = false;
		}
		else {
			new Break_Spawner(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), StringtoInt(Parameters[3]), TM);
		}
		
	}
	else if (RootCommand == "Editor_Make_IPTile" && totalparenth == 2) {
		if (totalparameters != 2) {
			ThrowError("Editor_Make_IPTile(int type, int SwitchID)");
			Clearbool = false;
		}
		else {
			new IPTile(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]));
		}
	}
	else if (RootCommand == "Editor_Make_HomingSkull" && totalparenth == 2) {
		if (totalparameters != 3) {
			ThrowError("Editor_Make_HomingSkull(int type, int color, int speed");
			Clearbool = false;
		}
		else {
			new HomingSkull(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_FlameThrower" && totalparenth == 2) {
		if (totalparameters != 2) {
			ThrowError("Editor_Make_FlameThrower(int type, int direction)");
			Clearbool = false;
		}
		else {
			new FlameThrower(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_EyeBall_MAIN" && totalparenth == 2) {
		if (totalparameters < 2) {
			ThrowError("Editor_Make_EyeBall_MAIN(int type, vector<int> switches...)");
			Clearbool = false;
		}
		else {
			std::vector<int> items3;
			for (unsigned int i = 1; i < Parameters.size(); i++) {
				items3.push_back(StringtoInt(Parameters[i]));
			}
		
			new EyeBall_MAIN(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), items3, TM);
		}
	}
	else if (RootCommand == "Editor_Make_P_Fog" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Editor_Make_P_Fog(int type)");
			Clearbool = false;
		}
		else {
			new P_Fog(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Com_Hand" && totalparenth == 2) {
		if (totalparameters != 2) {
			ThrowError("Editor_Make_Com_Hand(int type, int SwitchChannel)");
			Clearbool = false;
		}
		else {
			new Com_Hand(StringtoInt(Parameters[0]),  Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Com_MAIN" && totalparenth == 2) {
		if (totalparameters != 2) {
			ThrowError("Editor_Make_Com_MAIN(int type, int SwitchChannel)");
			Clearbool = false;
		}
		else {
			new Com_MAIN(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Big_Squisher" && totalparenth == 2) {
		if (totalparameters != 3) {
			ThrowError("Editor_Make_Big_Squisher(int type, int distance, int direction)");
			Clearbool = false;
		}
		else {
			new Big_Squisher(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Weather" && totalparenth == 2) {
		if (totalparameters != 2) {
			ThrowError("Editor_Make_Weather(int type, int y_ground_in_blocks)");
			Clearbool = false;
		}
		else {
			new Weather(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Sub_NPC_Block" && totalparenth == 2) {
		if (totalparameters != 2) {
			ThrowError("Editor_Make_Sub_NPC_Block(int type, int Switch)");
			Clearbool = false;
		}
		else {
			new Sub_NPC_Block(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]));
		}
	}
	else if (RootCommand == "Editor_Make_Elevator" && totalparenth == 2) {
		if (totalparameters != 3) {
			ThrowError("Editor_Make_Elevator(int type, int Switch_for_door, int Switch_for_toggle)");
			Clearbool = false;
		}
		else {
			new Elevator(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_BackSplash" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Editor_Make_BackSplash(int type)");
			Clearbool = false;
		}
		else {
			BackSplash_MOTHER::create(StringtoInt(Parameters[0]));
		}
	}
	else if (RootCommand == "Editor_Make_Blast" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Editor_Make_Blast(int type)");
			Clearbool = false;
		}
		else {
			new Blast(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), TM);
		}
	}
	else if (RootCommand == "Editor_Make_W_bomb" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Editor_Make_W_bomb(int type)");
			Clearbool = false;
		}
		else {
			new W_bomb(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), TM);
		}
	}
	//This is for making a light object appear at the designated cordinates. 
	else if (RootCommand == "Editor_Make_Light" && totalparenth == 2) {
		if (totalparameters != 5) {
			ThrowError("Editor_Make_Light(int typeID, int lightpower, bool red, bool blue, bool green)");
			Clearbool = false;
		}
		else {
			switch (StringtoInt(Parameters[0])) {
				//ConstLight
			case 0:
				new ConstLight(Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), StringtoInt(Parameters[3]), StringtoInt(Parameters[4]));
				break;
			case 1:
				new FlickerLight(Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), StringtoInt(Parameters[3]), StringtoInt(Parameters[4]));
				break;
			}
			Light_MOTHER::ResetLighting();
		}
		
	}
	else if (RootCommand == "Editor_Make_Stream" && totalparenth == 2) {
		if (totalparameters != 3) {
			ThrowError("Editor_Make_Stream(int type, int is_flowing_left, int speed)");
			Clearbool = false;
		}
		else {
			new Stream(StringtoInt(Parameters[0]), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), Editor::getx(), Editor::gety(), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Shop" && totalparenth == 2) {
		if (totalparameters < 2) {
			ThrowError("Editor_Make_Shop(spriteID, DialougeNum, The Rest of the parameters are the items)");
			Clearbool = false;
		}
		else {
			std::vector<int> items;
			for (unsigned int i = 2; i < Parameters.size(); i++) {
				items.push_back(StringtoInt(Parameters[i]));
			}
			new Shop(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), items, TM);
		}
	}
	else if (RootCommand == "Editor_Make_ChainBall" && totalparenth == 2) {
		if (totalparameters != 4) {
			ThrowError("Editor_Make_ChainBall(int type, int distance_from_center, int color, int speed");
			Clearbool = false;
		}
		else {
			new ChainBall(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), TM, StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), StringtoInt(Parameters[3]));
		}
	}
	else if (RootCommand == "Editor_Make_Hurts" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Editor_Make_Hurts(int Type)");
			Clearbool = false;
		}
		else {
			new Hurts(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety());
		}
	}
	else if (RootCommand == "Editor_Make_Foreground" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Editor_Make_Foreground(int ID)");
			Clearbool = false;
		}
		else {
			new Foreground(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Slime" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Editor_Make_Slime(int type)");
			Clearbool = false;
		}
		else {
			new Slime(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Sign" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Editor_Make_Sign(int type)");
			Clearbool = false;
		}
		else {
			new Sign(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Dragon" && totalparenth == 2) {
		if (totalparameters != 2) {
			ThrowError("Editor_Make_Dragon(int type, int how_long)");
			Clearbool = false;
		}
		else {
			new Dragon(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Stair" && totalparenth == 2) {
		if (totalparameters != 3) {
			ThrowError("Editor_Make_Stair(int Floor, int Dungeon, int type)");
			Clearbool = false;
		}
		else {
			new Stair(Editor::getx(), Editor::gety(), StringtoInt(Parameters[0]), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Shielder" && totalparenth == 2) {
		if (totalparameters < 2) {
			ThrowError("Editor_Make_Shielder(int type, int how_many_hits, vector<int> shield_directions...");
			Clearbool = false;
		}
		else {
			std::vector<int> items2;
			for (unsigned int i = 2; i < Parameters.size(); i++) {
				items2.push_back(StringtoInt(Parameters[i]));
			}
			
			new Shielder(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), TM, items2);
		}
	}
	else if (RootCommand == "Editor_Make_Cloud_Spawner" && totalparenth == 2) {
		if (totalparameters != 4) {
			ThrowError("Editor_Make_Cloud_Spawner(int type, int x_end, int max_ticks, int speed)");
			Clearbool = false;
		}
		else {
			new Cloud_Spawner(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), StringtoInt(Parameters[3]));
		}
	}
	else if (RootCommand == "Editor_Make_Cloud_Start" && totalparenth == 2) {
		if (totalparameters != 3) {
			ThrowError("Editor_Make_Cloud_Start(int type, int x_end, int speed)");
			Clearbool = false;
		}
		else {
			new Cloud_Start(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]));
		}
	}
	else if (RootCommand == "Editor_Make_Room" && totalparenth == 2) {
		if (totalparameters != 4) {
			ThrowError("Editor_Make_Room(int Type, int Channel, int width, int height");
			Clearbool = false;
		}
		else {
			new Room(StringtoInt(Parameters[0]), StringtoInt(Parameters[1]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[2]), StringtoInt(Parameters[3]));
		}
	}
	else if (RootCommand == "Editor_Make_Chest" && totalparenth == 2) {
		if (totalparameters == 0) {
			ThrowError("Editor_Make_Chest(int ID, int contentID)");
			Clearbool = false;
		}
		else {
			
			new Chest(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Entrance" && totalparenth == 2) {
		if (totalparameters != 3) {
			ThrowError("Editor_Make_Entrance(int Type, int RoomIDenter, int RoomIDexit)");
			Clearbool = false;
		}
		else {
			new Entrance(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]));
		}
	}
	else if (RootCommand == "Editor_Make_Exit" && totalparenth == 2) {
		if (totalparameters != 2) {
			ThrowError("Editor_Make_Exit(int type, int ExitID)");
			Clearbool = false;
		}
		else {
			new Exit(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]));
		}
	}
	else if (RootCommand == "Editor_Make_Skeleton" && totalparenth == 2) {
		
		if (totalparameters != 1) {
			ThrowError("Editor_Make_Skeleton(int type)");
			Clearbool = false;
		}
		else {
			new Skeleton(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), TM);
		}
	}

	else if (RootCommand == "Editor_Make_AniBg" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Editor_Make_AniBg(int ID)");
			Clearbool = false;
		}
		else {
			new AniBg(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Corner" && totalparenth == 2) {
		if (totalparameters != 2) {
			ThrowError("Editor_Make_Corner(int type, int direction");
			Clearbool = false;
		}
		else {
			new Corner(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), TM);
		}
	}
	else if (RootCommand == "Editor_Set_Haze" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Editor_Set_Haze(int index)");
			Clearbool = false;
		}
		else {
			World::setHaze(StringtoInt(Parameters[0]));
		}
	}
	else if (RootCommand == "Editor_Make_P_Switch" && totalparenth == 2) {
		if (totalparameters != 3) {
			ThrowError("Editor_Make_P_Switch(int type, int direction, int switch)");
			Clearbool = false;
		}
		else {
			new P_Switch(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_Seal" && totalparenth == 2) {
		if (totalparameters < 2) {
			ThrowError("Editor_Make_Seal(int type, int direction, V_int Switch_channels...)");
			Clearbool = false;
		}
		else {
			std::vector<int> v;
			for (unsigned int i = 2; i < Parameters.size(); i++) {
				v.push_back(StringtoInt(Parameters[i]));
			}
			new Seal(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), v, TM);
		}
	}
	else if (RootCommand == "Editor_Make_Door" && totalparenth == 2) {
		if (totalparameters != 5) {
			ThrowError("Editor_Make_Door(int load_X, int load_Y, int Extra, int direction, int type)");
			Clearbool = false;
		}
		else {
			new Door(Editor::getx(), Editor::gety(), StringtoInt(Parameters[0]), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), StringtoInt(Parameters[3]), StringtoInt(Parameters[4]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_SaveStation") {
		new SaveStation(Editor::getx(), Editor::gety(), TM);
	}
	else if (RootCommand == "Editor_Make_Character" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Editor_Make_Character(int type)");
			Clearbool = false;
		}
		else {
			new Character(Editor::getx(), Editor::gety(), StringtoInt(Parameters[0]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_PTile" && totalparenth == 2) {
		if (totalparameters != 2) {
			ThrowError("Editor_Make_PTile(int type, int SwitchChannel");
			Clearbool = false;
		}
		else {
			new PTile(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_P_Spawner_Const" && totalparenth == 2) {
		if (totalparameters != 3) {
			ThrowError("Editor_Make_P_Spawner_Const(int type, int direction, int SwitchChannel)");
			Clearbool = false;
		}
		else {
			new P_Spawner_Const(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), TM, StringtoInt(Parameters[2]));
			
		}
	}
	else if (RootCommand == "Editor_Make_WallLine" && totalparenth == 2) {
		if (totalparameters != 3) {
			ThrowError("Editor_Make_WallLine(unint typeID, int direction, int distance)");
			Clearbool = false;
		}
		else {
			Wall::Addline(StringtoUnint(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_BgLine" && totalparenth == 2) {
		if (totalparameters != 3) {
			ThrowError("Editor_Make_BgLine(unint typeID, int direction, int distance)");
			Clearbool = false;
		}
		else {
			Bg::Addline(StringtoUnint(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_AniBgLine" && totalparenth == 2) {
		if (totalparameters != 3) {
			ThrowError("Editor_Make_AniBgLine(unint ID, int direction, int distance)");
			Clearbool = false;
		}
		else {
			AniBg::Addline(StringtoUnint(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), TM);
		}
	}
	else if (RootCommand == "Editor_Make_SoundBlock" && totalparenth == 2) {
		if (totalparameters < 2) {
			ThrowError("Editor_Make_SoundBlock(int required_ticks, int soundIDs...)");
			Clearbool = false;
		}
		else {
			std::vector<int> v = {};
			for (unsigned int i = 1; i < Parameters.size(); i++) {
				v.push_back(StringtoInt(Parameters[i]));
			}
			new SoundBlock(Editor::getx(), Editor::gety(), StringtoInt(Parameters[0]), v);
		}
	}
	else if (RootCommand == "Editor_Make_Teleporter" && totalparenth == 2) {
		if (totalparameters != 4) {
			ThrowError("Editor_Make_Teleporter(int type, int dungeon, int floor, int Exitid)");
			Clearbool = false;
		}
		else {
			
			new Teleporter(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), StringtoInt(Parameters[3]));
		}
	}
	else if (RootCommand == "Editor_Make_TripleChest" && totalparenth == 2) {
		if (totalparameters != 3) {
			ThrowError("Editor_Make_TripleChest(int type, int contentID, int switchID)");
			Clearbool = false;
		}
		else {
			new TripleChest(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), StringtoInt(Parameters[1]), StringtoInt(Parameters[2]), TM);
		}
	}
	else if (RootCommand == "SavePlayerFile" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("SavePlayerFile(FileLocation)");
			Clearbool = false;
		}
		else {
			Player::PlayerObjects[PChannel]->SavePlayerFile(Parameters[0]);
		}
	}
	else if (RootCommand == "Editor_Make_RTile" && totalparenth == 2) {
		if (totalparameters != 1) {
			ThrowError("Editor_Make_RTile(int type)");
			Clearbool = false;
		}
		else {
			
			new RTile(StringtoInt(Parameters[0]), Editor::getx(), Editor::gety(), TM);
		}
	}
	else {
		ThrowError("Was not a valid command!");
		Clearbool = false;
	}
	//This will empty the entire command vector, making it ready for the next command. If the command allows it.
	if (Clearbool == true) {
		Clearcommand();
	}
	
}

void Debug::Backspace() {
	
	
	//This checks to see if the size of the command string is not zero.
	if (Command.size() != 0) {
		//This will get rid of the last character pushed back into the string.
		Command.erase(Command.begin() + (Command.size() - 1));
	}
	
}

int Debug::FindChar(char c, int NumberofPasses) {
	for (unsigned int i = 0; i < Command.size(); i++) {
		if (Command[i] == c) {
			//This will decide wether or not it needs to return the index.
			//If not then it will pass it and subtract the NumberofPasses variable.
			if (NumberofPasses == 0) {
				return i;
			}
			else {
				NumberofPasses -= 1;
			}
		}
	}
}
int Debug::FindNumChars(char c) {
	int total = 0;
	for (unsigned int i = 0; i < Command.size(); i++) {
		if (Command[i] == c) {
			total += 1;
		}
	}
	return total;
}

void Debug::DecipherCommand() {
	bool ParameterLock = false;
	std::string s;
	RootCommand.clear();
	for (unsigned int i = 0; i < Command.size(); i++) {
		if (ParameterLock == false) {
			//This will happen if it finds the end of the RootCommand(Anything thats not the parameters).
			if (Command[i] == *"(") {
				ParameterLock = true;
				continue;
			}
			//This happens if it finds something that is part of the RootCommand.
			else {
				RootCommand.push_back(Command[i]);
			}
		}
		//This happens if the index is inside the parameter section of the Command.
		else {
			if (Command[i] == *")") {
				if (Command[i - 1] != *"(") {
					Parameters.push_back(s);
				}
				break;
			}
			//This happens if it reachs a comma. Thus making it seperate the parameters.
			else if (Command[i] == *",") {
				//Putting the parameter string into the vector full of parameters.
				Parameters.push_back(s);
				//This is for clearing the string so that a new parameter can fall in the vector.
				s.clear();
				continue;
			}
			s.push_back(Command[i]);
		}
		
	}
}

void Debug::ThrowError(std::string ErrorReport) {
	//This is the process of clearing all the Command strings and such.
	Command.clear();
	RootCommand.clear();
	Parameters.clear();
	//This will show the error report in the Menu.
	Command = ErrorReport;
}

int Debug::StringtoInt(std::string string) {
	return std::stoi(string);
}

float Debug::StringtoFloat(std::string string) {
	return std::stof(string);
}

unsigned int Debug::StringtoUnint(std::string string) {
	return std::stoul(string);
}

void Debug::setlastcommand() {
	Parameters.clear();
	RootCommand.clear();
	Command = lastCommand;
}

void Debug::uselastcommand(sf::RenderWindow &win, TileMap &TM) {
	Parameters.clear();
	RootCommand.clear();
	Command = lastCommand;
	cout << Command << endl;
	Debug::UseCommand(win, TM);
}

void Debug::Clearcommand() {
	Command.clear();
	RootCommand.clear();
	Parameters.clear();
}