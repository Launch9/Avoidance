#include "stdafx.h"
#include "Sub_NPC_CD.h"
#include "P_Switch_MAIN.h"
std::vector<Sub_NPC_CD *> Sub_NPC_CD::Objects;
unsigned int Sub_NPC_CD::HowManyDead;
Sub_NPC_CD::Sub_NPC_CD()
{
	Objects.push_back(this);
}


Sub_NPC_CD::~Sub_NPC_CD()
{
	if (is_dead == true) {
		HowManyDead--;
	}

	for (unsigned int i = 0; i < Objects.size(); i++) {
		if (Objects[i] == this) {
			Objects.erase(Objects.begin() + i);
			break;
		}
	}
	
}

void Sub_NPC_CD::call_when_dead() {
	if (is_dead == false) {
		HowManyDead++;
		is_dead = true;
		check();
	}
	
	
	
}

void Sub_NPC_CD::check() {
	if (HowManyDead == Objects.size()) {
		P_Switch_MAIN::deathSwitch = true;
		P_Switch_MAIN::update();
	}
}

void Sub_NPC_CD::init() {
	HowManyDead = 0;
}