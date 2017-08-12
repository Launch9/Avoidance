#include "stdafx.h"
#include "NPC_MOTHER.h"
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include "Player.h"
#include <cmath>
#include "Debug.h"
#include "Cam.h"
#include <string>
#include "P_Switch_MAIN.h"
#define PlayerWidth 32
#define PlayerHeight 32
#define CamChan 0
//This is a static class that holds pointers to any derived class of the NPC_MOTHER class.
std::vector<NPC_MOTHER *> NPC_MOTHER::NPC_Cache;
std::vector<NPC_MOTHER *> NPC_MOTHER::Objects_to_be_deleted;
std::vector<std::vector<std::vector<std::vector<AniT>>>> NPC_MOTHER::All_Sprites;
std::vector<NPC_MOTHER *> NPC_MOTHER::Objects_to_be_put;
float NPC_MOTHER::GlobalSpeed;
bool NPC_MOTHER::ISPD;
NPC_MOTHER::~NPC_MOTHER() {
	
}
void NPC_MOTHER::animate() {
	
	ticks += GF::getDelta();
	
	//This is used to check to see if the ticks have reached the amount given.
	//This will add a spriteindex if conditions are met.
	if (ticks >= max_ticks) {
		ticks = 0;
		
		
		//This is used to check to see if the animation has reached the last frame in the vector full of sprites.
		if (svectorindex >= anisprites.size() - 1) {
			
			svectorindex = 0;
		}
		else {
			svectorindex++;
		}
		//Setting the sprite texture to the cordinates of the AniT in the Sprites vector according to animation variables.
		sprite *= anisprites[svectorindex];
		
	}
	
}
void NPC_MOTHER::maininit(sf::Texture &tex, sf::Texture &ctex) {
	for (unsigned int i = 0; i < 13; i++) {
		All_Sprites.push_back({}); //Filling empty indices
	}
	for (unsigned int i = 0; i < 8; i++) {
		All_Sprites[1].push_back({}); //Filling empty indices
	}
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Lobby Sprites-=-=-=-=-=-=-=-=-=-=-Texture-0
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Laser sprites~~~
	AniT tl0(sf::IntRect(320, 192, 32, 32));
	AniT tl1(sf::IntRect(320, 192 + 32, 32, 32));
	AniT tl2(sf::IntRect(320, 256, 32, 32));
	AniT tl3(sf::IntRect(320 + 32, 256, 32, 32));
	All_Sprites[1][0] = { {tl0, tl1}, {tl2,tl3} };
	//-=======================================================================-//
	//-=======================================================================-//
	//-=======This makes the character graphics!-=============================-//
	//-=======================================================================-//
	//-=======================================================================-//
	//This makes Europa's graphics.
	AniT tce0(sf::IntRect(544, 0, 32, 32));
	AniT tce1(sf::IntRect(544, (32 * 1), 32, 32));
	AniT tce2(sf::IntRect(544, (32 * 2), 32, 32));
	AniT tce3(sf::IntRect(544, (32 * 3), 32, 32));
	AniT tce4(sf::IntRect(544, (32 * 4), 32, 32));
	AniT tce5(sf::IntRect(544, (32 * 5), 32, 32));
	AniT tce6(sf::IntRect(544, (32 * 6), 32, 32));
	AniT tce7(sf::IntRect(544, (32 * 7), 32, 32));
	//Moving hands to shoot laser out of the gauntlet to build.
	AniT tce8(sf::IntRect(512, 0, 32, 32));
	AniT tce9(sf::IntRect(512, 32, 32, 32));
	AniT tce10(sf::IntRect(512, 64, 32, 32));
	//Shooting laser
	AniT tce11(sf::IntRect(512, 96, 32, 32));
	AniT tce12(sf::IntRect(512, 128, 32, 32));


	//This makes anode's graphics.-=-=-=-=-=-=-=-
	AniT tca0(sf::IntRect(224, 0, 32, 32));
	AniT tca1(sf::IntRect(224, 32, 32, 32));
	AniT tca2(sf::IntRect(224, 64, 32, 32));
	AniT tca3(sf::IntRect(224, 96, 32, 32));
	AniT tca4(sf::IntRect(224 + 32, 0, 32, 32));
	AniT tca5(sf::IntRect(224 + 32, 32, 32, 32));
	AniT tca6(sf::IntRect(224 + 32, 64, 32, 32));
	AniT tca7(sf::IntRect(224 + 32, 96, 32, 32));
	//Bunny on a rock
	AniT tca8(sf::IntRect(224, 128, 32, 32));
	AniT tca9(sf::IntRect(224, 128 + 32, 32, 32));
	AniT tca10(sf::IntRect(224, 128 + 64, 32, 32));
	All_Sprites[1][3] = { { tce3, tce2, tce1, tce0, tce1, tce2 },{ tce4, tce5, tce4 },{ tce3 },{ tce6 },{ tce7 },{ tce8, tce9, tce10 },{ tce11, tce12 },
	{ tca3 },{ tca0, tca1, tca2, tca1 },{ tca0 },{ tca7 },{ tca4,tca5,tca6,tca5 },{ tca4 },{tca8}, {tca9,tca10,tca9} };
	//Red slime enemy sprites~~~
	//Standing still
	AniT ts0(sf::IntRect(0, 416, 32, 32));
	AniT ts1(sf::IntRect(0, 416 + 32, 32, 32));
	AniT ts2(sf::IntRect(0, 416 + 64, 32, 32));
	AniT ts3(sf::IntRect(0, 416 + 96, 32, 32));
	//Blinking
	AniT ts4(sf::IntRect(0, 416 + 128, 32, 32));
	//Jumping in order
	AniT ts5(sf::IntRect(32,416,32,32));
	AniT ts6(sf::IntRect(32,416 + (32 * 1), 32, 32));
	AniT ts7(sf::IntRect(32,416 + (32 * 2), 32, 32));
	AniT ts8(sf::IntRect(32,416 + (32 * 3), 32, 32));
	AniT ts9(sf::IntRect(32,416 + (32 * 4), 32, 32));
	AniT ts10(sf::IntRect(64,416 + (32 * 4), 32, 32));
	AniT ts11(sf::IntRect(64,416 + (32 * 3), 32, 32));
	AniT ts12(sf::IntRect(64,416 + (32 * 2), 32, 32));
	AniT ts13(sf::IntRect(64,416 + (32 * 1), 32, 32));
	AniT ts14(sf::IntRect(64,416 + (32 * 0), 32, 32));
	AniT ts15(sf::IntRect(96,416 + (32 * 0), 32, 32));
	AniT ts16(sf::IntRect(96,416 + (32 * 1), 32, 32));
	AniT ts17(sf::IntRect(96,416 + (32 * 2), 32, 32));

	All_Sprites[1][5] = { {ts0,ts1,ts2,ts3,ts1,ts2,ts0,ts3}, {ts5,ts6,ts7,ts8,ts9,ts10,ts11,ts12,ts13,ts14,ts15,ts16,ts17}, {ts4} };
	for (unsigned int i = 0; i < 23; i++) {
		All_Sprites[3].push_back({}); //Filling empty indices
	}
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Lobby2 Sprites-=-=-=-=-=-=-=-=-=-=-Texture-0
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Laser sprites~~~
	AniT ul0(sf::IntRect(320, 192, 32, 32));
	AniT ul1(sf::IntRect(320, 192 + 32, 32, 32));
	AniT ul2(sf::IntRect(320, 256, 32, 32));
	AniT ul3(sf::IntRect(320 + 32, 256, 32, 32));
	All_Sprites[3][0] = { { ul0, ul1 },{ ul2,ul3 } };
	//-=======================================================================-//
	//-=======================================================================-//
	//-=======This makes the character graphics!-=============================-//
	//-=======================================================================-//
	//-=======================================================================-//
	//This makes Europa's graphics.
	AniT uce0(sf::IntRect(544, 0, 32, 32));
	AniT uce1(sf::IntRect(544, (32 * 1), 32, 32));
	AniT uce2(sf::IntRect(544, (32 * 2), 32, 32));
	AniT uce3(sf::IntRect(512, 160, 32, 32));
	AniT uce4(sf::IntRect(512, 192, 32, 32)); //Blinking sprites
	AniT uce5(sf::IntRect(512, 192 + 32, 32, 32)); //Blinking sprites
	AniT uce6(sf::IntRect(544, (32 * 6), 32, 32));
	AniT uce7(sf::IntRect(544, (32 * 7), 32, 32));
	//Moving hands to shoot laser out of the gauntlet to build.
	AniT uce8(sf::IntRect(512, 0, 32, 32));
	AniT uce9(sf::IntRect(512, 32, 32, 32));
	AniT uce10(sf::IntRect(512, 64, 32, 32));
	//Shooting laser
	AniT uce11(sf::IntRect(512, 96, 32, 32));
	AniT uce12(sf::IntRect(512, 128, 32, 32));


	//This makes anode's graphics.-=-=-=-=-=-=-=-
	AniT uca0(sf::IntRect(224, 0, 32, 32));
	AniT uca1(sf::IntRect(224, 32, 32, 32));
	AniT uca2(sf::IntRect(224, 64, 32, 32));
	AniT uca3(sf::IntRect(224, 96, 32, 32));
	AniT uca4(sf::IntRect(224 + 32, 0, 32, 32));
	AniT uca5(sf::IntRect(224 + 32, 32, 32, 32));
	AniT uca6(sf::IntRect(224 + 32, 64, 32, 32));
	AniT uca7(sf::IntRect(224 + 32, 96, 32, 32));
	//Bunny on a rock
	AniT uca8(sf::IntRect(224, 128, 32, 32));
	AniT uca9(sf::IntRect(224, 128 + 32, 32, 32));
	AniT uca10(sf::IntRect(224, 128 + 64, 32, 32));
	All_Sprites[3][3] = { { uce3, uce2, uce1, uce0, uce1, uce2 },{ uce4, uce5, uce4 },{ uce3 },{ uce6 },{ uce7 },{ uce8, uce9, uce10 },{ uce11, uce12 },
		//Anode graphics
		{ uca3 },{ uca1, uca2, uca3, uca2 }, {uca0}, {uca7}, {uca4,uca5,uca6,uca5}, {uca7}, { uca8 },{ uca9,uca10,uca9 } };

	
	//All_Sprites[3][3] = { { { uce3, uce2, uce1, uce0, uce1, uce2 }, {}}, {{}} };
	//Red slime enemy sprites~~~
	//Standing still
	AniT us0(sf::IntRect(0, 416, 32, 32));
	AniT us1(sf::IntRect(0, 416 + 32, 32, 32));
	AniT us2(sf::IntRect(0, 416 + 64, 32, 32));
	AniT us3(sf::IntRect(0, 416 + 96, 32, 32));
	//Blinking
	AniT us4(sf::IntRect(0, 416 + 128, 32, 32));
	//Jumping in order
	AniT us5(sf::IntRect(32, 416, 32, 32));
	AniT us6(sf::IntRect(32, 416 + (32 * 1), 32, 32));
	AniT us7(sf::IntRect(32, 416 + (32 * 2), 32, 32));
	AniT us8(sf::IntRect(32, 416 + (32 * 3), 32, 32));
	AniT us9(sf::IntRect(32, 416 + (32 * 4), 32, 32));
	AniT us10(sf::IntRect(64, 416 + (32 * 4), 32, 32));
	AniT us11(sf::IntRect(64, 416 + (32 * 3), 32, 32));
	AniT us12(sf::IntRect(64, 416 + (32 * 2), 32, 32));
	AniT us13(sf::IntRect(64, 416 + (32 * 1), 32, 32));
	AniT us14(sf::IntRect(64, 416 + (32 * 0), 32, 32));
	AniT us15(sf::IntRect(96, 416 + (32 * 0), 32, 32));
	AniT us16(sf::IntRect(96, 416 + (32 * 1), 32, 32));
	AniT us17(sf::IntRect(96, 416 + (32 * 2), 32, 32));

	All_Sprites[3][5] = { { us0,us1,us2,us3,us1,us2,us0,us3 },{ us5,us6,us7,us8,us9,us10,us11,us12,us13,us14,us15,us16,us17 },{ us4 } };
	//Dino sprites
	AniT dino0(sf::IntRect(448, 192, 32, 32)); //Standing still
	AniT dino1(sf::IntRect(448, 192 + 32, 32, 32)); //Standing still
	AniT dino2(sf::IntRect(448, 192 + 64, 32, 32)); //Standing still
	AniT dino3(sf::IntRect(448 + 32, 192, 32, 32)); //Standing still
	AniT dino4(sf::IntRect(448 + 32, 192 + 32, 32, 32)); //Standing still
	AniT dino5(sf::IntRect(448 + 32, 192 + 64, 32, 32)); //Walking
	AniT dino6(sf::IntRect(448 + 64, 192, 32, 32)); //Walking
	AniT dino7(sf::IntRect(448 + 64, 192 + 32, 32, 32)); //Walking
	AniT dino8(sf::IntRect(448 + 64, 192 + 64, 32, 32)); //Walking
	AniT dino9(sf::IntRect(448 + 96, 192, 32, 32)); //Blowing fire left
	AniT dino10(sf::IntRect(416, 256, 32, 32)); //Blowing fire right
	AniT dino11(sf::IntRect(448 + 96, 192 + 64, 32, 32)); //Getting ready to blow fire
	AniT dino12(sf::IntRect(448 + 96, 192 + 64, 32, 32)); //Getting ready to blow fire
	All_Sprites[3][9] = { {dino0,dino1,dino2,dino3,dino4,dino2,dino3,dino1,dino4}, {dino4,dino5,dino6,dino7,dino8}, {dino9}, {dino10}, {dino11,dino12} };
	
	
	for (unsigned int i = 0; i < 23; i++) {
		All_Sprites[5].push_back({}); //Filling empty indices
	}
	
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Lobby3 Sprites-=-=-=-=-=-=-=-=-=-=-Texture-0
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Laser sprites~~~
	AniT pl0(sf::IntRect(320, 192, 32, 32));
	AniT pl1(sf::IntRect(320, 192 + 32, 32, 32));
	AniT pl2(sf::IntRect(320, 256, 32, 32));
	AniT pl3(sf::IntRect(320 + 32, 256, 32, 32));
	All_Sprites[5][0] = { { pl0, pl1 },{ pl2,pl3 } };
	//-=======================================================================-//
	//-=======================================================================-//
	//-=======This makes the character graphics!-=============================-//
	//-=======================================================================-//
	//-=======================================================================-//
	//This makes Europa's graphics.
	AniT pce0(sf::IntRect(544, 0, 32, 32));
	AniT pce1(sf::IntRect(544, (32 * 1), 32, 32));
	AniT pce2(sf::IntRect(544, (32 * 2), 32, 32));
	AniT pce3(sf::IntRect(512, 160, 32, 32));
	AniT pce4(sf::IntRect(512, 192, 32, 32)); //Blinking sprites
	AniT pce5(sf::IntRect(512, 192 + 32, 32, 32)); //Blinking sprites
	AniT pce6(sf::IntRect(544, (32 * 6), 32, 32));
	AniT pce7(sf::IntRect(544, (32 * 7), 32, 32));
	//Moving hands to shoot laser out of the gauntlet to build.
	AniT pce8(sf::IntRect(512, 0, 32, 32));
	AniT pce9(sf::IntRect(512, 32, 32, 32));
	AniT pce10(sf::IntRect(512, 64, 32, 32));
	//Shooting laser
	AniT pce11(sf::IntRect(480, 0, 32, 32));
	AniT pce12(sf::IntRect(480, 32, 32, 32));
	AniT pce13(sf::IntRect(480, 64, 32, 32));
	AniT pce14(sf::IntRect(480, 96, 32, 32));

	//This makes anode's graphics.-=-=-=-=-=-=-=-
	AniT pca0(sf::IntRect(224, 0, 32, 32));
	AniT pca1(sf::IntRect(224, 32, 32, 32));
	AniT pca2(sf::IntRect(224, 64, 32, 32));
	AniT pca3(sf::IntRect(224, 96, 32, 32));
	AniT pca4(sf::IntRect(224 + 32, 0, 32, 32));
	AniT pca5(sf::IntRect(224 + 32, 32, 32, 32));
	AniT pca6(sf::IntRect(224 + 32, 64, 32, 32));
	AniT pca7(sf::IntRect(224 + 32, 96, 32, 32));
	//Bunny on a rock
	AniT pca8(sf::IntRect(224, 128, 32, 32));
	AniT pca9(sf::IntRect(224, 128 + 32, 32, 32));
	AniT pca10(sf::IntRect(224, 128 + 64, 32, 32));
	All_Sprites[5][3] = { { pce3, pce2, pce1, pce0, pce1, pce2 },{ pce4, pce5, pce4 },{ pce3 },{ pce6 },{ pce7 },{ pce8, pce9, pce10 },{ pce11, pce12, pce13, pce14, pce13, pce12, pce11 },
		//Anode graphics
	{ pca3 },{ pca1, pca2, pca3, pca2 },{ pca0 },{ pca7 },{ pca4,pca5,pca6,pca5 },{ pca4 },{ pca8 },{ pca9,pca10,pca9 } };
	
	
	//Red slime enemy sprites~~~
	//Standing still
	AniT ps0(sf::IntRect(0, 416, 32, 32));
	AniT ps1(sf::IntRect(0, 416 + 32, 32, 32));
	AniT ps2(sf::IntRect(0, 416 + 64, 32, 32));
	AniT ps3(sf::IntRect(0, 416 + 96, 32, 32));
	//Blinking
	AniT ps4(sf::IntRect(0, 416 + 128, 32, 32));
	//Jumping in order
	AniT ps5(sf::IntRect(32, 416, 32, 32));
	AniT ps6(sf::IntRect(32, 416 + (32 * 1), 32, 32));
	AniT ps7(sf::IntRect(32, 416 + (32 * 2), 32, 32));
	AniT ps8(sf::IntRect(32, 416 + (32 * 3), 32, 32));
	AniT ps9(sf::IntRect(32, 416 + (32 * 4), 32, 32));
	AniT ps10(sf::IntRect(64, 416 + (32 * 4), 32, 32));
	AniT ps11(sf::IntRect(64, 416 + (32 * 3), 32, 32));
	AniT ps12(sf::IntRect(64, 416 + (32 * 2), 32, 32));
	AniT ps13(sf::IntRect(64, 416 + (32 * 1), 32, 32));
	AniT ps14(sf::IntRect(64, 416 + (32 * 0), 32, 32));
	AniT ps15(sf::IntRect(96, 416 + (32 * 0), 32, 32));
	AniT ps16(sf::IntRect(96, 416 + (32 * 1), 32, 32));
	AniT ps17(sf::IntRect(96, 416 + (32 * 2), 32, 32));

	All_Sprites[5][5] = { { ps0,ps1,ps2,ps3,ps1,ps2,ps0,ps3 },{ ps5,ps6,ps7,ps8,ps9,ps10,ps11,ps12,ps13,ps14,ps15,ps16,ps17 },{ ps4 } };
	//Dino sprites
	AniT pdino0(sf::IntRect(448, 192, 32, 32)); //Standing stills
	AniT pdino1(sf::IntRect(448, 192 + 32, 32, 32)); //Standing still
	AniT pdino2(sf::IntRect(448, 192 + 64, 32, 32)); //Standing still
	AniT pdino3(sf::IntRect(448 + 32, 192, 32, 32)); //Standing still
	AniT pdino4(sf::IntRect(448 + 32, 192 + 32, 32, 32)); //Standing still
	AniT pdino5(sf::IntRect(448 + 32, 192 + 64, 32, 32)); //Walking
	AniT pdino6(sf::IntRect(448 + 64, 192, 32, 32)); //Walking
	AniT pdino7(sf::IntRect(448 + 64, 192 + 32, 32, 32)); //Walking
	AniT pdino8(sf::IntRect(448 + 64, 192 + 64, 32, 32)); //Walking
	AniT pdino9(sf::IntRect(448 + 96, 192, 32, 32)); //Blowing fire left
	AniT pdino10(sf::IntRect(416, 256, 32, 32)); //Blowing fire right
	AniT pdino11(sf::IntRect(448 + 96, 192 + 64, 32, 32)); //Getting ready to blow fire
	AniT pdino12(sf::IntRect(448 + 96, 192 + 64, 32, 32)); //Getting ready to blow fire
	All_Sprites[5][9] = { { pdino0,pdino1,pdino2,pdino3,pdino4,pdino2,pdino3,pdino1,pdino4 },{ pdino4,pdino5,pdino6,pdino7,pdino8 },{ pdino9 },{ pdino10 },{ pdino11,pdino12 } };

	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Lobby4 Sprites-=-=-=-=-=-=-=-=-=-=-Texture-0
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	for (unsigned int i = 0; i < 23; i++) {
		All_Sprites[7].push_back({}); //Filling empty indices
	}
	//Laser sprites~~~
	AniT jl0(sf::IntRect(320, 192, 32, 32));
	AniT jl1(sf::IntRect(320, 192 + 32, 32, 32));
	AniT jl2(sf::IntRect(320, 256, 32, 32));
	AniT jl3(sf::IntRect(320 + 32, 256, 32, 32));
	All_Sprites[7][0] = { { jl0, jl1 },{ jl2,jl3 } };
	//-=======================================================================-//
	//-=======================================================================-//
	//-=======This makes the character graphics!-=============================-//
	//-=======================================================================-//
	//-=======================================================================-//
	//This makes Europa's graphics.
	AniT jce0(sf::IntRect(544, 0, 32, 32));
	AniT jce1(sf::IntRect(544, (32 * 1), 32, 32));
	AniT jce2(sf::IntRect(544, (32 * 2), 32, 32));
	AniT jce3(sf::IntRect(544, (32 * 3), 32, 32));
	AniT jce4(sf::IntRect(544, (32 * 4), 32, 32));
	AniT jce5(sf::IntRect(544, (32 * 5), 32, 32));
	AniT jce6(sf::IntRect(544, (32 * 6), 32, 32));
	AniT jce7(sf::IntRect(544, (32 * 7), 32, 32));
	//Moving hands to shoot laser out of the gauntlet to build.
	AniT jce8(sf::IntRect(512, 0, 32, 32));
	AniT jce9(sf::IntRect(512, 32, 32, 32));
	AniT jce10(sf::IntRect(512, 64, 32, 32));
	//Shooting laser
	AniT jce11(sf::IntRect(512, 96, 32, 32));
	AniT jce12(sf::IntRect(512, 128, 32, 32));


	//This makes anode's graphics.-=-=-=-=-=-=-=-
	AniT jca0(sf::IntRect(224, 0, 32, 32));
	AniT jca1(sf::IntRect(224, 32, 32, 32));
	AniT jca2(sf::IntRect(224, 64, 32, 32));
	AniT jca3(sf::IntRect(224, 96, 32, 32));
	AniT jca4(sf::IntRect(224 + 32, 0, 32, 32));
	AniT jca5(sf::IntRect(224 + 32, 32, 32, 32));
	AniT jca6(sf::IntRect(224 + 32, 64, 32, 32));
	AniT jca7(sf::IntRect(224 + 32, 96, 32, 32));
	//Bunny on a rock
	AniT jca8(sf::IntRect(224, 128, 32, 32));
	AniT jca9(sf::IntRect(224, 128 + 32, 32, 32));
	AniT jca10(sf::IntRect(224, 128 + 64, 32, 32));
	All_Sprites[7][3] = { { jce3, jce2, jce1, jce0, jce1, jce2 },{ jce4, jce5, jce4 },{ jce3 },{ jce6 },{ jce7 },{ jce8, jce9, jce10 },{ jce11, jce12 },
		//Anode graphics
	{ jca3 },{ jca1, jca2, jca3, jca2 },{ jca0 },{ jca7 },{ jca4,jca5,jca6,jca5 },{ jca7 },{jca8 },{ jca9,jca10,jca9 } };
	
	//Red slime enemy sprites~~~
	//Standing still
	AniT js0(sf::IntRect(0, 416, 32, 32));
	AniT js1(sf::IntRect(0, 416 + 32, 32, 32));
	AniT js2(sf::IntRect(0, 416 + 64, 32, 32));
	AniT js3(sf::IntRect(0, 416 + 96, 32, 32));
	//Blinking
	AniT js4(sf::IntRect(0, 416 + 128, 32, 32));
	//Jumping in order
	AniT js5(sf::IntRect(32, 416, 32, 32));
	AniT js6(sf::IntRect(32, 416 + (32 * 1), 32, 32));
	AniT js7(sf::IntRect(32, 416 + (32 * 2), 32, 32));
	AniT js8(sf::IntRect(32, 416 + (32 * 3), 32, 32));
	AniT js9(sf::IntRect(32, 416 + (32 * 4), 32, 32));
	AniT js10(sf::IntRect(64, 416 + (32 * 4), 32, 32));
	AniT js11(sf::IntRect(64, 416 + (32 * 3), 32, 32));
	AniT js12(sf::IntRect(64, 416 + (32 * 2), 32, 32));
	AniT js13(sf::IntRect(64, 416 + (32 * 1), 32, 32));
	AniT js14(sf::IntRect(64, 416 + (32 * 0), 32, 32));
	AniT js15(sf::IntRect(96, 416 + (32 * 0), 32, 32));
	AniT js16(sf::IntRect(96, 416 + (32 * 1), 32, 32));
	AniT js17(sf::IntRect(96, 416 + (32 * 2), 32, 32));

	All_Sprites[7][5] = { { js0,js1,js2,js3,js1,js2,js0,js3 },{ js5,js6,js7,js8,js9,js10,js11,js12,js13,js14,js15,js16,js17 },{ js4 } };
	//Dino sprites
	AniT jdino0(sf::IntRect(448, 192, 32, 32)); //Standing stills
	AniT jdino1(sf::IntRect(448, 192 + 32, 32, 32)); //Standing still
	AniT jdino2(sf::IntRect(448, 192 + 64, 32, 32)); //Standing still
	AniT jdino3(sf::IntRect(448 + 32, 192, 32, 32)); //Standing still
	AniT jdino4(sf::IntRect(448 + 32, 192 + 32, 32, 32)); //Standing still
	AniT jdino5(sf::IntRect(448 + 32, 192 + 64, 32, 32)); //Walking
	AniT jdino6(sf::IntRect(448 + 64, 192, 32, 32)); //Walking
	AniT jdino7(sf::IntRect(448 + 64, 192 + 32, 32, 32)); //Walking
	AniT jdino8(sf::IntRect(448 + 64, 192 + 64, 32, 32)); //Walking
	AniT jdino9(sf::IntRect(448 + 96, 192, 32, 32)); //Blowing fire left
	AniT jdino10(sf::IntRect(416, 256, 32, 32)); //Blowing fire right
	AniT jdino11(sf::IntRect(448 + 96, 192 + 64, 32, 32)); //Getting ready to blow fire
	AniT jdino12(sf::IntRect(448 + 96, 192 + 64, 32, 32)); //Getting ready to blow fire
	All_Sprites[7][9] = { { jdino0,jdino1,jdino2,jdino3,jdino4,jdino2,jdino3,jdino1,jdino4 },{ jdino4,jdino5,jdino6,jdino7,jdino8 },{ jdino9 },{ jdino10 },{ jdino11,jdino12 } };

	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Dungeon one Sprites-=-=-=-=-=-=-=-=-=-=-Texture-0
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	for (unsigned int i = 0; i < 30; i++) {
		All_Sprites[2].push_back({});
	}
	//This makes the laser graphics.
	AniT s0(sf::IntRect(128, 128, 32, 32));
	AniT s1(sf::IntRect(128, 96, 32, 32));
	AniT s2(sf::IntRect(0, 96, 32, 32));
	AniT s3(sf::IntRect(32, 96, 32, 32));
	All_Sprites[2][0] = { {s0,s1}, {s2,s3} }; //lASER SPRITES 0
	//This makes the homingskull graphics.
	AniT h0(sf::IntRect(438, 0, 32, 32));
	AniT h1(sf::IntRect(438, 32, 32, 32));
	AniT h2(sf::IntRect(438, 64, 32, 32));
	
	All_Sprites[2][1] = { {h0,h1,h2} }; //HomingSkullSprites 1
	//This makes the ChainBall graphics.
	AniT c0(sf::IntRect(471, 65, 62, 62));
	AniT c1(sf::IntRect(470, 33, 32, 32));
	
	All_Sprites[2][2] = { {c0,c1} }; //Chainballsprites 2
	//-=======================================================================-//
	//-=======================================================================-//
	//-=======This makes the character graphics!-=============================-//
	//-=======================================================================-//
	//-=======================================================================-//
	//This makes Europa's graphics.
	AniT ce0(sf::IntRect(544, 0, 32, 32));
	AniT ce1(sf::IntRect(544, (32 * 1), 32, 32));
	AniT ce2(sf::IntRect(544, (32 * 2), 32, 32));
	AniT ce3(sf::IntRect(544, (32 * 3), 32, 32));
	AniT ce4(sf::IntRect(544, (32 * 4), 32, 32));
	AniT ce5(sf::IntRect(544, (32 * 5), 32, 32));
	AniT ce6(sf::IntRect(544, (32 * 6), 32, 32));
	AniT ce7(sf::IntRect(544, (32 * 7), 32, 32));
	//Moving hands to shoot laser out of the gauntlet to build.
	AniT ce8(sf::IntRect(512, 0, 32, 32));
	AniT ce9(sf::IntRect(512, 32, 32, 32));
	AniT ce10(sf::IntRect(512, 64, 32, 32));
	//Shooting laser
	AniT ce11(sf::IntRect(512, 96, 32, 32));
	AniT ce12(sf::IntRect(512, 128, 32, 32));
	All_Sprites[2][3] = { { { ce3, ce2, ce1, ce0, ce1, ce2 }, { ce4, ce5, ce4 },  { ce3 }, { ce6 }, { ce7 }, { ce8, ce9, ce10 }, { ce11, ce12 } } }; //EuropaSprites 3

	//Skeleton sprites~~~
	//Standing still
	AniT Skele0(sf::IntRect(0, 416, 32, 32));
	AniT Skele1(sf::IntRect(0, 416 + 32, 32, 32));
	AniT Skele2(sf::IntRect(0, 416 + 64, 32, 32));
	AniT Skele3(sf::IntRect(0, 416 + 96, 32, 32));
	AniT Skele4(sf::IntRect(0, 416 + 128, 32, 32));
	//Walking
	AniT Skele5(sf::IntRect(32, 416 + 32, 32, 32));
	AniT Skele6(sf::IntRect(32, 416 + 64, 32, 32));
	AniT Skele7(sf::IntRect(32, 416 + 96, 32, 32));
	AniT Skele8(sf::IntRect(32, 416 + 128, 32, 32));
	All_Sprites[2][4] = { { {Skele0,Skele1,Skele2,Skele3,Skele2,Skele1}, { Skele5, Skele6, Skele7, Skele8, Skele7, Skele6 } } }; //SkeletonSprites 4
	//Shielder sprites
	AniT Shield0(sf::IntRect(192, 256, 32, 32)); //Shield up
	AniT Shield1(sf::IntRect(192 + 32, 256, 32, 32)); //Shield right
	AniT Shield2(sf::IntRect(192 + 32, 256 + 32, 32, 32)); //Shield down
	AniT Shield3(sf::IntRect(192, 256 + 32, 32, 32)); //Shield left
	AniT Shield4(sf::IntRect(192, 320, 32, 32)); //Shield broken up
	AniT Shield5(sf::IntRect(192 + 32, 320, 32, 32)); //Shield broken right
	AniT Shield6(sf::IntRect(192 + 32, 320 + 32, 32, 32)); //Shield broken down
	AniT Shield7(sf::IntRect(192, 320 + 32, 32, 32)); //Shield broken left
	AniT Shield8(sf::IntRect(160, 352, 32, 32)); //Center piece
	All_Sprites[2][6] = { { Shield8,Shield0,Shield1,Shield2,Shield3,Shield4,Shield5,Shield6,Shield7 } };
	//Dragon sprites
	AniT Dragon0(sf::IntRect(64, 544, 32, 32));//Face open
	AniT Dragon1(sf::IntRect(96, 544, 32, 32));//Hard shell taco body
	AniT Dragon2(sf::IntRect(128, 544, 32, 32));//Tail
	AniT Dragon3(sf::IntRect(64, 512, 32, 32));//Eye open
	AniT Dragon4(sf::IntRect(96, 512, 32, 32));//Eye closed
	All_Sprites[2][7] = { {Dragon0,Dragon1,Dragon2,Dragon3,Dragon4} };
	//Break_Spawner
	AniT BS0(sf::IntRect(160, 544, 32, 32));
	AniT BS1(sf::IntRect(160 + 32, 544, 32, 32));
	All_Sprites[2][8] = { {BS0,BS1} };
	//Red slime enemy sprites~~~
	//Standing still
	AniT slime0(sf::IntRect(128, 384, 32, 32));
	AniT slime1(sf::IntRect(128, 384 + 32, 32, 32));
	AniT slime2(sf::IntRect(128, 384 + 64, 32, 32));
	AniT slime3(sf::IntRect(128, 384 + 96, 32, 32));
	//Blinking
	AniT slime4(sf::IntRect(128, 384 + 128, 32, 32));
	//Jumping in order
	AniT slime5(sf::IntRect(128 + 32, 384, 32, 32));
	AniT slime6(sf::IntRect(128 + 32, 384 + (32 * 1), 32, 32));
	AniT slime7(sf::IntRect(128 + 32, 384 + (32 * 2), 32, 32));
	AniT slime8(sf::IntRect(128 + 32, 384 + (32 * 3), 32, 32));
	AniT slime9(sf::IntRect(128 + 32, 384 + (32 * 4), 32, 32));
	AniT slime10(sf::IntRect(128 + 64, 384 + (32 * 4), 32, 32));
	AniT slime11(sf::IntRect(128 + 64, 384 + (32 * 3), 32, 32));
	AniT slime12(sf::IntRect(128 + 64, 384 + (32 * 2), 32, 32));
	AniT slime13(sf::IntRect(128 + 64, 384 + (32 * 1), 32, 32));
	AniT slime14(sf::IntRect(128 + 64, 384 + (32 * 0), 32, 32));
	AniT slime15(sf::IntRect(128 + 96, 384 + (32 * 0), 32, 32));
	AniT slime16(sf::IntRect(128 + 96, 384 + (32 * 1), 32, 32));
	AniT slime17(sf::IntRect(128 + 96, 384 + (32 * 2), 32, 32));

	All_Sprites[2][5] = { { slime0,slime1,slime2,slime3,slime1,slime2,slime0,slime3 },{ slime5,slime6,slime7,slime8,slime9,slime10,slime11,slime12,slime13,slime14,slime15,slime16,slime17 },{ slime4 } };
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Dungeon two Sprites-=-=-=-=-=-=-=-=-=-=-Texture-0
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	for (unsigned int i = 0; i < 30; i++) {
		All_Sprites[4].push_back({});
	}
	//This makes the laser graphics.
	AniT qs0(sf::IntRect(128, 128, 32, 32));
	AniT qs1(sf::IntRect(128, 96, 32, 32));
	AniT qs2(sf::IntRect(0, 96, 32, 32));
	AniT qs3(sf::IntRect(32, 96, 32, 32));
	All_Sprites[4][0] = { { qs0,qs1 },{ qs2,qs3 } }; //lASER SPRITES 0
												 //This makes the homingskull graphics.
	AniT qh0(sf::IntRect(438, 0, 32, 32));
	AniT qh1(sf::IntRect(438, 32, 32, 32));
	AniT qh2(sf::IntRect(438, 64, 32, 32));

	All_Sprites[4][1] = { { qh0,qh1,qh2 } }; //HomingSkullSprites 1
										  //This makes the ChainBall graphics.
	AniT qc0(sf::IntRect(471, 65, 62, 62));
	AniT qc1(sf::IntRect(470, 33, 32, 32));

	All_Sprites[4][2] = { { qc0,qc1 } }; //Chainballsprites 2
									   //-=======================================================================-//
									   //-=======================================================================-//
									   //-=======This makes the character graphics!-=============================-//
									   //-=======================================================================-//
									   //-=======================================================================-//
									   //This makes Europa's graphics.
	AniT qce0(sf::IntRect(544, 0, 32, 32));
	AniT qce1(sf::IntRect(544, (32 * 1), 32, 32));
	AniT qce2(sf::IntRect(544, (32 * 2), 32, 32));
	AniT qce3(sf::IntRect(544, (32 * 3), 32, 32));
	AniT qce4(sf::IntRect(544, (32 * 4), 32, 32));
	AniT qce5(sf::IntRect(544, (32 * 5), 32, 32));
	AniT qce6(sf::IntRect(544, (32 * 6), 32, 32));
	AniT qce7(sf::IntRect(544, (32 * 7), 32, 32));
	//Moving hands to shoot laser out of the gauntlet to build.
	AniT qce8(sf::IntRect(512, 0, 32, 32));
	AniT qce9(sf::IntRect(512, 32, 32, 32));
	AniT qce10(sf::IntRect(512, 64, 32, 32));
	//Shooting laser
	AniT qce11(sf::IntRect(512, 96, 32, 32));
	AniT qce12(sf::IntRect(512, 128, 32, 32));
	All_Sprites[4][3] = { { { qce3, qce2, qce1, qce0, qce1, qce2 },{ qce4, qce5, qce4 },{ qce3 },{ qce6 },{ qce7 },{ qce8, qce9, qce10 },{ qce11, qce12 } } }; //EuropaSprites 3

																																			  //Skeleton sprites~~~
																																			  //Standing still
	AniT qSkele0(sf::IntRect(0, 416, 32, 32));
	AniT qSkele1(sf::IntRect(0, 416 + 32, 32, 32));
	AniT qSkele2(sf::IntRect(0, 416 + 64, 32, 32));
	AniT qSkele3(sf::IntRect(0, 416 + 96, 32, 32));
	AniT qSkele4(sf::IntRect(0, 416 + 128, 32, 32));
	//Walking
	AniT qSkele5(sf::IntRect(32, 416 + 32, 32, 32));
	AniT qSkele6(sf::IntRect(32, 416 + 64, 32, 32));
	AniT qSkele7(sf::IntRect(32, 416 + 96, 32, 32));
	AniT qSkele8(sf::IntRect(32, 416 + 128, 32, 32));
	All_Sprites[4][4] = { { { qSkele0,qSkele1,qSkele2,qSkele3,qSkele2,qSkele1 },{ qSkele5, qSkele6, qSkele7, qSkele8, qSkele7, qSkele6 } } }; //SkeletonSprites 4
																																  //Shielder sprites
	AniT qShield0(sf::IntRect(192, 256, 32, 32)); //Shield up
	AniT qShield1(sf::IntRect(192 + 32, 256, 32, 32)); //Shield right
	AniT qShield2(sf::IntRect(192 + 32, 256 + 32, 32, 32)); //Shield down
	AniT qShield3(sf::IntRect(192, 256 + 32, 32, 32)); //Shield left
	AniT qShield4(sf::IntRect(192, 320, 32, 32)); //Shield broken up
	AniT qShield5(sf::IntRect(192 + 32, 320, 32, 32)); //Shield broken right
	AniT qShield6(sf::IntRect(192 + 32, 320 + 32, 32, 32)); //Shield broken down
	AniT qShield7(sf::IntRect(192, 320 + 32, 32, 32)); //Shield broken left
	AniT qShield8(sf::IntRect(160, 352, 32, 32)); //Center piece
	All_Sprites[4][6] = { { qShield8,qShield0,qShield1,qShield2,qShield3,qShield4,qShield5,qShield6,qShield7 } };
	//Dragon sprites
	AniT qDragon0(sf::IntRect(64, 544, 32, 32));//Face open
	AniT qDragon1(sf::IntRect(96, 544, 32, 32));//Hard shell taco body
	AniT qDragon2(sf::IntRect(128, 544, 32, 32));//Tail
	AniT qDragon3(sf::IntRect(64, 512, 32, 32));//Eye open
	AniT qDragon4(sf::IntRect(96, 512, 32, 32));//Eye closed
	All_Sprites[4][7] = { { qDragon0,qDragon1,qDragon2,qDragon3,qDragon4 } };
	//Break_Spawner
	AniT qBS0(sf::IntRect(160, 544, 32, 32));
	AniT qBS1(sf::IntRect(160 + 32, 544, 32, 32));
	All_Sprites[4][8] = { { qBS0,qBS1 } };
	//Red slime enemy sprites~~~
	//Standing still
	AniT qslime0(sf::IntRect(128, 384, 32, 32));
	AniT qslime1(sf::IntRect(128, 384 + 32, 32, 32));
	AniT qslime2(sf::IntRect(128, 384 + 64, 32, 32));
	AniT qslime3(sf::IntRect(128, 384 + 96, 32, 32));
	//Blinking
	AniT qslime4(sf::IntRect(128, 384 + 128, 32, 32));
	//Jumping in order
	AniT qslime5(sf::IntRect(128 + 32, 384, 32, 32));
	AniT qslime6(sf::IntRect(128 + 32, 384 + (32 * 1), 32, 32));
	AniT qslime7(sf::IntRect(128 + 32, 384 + (32 * 2), 32, 32));
	AniT qslime8(sf::IntRect(128 + 32, 384 + (32 * 3), 32, 32));
	AniT qslime9(sf::IntRect(128 + 32, 384 + (32 * 4), 32, 32));
	AniT qslime10(sf::IntRect(128 + 64, 384 + (32 * 4), 32, 32));
	AniT qslime11(sf::IntRect(128 + 64, 384 + (32 * 3), 32, 32));
	AniT qslime12(sf::IntRect(128 + 64, 384 + (32 * 2), 32, 32));
	AniT qslime13(sf::IntRect(128 + 64, 384 + (32 * 1), 32, 32));
	AniT qslime14(sf::IntRect(128 + 64, 384 + (32 * 0), 32, 32));
	AniT qslime15(sf::IntRect(128 + 96, 384 + (32 * 0), 32, 32));
	AniT qslime16(sf::IntRect(128 + 96, 384 + (32 * 1), 32, 32));
	AniT qslime17(sf::IntRect(128 + 96, 384 + (32 * 2), 32, 32));

	All_Sprites[4][5] = { { qslime0,qslime1,qslime2,qslime3,qslime1,qslime2,qslime0,qslime3 },{ qslime5,qslime6,qslime7,qslime8,qslime9,qslime10,qslime11,qslime12,qslime13,qslime14,qslime15,qslime16,qslime17 },{ qslime4 } };
	
	//Dino sprites
	AniT qdino0(sf::IntRect(32, 288, 32, 32)); //Standing still
	AniT qdino1(sf::IntRect(32, 288 + 32, 32, 32)); //Standing still
	AniT qdino2(sf::IntRect(32, 288 + 64, 32, 32)); //Standing still
	AniT qdino3(sf::IntRect(32 + 32, 288, 32, 32)); //Standing still
	AniT qdino4(sf::IntRect(32 + 32, 288 + 32, 32, 32)); //Standing still
	AniT qdino5(sf::IntRect(32 + 32, 288 + 64, 32, 32)); //Walking
	AniT qdino6(sf::IntRect(32 + 64, 288, 32, 32)); //Walking
	AniT qdino7(sf::IntRect(32 + 64, 288 + 32, 32, 32)); //Walking
	AniT qdino8(sf::IntRect(32 + 64, 288 + 64, 32, 32)); //Walking
	AniT qdino9(sf::IntRect(32 + 96, 288, 32, 32)); //Blowing fire left
	AniT qdino10(sf::IntRect(0, 352, 32, 32)); //Blowing fire right
	AniT qdino11(sf::IntRect(32 + 96, 288 + 64, 32, 32)); //Getting ready to blow fire
	AniT qdino12(sf::IntRect(32 + 96, 288 + 64, 32, 32)); //Getting ready to blow fire
	All_Sprites[4][9] = { { qdino0,qdino1,qdino2,qdino3,qdino4,qdino2,qdino3,qdino1,qdino4 },{ qdino4,qdino5,qdino6,qdino7,qdino8 },{ qdino9 },{ qdino10 },{ qdino11,qdino12 } };

	//Squisher sprites~~~
	AniT qsquish0(sf::IntRect(374, 416 + 64, 32, 32)); //Spring up
	AniT qsquish0_1(sf::IntRect(374 - 32, 416 + 64, 32, 32)); //Spring right
	AniT qsquish0_2(sf::IntRect(374 - 32, 416 + 32, 32, 32)); //Spring down
	AniT qsquish0_3(sf::IntRect(374, 416, 32, 32)); //Spring left
	AniT qsquish1(sf::IntRect(374, 416 + 32, 32, 32)); //Block without face
	AniT qsquish2(sf::IntRect(374 - 32, 416, 32, 32)); //Block with face

	All_Sprites[4][10] = { { { qsquish1,qsquish2 },{ qsquish0,qsquish0_1,qsquish0_2,qsquish0_3 } } };

	//W_bomb sprites
	AniT qex0(sf::IntRect(288, 384, 32, 32));//Standing still
	AniT qex1(sf::IntRect(288, 384 + (32 * 1), 32, 32));//Standing still
	AniT qex2(sf::IntRect(288, 384 + (32 * 2), 32, 32));//Standing still
	AniT qex3(sf::IntRect(288, 384 + (32 * 3), 32, 32));//Standing still
	
	AniT qex4(sf::IntRect(288, 384 + (32 * 4), 32, 32));//Walking sprite
	AniT qex5(sf::IntRect(288, 384 + (32 * 5), 32, 32));//Walking sprite
	AniT qex6(sf::IntRect(288, 384 + (32 * 6), 32, 32));//Walking sprite
	AniT qex7(sf::IntRect(288, 384 + (32 * 7), 32, 32));//Walking sprite
	All_Sprites[4][11] = { {{qex0,qex1,qex2,qex3}, {qex4,qex5,qex6,qex7}} };
	
	//EBM sprites

	AniT qebm0(sf::IntRect(406, 576, 32, 32));//Blinking
	AniT qebm1(sf::IntRect(406, 576 + 32, 32, 32));//Blinking
	AniT qebm2(sf::IntRect(406, 576 + 64, 32, 32));//Blinking
	AniT qebm3(sf::IntRect(406, 576 + 96, 32, 32));//Blinking

	AniT qebm4(sf::IntRect(406 + 32, 576, 32, 32));//Floating with eye open
	AniT qebm5(sf::IntRect(406 + 32, 576 + 32, 32, 32));//Floating with eye open
	AniT qebm6(sf::IntRect(406 + 32, 576 + 64, 32, 32));//Floating with eye open
	AniT qebm7(sf::IntRect(406 + 32, 576 + 96, 32, 32));//Floating with eye open

	AniT qebm8(sf::IntRect(406 + 64, 576, 32, 32));//Floating with eye closed
	AniT qebm9(sf::IntRect(406 + 64, 576 + 32, 32, 32));//Floating with eye closed
	AniT qebm10(sf::IntRect(406 + 64, 576 + 64, 32, 32));//Floating with eye closed
	AniT qebm11(sf::IntRect(406 + 64, 576 + 96, 32, 32));//Floating with eye closed

	All_Sprites[4][12] = { { {qebm0,qebm4,qebm5,qebm6,qebm7,qebm6,qebm5,qebm4},{ qebm4,qebm5,qebm6,qebm7,qebm6,qebm5 } , {qebm3,qebm8,qebm9,qebm10,qebm11,qebm10,qebm9,qebm8}, {qebm1,qebm2,qebm3}, {qebm2,qebm1,qebm0},  } };
	
	//EyeBall MAIN sprites
	AniT qEyeBall_MAIN0(sf::IntRect(502, 480, 64, 32));
	AniT qEyeBall_MAIN1(sf::IntRect(502, 480 + 32, 64, 32));
	AniT qEyeBall_MAIN2(sf::IntRect(502, 480 + 64, 64, 32));
	AniT qEyeBall_MAIN3(sf::IntRect(502, 480 + 96, 64, 32));
	
	All_Sprites[4][13] = { {{qEyeBall_MAIN0}, {qEyeBall_MAIN1}, {qEyeBall_MAIN2,qEyeBall_MAIN2}, {qEyeBall_MAIN3,qEyeBall_MAIN3}} };
	

	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Dungeon three Sprites-=-=-=-=-=-=-=-=-=-=-Texture-0
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	for (unsigned int i = 0; i < 30; i++) {
		All_Sprites[6].push_back({});
	}
	//This makes the laser graphics.
	AniT vs0(sf::IntRect(128, 128, 32, 32));
	AniT vs1(sf::IntRect(128, 96, 32, 32));
	AniT vs2(sf::IntRect(0, 96, 32, 32));
	AniT vs3(sf::IntRect(32, 96, 32, 32));
	All_Sprites[6][0] = { { vs0,vs1 },{ vs2,vs3 } }; //lASER SPRITES 0
													 //This makes the homingskull graphics.
	AniT vh0(sf::IntRect(438, 0, 32, 32));
	AniT vh1(sf::IntRect(438, 32, 32, 32));
	AniT vh2(sf::IntRect(438, 64, 32, 32));

	All_Sprites[6][1] = { { vh0,vh1,vh2 } }; //HomingSkullSprites 1
											 //This makes the ChainBall graphics.
	AniT vc0(sf::IntRect(471, 65, 62, 62));
	AniT vc1(sf::IntRect(470, 33, 32, 32));

	All_Sprites[6][2] = { { vc0,vc1 } }; //Chainballsprites 2
										 //-=======================================================================-//
										 //-=======================================================================-//
										 //-=======This makes the character graphics!-=============================-//
										 //-=======================================================================-//
										 //-=======================================================================-//
										 //This makes Europa's graphics.
	AniT vce0(sf::IntRect(544, 0, 32, 32));
	AniT vce1(sf::IntRect(544, (32 * 1), 32, 32));
	AniT vce2(sf::IntRect(544, (32 * 2), 32, 32));
	AniT vce3(sf::IntRect(544, (32 * 3), 32, 32));
	AniT vce4(sf::IntRect(544, (32 * 4), 32, 32));
	AniT vce5(sf::IntRect(544, (32 * 5), 32, 32));
	AniT vce6(sf::IntRect(544, (32 * 6), 32, 32));
	AniT vce7(sf::IntRect(544, (32 * 7), 32, 32));
	//Moving hands to shoot laser out of the gauntlet to build.
	AniT vce8(sf::IntRect(512, 0, 32, 32));
	AniT vce9(sf::IntRect(512, 32, 32, 32));
	AniT vce10(sf::IntRect(512, 64, 32, 32));
	//Shooting laser
	AniT vce11(sf::IntRect(512, 96, 32, 32));
	AniT vce12(sf::IntRect(512, 128, 32, 32));
	All_Sprites[6][3] = { { { vce3, vce2, vce1, vce0, vce1, vce2 },{ vce4, vce5, vce4 },{ vce3 },{ vce6 },{ vce7 },{ vce8, vce9, vce10 },{ vce11, vce12 } } }; //EuropaSprites 3

																																							   //Skeleton sprites~~~
																																							   //Standing still
	AniT vSkele0(sf::IntRect(0, 416, 32, 32));
	AniT vSkele1(sf::IntRect(0, 416 + 32, 32, 32));
	AniT vSkele2(sf::IntRect(0, 416 + 64, 32, 32));
	AniT vSkele3(sf::IntRect(0, 416 + 96, 32, 32));
	AniT vSkele4(sf::IntRect(0, 416 + 128, 32, 32));
	//Walking
	AniT vSkele5(sf::IntRect(32, 416 + 32, 32, 32));
	AniT vSkele6(sf::IntRect(32, 416 + 64, 32, 32));
	AniT vSkele7(sf::IntRect(32, 416 + 96, 32, 32));
	AniT vSkele8(sf::IntRect(32, 416 + 128, 32, 32));
	All_Sprites[6][4] = { { { vSkele0,vSkele1,vSkele2,vSkele3,vSkele2,vSkele1 },{ vSkele5, vSkele6, vSkele7, vSkele8, vSkele7, vSkele6 } } }; //SkeletonSprites 4
																																			  //Shielder sprites
	AniT vShield0(sf::IntRect(192, 256, 32, 32)); //Shield up
	AniT vShield1(sf::IntRect(192 + 32, 256, 32, 32)); //Shield right
	AniT vShield2(sf::IntRect(192 + 32, 256 + 32, 32, 32)); //Shield down
	AniT vShield3(sf::IntRect(192, 256 + 32, 32, 32)); //Shield left
	AniT vShield4(sf::IntRect(192, 320, 32, 32)); //Shield broken up
	AniT vShield5(sf::IntRect(192 + 32, 320, 32, 32)); //Shield broken right
	AniT vShield6(sf::IntRect(192 + 32, 320 + 32, 32, 32)); //Shield broken down
	AniT vShield7(sf::IntRect(192, 320 + 32, 32, 32)); //Shield broken left
	AniT vShield8(sf::IntRect(160, 352, 32, 32)); //Center piece
	All_Sprites[6][6] = { { vShield8,vShield0,vShield1,vShield2,vShield3,vShield4,vShield5,vShield6,vShield7 } };
	//Dragon sprites
	AniT vDragon0(sf::IntRect(64, 544, 32, 32));//Face open
	AniT vDragon1(sf::IntRect(96, 544, 32, 32));//Hard shell taco body
	AniT vDragon2(sf::IntRect(128, 544, 32, 32));//Tail
	AniT vDragon3(sf::IntRect(64, 512, 32, 32));//Eye open
	AniT vDragon4(sf::IntRect(96, 512, 32, 32));//Eye closed
	All_Sprites[6][7] = { { vDragon0,vDragon1,vDragon2,vDragon3,vDragon4 } };
	//Break_Spawner
	AniT vBS0(sf::IntRect(160, 544, 32, 32));
	AniT vBS1(sf::IntRect(160 + 32, 544, 32, 32));
	All_Sprites[6][8] = { { vBS0,vBS1 } };
	//Red slime enemy sprites~~~
	//Standing still
	AniT vslime0(sf::IntRect(128, 384, 32, 32));
	AniT vslime1(sf::IntRect(128, 384 + 32, 32, 32));
	AniT vslime2(sf::IntRect(128, 384 + 64, 32, 32));
	AniT vslime3(sf::IntRect(128, 384 + 96, 32, 32));
	//Blinking
	AniT vslime4(sf::IntRect(128, 384 + 128, 32, 32));
	//Jumping in order
	AniT vslime5(sf::IntRect(128 + 32, 384, 32, 32));
	AniT vslime6(sf::IntRect(128 + 32, 384 + (32 * 1), 32, 32));
	AniT vslime7(sf::IntRect(128 + 32, 384 + (32 * 2), 32, 32));
	AniT vslime8(sf::IntRect(128 + 32, 384 + (32 * 3), 32, 32));
	AniT vslime9(sf::IntRect(128 + 32, 384 + (32 * 4), 32, 32));
	AniT vslime10(sf::IntRect(128 + 64, 384 + (32 * 4), 32, 32));
	AniT vslime11(sf::IntRect(128 + 64, 384 + (32 * 3), 32, 32));
	AniT vslime12(sf::IntRect(128 + 64, 384 + (32 * 2), 32, 32));
	AniT vslime13(sf::IntRect(128 + 64, 384 + (32 * 1), 32, 32));
	AniT vslime14(sf::IntRect(128 + 64, 384 + (32 * 0), 32, 32));
	AniT vslime15(sf::IntRect(128 + 96, 384 + (32 * 0), 32, 32));
	AniT vslime16(sf::IntRect(128 + 96, 384 + (32 * 1), 32, 32));
	AniT vslime17(sf::IntRect(128 + 96, 384 + (32 * 2), 32, 32));

	All_Sprites[6][5] = { { vslime0,vslime1,vslime2,vslime3,vslime1,vslime2,vslime0,vslime3 },{ vslime5,vslime6,vslime7,vslime8,vslime9,vslime10,vslime11,vslime12,vslime13,vslime14,vslime15,vslime16,vslime17 },{ vslime4 } };

	//Dino sprites
	AniT vdino0(sf::IntRect(32, 288, 32, 32)); //Standing still
	AniT vdino1(sf::IntRect(32, 288 + 32, 32, 32)); //Standing still
	AniT vdino2(sf::IntRect(32, 288 + 64, 32, 32)); //Standing still
	AniT vdino3(sf::IntRect(32 + 32, 288, 32, 32)); //Standing still
	AniT vdino4(sf::IntRect(32 + 32, 288 + 32, 32, 32)); //Standing still
	AniT vdino5(sf::IntRect(32 + 32, 288 + 64, 32, 32)); //Walking
	AniT vdino6(sf::IntRect(32 + 64, 288, 32, 32)); //Walking
	AniT vdino7(sf::IntRect(32 + 64, 288 + 32, 32, 32)); //Walking
	AniT vdino8(sf::IntRect(32 + 64, 288 + 64, 32, 32)); //Walking
	AniT vdino9(sf::IntRect(32 + 96, 288, 32, 32)); //Blowing fire left
	AniT vdino10(sf::IntRect(0, 352, 32, 32)); //Blowing fire right
	AniT vdino11(sf::IntRect(32 + 96, 288 + 64, 32, 32)); //Getting ready to blow fire
	AniT vdino12(sf::IntRect(32 + 96, 288 + 64, 32, 32)); //Getting ready to blow fire
	All_Sprites[6][9] = { { vdino0,vdino1,vdino2,vdino3,vdino4,vdino2,vdino3,vdino1,vdino4 },{ vdino4,vdino5,vdino6,vdino7,vdino8 },{ vdino9 },{ vdino10 },{ vdino11,vdino12 } };

	//Squisher sprites~~~
	AniT vsquish0(sf::IntRect(374, 416 + 64, 32, 32)); //Spring up
	AniT vsquish0_1(sf::IntRect(374 - 32, 416 + 64, 32, 32)); //Spring right
	AniT vsquish0_2(sf::IntRect(374 - 32, 416 + 32, 32, 32)); //Spring down
	AniT vsquish0_3(sf::IntRect(374, 416, 32, 32)); //Spring left
	AniT vsquish1(sf::IntRect(374, 416 + 32, 32, 32)); //Block without face
	AniT vsquish2(sf::IntRect(374 - 32, 416, 32, 32)); //Block with face

	All_Sprites[6][10] = { { { vsquish1,vsquish2 },{ vsquish0,vsquish0_1,vsquish0_2,vsquish0_3 } } };

	//W_bomb sprites
	AniT vex0(sf::IntRect(288, 384, 32, 32));//Standing still
	AniT vex1(sf::IntRect(288, 384 + (32 * 1), 32, 32));//Standing still
	AniT vex2(sf::IntRect(288, 384 + (32 * 2), 32, 32));//Standing still
	AniT vex3(sf::IntRect(288, 384 + (32 * 3), 32, 32));//Standing still

	AniT vex4(sf::IntRect(288, 384 + (32 * 4), 32, 32));//Walking sprite
	AniT vex5(sf::IntRect(288, 384 + (32 * 5), 32, 32));//Walking sprite
	AniT vex6(sf::IntRect(288, 384 + (32 * 6), 32, 32));//Walking sprite
	AniT vex7(sf::IntRect(288, 384 + (32 * 7), 32, 32));//Walking sprite
	All_Sprites[6][11] = { { { vex0,vex1,vex2,vex3 },{ vex4,vex5,vex6,vex7 } } };

	//EBM sprites

	AniT vebm0(sf::IntRect(406, 576, 32, 32));//Blinking
	AniT vebm1(sf::IntRect(406, 576 + 32, 32, 32));//Blinking
	AniT vebm2(sf::IntRect(406, 576 + 64, 32, 32));//Blinking
	AniT vebm3(sf::IntRect(406, 576 + 96, 32, 32));//Blinking

	AniT vebm4(sf::IntRect(406 + 32, 576, 32, 32));//Floating with eye open
	AniT vebm5(sf::IntRect(406 + 32, 576 + 32, 32, 32));//Floating with eye open
	AniT vebm6(sf::IntRect(406 + 32, 576 + 64, 32, 32));//Floating with eye open
	AniT vebm7(sf::IntRect(406 + 32, 576 + 96, 32, 32));//Floating with eye open

	AniT vebm8(sf::IntRect(406 + 64, 576, 32, 32));//Floating with eye closed
	AniT vebm9(sf::IntRect(406 + 64, 576 + 32, 32, 32));//Floating with eye closed
	AniT vebm10(sf::IntRect(406 + 64, 576 + 64, 32, 32));//Floating with eye closed
	AniT vebm11(sf::IntRect(406 + 64, 576 + 96, 32, 32));//Floating with eye closed

	All_Sprites[6][12] = { { { vebm0,vebm4,vebm5,vebm6,vebm7,vebm6,vebm5,vebm4 },{ vebm4,vebm5,vebm6,vebm7,vebm6,vebm5 } ,{ vebm3,vebm8,vebm9,vebm10,vebm11,vebm10,vebm9,vebm8 },{ vebm1,vebm2,vebm3 },{ vebm2,vebm1,vebm0 }, } };

	AniT vEyeBall_MAIN0(sf::IntRect(502, 480, 64, 32));
	AniT vEyeBall_MAIN1(sf::IntRect(502, 480 + 32, 64, 32));
	AniT vEyeBall_MAIN2(sf::IntRect(502, 480 + 64, 64, 32));
	AniT vEyeBall_MAIN3(sf::IntRect(502, 480 + 96, 64, 32));

	All_Sprites[6][13] = { { { vEyeBall_MAIN0 },{ vEyeBall_MAIN1 },{ vEyeBall_MAIN2,vEyeBall_MAIN2 },{ vEyeBall_MAIN3,vEyeBall_MAIN3 } } };

	//Big_Squisher sprites~~~
	AniT vBSS(sf::IntRect(64, 384, 32, 32));
	AniT vBSS1(sf::IntRect(96, 384, 32, 32));
	AniT vBSS2(sf::IntRect(64 + 32, 384 + 32, 32, 32));
	AniT vBSS3(sf::IntRect(64, 384 + 32, 32, 32));
	AniT vBSS4(sf::IntRect(160, 224, 32, 32)); //Block
	All_Sprites[6][14] = { {{vBSS3,vBSS,vBSS1,vBSS2, vBSS4}} };

	
	
	//Com_Hand sprites~~~
	//Chain of wires
	AniT vCHWire(sf::IntRect(256, 1184, 32, 32));
	//Non-Bright claw
	AniT vCH(sf::IntRect(320, 1216, 64, 96));
	//Bright claw
	AniT vCH1(sf::IntRect(320 - 64, 1216, 64, 96));
	All_Sprites[6][15] = { { { vCHWire, vCH, vCH1 } } };
	//Com_MAIN sprites~~~
	//Body sprite
	AniT vCMbody(sf::IntRect(342, 704, 128, 82));
	//Mouth piece left
	AniT vCMMouth(sf::IntRect(224, 800, 25, 46));
	//Mouth piece right
	AniT vCMMouth1(sf::IntRect(249, 800, 25, 46));
	//EyeBall sprites: Starts open
	AniT vCMEye(sf::IntRect(480, 1120, 96, 96));
	AniT vCMEye1(sf::IntRect(480, 1120 + (96 * 1), 96, 96));
	AniT vCMEye2(sf::IntRect(480, 1120 + (96 * 2), 96, 96));
	AniT vCMEye3(sf::IntRect(480 - 96, 1120, 96, 96));
	AniT vCMEye4(sf::IntRect(480 - 96, 1120 + (96 * 1), 96, 96));
	AniT vCMEye5(sf::IntRect(480 - 96, 1120 + (96 * 2), 96, 96));
	AniT vCMEye6(sf::IntRect(480 - (96 * 2), 1120, 96, 96));
	
	All_Sprites[6][16] = { {{vCMbody,vCMMouth,vCMMouth1}, {vCMEye,vCMEye1,vCMEye2,vCMEye3,vCMEye4,vCMEye5,vCMEye6},{ vCMEye6,vCMEye5,vCMEye4,vCMEye3,vCMEye2,vCMEye1,vCMEye } } };
	
	///End of laser graphics.
	ISPD = false;
	GlobalSpeed = 0.1;
}

void NPC_MOTHER::draw(sf::RenderWindow &win) {
	
	//win.draw(anisprites[svectorindex][spriteindex]);
	
}

void NPC_MOTHER::check_OTBP() {
	for (unsigned int i = 0; i < Objects_to_be_put.size(); i++) {
			Objects_to_be_put[i]->when_dead();
			for (unsigned int b = 0; b < NPC_Cache.size(); b++) {
				if (NPC_Cache[b] == Objects_to_be_put[i]) {
					NPC_Cache.erase(NPC_Cache.begin() + b);
					break;
				}
			}
			if (Objects_to_be_put[i]->I_Del == true) {
				
				delete Objects_to_be_put[i];
			}
			else {
				Objects_to_be_deleted.push_back(Objects_to_be_put[i]);
			}
			Objects_to_be_put.erase(Objects_to_be_put.begin() + i);
	}
}

void NPC_MOTHER::maintick() {
	check_OTBP();
	Tick1();
	Tick2();
	if (ISPD == true) {
		resetall();
		Invisible_MOTHER::tell_WorldReset_all();
		ISPD = false;
	}
}

void NPC_MOTHER::maindraw(sf::RenderWindow &win) {
	for (unsigned int i = 0; i < NPC_Cache.size(); i++) {
		NPC_Cache[i]->draw(win);
	}
}
void NPC_MOTHER::tick(bool render) {
	
	
}

void NPC_MOTHER::SetSpriteColor(unsigned int Red, unsigned int Green, unsigned int Blue, unsigned int alpha) {
	sf::Color colour(Red, Green, Blue, alpha);
	colour.r = Red;
	colour.g = Green;
	colour.b = Blue;
	sprite.setColor(colour);
	
}

bool NPC_MOTHER::DynamicCheckPlayerCollision2(float NPCxpos, float NPCypos, float NPCwidth, float NPCheight) {
	float px = Player::PlayerObjects[PlayerChan]->getvx() + 16;
	float py = Player::PlayerObjects[PlayerChan]->getvy();
	//This side of the if statement is checking the x positions.
	if ((px > NPCxpos && px < NPCxpos + NPCwidth) && (py > NPCypos && py < NPCypos + NPCheight)) {
		return true;
	}
	py = Player::PlayerObjects[PlayerChan]->getvy() + 32;
	if ((px > NPCxpos && px < NPCxpos + NPCwidth) && (py > NPCypos && py < NPCypos + NPCheight)) {
		return true;
	}
	px = Player::PlayerObjects[PlayerChan]->getvx() + 32;
	py = Player::PlayerObjects[PlayerChan]->getvy() + 16;
	if ((px > NPCxpos && px < NPCxpos + NPCwidth) && (py > NPCypos && py < NPCypos + NPCheight)) {
		return true;
	}
	px = Player::PlayerObjects[PlayerChan]->getvx();
	py = Player::PlayerObjects[PlayerChan]->getvy() + 16;
	if ((px > NPCxpos && px < NPCxpos + NPCwidth) && (py > NPCypos && py < NPCypos + NPCheight)) {
		return true;
	}
	return false;
}

bool NPC_MOTHER::DynamicCheckPlayerCollision(float NPCxpos, float NPCypos, float NPCwidth, float NPCheight) {
	float px = Player::PlayerObjects[PlayerChan]->getvx();
	float py = Player::PlayerObjects[PlayerChan]->getvy();
	if ((((NPCxpos + RoughWidthL) >= px && (NPCxpos + RoughWidthL) <= px + PlayerWidth) || (((NPCxpos + NPCwidth) - RoughWidthR) >= px && ((NPCxpos + NPCwidth) - RoughWidthR) <= px + PlayerWidth)) &&
	//This side of the if statement is checking the y positions.
	((NPCypos + RoughHeightT) >= py && ((NPCypos + RoughHeightT) <= py + PlayerHeight) || ((NPCypos+NPCheight) - RoughHeightB >= py && (NPCypos+NPCheight)-RoughHeightB <= py+PlayerHeight))) {
		return true;
	}
	else {
		return false;
	}
}

bool NPC_MOTHER::StaticCheckPlayerCollision(int NPCxpos, int NPCypos) {
	return false;
}

bool NPC_MOTHER::initStaticCheckPlayerCollision(int Yourxpos, int Yourypos) {
	if (Yourxpos == initx && Yourypos == inity) {
		return true;
	}
	else {
		return false;
	}
}
bool NPC_MOTHER::CheckPlayerSliding() {
	return Player::PlayerObjects[PlayerChan]->getSliding();
}
void NPC_MOTHER::KillPlayer() {
	Player::PlayerObjects[PlayerChan]->Die();
	ISPD = true;
}

int NPC_MOTHER::Render(int NPCxpos, int NPCypos) {
	int d = sqrt(pow((Player::PlayerObjects[PlayerChan]->getx() - NPCxpos), 2) + pow((Player::PlayerObjects[PlayerChan]->gety() - NPCypos), 2));
	return d / base32;
}

float NPC_MOTHER::getx() {
	return x;
}

float NPC_MOTHER::gety() {
	return y;
}

void NPC_MOTHER::PauseAllNPC() {
	for (unsigned int i = 0; i < NPC_Cache.size(); i++) {
		NPC_Cache[i]->reset();
		Invisible_MOTHER::tell_WorldReset_all();
		NPC_Cache[i]->setPause(true);
	}
}

void NPC_MOTHER::UnPauseAllNPC() {
	for (unsigned int i = 0; i < NPC_Cache.size(); i++) {
		NPC_Cache[i]->setPause(false);
	}
}

void NPC_MOTHER::setPause(bool TF) {
	if (pause_lock == false) {
		isPaused = TF;
	}
	
}

void NPC_MOTHER::reset() {
	x = initx;
	y = inity;
}

bool NPC_MOTHER::deleteNPC(int x, int y) {
	for (unsigned int i = 0; i < NPC_Cache.size(); i++) {
		//This if statement checks to see if the x and y cordinates match up with the initial x and y's of the npc.
		if (NPC_Cache[i]->getdelx() == x && NPC_Cache[i]->getdely() == y) {
			//Deleting the pointer to stop memory leaks.
			delete NPC_Cache[i];
			//This will actually delete the npc.
			NPC_Cache.erase(NPC_Cache.begin() + i);
			return true;
		}
	}
	return false;
}

void NPC_MOTHER::delete_self(NPC_MOTHER * Object) {
	if (did_delete_self == false) {
		for (unsigned int i = 0; i < NPC_Cache.size(); i++) {
			if (NPC_Cache[i] == Object) {
				Objects_to_be_put.push_back(Object);
			}
		}
		did_delete_self = true;
	}
	
}

//This function is called when the NPC is revived.
void NPC_MOTHER::when_revive() {
	did_delete_self = false;
	sprite.activate();
}
//This function is called when the NPC is killed or deleted_self.
void NPC_MOTHER::when_dead() {
	sprite.deactivate();
}

void NPC_MOTHER::revive_NPCs() {
	check_OTBP();
	for (unsigned int i = 0; i < Objects_to_be_deleted.size(); i++) {
		NPC_Cache.push_back(Objects_to_be_deleted[i]);
		Objects_to_be_deleted[i]->when_revive();
		
	}
	Objects_to_be_deleted.clear();
}

void NPC_MOTHER::delete_ready() {
	for (unsigned int i = 0; i < Objects_to_be_deleted.size(); i++) {
		delete Objects_to_be_deleted[i];
	}
	for (unsigned int i = 0; i < Objects_to_be_put.size(); i++) {
		delete Objects_to_be_put[i];
	}
	Objects_to_be_deleted.clear();
	Objects_to_be_put.clear();
}
int NPC_MOTHER::getinitx() {
	return initx;
}

int NPC_MOTHER::getinity() {
	return inity;
}

int NPC_MOTHER::getdelx() {
	return delx;
}

int NPC_MOTHER::getdely() {
	return dely;
}

int NPC_MOTHER::gettypeID() {
	return typeID;
}

std::vector<int> NPC_MOTHER::getSavedParameters() {
	return SavedParameters;
}

void NPC_MOTHER::deleteAll() {
	//Deleting the pointers so that they do not cause memory leaks.
	for (unsigned int i = 0; i < NPC_Cache.size(); i++) {
		delete NPC_Cache[i];
	}
	delete_ready();
	//Deleting the empty pointer from the vector.
	NPC_Cache.clear();
}

void NPC_MOTHER::setWholePos(float x_pos, float y_pos) {
	
	sprite.setPosition(x_pos, y_pos);
}
std::string NPC_MOTHER::GetSave() {
	std::string r = "&1&";
	for (unsigned int i = 0; i < NPC_Cache.size(); i++) {
		r.append(":");
		
		for (unsigned int b = 0; b < NPC_Cache[i]->getSavedParameters().size(); b++) {
			r.append(std::to_string(NPC_Cache[i]->getSavedParameters()[b]) + ",");
		}
		r.append(":");

	}
	return r;
}

bool NPC_MOTHER::Check_Overlap(int Yourxpos, int Yourypos) {
	for (unsigned int i = 0; i < NPC_Cache.size(); i++) {
		if (NPC_Cache[i]->initStaticCheckPlayerCollision(Yourxpos, Yourypos) == true) {
			return true;
		}
	}
	return false;
}

bool NPC_MOTHER::getOVERRIDE_ANI() {
	return OVERRIDE_ANI;
}

void NPC_MOTHER::resetall() {
	revive_NPCs();
	for (unsigned int i = 0; i < NPC_Cache.size(); i++) {
		NPC_Cache[i]->reset();
	}
	
	
}

void NPC_MOTHER::setISPD() {
	ISPD = true;
}

void NPC_MOTHER::Aniset(int aniset, float new_max_ticks) {
	ani_set_index = aniset;
	if (new_max_ticks >= 0) {
		max_ticks = new_max_ticks;
	}
	ticks = 0;
	svectorindex = 0;
	anisprites = Sprites[aniset];
	sprite *= anisprites[0];
	spriteindex = 0;
}

void NPC_MOTHER::setGlobalSpeed(float new_speed) {
	GlobalSpeed = new_speed;
}

float NPC_MOTHER::getGlobalSpeed() {
	return GlobalSpeed;
}

CT *NPC_MOTHER::getSpritePointer() {
	return &sprite;
}

void NPC_MOTHER::deactivate() {
	sprite.deactivate();
	is_active = false;
	isPaused = true;
	pause_lock = true;
}
void NPC_MOTHER::activate() {
	isPaused = false;
	pause_lock = false;
	is_active = true;
	sprite.activate();
}

void NPC_MOTHER::Tick2() {
	for (unsigned int i = NPC_Cache.size() / 2; i < NPC_Cache.size(); i++) {
		if (NPC_Cache[i]->is_active == true) {

			NPC_Cache[i]->tick(true);
			NPC_Cache[i]->animate();
		}



	}
}

void NPC_MOTHER::Tick1() {
	for (unsigned int i = 0; i < NPC_Cache.size() / 2; i++) {
		if (NPC_Cache[i]->is_active == true) {

			NPC_Cache[i]->tick(true);
			NPC_Cache[i]->animate();
		}
	}
}

bool NPC_MOTHER::get_is_dead() {
	return did_delete_self;
}

const sf::Vector2f &NPC_MOTHER::getPosition() {
	return sf::Vector2f(x, y);
}