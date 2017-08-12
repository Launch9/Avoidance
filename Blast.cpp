#include "stdafx.h"
#include "Blast.h"
#include "Player.h"
#include "NPC_MOTHER.h"
#include "Basic_Tile_MOTHER.h"
#include "Sound.h"
#include "random2.h"
#include "Sub_NPC_A.h"
#define max_dist_type_2 10
#define max_dist_type_3_least 5
#define max_dist_type_3_max 15
std::vector<Blast *> Blast::Objects;

Blast::Blast(int Type, int x_pos, int y_pos, TileMap &TM)
{
	type = Type;
	Tmap = &TM;
	bool should_leave = false;
	int rnd_num = random2::randomrange(max_dist_type_3_least, max_dist_type_3_max);
	switch (type) {
	case 0: //Single explosion: simple, standard, nothing special.
		Blasts.push_back(new B(0, All_Sprites[TM.getTextureID()][1][0], 0.2, x_pos, y_pos));
		c_rect = sf::IntRect(x_pos,y_pos,32,32);
		break;
	case 1:
		Blasts.push_back(new B(0, All_Sprites[TM.getTextureID()][1][0], 0.2, x_pos - 32, y_pos - 32));
		Blasts.push_back(new B(0, All_Sprites[TM.getTextureID()][1][0], 0.2, x_pos, y_pos - 32));
		Blasts.push_back(new B(0, All_Sprites[TM.getTextureID()][1][0], 0.2, x_pos + 32, y_pos - 32));
		Blasts.push_back(new B(0, All_Sprites[TM.getTextureID()][1][0], 0.2, x_pos - 32, y_pos));
		Blasts.push_back(new B(0, All_Sprites[TM.getTextureID()][1][0], 0.2, x_pos, y_pos));
		Blasts.push_back(new B(0, All_Sprites[TM.getTextureID()][1][0], 0.2, x_pos + 32, y_pos));
		Blasts.push_back(new B(0, All_Sprites[TM.getTextureID()][1][0], 0.2, x_pos - 32, y_pos + 32));
		Blasts.push_back(new B(0, All_Sprites[TM.getTextureID()][1][0], 0.2, x_pos, y_pos + 32));
		Blasts.push_back(new B(0, All_Sprites[TM.getTextureID()][1][0], 0.2, x_pos + 32, y_pos + 32));
		c_rect = sf::IntRect(x_pos - 32, y_pos - 32, 96, 96);
		break;
	case 2:
		dists = { 0,0,0,0 };
		
		for (unsigned int i = 0; i < dists.size(); i++) {
			for (unsigned int b = 0; b < max_dist_type_2; b++) {
				switch (i) {
				case 0:
					if (Basic_Tile_MOTHER::CheckCollision(x_pos, y_pos - ((b + 1) * 32)) == true) {
						dists[i] = b;
						should_leave = true;
					}
					break;
				case 1:
					if (Basic_Tile_MOTHER::CheckCollision(x_pos + ((b + 1) * 32), y_pos) == true) {
						dists[i] = b;
						should_leave = true;
					}
					break;
				case 2:
					if (Basic_Tile_MOTHER::CheckCollision(x_pos, y_pos + ((b + 1) * 32)) == true) {
						dists[i] = b;
						should_leave = true;
					}
					break;
				case 3:
					if (Basic_Tile_MOTHER::CheckCollision(x_pos - ((b + 1) * 32), y_pos) == true) {
						dists[i] = b;
						should_leave = true;
					}
					break;
				}
				if (should_leave == true) {
					should_leave = false;
					break;
				}
				else if (b == max_dist_type_2 - 1) {
					dists[i] = b;
					break;
				}
				
			}
			
		}
		ani = All_Sprites[TM.getTextureID()][1][0];
		Blasts.push_back(new B(0, All_Sprites[TM.getTextureID()][1][0], 0.07, x_pos, y_pos));

		c_rect = sf::IntRect(x_pos, y_pos, 32, 32);
		break;
	case 3:
		dists = { 0,0,0,0 };
		
			
			for (unsigned int b = 0; b < rnd_num; b++) {
				
				
				if (Basic_Tile_MOTHER::CheckCollision(x_pos, y_pos + ((b + 1) * 32)) == true) {
					dists[2] = b;
					should_leave = true;
				}
					
				
				if (should_leave == true) {
					should_leave = false;
					break;
				}
				else if (b == rnd_num - 1) {
					dists[2] = b;
					break;
				}

			}
			ani = All_Sprites[TM.getTextureID()][1][0];
			Blasts.push_back(new B(1, All_Sprites[TM.getTextureID()][1][0], 0.07, x_pos, y_pos));
			type = 3;
			c_rect = sf::IntRect(x_pos, y_pos, 32, 32);
			break;
		
		
	}
	initx = x_pos;
	inity = y_pos;
	Objects.push_back(this);

}

void Blast::tick() {
	int blastindex = 0;
	for (unsigned int i = 0; i < Blasts.size(); i++) {
		Blasts[i]->animate();
	}
	for (unsigned int i = 0; i < Blasts.size(); i++) {
		if (Blasts[i]->x == Player::PlayerObjects[0]->getcx() && Blasts[i]->y == Player::PlayerObjects[0]->getcy()) {
			if (Blasts[i]->svectorindex < Blasts[i]->anisprites.size() - 3 && Blasts[i]->svectorindex > 0) {
				Player::PlayerObjects[0]->Die();
			}
			
		}
	}
	
		for (unsigned int b = 0; b < Blasts.size(); b++) {
			int g = Sub_NPC_A::StaticCheckCollision(sf::Vector2f(Blasts[b]->x, Blasts[b]->y));
			if (g != -1) {
			//if (Blasts[b]->x == Sub_NPC_A::Object_Cache[i]->getPosition().x && Blasts[b]->y == Sub_NPC_A::Object_Cache[i]->getPosition().y) {
				Sub_NPC_A::Object_Cache[g]->delete_self(Sub_NPC_A::Object_Cache[g]);
			}
		}
	
	switch (type) {
	case 0:
		if (Blasts.size() == 0) {
			ready_to_be_deleted = true;
		}
		break;
	case 1:
		if (Blasts.size() == 0) {
			ready_to_be_deleted = true;
		}
		break;
	case 2:
		
		if (Blasts.size() != 0) {
			if (iters != dists) {
				for (unsigned int i = 0; i < Blasts.size(); i += 4) {
					if (Blasts[i]->toggle == false) {
						if (Blasts[i]->svectorindex >= floor(Blasts[i]->anisprites.size() / 2)) {
							Blasts[i]->toggle = true;
							Sound::Play(47, 0, 0, random2::randomrange(1, 5));
							for (unsigned int b = 0; b < dists.size(); b++) {
								if (iters[b] != dists[b]) {
									iters[b]++;
									switch (b) {
									case 0:
										Blasts.push_back(new B(0, ani, 0.07, initx, inity - (iters[b] * 32)));
										break;
									case 1:
										Blasts.push_back(new B(0, ani, 0.07, initx + (iters[b] * 32), inity));
										break;
									case 2:
										Blasts.push_back(new B(0, ani, 0.07, initx, inity + (iters[b] * 32)));
										break;
									case 3:
										Blasts.push_back(new B(0, ani, 0.07, initx - (iters[b] * 32), inity));
										break;
									}


								}

							}
						}
					}
				}
				
			}
		}
		else {
			ready_to_be_deleted = true;
		}
		break;
	case 3:
		
		if (Blasts.size() != 0) {
			if (iters != dists) {
				for (unsigned int i = 0; i < Blasts.size(); i += 4) {
					if (Blasts[i]->toggle == false) {
						if (Blasts[i]->svectorindex >= floor(Blasts[i]->anisprites.size() / 2)) {
							Blasts[i]->toggle = true;
							Sound::Play(47, 0, 0, random2::randomrange(1, 5));
							for (unsigned int b = 0; b < dists.size(); b++) {
								if (iters[b] != dists[b]) {
									iters[b]++;
									switch (b) {
									case 0:
										Blasts.push_back(new B(1, ani, 0.07, initx, inity - (iters[b] * 32)));
										break;
									case 1:
										Blasts.push_back(new B(1, ani, 0.07, initx + (iters[b] * 32), inity));
										break;
									case 2:
										Blasts.push_back(new B(1, ani, 0.07, initx, inity + (iters[b] * 32)));
										break;
									case 3:
										Blasts.push_back(new B(1, ani, 0.07, initx - (iters[b] * 32), inity));
										break;
									}


								}
								

							}
						}
					}
				}

			}
			else {
				if (made_new_blast == false) {
					made_new_blast = true;
					new Blast(2, Blasts[0]->x, Blasts[0]->y, *Tmap);
				}
				
			}
		}
		else {
			
			ready_to_be_deleted = true;
		}
		//if (Blasts.size() == 0) {
			
			
		//}
	}
	check_Blasts_delete();
}

void Blast::tick_all() {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		Objects[i]->tick();
	}
	check_delete();
}

void Blast::check_delete() {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		if (Objects[i]->ready_to_be_deleted == true) {
			delete Objects[i];
			Objects.erase(Objects.begin() + i);
			i--;
		}
	}
}

void Blast::check_Blasts_delete() {
	for (unsigned int i = 0; i < Blasts.size(); i++) {
		if (Blasts[i]->ready_to_be_deleted == true) {
			delete Blasts[i];
			Blasts.erase(Blasts.begin() + i);
			if (i != 0) {
				i--;
			}
		}
	}
}

void Blast::clear_all() {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		delete Objects[i];
	}
	Objects.clear();
}

Blast::~Blast() {
	for (unsigned int i = 0; i < Blasts.size(); i++) {
		delete Blasts[i];
	}
	Blasts.clear();
}