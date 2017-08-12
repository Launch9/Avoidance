#include "stdafx.h"
#include "NPC_temp.h"
#include "GF.h"
#include "Editor.h"

NPC_temp::NPC_temp(int Type, int x_pos, int y_pos, TileMap &TM)
{
	type = Type;
	x = x_pos;
	y = y_pos;
	GF::CheckTile_OverLap(x, y); //This checks to see if the tile is overlapping another tile.
	//typeID = ; //This is what distinguishes the NPC from all the other ones when being referred to.
	initx = x_pos; //This stores the initial x coordinate of creation.
	inity = y_pos; //This stores the initial y coordinate of creation.
	delx = x_pos; //This stores the x coordinate of where the editor needs to be to delete it.
	dely = y_pos; //This stores the y coordinate of where the editor needs to be to delete it.
	x2 = x_pos; //Extra x variable used for calculations.
	y2 = y_pos; //Extra y variable used for calculations.
	if (Editor::GetStatus() == true) {
		setPause(true);
	}
	else {
		setPause(false);
	}
	//max_ticks = ; //Normal 0.1 //These are the max ticks needed for a frame of animation to go by.
	sprite.setPosition(x, y); //This sets the position of the sprite to the given x and y coordinates.
	sprite.setTexture(2); //This sets when the sprite should be drawn. 0: Background, 1: Character, 2: Foreground
	sprite.setup(); //This tells the sprite that it is ready to be drawn.
	SavedParameters = { typeID, x_pos, y_pos }; //These are the parameters that are used when you load up the NPC. refer to World.cpp for details.
	//anisprites = All_Sprites[TM.getTextureID()][typeID][]; //What kind of animation you want to use.
	OVERRIDE_ANI = true; //If this is true, then the animation will still occur even when offscreen; Otherwise, it will stop animation when not rendered.
	sprite *= anisprites[0]; //Setting the sprite to the AniT of zero index.
	NPC_Cache.push_back(this); //Pushing it into the cache to allow ticking.
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-~MAIN TICK~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//This function is an overwritten virtual function, but this is a very important function
//So, this is placed seperate from the less important ones.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void NPC_temp::tick(bool render) {
	if (did_delete_self == false) {
		//Checking to see if you should be dead or not.
		if (render == true) {
			if (DynamicCheckPlayerCollision(x, y, 32, 32) == true) {
				KillPlayer();
			}
		}
	}
	
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-~VIRTUAL FUNCTIONS~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//These are functions that overwrite the virtual functions in NPC_MOTHER.
//You may change these functions, but it is not necessary.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//This function is called when the NPC is revived.
void NPC_temp::when_revive() {
	did_delete_self = false;
	sprite.activate();
}
//This function is called when the NPC is killed or deleted_self.
void NPC_temp::when_dead() {
	sprite.deactivate();
}

//This is called when the player dies, the editor starts, etc.
//Its purpose is to place everything back to where it started.
void NPC_temp::reset() {
	x = initx;
	y = inity;
}