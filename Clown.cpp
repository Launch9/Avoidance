#include "stdafx.h"
#include "Clown.h"
#include "Editor.h"
#include "Player.h"

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=CONTROL PANEL-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define particleColor sf::Color::White //This is the color of the particles that are shot out when you defeat the enemy.
#define particleFadetype 0 //This is the way the particle is delete.
#define number_of_particles 30 //This is how many particles are created when the NPC dies.
#define spriteBatchIndex 0 //This is what batch of sprite the NPC should use.
#define default_max_ticks 0.008//This is how long it takes to reach the next frame in an animation.
#define TypeID -1 //This is the identification of what object it is in relation to others in the NPC_MOTHER class.
#define PowerGivenToPlayer 1 //This tells how much power should be given to the player when the NPC dies.
#define AniSpeed_Walk 0.008 //This tells how fast the animation should go when the NPC moves.
#define AniSpeed_Stand 0.13 //This tells how fast the animation should go when the NPC is standing.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


Clown::Clown(int Type, int x_pos, int y_pos, TileMap &TM)
{
	type = Type;
	x = x_pos;
	y = y_pos;
	C_position.x = x_pos;
	C_position.y = y_pos;
	GF::CheckTile_OverLap(x, y); //This checks to see if the tile is overlapping another tile.
	typeID = TypeID; //This is what distinguishes the NPC from all the other ones when being referred to.
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
	max_ticks = default_max_ticks; //Normal 0.1 //These are the max ticks needed for a frame of animation to go by.
	sprite.setPosition(x, y); //This sets the position of the sprite to the given x and y coordinates.
	sprite.setTexture(2); //This sets when the sprite should be drawn. 0: Background, 1: Character, 2: Foreground
	sprite.setup(); //This tells the sprite that it is ready to be drawn.
	SavedParameters = { typeID, x_pos, y_pos }; //These are the parameters that are used when you load up the NPC. refer to World.cpp for details.
	Sprites = All_Sprites[TM.getTextureID()][spriteBatchIndex]; //What kind of animations you want to use.
	anisprites = Sprites[0]; //Animation starts at zero
	OVERRIDE_ANI = true; //If this is true, then the animation will still occur even when offscreen; Otherwise, it will stop animation when not rendered.
	sprite *= anisprites[0]; //Setting the sprite to the AniT of zero index.
	NPC_Cache.push_back(this); //Pushing it into the cache to allow ticking.
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-~MAIN TICK~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//This function is an overwritten virtual function, but this is a very important function
//So, this is placed seperate from the less important ones.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void Clown::tick(bool render) {
	if (did_delete_self == false) {
		if (C_position.x == Player::PlayerObjects[0]->getcx() && C_position.y == Player::PlayerObjects[0]->getcy()) {
			KillPlayer();
		}
		if (Projectile::DynamicCheckCollisionLight(get_C_position().x, get_C_position().y, 32, 32, true) != -1) {
			delete_self(this);
			ParticleSettings s(get_C_position().x + 16, get_C_position().y + 16, 2, number_of_particles, 1, particleFadetype);
			s.color = particleColor;
			s.ac1 = 0;
			s.ac2 = 360;
			ParticleSystem::create(s);
		}

		if (get_isMoving() == false) {

			if (standing_toggle == false) {

				Aniset(0, AniSpeed_Stand);
				standing_toggle = true;
			}
		}

		m_tick();
	}


}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-~VIRTUAL FUNCTIONS~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//These are functions that overwrite the virtual functions in NPC_MOTHER.
//You may change these functions, but it is not necessary.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


void Clown::ifPlayerMoved(int speed, int direction, int spaces, float remainder) {
	if (isPaused == false) {


		int Q = findQuadrant(Player::PlayerObjects[0]->getx(), Player::PlayerObjects[0]->gety());
		if (Q == -1) {
			Q = findDirection(Player::PlayerObjects[0]->getx(), Player::PlayerObjects[0]->gety());
			if (checkLoop(1, Q, speed, remainder) == true) {
				Aniset(1, AniSpeed_Walk);
				standing_toggle = false;
			}
		}
		else {
			switch (Q) {
			case 1:
				if (checkLoop(1, 0, speed, remainder) == true) {
					Aniset(1, AniSpeed_Walk);
					standing_toggle = false;
				};
				break;
			case 2:
				if (checkLoop(1, 3, speed, remainder)) {
					Aniset(1, AniSpeed_Walk);
					standing_toggle = false;
				};
				break;
			case 3:
				if (checkLoop(1, 2, speed, remainder) == true) {
					Aniset(1, AniSpeed_Walk);
					standing_toggle = false;
				};
				break;
			case 4:
				if (checkLoop(1, 1, speed, remainder) == true) {
					Aniset(1, AniSpeed_Walk);
					standing_toggle = false;
				}

			}

		}

	}

	
}

//This function is called when the NPC is revived.
void Clown::when_revive() {
	did_delete_self = false;
	sprite.activate();
}
//This function is called when the NPC is killed or deleted_self.
void Clown::when_dead() {
	Player::PlayerObjects[0]->addPower(PowerGivenToPlayer);
	sprite.deactivate();
	call_when_dead();
}

//This is called when the player dies, the editor starts, etc.
//Its purpose is to place everything back to where it started.
void Clown::reset() {
	x = initx;
	y = inity;
	C_position.x = initx;
	C_position.y = inity;
	stop_ani();
	sprite.setPosition(x, y);
}

//This is called once when the class has completed its movement and is waiting for more commands.
void Clown::next() {

}

