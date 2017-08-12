#include "stdafx.h"
#include "P_Switch_MAIN.h"
#include "Seal.h"
#include "Chest.h"
#include "Stair.h"
#include "Squisher.h"
#include "PTile.h"
#include "Squisher.h"
#include "EyeBall_MAIN.h"
#include "Elevator.h"
#include "PTile.h"
#include "Sub_NPC_Block.h"
std::vector<bool> P_Switch_MAIN::Switches;
bool P_Switch_MAIN::deathSwitch;

void P_Switch_MAIN::clearSwitches() {
	Switches = { false, false, false, false, false, false, false, false , false };
	deathSwitch = false;
}

void P_Switch_MAIN::init() {
	clearSwitches();
}

void P_Switch_MAIN::update() {
	Seal::update_all();
	Chest::update();
	Stair::update();
	Squisher::update_all();
	EyeBall_MAIN::update();
	Elevator::update_all();
	PTile::update_all();
	Sub_NPC_Block::update_all();
}

