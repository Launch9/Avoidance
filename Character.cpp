#include "stdafx.h"
#include "Character.h"
#include "GF.h"
#include <iostream>
#include "Dia.h"
#include "Player.h"
#include "P_Switch_MAIN.h"
#include "random2.h"
#include "Sound.h"
Character::Character(int startx, int starty, int type, TileMap &TM)
{
	x = startx;
	y = starty;
	typeID = 3;
	//Europa's graphics
	std::vector<AniT> v0 = All_Sprites[TM.getTextureID()][typeID][0];
	std::vector<AniT> v1 = All_Sprites[TM.getTextureID()][typeID][1];
	std::vector<AniT> v2 = All_Sprites[TM.getTextureID()][typeID][2];
	std::vector<AniT> v3 = All_Sprites[TM.getTextureID()][typeID][3];
	std::vector<AniT> v4 = All_Sprites[TM.getTextureID()][typeID][4];
	std::vector<AniT> v5 = All_Sprites[TM.getTextureID()][typeID][5];
	std::vector<AniT> v6 = All_Sprites[TM.getTextureID()][typeID][6];
	//Anode's graphics
	std::vector<AniT> v7 = All_Sprites[TM.getTextureID()][typeID][7];
	std::vector<AniT> v8 = All_Sprites[TM.getTextureID()][typeID][8];
	std::vector<AniT> v9 = All_Sprites[TM.getTextureID()][typeID][9];
	std::vector<AniT> v10 = All_Sprites[TM.getTextureID()][typeID][10];
	std::vector<AniT> v11 = All_Sprites[TM.getTextureID()][typeID][11];
	std::vector<AniT> v12 = All_Sprites[TM.getTextureID()][typeID][12];
	//Anode on rock.
	std::vector<AniT> v13 = All_Sprites[TM.getTextureID()][typeID][13]; //Standing still
	std::vector<AniT> v14 = All_Sprites[TM.getTextureID()][typeID][14]; //Blinking
	//V is the walking animation.
	//v2 is stand still animation.
	//v3 is point left animation.
	//v4 is point right animation.
	Sprites = { v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14 };
	switch (type) {
	case 0:
		switch (Player::PlayerObjects[0]->getStoryID()) {
		case 0:
			break;
		case 1:
			x = (2 * 32);
			y = (-6 * 32);
			setCheck(true);
			setAni(6);
			break;
		
		}
		break;
	case 1:
		setAni(1);
		setCheck(true);
		boolean_telling_if_it_is_ready_for_random_blinking_in_the_animate_function_because_I_want_the_character_to_blink_randomly = true;
		break;
	case 2:
		setAni(6);
		setCheck(true);
		boolean_telling_if_it_is_ready_for_random_blinking_in_the_animate_function_because_I_want_the_character_to_blink_randomly = false;
		break;
	case 3:
		w_ticks0 = 0;
		max_w_ticks0 = 3;
		AniN = 0;
		boundary0.left = x - (32 * 2);
		boundary0.top = y - (32 * 2);
		boundary0.width = (32 * 4);
		boundary0.height = (32 * 4);
		setAni(9);
		direction0 = 0;
		setCheck(true);
		boolean_telling_if_it_is_ready_for_random_blinking_in_the_animate_function_because_I_want_the_character_to_blink_randomly = true;
		break;
	case 4:
		setAni(13);
		setCheck(true);
		boolean_telling_if_it_is_ready_for_random_blinking_in_the_animate_function_because_I_want_the_character_to_blink_randomly = true;
	
	
	}
	
	GF::CheckTile_OverLap(x, y);
	
	initx = x;
	inity = y;
	delx = x;
	dely = y;
	x2 = x;
	y2 = y;
	x3 = x;
	y3 = y;
	Type = type;
	speed = 100;
	svectorindex = 1;
	SavedParameters = { typeID, startx, starty, type };
	sprite.setTexture(1);
	
	OVERRIDE_ANI = true;
	setWholePos(x, y);
	sprite.setup();
	NPC_Cache.push_back(this);
}

void Character::tick(bool render) {
	Player *PlayerPtr = Player::PlayerObjects[0];
	/*if (Animation == 0) {
		//Stand still animation.
		

	}
	else if (Animation == 1) {

		//Walking animation.
		switch (direction) {
		case 0:
			y -= speed * GF::getDelta();
			if (y <= y2) {

				movinganitick = 0;

			
					ReadyAC = true;
					setAni(0);
					iterate();
				
			}
			break;
		case 1:
			x += speed * GF::getDelta();
			if (x >= x2) {

				movinganitick = 0;

	
				ReadyAC = true;
				setAni(0);
				iterate();
				
			}
			break;
		case 2:
			y += speed * GF::getDelta();
			if (y >= y2) {

				movinganitick = 0;

					ReadyAC = true;
					setAni(0);
					iterate();
			
			}
			break;
		case 3:
			x -= speed * GF::getDelta();
			if (x <= x2) {

				movinganitick = 0;

			
					ReadyAC = true;
					setAni(0);
					iterate();
				
			}
			break;
		}

		
	}*/
		//This only can run if you are not doing a do_animation secquence.
		if (boolean_telling_if_it_is_ready_for_random_blinking_in_the_animate_function_because_I_want_the_character_to_blink_randomly == true && is_doAnimation == false) {
			if (random2::randomrange(1, 200) == 1) {
				switch (Type) {
				case 0:
					doAnimation(1, 2); //Making the animation for blinking occur only if the random number is equal to one.
					break;
				case 1:
					doAnimation(1, 2);
					break;
				case 2:
					doAnimation(1, 2);
					break;
				case 3:
					//if (get_isMoving() == false) {
						switch (direction0) {
						case 0:
							doAnimation(8, 9);
							break;
						case 1:
							doAnimation(8, 9);
							break;
						case 2:
							doAnimation(8, 9);
							break;
						case 3:
							doAnimation(11, 12);
							break;
						}
					//}
					break;
				case 4:
					doAnimation(14, 13);
					break;
				}
			}
		}
		m_tick();
		//Checking the 
		switch (Type) {
		case 0:
			switch (PlayerPtr->getStoryID()) {
			case 0:
				switch (AniN) {
				case 0:
					Dia::Dia(Dia::getDia_sprite(0), "Europa: Hey you!");
					setAni(0);
					moveright(6, speed, GF::getDelta());
					break;
				case 1:
					moveup(4, speed, GF::getDelta());
					break;
				case 2:
					setCheck(true);
					Dia::clear();
					setAni(2);
					boolean_telling_if_it_is_ready_for_random_blinking_in_the_animate_function_because_I_want_the_character_to_blink_randomly = true;
					//doAnimation(1, 2);
					Dia::Dia(Dia::getDia_sprite(0), "Europa: Hey, I have a lot to explain to you. \nPush E to continue the text.");
					Dia::Dia(Dia::getDia_sprite(0), "Europa: You may be wondering why you found yourself\nin a spaceship when you woke up.");
					Dia::Dia(Dia::getDia_sprite(4), "Europa: Well... ");
					Dia::Dia(Dia::getDia_sprite(4), "Europa: Our planet is going to die very soon. ");
					Dia::Dia(Dia::getDia_sprite(0), "Europa: Everyone is already in orbit, \nfar away from anything down here.");
					Dia::Dia(Dia::getDia_sprite(0), "Europa: We were abandoned by our parents. \nWe never got taken to space with them.");
					Dia::Dia(Dia::getDia_sprite(5), "Europa: But, this spaceship, \nI have been working on for a couple of years, \nshould get us up there.");
					Dia::Dia(Dia::getDia_sprite(5), "Europa: I just need a few more parts.");
					Dia::Dia(Dia::getDia_sprite(0), "Europa: So, I would like you to go get the parts for me.");
					Dia::Dia(Dia::getDia_sprite(5), "Europa: Anode is my friend over there.\nHe is all fluffy and adorable.");
					Dia::Dia(Dia::getDia_sprite(0), "Europa: By the way my gauntlet is in my tool box over near the ship. \nCan you please go get it for me.");
					iterate();
					break;
				case 3:
					if (((PlayerPtr->getx() == x + 32 && PlayerPtr->gety() == y) || (PlayerPtr->getx() == x && PlayerPtr->gety() == y + 32)
						|| (PlayerPtr->getx() == x && PlayerPtr->gety() == y - 32)) && P_Switch_MAIN::Switches[0] == true) {
						Dia::clear();
						Dia::Dia(Dia::getDia_sprite(5), "Europa: Just joking, I have one right here.");
						Dia::Dia(Dia::getDia_sprite(0), "Europa: You can keep that piece of junk. \nI don't need it, you probably do.");
						Dia::Dia(Dia::getDia_sprite(0), "Europa: We come from the same village, \nSo I presume you know how these things work.");
						check4 = false;
						iterate();
					}
					else if (PlayerPtr->getx() == x - 32 && PlayerPtr->gety() == y && P_Switch_MAIN::Switches[0] == true) {
						Dia::clear();
						Dia::Dia(Dia::getDia_sprite(5), "Europa: Just joking, I have one right here.");
						Dia::Dia(Dia::getDia_sprite(0), "Europa: You can keep that piece of junk. \nI don't need it, you probably do.");
						Dia::Dia(Dia::getDia_sprite(0), "Europa: We come from the same village, \nSo I presume you know how these things work.");
						check4 = true;
						iterate();
					}
					
					if (PlayerPtr->getx() < -(23 * 32) && P_Switch_MAIN::Switches[0] == true) {
						Dia::clear();
						Dia::Dia(Dia::getDia_sprite(0), "Europa: HEY, WHERE ARE YOU GOING WITH THAT!");
						check3 = true;
						check0 = true;
						iterate();
					}

					check2 = true;
					break;
				case 4:
					if (check3 == true) {
						if (PlayerPtr->getx() >= -(23 * 32)) {
							Dia::clear();
							AniN--;
							check3 = false;
							check0 = false;
						}
						else if (PlayerPtr->getx() <= -(26 * 32)) {
							if (check0 == true) {
								Dia::clear();
								Dia::Dia(Dia::getDia_sprite(0), "Europa: GET BACK HERE WITH THAT GAUNTLET!");
								check0 = false;
							}

						}
					}
					else {
						if (check2 == true) {
							switch (check4) {
							case 0:
								doAnimation(4, 0);
								break;
							case 1:
								doAnimation(3, 0);
							}
							
							check2 = false;
						}
						if (is_doAnimation == false) {
							iterate();
						}
					}


					break;
				case 5:
					boolean_telling_if_it_is_ready_for_random_blinking_in_the_animate_function_because_I_want_the_character_to_blink_randomly = false;
					setCheck(false);
					setAni(0);
					moveleft(4, speed, GF::getDelta());
					check1 = true;
					break;
				case 6:
					if (check1 == true) {
					
						setCheck(true);
						doAnimation(5, 6);
						check1 = false;
					}

					break;

				}
				break;
			case 1:
				break;
			}
			break;
		case 1:
			switch (AniN) {
			case 0:
				check0 = false;
				check2 = true;
					
				
				if (PlayerPtr->getx() == x && PlayerPtr->gety() == y + 32) {
					check0 = true;
					direction0 = 2;
				}
				else if (PlayerPtr->getx() == x + 32 && PlayerPtr->gety() == y) {
					check0 = true;
					direction0 = 1;
				}
				else if (PlayerPtr->getx() == x && PlayerPtr->gety() == y - 32) {
					check0 = true;
					direction0 = 0;
				}
				else if (PlayerPtr->getx() == x - 32 && PlayerPtr->gety() == y) {
					check0 = true;
					direction0 = 3;
				}
				else {
					check0 = false;
					check1 = true;
				}
				if (check0 == true) {
					for (unsigned int i = 0; i < PlayerPtr->get_Obtained_Gauntlets().size(); i++) {
						if (PlayerPtr->get_Obtained_Gauntlets()[i] == 1) {
							check2 = false;
							break;
						}
					}
					if (check2 == true) {
						Dia::Dia(Dia::getDia_sprite(5), "Here is a gauntlet that you might need\n for later dungeons.");
						Dia::Dia(Dia::getDia_sprite(0), "I have been using this gauntlet for a while now\nbut I have no need for it anymore.");
						Dia::Dia(Dia::getDia_sprite(5), "This shoots a huge power shot in the direction\nyou choose.");
						Dia::Dia(Dia::getDia_sprite(5), "Otherwise, it will just shoot a very slow shot\nthat has a lot of power to it.");
						Dia::Dia(Dia::getDia_sprite(5), "Make good use of it please.");
						PlayerPtr->giveItem(5);
						if (direction == 3) {
							doAnimation(3, 2);
						}
						else {
							doAnimation(4, 2);
						}
						check1 = false;
					}
					else if (check1 == true) {
						if (Dia::getcachelength() == 0) {
							Dia::Dia(Dia::getDia_sprite(5), "I love watching the stars under the rain.\nWe are such little creatures under the size \nof the universe.");
							Dia::Dia(Dia::getDia_sprite(5), "I have never been to space before,\nI wonder what it is like.");
							Dia::Dia(Dia::getDia_sprite(5), "It must be beautiful, as we orbit around \n the star.");
							Dia::Dia(Dia::getDia_sprite(5), "I am almost done with the ship\nI just need a few more parts.");
						}
						else {
							Dia::Dia(Dia::getDia_sprite(0), "Someone else is talking to you.\nPerhaps you should go finish.");

						}
						check1 = false;
					}
					
					
				}
				break;
			}
			break;
		case 2:
			
			switch (AniN) {
			case 0:
				check0 = false;
				check2 = true;
				if (PlayerPtr->getx() == x && PlayerPtr->gety() == y + 32) {
					check0 = true;
					direction0 = 2;
				}
				else if (PlayerPtr->getx() == x + 32 && PlayerPtr->gety() == y) {
					check0 = true;
					direction0 = 1;
				}
				else if (PlayerPtr->getx() == x && PlayerPtr->gety() == y - 32) {
					check0 = true;
					direction0 = 3;
				}
				else {
					check0 = false;
					check1 = true;
				}
				if (check0 == true) {
					for (unsigned int i = 0; i < PlayerPtr->get_Obtained_Gauntlets().size(); i++) {
						if (PlayerPtr->get_Obtained_Gauntlets()[i] == 2) {
							check2 = false;
							break;
						}
					}
					if (check2 == true) {
						Dia::Dia(Dia::getDia_sprite(5), "Here is another gauntlet I think you will need.\nI found it while I was cleaning the ship.");
						Dia::Dia(Dia::getDia_sprite(5), "Its pretty old. I wouldn't use it,\nbut your not me, so go ahead!");
						Dia::Dia(Dia::getDia_sprite(0), "This one will bend in the direction an enemy is in.");
						Dia::Dia(Dia::getDia_sprite(0), "But it will only do this one time.");
						Dia::Dia(Dia::getDia_sprite(0), "The power shot makes a very long projectile,\nalso with the ability to bend.\nGood Luck!");
						PlayerPtr->giveItem(4);
						boolean_telling_if_it_is_ready_for_random_blinking_in_the_animate_function_because_I_want_the_character_to_blink_randomly = true;
						doAnimation(4, 2);
						check1 = false;
					}
					else if (check1 == true) {
						setAni(2);
						if (Dia::getcachelength() == 0) {
							Dia::Dia(Dia::getDia_sprite(5), "Thanks for getting the parts,\nWe will be off this planet in no time.");
							Dia::Dia(Dia::getDia_sprite(0), "You have one last part to find. \nIt is in the abandoned tower.");
							Dia::Dia(Dia::getDia_sprite(0), "We had to abandon it because it\ngot invaded by monsters.");

						
						}
						else {
							Dia::Dia(Dia::getDia_sprite(0), "Someone else is talking to you.\nPerhaps you should go finish.");

						}
						check1 = false;
					}

					
				}
				break;
			}
			break;
		case 3:
			w_ticks0 += GF::getDelta();
			//std::cout << w_ticks0 << std::endl;
			//std::cout << boundary0.height << ":::" << boundary0.top << std::endl;
			
			
			
			if (AniN != 0) {
				switch (direction0) {
				case 3:
					setAni(9);
					break;
				case -1:
					std::cout << "Anode movement ended in -1 direction0! Character.cpp, type 3" << std::endl;
					throw("error");
					break;
				default:
					setAni(12);
				}
				direction0 = -1;
				setCheck(true);
				AniN = 0;
			}
			else {
				if (w_ticks0 >= max_w_ticks0) {
					int rdm_int = random2::randomrange(0, 4);
					int move_int = -1;
					//Checking to make sure that the bunny never leaves it's boundary.
					if (x > boundary0.left + boundary0.width) {
						move_int = moveleft(1, speed, GF::getDelta());
						direction0 = 3;
					}
					else if (x < boundary0.left) {
						move_int = moveright(1, speed, GF::getDelta());
						direction0 = 1;
					}
					else if (y > boundary0.top + boundary0.height) {
						move_int = moveup(1, speed, GF::getDelta());
						direction0 = 0;
					}
					else if (y < boundary0.top) {
						move_int = movedown(1, speed, GF::getDelta());
						direction0 = 2;
					}
					else { //This is called if the bunny is within it's boundary.
						switch (rdm_int) {
						case 0:
							move_int = moveup(1, speed, GF::getDelta());
							direction0 = 0;
							break;
						case 1:
							move_int = moveright(1, speed, GF::getDelta());
							direction0 = 1;
							break;
						case 2:
							move_int = movedown(1, speed, GF::getDelta());
							direction0 = 2;
							break;
						case 3:
							move_int = moveleft(1, speed, GF::getDelta());
							direction0 = 3;

							break;
						default:
							std::cout << "Default anode movement!" << std::endl;
						}
					}

					switch (move_int) {
					case 2:
						switch (direction0) {
						case 3:
							setAni(7);
							break;
						default:
							setAni(10);
						}
						setCheck(false);
						break;
					}
					w_ticks0 = 0;
				}
			}
											     
			
			//break;
		}
		//sprite.setPosition(x, y);
	
	
}

void Character::setAni(int num) {
	
	if (num != last_num) {
		switch (num) {
		case 0://Walk
			Aniset(0);
			max_ticks = 0.09;
			Animation = num;
			break;
		case 1://Blink
			Aniset(1);
			max_ticks = 0.03;
			Animation = num;
			break;
		case 2: //Standstill
			Aniset(2);
			max_ticks = 1000000;
			//Aniset(2);
			//boolean_telling_if_it_is_ready_for_random_blinking_in_the_animate_function_because_I_want_the_character_to_blink_randomly = true;
			//max_ticks = 10000000;
			Animation = num;
			break;
		case 3: //Hand out left
			Aniset(3);
			max_ticks = 0.7;
			Animation = num;
			break;
		case 4: //Hand out right
			Aniset(4);
			max_ticks = 0.7;
			Animation = num;
			break;
		case 5:
			//Moving hands to firing position left
			Aniset(5);
			max_ticks = 0.09;
			Animation = num;
			break;
		case 6:
			//Welding with laser animation.
			Aniset(6);
			max_ticks = 0.09;
			Animation = num;
			break;


		//Anode's animations:-=-=-=-=-=-=-=-=-=-=-=-=-

		default:
			Aniset(num);
			max_ticks = 0.03;
			Animation = num;
			break;

		}
		last_num = num;
		
	}
	
}

/*void Character::moveup(int distance) {
	distance += 1;
	if (ReadyAC == true) {
		for (unsigned int i = 0; i < distance; i++) {
			if (Basic_Tile_MOTHER::CheckCollision(x2, y2 - 32) == false) {
				setAni(1);
				direction = 0;
				y2 = y3 - (i * 32);
				
				ReadyAC = false;
			}
			else {
				Aniset(0);
				break;
			}
			
		}
		y3 = y2;
		
		
	}
	

}
void Character::movedown(int distance) {
	distance += 1;
	if (ReadyAC == true) {
		for (unsigned int i = 0; i < distance; i++) {
			if (Basic_Tile_MOTHER::CheckCollision(x2, y2 + 32) == false) {
				setAni(1);
				direction = 2;

				y2 = y3 + (i * 32);
				
				ReadyAC = false;
			}
			else {
				Aniset(0);
				break;
			}

		}
		y3 = y2;
	}
}
void Character::moveleft(int distance) {
	distance += 1;
	if (ReadyAC == true) {
		for (unsigned int i = 0; i < distance; i++) {
			if (Basic_Tile_MOTHER::CheckCollision(x2 - 32, y2) == false) {
				setAni(1);
				direction = 3;

				x2 = x3 - (i * 32);
				
				ReadyAC = false;
			}
			else {
				Aniset(0);
				break;
			}

		}
		x3 = x2;
	}
}
void Character::moveright(int distance) {
	distance += 1;
	if (ReadyAC == true) {
		for (unsigned int i = 0; i < distance; i++) {
			if (Basic_Tile_MOTHER::CheckCollision(x2 + 32, y2) == false) {
				setAni(1);
				direction = 1;
				x2 = x3 + (i * 32);
				ReadyAC = false;
			}
			else {
				Aniset(0);
				break;
			}

		}
		x3 = x2;
	}
}*/

void Character::iterate() {
	AniN++;
}

void Character::reset() {

}

void Character::next() {
	iterate();
}

void Character::animate() {
	ticks += GF::getDelta();
	//This is used to check to see if the ticks have reached the amount given.
	//This will add a spriteindex if conditions are met.
	if (ticks >= max_ticks) {
		ticks = 0;
		//This is used to check to see if the animation has reached the last frame in the vector full of sprites.
		if (svectorindex >= anisprites.size() - 1) {
			if (is_doAnimation == true) { //Finished doAnimation
				setAni(last_enddoAninum);
				last_enddoAninum = -1;
				last_doAninum = -1;
				is_doAnimation = false;
			}
			svectorindex = 0;
		}
		else {
			svectorindex++;
		}
		//Setting the sprite texture to the cordinates of the AniT in the Sprites vector according to animation variables.
		sprite *= anisprites[svectorindex];
	}
}

void Character::doAnimation(int doNum, int endNum) {
	if (last_doAninum != doNum) {
		last_doAninum = doNum;
		last_enddoAninum = endNum;
		is_doAnimation = true;
		setAni(doNum);
	}
}

void Character::setCheck(bool TF) {
	should_check = TF;
	scx = x;
	scy = y;
}