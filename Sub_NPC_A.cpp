#include "stdafx.h"
#include "Sub_NPC_A.h"
#include "GF.h"
#include <iostream>
#include "Wall.h"
Sub_NPC_A::Move_Data Sub_NPC_A::M_Data;
std::vector<Sub_NPC_A *> Sub_NPC_A::Object_Cache;

Sub_NPC_A::Sub_NPC_A() {
	
	//Putting this object into the vector.
	Object_Cache.push_back(this);
}

Sub_NPC_A::~Sub_NPC_A() {
	for (unsigned int i = 0; i < Object_Cache.size(); i++) {
		if (Object_Cache[i] == this) {
			Object_Cache.erase(Object_Cache.begin() + i);
		}
	}
}
int Sub_NPC_A::findQuadrant(float x_pos, float y_pos) {
	if (x_pos < x && y_pos > y) {
		//quadrant 3, bottom_left
		return 3;
	}
	else if (x_pos > x && y_pos > y) {
		//quadrant 4, bottom_right
		return 4;
	}
	else if (x_pos < x && y_pos < y) {
		//quadrant 2, top_left
		return 2;
	}
	else if (x_pos > x && y_pos < y) {
		//quadrant 1, top_right
		return 1;
	}
	else {
		//Exactly in between quadrants.
		return -1;
	}
}

int Sub_NPC_A::moveup(int amount, float new_speed, float remainder) {

	if (movingdirection == -1) {
		C_position.x = x;
		C_position.y = y;
		for (unsigned int i = 1; i < amount + 1; i++) {
			if (Wall::CheckCollision(x, y - (32 * i)) == true) {
				movingamount = (i - 1) * 32;
				if (movingamount == 0) {
					return -1;
				}
				speed = new_speed;
				movingdirection = 0;
				
				if (remainder < movingamount) {
					howMuchDone += remainder;
				}
				
				y -= movingamount;
				return 1;
			}
			else {
				if (Check_C(C_position.x, C_position.y - (32 * i)) == true) {
					movingamount = (i - 1) * 32;
					if (movingamount == 0) {
						return -1;
					}
					speed = new_speed;
					movingdirection = 0;

					if (remainder < movingamount) {
						howMuchDone += remainder;
					}

					y -= movingamount;
					return 3;
				}
			}
		}
		speed = new_speed;
		movingdirection = 0;
		movingamount = amount * 32;
		if (remainder < movingamount) {
			
			howMuchDone += remainder;
		}
		
		y -= movingamount;
		return 2;
	}
	return 0;
}

int Sub_NPC_A::movedown(int amount, float new_speed, float remainder) {
	if (movingdirection == -1) {
		C_position.x = x;
		C_position.y = y;
		for (unsigned int i = 1; i < amount + 1; i++) {
			if (Wall::CheckCollision(x, y + (32 * i)) == true) {
				movingamount = (i - 1) * 32;
				if (movingamount == 0) {
					return -1;
				}
				speed = new_speed;
				movingdirection = 2;
				
				if (remainder < movingamount) {
					howMuchDone += remainder;
				}
				y += movingamount;
				return 1;
			}
			else {
				if (Check_C(C_position.x, C_position.y + (32 * i)) == true) {
					movingamount = (i - 1) * 32;
					if (movingamount == 0) {
						return -1;
					}
					speed = new_speed;
					movingdirection = 2;

					if (remainder < movingamount) {
						howMuchDone += remainder;
					}
					y += movingamount;
					return 3;
				}
			}
		}
		speed = new_speed;
		movingdirection = 2;
		movingamount = amount * 32;
		if (remainder < movingamount) {
			howMuchDone += remainder;
		}
		y += movingamount;
		return 2;
	}
	return 0;
}

int Sub_NPC_A::moveleft(int amount, float new_speed, float remainder) {
	if (movingdirection == -1) {
		C_position.x = x;
		C_position.y = y;
		for (unsigned int i = 1; i < amount + 1; i++) {
			if (Wall::CheckCollision(x - (32 * i), y) == true) {
				movingamount = (i - 1) * 32;
				if (movingamount == 0) {
					return -1;
				}
				speed = new_speed;
				movingdirection = 3;
				
				if (remainder < movingamount) {
					howMuchDone += remainder;
				}
				x -= movingamount;
				return 1;
			}
			else {
				if (Check_C(C_position.x - (32 * i), C_position.y) == true) {
					movingamount = (i - 1) * 32;
					if (movingamount == 0) {
						return -1;
					}
					speed = new_speed;
					movingdirection = 3;

					if (remainder < movingamount) {
						howMuchDone += remainder;
					}
					x -= movingamount;
					return 3;
				}
			}
		}
		speed = new_speed;
		movingdirection = 3;
		movingamount = amount * 32;
		if (remainder < movingamount) {
			howMuchDone += remainder;
		}
		x -= movingamount;
		return 2;
	}
	return 0;
}

int Sub_NPC_A::moveright(int amount, float new_speed, float remainder) {
	if (movingdirection == -1) {
		C_position.x = x;
		C_position.y = y;
		for (unsigned int i = 1; i < amount + 1; i++) {
			if (Wall::CheckCollision(x + (32 * i), y) == true) {
				movingamount = (i - 1) * 32;
				if (movingamount == 0) {
					return -1;
				}
				speed = new_speed;
				movingdirection = 1;
				
				if (remainder < movingamount) {
					howMuchDone += remainder;
				}
				x += movingamount;
				return 1;
			}
			else {
				if (Check_C(C_position.x + (32 * i), C_position.y) == true) {
					movingamount = (i - 1) * 32;
					if (movingamount == 0) {
						return -1;
					}
					speed = new_speed;
					movingdirection = 1;

					if (remainder < movingamount) {
						howMuchDone += remainder;
					}
					x += movingamount;
					return 3;
				}
			}
		}
		
		speed = new_speed;
		movingdirection = 1;
		movingamount = amount * 32;
		if (remainder < movingamount) {
			howMuchDone += remainder;
		}
		x += movingamount;
		return 2;
	}
	return 0;
}

void Sub_NPC_A::m_tick() {
	if (movingdirection != -1) {
		howMuchDone = howMuchDone + (speed * GF::getDelta());
		
		switch (movingdirection) {
		case 0:
			
			sprite.setPosition(x, (y + movingamount) - howMuchDone);
			if (howMuchDone >= movingamount) {
				C_position.x = x;
				C_position.y = y;
				sprite.setPosition(x, y);
				stop_ani();
				next();
			}
			break;
		case 1:
			sprite.setPosition((x - movingamount) + howMuchDone, y);
			if (howMuchDone >= movingamount) {
				C_position.x = x;
				C_position.y = y;
				sprite.setPosition(x, y);
				stop_ani();
				next();
			}
			break;
		case 2:
			sprite.setPosition(x, (y - movingamount) + howMuchDone);
			if (howMuchDone >= movingamount) {
				C_position.x = x;
				C_position.y = y;
				sprite.setPosition(x, y);
				stop_ani();
				next();
			}
			break;
		case 3:
			sprite.setPosition((x + movingamount) - howMuchDone, y);
			if (howMuchDone >= movingamount) {
				C_position.x = x;
				C_position.y = y;
				sprite.setPosition(x, y);
				stop_ani();
				next();
			}
			break;
		}
	}
	
	
}

void Sub_NPC_A::stop_ani() {
	movingdirection = -1;
	movingamount = 0;
	howMuchDone = 0;
}



void Sub_NPC_A::set_moved(int speed, int direction, int num_of_spaces, float remainder) {
	M_Data.is_ready = true;
	M_Data.direction = direction;
	M_Data.spaces = num_of_spaces;
	M_Data.remainder = remainder;
	M_Data.Speed = speed;
}


void Sub_NPC_A::A_tick() {
	if (M_Data.is_ready == true) {
		for (unsigned int i = 0; i < Object_Cache.size(); i++) {
			Object_Cache[i]->ifPlayerMoved(M_Data.Speed, M_Data.direction, M_Data.spaces, M_Data.remainder);
		}
		M_Data.is_ready = false;
	}

}

int Sub_NPC_A::findDirection(float x_pos, float y_pos) {
	if (x_pos == x) {
		if (y_pos < y) {
			//Upward
			return 0;
		}
		else if (y_pos > y) {
			//Downward
			return 2;
		}
		else {
			//If the points are on top of each other.
			return -1;
		}
	}
	else if (y_pos == y) {
		if (x_pos > x) {
			//Rightward
			return 1;
		}
		else if (x_pos < x) {
			//Leftward
			return 3;
		}
		else {
			//If the points are on top of each other.
			return -1;
		}
	}
}

bool Sub_NPC_A::get_isMoving() {
	if (movingdirection == -1) {
		return false;
	}
	else {
		return true;
	}
}

bool Sub_NPC_A::Check_C(int sx_pos, int sy_pos) {
	
	for (unsigned int i = 0; i < Object_Cache.size(); i++) {
		
		if (sx_pos == Object_Cache[i]->x && sy_pos == Object_Cache[i]->y && Object_Cache[i]->get_is_dead() == false) {
			
			return true;
		}
	}
	return false;

}

const sf::Vector2i &Sub_NPC_A::get_C_position() {
	return C_position;
}

void Sub_NPC_A::ifPlayerMoved(int speed, int direction, int spaces, float remainder) {

}

void Sub_NPC_A::reset() {
	x = initx;
	y = inity;
	C_position.x = initx;
	C_position.y = inity;
	stop_ani();
	sprite.setPosition(x, y);
}

bool Sub_NPC_A::checkLoop(int distance, int startingdirection, int speed, float remainder) {

	for (unsigned int i = 0; i < 3; i++) {

		switch (startingdirection) {
		case 0:
			switch (moveup(distance, speed, remainder)) {
			case 0:
				return false;
			case 1:
				break;
			case 2:
				return true;
			case 3:
				break;
			}
			break;
		case 1:
			switch (moveright(distance, speed, remainder)) {
			case 0:
				return false;
			case 1:
				break;
			case 2:
				return true;
			case 3:
				break;
			}
			break;
		case 2:
			switch (movedown(distance, speed, remainder)) {
			case 0:
				return false;
			case 1:
				break;
			case 2:
				return true;
			case 3:
				break;
			}
			break;
		case 3:
			switch (moveleft(distance, speed, remainder)) {
			case 0:
				return false;
			case 1:
				break;
			case 2:
				return true;
			case 3:
				break;
			}
		}
		startingdirection++;
		if (startingdirection > 3) {
			startingdirection = 0;
		}
	}
	return false;
}

void Sub_NPC_A::next() {

}

int Sub_NPC_A::StaticCheckCollision(const sf::Vector2f &position) {
	for (unsigned int i = 0; i < Object_Cache.size(); i++) {
		if (position.x == Object_Cache[i]->getx() && position.y == Object_Cache[i]->gety()) {
			return i;
		}
	}
	
	return -1;
}

int Sub_NPC_A::DynamicCheckCollision(const sf::FloatRect &rect) {
	for (unsigned int i = 0; i < Object_Cache.size(); i++) {
		if (Object_Cache[i]->did_delete_self == false) {
			if ((Object_Cache[i]->get_C_position().x + 16 > rect.left && Object_Cache[i]->get_C_position().x + 16 < rect.left + rect.width) && (Object_Cache[i]->get_C_position().y + 16 > rect.top && Object_Cache[i]->get_C_position().y + 16 < rect.top + rect.height)) {
				
				return i;
			}
		}
		
	}
	return -1;

}