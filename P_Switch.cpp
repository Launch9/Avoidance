#include "stdafx.h"
#include "P_Switch.h"
#include "Seal.h"
#include "P_Switch_MAIN.h"
#include "Sound.h"
#define Smax_ticks 0.1
#define Stimer_pitch 1
#define Min_max_ticks 0.03
P_Switch::P_Switch(const int &type, const int &x_pos, const int &y_pos, const int &Direction, const int &Switch, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	typeID = 10;
	typec = type;
	channel = Switch;
	dir = Direction;
	max_ticks = 0.1;
	text.setPosition(x_pos + 16, y_pos + 16);
	sprite.setPosition(x, y);
	sprite.setup();
	isSIMPLELIGHTING = false;
	timer_Sound.setBuffer(Sound::GetSoundBuffer(48));
	timer_Sound.setLoop(false);
	SavedParameters = { x_pos, y_pos, type, dir, channel };
	spr = All_Sprites[TM.getTextureID()][typeID];
	switch (Direction) {
	case 0:
		Sprites = { All_Sprites[TM.getTextureID()][typeID][0][0], All_Sprites[TM.getTextureID()][typeID][0][1] };
		break;
	case 1:
		Sprites = { All_Sprites[TM.getTextureID()][typeID][0][2], All_Sprites[TM.getTextureID()][typeID][0][3] };
		break;
	case 2:
		Sprites = { All_Sprites[TM.getTextureID()][typeID][0][4], All_Sprites[TM.getTextureID()][typeID][0][5] };
		break;
	case 3:
		Sprites = { All_Sprites[TM.getTextureID()][typeID][0][6], All_Sprites[TM.getTextureID()][typeID][0][7] };
		break;
	}

	sprite *= Sprites[0];
	ColProjectiles.push_back(this);
}


void P_Switch::ifProjectileCollision(Projectile &P, int direction) {
	
	if (direction == 2 && dir == 0) {
		Collide(P, direction);
	}
	else if (direction == 3 && dir == 1) {
		Collide(P, direction);
	}
	else if (direction == 0 && dir == 2) {
		Collide(P, direction);
	}
	else if (direction == 1 && dir == 3) {
		Collide(P, direction);
	}
	P.kill(1);
	
}

void P_Switch::Collide(Projectile &P, const int &direction) {
	
	
	//Actives the P_Switch
	Active();
	//Making it so that the projectile collides with the P_Switch and does not go through it.
	P.kill(1);
}


void P_Switch::Active() {
	if (is_active == false) {
		//Making the text tell you that it is now active.
		text.setString("Activated!");
		//Making the text appear.
		P_Switch_MAIN::Switches[channel] = true;
		is_active = true;
		P_Switch_MAIN::update();
		switch (dir) {
		case 0:
			Sprites = { spr[0][8], spr[0][1] };
			break;
		case 1:
			Sprites = { spr[0][10], spr[0][3] };
			break;
		case 2:
			Sprites = { spr[0][9], spr[0][5] };
			break;
		case 3:
			Sprites = { spr[0][11], spr[0][7] };
			break;
		}
	}
	
}

void P_Switch::Deactive() {
	if (is_active == true) {
		//Making the text tell you that it is now active.
		text.setString("Deactivated!");
		//Making the text appear.
		P_Switch_MAIN::Switches[channel] = false;
		timer_ticks = 0;
		timer_Sound.setPitch(1);
		max_ticks = 0.1;
		timer_Sound.stop();
		is_active = false;
		P_Switch_MAIN::update();

		switch (dir) {
		case 0:
			Sprites = { spr[0][0], spr[0][1] };
			break;
		case 1:
			Sprites = { spr[0][2], spr[0][3] };
			break;
		case 2:
			Sprites = { spr[0][4], spr[0][5] };
			break;
		case 3:
			Sprites = { spr[0][6], spr[0][7] };
			break;
		}
	}
	
}

void P_Switch::animate() {
	ticks += GF::getDelta();
	if (is_active == true) {
		if (max_ticks >= Min_max_ticks) {
			max_ticks = Smax_ticks - (Smax_ticks * (timer_ticks / max_timer_ticks));
			timer_Sound.setPitch((Stimer_pitch + (timer_ticks / max_timer_ticks)));
		}
		
	}
	if (ticks >= max_ticks) {
		
		
		svectorindex += 1;
		if (svectorindex >= Sprites.size()) {
			svectorindex = 0;
			switch (typec) {
			case 1:
				if (is_active == true) {
					timer_Sound.play();
				}
			}
			
			
			//Setting the texture rectangle to the correct position for proper animation.
		}
		sprite *= Sprites[svectorindex];
		ticks = 0;
	}
	switch (typec) {
	case 1:
		if (is_active == true) {
			timer_ticks += GF::getDelta();
			
			if (timer_ticks >= max_timer_ticks) {
				Deactive();
			}
		}
	}
}