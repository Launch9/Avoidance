#include "stdafx.h"
#include "Sub_NPC_StaticCollision.h"
#include <iostream>
std::vector<Sub_NPC_StaticCollision *> Sub_NPC_StaticCollision::Objects;

Sub_NPC_StaticCollision::~Sub_NPC_StaticCollision() {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		if (this == Objects[i]) {
			Objects.erase(Objects.begin() + i);
		}
	}
}

bool Sub_NPC_StaticCollision::checkCollision_over(int x_pos, int y_pos) {
	if (should_check == true) { 
		if (scx == x_pos && scy == y_pos) {
			return true;
		}
		else {
			return false;
		}
	}
	
}

bool Sub_NPC_StaticCollision::checkCollision(int x_pos, int y_pos) {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		if (Objects[i]->checkCollision_over(x_pos, y_pos) == true) {
			return true;
		}
	}
	return false;
}

Sub_NPC_StaticCollision::Sub_NPC_StaticCollision() {
	Objects.push_back(this);
}