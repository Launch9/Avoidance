#include "stdafx.h"
#include "Basic_Tile_MOTHER.h"
#include "Light_MOTHER.h"
#include <thread>
#include <future>
#include <iostream>
#include "GF.h"
#include <memory>
#include <vector>
#include "Invisible_MOTHER.h"
#include "Sub_NPC_StaticCollision.h"
#include "Player.h"
std::vector<Basic_Tile_MOTHER *> Basic_Tile_MOTHER::NonColTiles;
std::vector<Basic_Tile_MOTHER *> Basic_Tile_MOTHER::NonColTiles_FORE;
//std::vector<ST> Basic_Tile_MOTHER::ForegroundSprites;
std::vector<Basic_Tile_MOTHER *> Basic_Tile_MOTHER::ColTiles;
std::vector<Basic_Tile_MOTHER *>  Basic_Tile_MOTHER::ColAniTiles;
std::vector<Basic_Tile_MOTHER *> Basic_Tile_MOTHER::ColProjectiles;
std::vector<std::vector<std::vector<std::vector<AniT>>>> Basic_Tile_MOTHER::All_Sprites;
//std::vector<ST> Basic_Tile_MOTHER::WallSprites;
//std::vector<ST> Basic_Tile_MOTHER::BackgroundSprites;
//std::vector<ST> Basic_Tile_MOTHER::ShopSprites;
//std::vector<ST> Basic_Tile_MOTHER::StairSprites;
//std::vector<std::vector<AniT>> Basic_Tile_MOTHER::AniBgSprites;
std::vector<Basic_Tile_MOTHER *> Basic_Tile_MOTHER::NonColAniTiles;
std::vector<Basic_Tile_MOTHER *> Basic_Tile_MOTHER::NonColAniTiles_FORE;
//std::vector<AniT> Basic_Tile_MOTHER::SaveStationSprites;
//std::vector<ST> Basic_Tile_MOTHER::DoorSprites;
//std::vector<std::vector<AniT>> Basic_Tile_MOTHER::ChestSprites;
//std::vector<std::vector<AniT>> Basic_Tile_MOTHER::CornerSprites;
//std::vector<std::vector<AniT>> Basic_Tile_MOTHER::PSwitchSprites;
//std::vector<ST> Basic_Tile_MOTHER::SealSprites;
//std::vector<std::vector<AniT>> Basic_Tile_MOTHER::RTileSprites;
//std::vector<std::vector<AniT>> Basic_Tile_MOTHER::P_Spawner_ConstSprites;
//std::vector<std::vector<AniT>> Basic_Tile_MOTHER::PTileSprites;

Basic_Tile_MOTHER::Basic_Tile_MOTHER() {
	sprite.setTexture(0);
}

Basic_Tile_MOTHER::~Basic_Tile_MOTHER() {

}
void Basic_Tile_MOTHER::Draw(sf::RenderWindow &win) {
	
}
void Basic_Tile_MOTHER::Drawall(sf::RenderWindow &win) {
	for (unsigned int i = 0; i < NonColTiles.size(); i++) {
		NonColTiles[i]->Draw(win);
	}
	for (unsigned int i = 0; i < ColTiles.size(); i++) {
		ColTiles[i]->Draw(win);
	}
	for (unsigned int i = 0; i < NonColAniTiles.size(); i++) {
		NonColAniTiles[i]->Draw_Ani(win);
	}
	for (unsigned int i = 0; i < ColProjectiles.size(); i++) {
		ColProjectiles[i]->Draw_Ani(win);
	}
	for (unsigned int i = 0; i < ColAniTiles.size(); i++) {
		ColAniTiles[i]->Draw_Ani(win);
	}
	for (unsigned int i = 0; i < NonColAniTiles_FORE.size(); i++) {
		NonColAniTiles_FORE[i]->Draw_Ani(win);
	}
}
bool Basic_Tile_MOTHER::ifCollision(int PlayerChannel) {
	//This is only ran if the tile is not special.
	return false;
}
bool Basic_Tile_MOTHER::CheckCollision(int Your_xpos, int Your_ypos, bool isPlayer, bool isProjectile) {
	
	std::future<int> b0 = std::async(CC0, Your_xpos, Your_ypos);
	int b1 = CC1(Your_xpos, Your_ypos);
	int b2 = b0.get();
	//In the case the you do actually collide into something, it returns true.
	if (b2 != -1 || b1 != -1) {
		if (b2 != -1) {
			if (ColTiles[b2]->ifCollisionBefore(isPlayer) == true) {
				return true;
			}
			
		}
		else {
			if (ColTiles[b1]->ifCollisionBefore(isPlayer) == true) {
				return true;
			};
		}
		
		
	}
	else {
		for (unsigned int i = 0; i < ColTiles.size(); i++) {
			ColTiles[i]->elseCollisionBefore(0);
		}
	}
	for (unsigned int i = 0; i < ColProjectiles.size(); i++) {
		if (ColProjectiles[i]->CheckCollision_Over(Your_xpos, Your_ypos) == true) {
			if (ColProjectiles[i]->ifCollisionBefore(isPlayer) == true) {
				return true;
			}
		}
		
	}
	for (unsigned int i = 0; i < ColAniTiles.size(); i++) {
		if (ColAniTiles[i]->CheckCollision_Over(Your_xpos, Your_ypos) == true) {
			if (ColAniTiles[i]->ifCollisionBefore(isPlayer) == true) {
				return true;
			}
		}
	}

	if (Invisible_MOTHER::checkCollision(Your_xpos, Your_ypos, isPlayer, isProjectile) == true) {
		return true;
	}

	if (Sub_NPC_StaticCollision::checkCollision(Your_xpos, Your_ypos) == true) {
		return true;
	}
	//Otherwise...
	//This happens when you are not colliding into any blocks.
	return false;
}

bool Basic_Tile_MOTHER::CheckCollision_Over(int Your_xpos, int Your_ypos) {
		//This checks to see if your pixels line up with the wall object's pixels.
		if ((Your_xpos == x) && (Your_ypos == y)) {
			return true;
		}
		//This happens if it did not line up.
		else {
			return false;
		}
}

void Basic_Tile_MOTHER::ResetLighting() {
	color.r = 0;color.g = 0; color.b = 0;color.a = 0;
	Light_MOTHER::SetColorAndLighting(color, x, y);
	sprite.setColor(color);
	
}


void Basic_Tile_MOTHER::ResetLighting_ANI() {
	Light_MOTHER::SetColorAndLighting(color, x, y);
	sprite.setColor(color);

}
void Basic_Tile_MOTHER::ResetAllLighting() {
	//This is used to thread the two different functions.
	std::thread t0(RL0);
	RL1();
	t0.join();

}

bool Basic_Tile_MOTHER::getSIMPLELIGHTING() {
	return isSIMPLELIGHTING;
}

void Basic_Tile_MOTHER::RL0() {
	for (unsigned int i = 0; i < ColTiles.size(); i++) {
		if (ColTiles[i]->getSIMPLELIGHTING() == false) {
			ColTiles[i]->ResetLighting();
		}
	}
	for (unsigned int i = 0; i < NonColTiles_FORE.size(); i++) {
		if (NonColTiles_FORE[i]->getSIMPLELIGHTING() == false) {
			NonColTiles_FORE[i]->ResetLighting_ANI();
		}
	}
	for (unsigned int i = 0; i < ColProjectiles.size(); i++) {
		if (ColProjectiles[i]->getSIMPLELIGHTING() == false) {
			ColProjectiles[i]->ResetLighting_ANI();
		}
	}
	for (unsigned int i = 0; i < NonColAniTiles_FORE.size(); i++) {
		if (NonColAniTiles_FORE[i]->getSIMPLELIGHTING() == false) {
			NonColAniTiles_FORE[i]->ResetLighting_ANI();
		}
	}
}
void Basic_Tile_MOTHER::RL1() {
	for (unsigned int i = 0; i < NonColTiles.size(); i++) {
		if (NonColTiles[i]->getSIMPLELIGHTING() == false) {
			
			NonColTiles[i]->ResetLighting();
		}
		
	}
	for (unsigned int i = 0; i < NonColAniTiles.size(); i++) {
		if (NonColAniTiles[i]->getSIMPLELIGHTING() == false) {
			NonColAniTiles[i]->ResetLighting_ANI();
		}
	}
	for (unsigned int i = 0; i < ColAniTiles.size(); i++) {
		if (ColAniTiles[i]->getSIMPLELIGHTING() == false) {
			ColAniTiles[i]->ResetLighting_ANI();
		}
	}
}

int Basic_Tile_MOTHER::CC0(int x, int y) {
	bool b = false;
	for (unsigned int i = 0; i < ColTiles.size() / 2; i++) {
		b = ColTiles[i]->CheckCollision_Over(x, y);
		if (b == true) {
			return i;
		}
	}

	return -1;
}

int Basic_Tile_MOTHER::CC1(int x, int y) {
	bool b = false;
	for (unsigned int i = ColTiles.size() / 2; i < ColTiles.size(); i++) {
		
		b = ColTiles[i]->CheckCollision_Over(x, y);
		if (b == true) {
			return i;
		}
	}
	return -1;
}


void Basic_Tile_MOTHER::Draw_Ani(sf::RenderWindow &win) {
	
}

void Basic_Tile_MOTHER::init(sf::Texture &tex) { 
	for (unsigned int i = 0; i < 13; i++) {
		All_Sprites.push_back({});
	}
	for (unsigned int i = 0; i < 200; i++) {
		All_Sprites[1].push_back({});
	}
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Lobby Sprites-=-=-=-=-=-=-=-=-=-=-
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	AniT tw1(sf::IntRect(0, 0, 32, 32));
	AniT tw2(sf::IntRect(0, 0, 32, 32));
	AniT tw3(sf::IntRect(0, 0, 32, 32));
	AniT tw4(sf::IntRect(0, 0, 32, 32));
	AniT tw5(sf::IntRect(0, 0, 32, 32));
	AniT tw6(sf::IntRect(288, 96, 32, 32));
	AniT tw7(sf::IntRect(0, 0, 32, 32));
	AniT tw8(sf::IntRect(0, 0, 32, 32));
	AniT tw9(sf::IntRect(0, 0, 32, 32));
	AniT tw10(sf::IntRect(0, 0, 32, 32));
	AniT tw11(sf::IntRect(0, 0, 32, 32));
	AniT tw12(sf::IntRect(0, 0, 32, 32));
	AniT tw13(sf::IntRect(0, 0, 32, 32));
	AniT tw14(sf::IntRect(0, 0, 32, 32));
	AniT tw15(sf::IntRect(0, 0, 32, 32));
	AniT tw16(sf::IntRect(0, 0, 32, 32));
	AniT tw17(sf::IntRect(256, 192, 32, 32));
	AniT tw18(sf::IntRect(320, 96, 32, 32));
	AniT tw19(sf::IntRect(416, 0, 32, 32));
	AniT tw20(sf::IntRect(416 + 32, 0, 32, 32));
	AniT tw21(sf::IntRect(416, 32, 32, 32));
	AniT tw22(sf::IntRect(416 + 32, 32, 32, 32));
	AniT tw23(sf::IntRect(352, 0, 32, 32));
	AniT tw24(sf::IntRect(352 + 32, 0, 32, 32));
	AniT tw25(sf::IntRect(352, 32, 32, 32));
	AniT tw26(sf::IntRect(352 + 32, 32, 32, 32));
	AniT tw27(sf::IntRect(480, 0, 32, 32));
	std::vector<std::vector<AniT>> tv = { { { tw1,tw2,tw3,tw4,tw5,tw6,tw7,tw8,tw9,tw10,tw11,tw12,tw13,tw14,tw15,tw16,tw17,tw18,tw19,tw20,tw21,tw22,tw23,tw24,tw25,tw26,tw27 } } };
	All_Sprites[1][0] = tv;//0
	//Background sprites~~~
	AniT tb1(sf::IntRect(288, 128, 32, 32)); //Purple flower
 	AniT tb2(sf::IntRect(288, 128 + 32, 32, 32)); //Blue flower
	AniT tb3(sf::IntRect(224, 32, 32, 32));
	AniT tb4(sf::IntRect(406, 0, 32, 32));
	AniT tb5(sf::IntRect(406, 32, 32, 32));
	AniT tb6(sf::IntRect(406, 64, 32, 32));
	AniT tb7(sf::IntRect(224 + 32, 128, 32, 32));
	AniT tb8(sf::IntRect(224 + 32, 128 + 32, 32, 32));
	AniT tb9(sf::IntRect(224, 128, 32, 32));
	AniT tb10(sf::IntRect(224, 128 + 32, 32, 32));
	AniT tb11(sf::IntRect(374, 128, 32, 64));
	AniT tb12(sf::IntRect(438, 224, 32, 64));
	AniT tb13(sf::IntRect(502, 128, 32, 32)); //left
	AniT tb14(sf::IntRect(320, 416, 256, 128)); //right
	AniT tb15(sf::IntRect(502, 128 + 32, 32, 32)); //up
	AniT tb16(sf::IntRect(502 + 32, 128 + 32, 32, 32)); //down
	AniT tb17(sf::IntRect(64, 96, 32, 32));
	AniT tb18(sf::IntRect(160, 0, 96, 96));
	AniT tb19(sf::IntRect(96, 96, 32, 32));
	AniT tb20(sf::IntRect(96, 96, 64, 64));
	AniT tb21(sf::IntRect(96, 96, 128, 128));
	AniT tb22(sf::IntRect(64, 0, 32, 32));
	AniT tb23(sf::IntRect(64 + 32, 0, 32, 32));
	AniT tb24(sf::IntRect(64 + 64, 0, 32, 32));
	AniT tb25(sf::IntRect(64, 32, 32, 32));
	AniT tb26(sf::IntRect(64 + 32, 32, 32, 32));
	AniT tb27(sf::IntRect(64 + 64, 32, 32, 32));
	AniT tb28(sf::IntRect(64, 64, 32, 32));
	AniT tb29(sf::IntRect(64 + 32, 64, 32, 32));
	AniT tb30(sf::IntRect(64 + 64, 64, 32, 32));
	
	std::vector<std::vector<AniT>> tv1 = { { { tb1,tb2,tb3,tb4,tb5,tb6,tb7,tb8,tb9,tb10,tb11,tb12,tb13,tb14,tb15,tb16,tb17,tb18,tb19,tb20,tb21,tb22,tb23,tb24,tb25,tb26,tb27,tb28,tb29,tb30 } } };
	All_Sprites[1][1] = tv1;//1
	
	//Foreground sprites~~~
	AniT tfore1(sf::IntRect(320, 416, 256, 128));
	AniT tfore2(sf::IntRect(512, 0, 32, 32));
	AniT tfore3(sf::IntRect(512 + 32, 0, 32, 32));
	AniT tfore4(sf::IntRect(512, 32, 32, 32));
	AniT tfore5(sf::IntRect(512 + 32, 32, 32, 32));
	AniT tfore6(sf::IntRect(256, 0, 96, 96));
	AniT tfore7(sf::IntRect(0, 0, 64, 96));
	AniT tfore8(sf::IntRect(320, 416, 256, 32));
	AniT tfore9(sf::IntRect(320, 416 + 32, 256, 32));
	AniT tfore10(sf::IntRect(320, 416, 32, 128));
	AniT tfore11(sf::IntRect(320 + 32, 416, 32, 128));
	AniT tfore12(sf::IntRect(320, 288, 256, 64));
	AniT tfore13(sf::IntRect(320, 288 + 64, 256, 64));
	AniT tfore14(sf::IntRect(192, 416, 64, 128));
	AniT tfore15(sf::IntRect(192 + 64, 416, 64, 128));
	//water banks
	AniT tfore16(sf::IntRect(64, 224, 32, 32));
	AniT tfore17(sf::IntRect(96, 224, 32, 32));
	AniT tfore18(sf::IntRect(128, 224, 32, 32));
	AniT tfore19(sf::IntRect(128, 224 + 32, 32, 32));
	AniT tfore20(sf::IntRect(128, 224 + 64, 32, 32));
	AniT tfore21(sf::IntRect(96, 224 + 64, 32, 32));
	AniT tfore22(sf::IntRect(64, 224 + 64, 32, 32));
	AniT tfore23(sf::IntRect(64, 224 + 32, 32, 32));
	All_Sprites[1][7] = { { { tfore1, tfore2, tfore3, tfore4, tfore5, tfore6, tfore7, tfore8, tfore9, tfore10, tfore11,tfore12,tfore13,tfore14,tfore15,
		tfore16,tfore17,tfore18,tfore19,tfore20,tfore21,tfore22,tfore23} } };//7

	//AniBg sprites~~~
	AniT tba1(sf::IntRect(96, 96, 32, 32));
	AniT tba2(sf::IntRect(96, 96 + (32 * 1), 32, 32));
	AniT tba3(sf::IntRect(96, 96 + (32 * 2), 32, 32));
	AniT tba4(sf::IntRect(224, 96, 32, 32));
	AniT tba5(sf::IntRect(224 + 32, 96, 32, 32));
	//Water
	AniT tba6(sf::IntRect(288, 192, 32, 32));
	AniT tba7(sf::IntRect(288, 192 + 32, 32, 32));
	AniT tba8(sf::IntRect(288, 192 + 64, 32, 32));
	//Dungeon one
	AniT tba9(sf::IntRect(352, 192 - 128, 96, 64));
	AniT tba10(sf::IntRect(352, 192 - 64, 96, 64));
	AniT tba11(sf::IntRect(352, 192, 96, 64));
	

	All_Sprites[1][4] = { { { tba1, tba2, tba3, tba2 },{ tba4,tba5 },{tba6,tba7,tba8},{tba9,tba10,tba11,tba10,tba9,tba11,tba9,tba10,tba11} } };
	
	//SaveStation sprites~~~
	AniT tsa1(sf::IntRect(64, 128, 32, 32));
	AniT tsa2(sf::IntRect(64, 128 + 32, 32, 32));
	AniT tsa3(sf::IntRect(64, 128 + 64, 32, 32));
	All_Sprites[1][5] = { { { tsa1,tsa2,tsa3,tsa2 } } };//5
	
	//Chest sprites~~~
	
	//TripleChest sprites~~~
	AniT tch1(sf::IntRect(256, 224, 32, 32)); //Tool box closed
	AniT tch2(sf::IntRect(256, 224 + 32, 32, 32)); //Tool box open
	AniT tch3(sf::IntRect(256, 224 + 64, 32, 32)); //Tool box empty
	All_Sprites[1][17] = { { { tch1,tch2,tch3 } } };
	//Sign sprites~~~
	//Mr. Sign
	AniT tsign12(sf::IntRect(320, 96, 32, 32));
	AniT tsign13(sf::IntRect(320, 96 + 32, 32, 32));
	AniT tsign14(sf::IntRect(320, 96 + 64, 32, 32));
	All_Sprites[1][15] = { {tsign12,tsign13,tsign14} };
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Dungeon 1 Sprites-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	
	for (unsigned int i = 0; i < 25; i++) {
		All_Sprites[2].push_back({});
	}
	//Wall sprites~~~
	AniT w1(sf::IntRect(32 * 3, 0, 32, 32));
	AniT w2(sf::IntRect(32 * 2, 32, 32, 32));
	AniT w3(sf::IntRect(32 * 3, 32 * 2, 32, 32));
	//Dungeon tile
	AniT w4(sf::IntRect(224, 64, 32, 32));
	//Dungeon tile
	AniT w5(sf::IntRect(224, 96, 32, 32));
	//Lobby tiles
	AniT w6(sf::IntRect(406 + (32 * 0), 96 + (32 * 0), 32, 32)); //Static boulder
	AniT w7(sf::IntRect(406 + (32 * 0), 96 + (32 * 1), 32, 32));
	AniT w8(sf::IntRect(406 + (32 * 1), 96 + (32 * 1), 32, 32));
	AniT w9(sf::IntRect(406 + (32 * 2), 96 + (32 * 1), 32, 32));
	AniT w10(sf::IntRect(406 + (32 * 1), 96 + (32 * 2), 32, 32));
	AniT w11(sf::IntRect(406 + (32 * 2), 96 + (32 * 2), 32, 32));
	////Chemistry table tile
	AniT w12(sf::IntRect(438, 192, 64, 32));
	//Concrete tile
	AniT w13(sf::IntRect(470, 224, 32, 32));
	AniT w14(sf::IntRect(470 + 32, 224, 32, 32));
	AniT w15(sf::IntRect(470 + 32, 224 + 32, 32, 32));
	AniT w16(sf::IntRect(470, 224 + 32, 32, 32));
	AniT w17(sf::IntRect(470 + 64, 224, 32, 32));
	AniT w18(sf::IntRect(470 + 64, 224 + 32, 32, 32));
	//SpaceShip Lobby tiles.
	AniT w19(sf::IntRect(32, 192, 32, 32));
	AniT w20(sf::IntRect(64, 192, 32, 32));
	AniT w21(sf::IntRect(32, 224, 32, 32));
	AniT w22(sf::IntRect(64, 224, 32, 32));
	AniT w23(sf::IntRect(32, 256, 32, 32));
	AniT w24(sf::IntRect(64, 256, 32, 32));
	AniT w25(sf::IntRect(32, 289, 32, 32));
	AniT w26(sf::IntRect(64, 289, 32, 32));
	AniT w27(sf::IntRect(0, 192, 32, 32));
	//Cap block
	AniT w28(sf::IntRect(192, 224, 32, 32));
	std::vector<std::vector<AniT>> v = { { {w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14,w15,w16,w17,w18,w19,w20,w21,w22,w23,w24,w25,w26,w27,w28} } };
	All_Sprites[2][0] = v;//0
	//Background sprites~~~
	//Dungeon ground tile
	AniT b1(sf::IntRect(64, 0, 32, 32));
	//Normal grass tile
	AniT b2(sf::IntRect(224, 0, 32, 32));
	//Flower grass tile
	AniT b3(sf::IntRect(224, 32, 32, 32));
	//Brown Floor Dungeon tile
	AniT b4(sf::IntRect(406, 0, 32, 32));
	//Purplesponge Floor Dungeon tile
	AniT b5(sf::IntRect(406, 32, 32, 32));
	//Red lobby carpet tile
	AniT b6(sf::IntRect(406, 64, 32, 32));
	//Purple mushroom tile
	AniT b7(sf::IntRect(374, 64, 32, 32));
	//Red mushroom tile
	AniT b8(sf::IntRect(374, 96, 32, 32));
	//Rubble tile
	AniT b9(sf::IntRect(342, 64, 32, 32));
	//Dungeon grass sticking out of floor tile
	AniT b10(sf::IntRect(342, 96, 32, 32));
	//Ladder up tile
	AniT b11(sf::IntRect(374, 128, 32, 64));
	//Potted flower tile
	AniT b12(sf::IntRect(438, 224, 32, 64));
	//Wall Lamps
	AniT b13(sf::IntRect(502, 128, 32, 32)); //left
	AniT b14(sf::IntRect(502 + 32, 128, 32, 32)); //right
	AniT b15(sf::IntRect(502, 128 + 32, 32, 32)); //up
	AniT b16(sf::IntRect(502 + 32, 128 + 32, 32, 32)); //down
	//SpaceShip Lobby tiles
	AniT b17(sf::IntRect(32, 160, 32, 32));
	AniT b18(sf::IntRect(96, 256, 96, 96));
	AniT b19(sf::IntRect(192, 0, 32, 32));
	AniT b20(sf::IntRect(192, 256, 64, 64));
	AniT b21(sf::IntRect(342, 416, 128, 128));
	//Lobby Path
	AniT b22(sf::IntRect(224, 384, 32, 32));
	AniT b23(sf::IntRect(224 + 32, 384, 32, 32));
	AniT b24(sf::IntRect(224 + 64, 384, 32, 32));
	AniT b25(sf::IntRect(224, 384 + 32, 32, 32));
	AniT b26(sf::IntRect(224 + 32, 384 + 32, 32, 32));
	AniT b27(sf::IntRect(224 + 64, 384 + 32, 32, 32));
	AniT b28(sf::IntRect(224, 384 + 64, 32, 32));
	AniT b29(sf::IntRect(224 + 32, 384 + 64, 32, 32));
	AniT b30(sf::IntRect(128, 224, 32, 32));
	
	std::vector<std::vector<AniT>> v1 = { { { b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15,b16,b17,b18,b19,b20,b21,b22,b23,b24,b25,b26,b27,b28,b29,b30} } };
	All_Sprites[2][1] = v1;//1
	//Shop sprites~~~
	AniT s1(sf::IntRect(32 * 3, 32, 32, 32));
	All_Sprites[2][2] = { { {s1} } };//2
	//Stair sprites~~~
	AniT st1(sf::IntRect(32, 0, 32, 32));
	AniT st1_2(sf::IntRect(32, 32, 32, 32));
	All_Sprites[2][3] = { { {st1,st1_2} } };//3
	//AniBg sprites~~~
	AniT ba1(sf::IntRect(96, 96, 32, 32));
	AniT ba2(sf::IntRect(96, 96 + (32 * 1), 32, 32));
	AniT ba3(sf::IntRect(96, 96 + (32 * 2), 32, 32));
	AniT ba4(sf::IntRect(342, 192, 32, 32));
	AniT ba5(sf::IntRect(342 + 32, 192, 32, 32));
	//Torches
	//Top square
	AniT ba6(sf::IntRect(406, 288, 32, 32)); //top left
	AniT ba7(sf::IntRect(406 + 32, 288, 32, 32)); //top right
	AniT ba8(sf::IntRect(406 + 32, 288 + 32, 32, 32)); //bottom right
	AniT ba9(sf::IntRect(406, 288 + 32, 32, 32)); //bottom left
	//Next square down
	AniT ba10(sf::IntRect(406, 288 + (32 * 2), 32, 32)); //top left
	AniT ba11(sf::IntRect(406 + 32, 288 + (32 * 2), 32, 32)); //top right
	AniT ba12(sf::IntRect(406 + 32, 288 + 32 + (32 * 2), 32, 32)); //bottom right
	AniT ba13(sf::IntRect(406, 288 + 32 + (32 * 2), 32, 32)); //bottom left
    //Next square down
	AniT ba14(sf::IntRect(406, 288 + (32 * 4), 32, 32)); //top left
	AniT ba15(sf::IntRect(406 + 32, 288 + (32 * 4), 32, 32)); //top right
	AniT ba16(sf::IntRect(406 + 32, 288 + 32 + (32 * 4), 32, 32)); //bottom right
	AniT ba17(sf::IntRect(406, 288 + 32 + (32 * 4), 32, 32)); //bottom left
	//Next square down
	AniT ba18(sf::IntRect(406, 288 + (32 * 6), 32, 32)); //top left
	AniT ba19(sf::IntRect(406 + 32, 288 + (32 * 6), 32, 32)); //top right
	AniT ba20(sf::IntRect(406 + 32, 288 + 32 + (32 * 6), 32, 32)); //bottom right
	AniT ba21(sf::IntRect(406, 288 + 32 + (32 * 6), 32, 32)); //bottom left
	std::vector<std::vector<AniT>> v2 = { { {ba1, ba2, ba3, ba2}, {ba4,ba5}, {ba6,ba10,ba14,ba18},{ba7,ba11,ba15,ba19},{ba8,ba12,ba16,ba20},{ba9,ba13,ba17,ba21} } };
	All_Sprites[2][4] = v2;//4

	//SaveStation sprites~~~
	AniT sa1(sf::IntRect(406, 192 - 32, 32, 32));
	AniT sa2(sf::IntRect(406, 192, 32, 32));
	AniT sa3(sf::IntRect(406, 192 + 32, 32, 32));
	All_Sprites[2][5] = { { {sa1,sa2,sa3,sa2} } };//5
	
	//Door sprites~~~
	AniT d1(sf::IntRect(32, 32, 32, 32));
	All_Sprites[2][6] = { { {d1} } };//6
	//Foreground sprites~~~
	AniT fore1(sf::IntRect(160, 96, 64, 96));
	AniT fore2(sf::IntRect(0, 96, 32, 32));
	AniT fore3(sf::IntRect(32, 96, 32, 32));
	AniT fore4(sf::IntRect(0, 128, 32, 32));
	AniT fore5(sf::IntRect(32, 128, 32, 32));
	AniT fore6(sf::IntRect(0, 320, 96, 96));
	AniT fore7(sf::IntRect(160, 384, 64, 96));
	
	All_Sprites[2][7] = { { { fore1, fore2, fore3, fore4, fore5, fore6, fore7 } } };//7
	//Chest sprites~~~
	//Standard
	AniT ch1(sf::IntRect(256, 64, 32, 32));//Chest closed : Standard
	AniT ch2(sf::IntRect(256, 96, 32, 32));//Chest open : Standard
	//Advanced
	AniT ch3(sf::IntRect(192, 0, 32, 32));
	AniT ch4(sf::IntRect(192, 32, 32, 32));
	All_Sprites[2][8] = { { {ch1,ch2}, {ch3,ch4} } };//8
	//Corner sprites~~~
	//Purple
	AniT cr(sf::IntRect(256, 128, 32, 32));//Top left
	AniT cr1(sf::IntRect(288, 128, 32, 32));//Top right
	AniT cr2(sf::IntRect(288, 160, 32, 32));//Bottom right
	AniT cr3(sf::IntRect(256, 160, 32, 32));//Bottom left
	//Red cr
	AniT cr4(sf::IntRect(256, 128 + 64, 32, 32));//Top left
	AniT cr5(sf::IntRect(288, 128 + 64, 32, 32));//Top right
	AniT cr6(sf::IntRect(288, 160 + 64, 32, 32));//Bottom right
	AniT cr7(sf::IntRect(256, 160 + 64, 32, 32));//Bottom left
	All_Sprites[2][9] = { { {cr,cr1,cr2,cr3,cr4,cr5,cr6,cr7} } };//9
	//PSwitch sprites~~~

	//Up
	AniT ps(sf::IntRect(342, 224, 32, 32));
	AniT ps1(sf::IntRect(342 + 32, 224, 32, 32));
	//Right
	AniT ps2(sf::IntRect(342 + 32, 224 + 32, 32, 32));
	AniT ps3(sf::IntRect(342 + 32, 224 + 64, 32, 32));
	//Down
	AniT ps4(sf::IntRect(342, 224 + 96, 32, 32));
	AniT ps5(sf::IntRect(342 + 32, 224 + 96, 32, 32));
	//Left
	AniT ps6(sf::IntRect(342, 224 + 32, 32, 32));
	AniT ps7(sf::IntRect(342, 224 + 64, 32, 32));
	//Up Light
	AniT ps8(sf::IntRect(342, 352, 32, 32));
	//Down Light
	AniT ps9(sf::IntRect(342 + 32, 352, 32, 32));
	//Right Light
	AniT ps10(sf::IntRect(342 + 32, 352 + 32, 32, 32));
	//Left Light
	AniT ps11(sf::IntRect(342, 352 + 32, 32, 32));
	All_Sprites[2][10] = { { {ps,ps1,ps2,ps3,ps4,ps5,ps6,ps7,ps8,ps9,ps10,ps11} } };//10
	//P_Spawner_Const sprites~~~
	//Up
	AniT pc(sf::IntRect(256,256,32,32));
	AniT pc1(sf::IntRect(256, 256 + 64, 32, 32));
	//Right
	AniT pc2(sf::IntRect(256 + 32, 256, 32, 32));
	AniT pc3(sf::IntRect(256 + 32, 256 + 64, 32, 32));
	//Down
	AniT pc4(sf::IntRect(256 + 32, 256 + 32, 32, 32));
	AniT pc5(sf::IntRect(256 + 32, 256 + 96, 32, 32));
	//Left
	AniT pc6(sf::IntRect(256, 256 + 32, 32, 32));
	AniT pc7(sf::IntRect(256, 256 + 96, 32, 32));
	All_Sprites[2][13] = { { {pc,pc1,pc2,pc3,pc4,pc5,pc6,pc7} } };//13
	//Seal sprites~~~
	AniT se(sf::IntRect(342, 160, 32, 32));
	
	All_Sprites[2][11] = { { { se } } };//11
	//RTile sprites-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	AniT rt0(sf::IntRect(128, 0, 32, 32)); //tile lit red
	AniT rt1(sf::IntRect(128, 32, 32, 32)); //tile lit pink
	AniT rt2(sf::IntRect(128, 64, 32, 32)); //tile lit nothing
	All_Sprites[2][12] = { { {rt0, rt1}, {rt2} } };//12
	//PTile sprites~~~
	AniT pt0(sf::IntRect(160, 0, 32, 32));
	AniT pt1(sf::IntRect(160, 32, 32, 32));
	AniT pt2(sf::IntRect(160, 64, 32, 32));
	All_Sprites[2][14] = { { {pt0,pt1,pt2} } };//14
	//Stream sprites~~~
	AniT str0(sf::IntRect(128, 192, 64, 32));
	All_Sprites[2][16] = { { {str0} } };
	//Rock sprites~~~
	AniT rock0(sf::IntRect(0, 128, 32, 32));
	AniT rock1(sf::IntRect(32, 128, 32, 32));
	AniT rock2(sf::IntRect(0, 128 + 32, 32, 32));
	AniT rock3(sf::IntRect(32, 128 + 32, 32, 32));
	All_Sprites[2][18] = { {{rock0,rock1,rock2,rock3}} };
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Lobby 2 Sprites-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	for (unsigned int i = 0; i < 200; i++) {
		All_Sprites[3].push_back({});
	}
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Lobby Sprites-=-=-=-=-=-=-=-=-=-=-
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	AniT uw1(sf::IntRect(160, 224, 32, 32));
	AniT uw2(sf::IntRect(192, 224, 32, 32));
	AniT uw3(sf::IntRect(160, 288, 32, 32));
	AniT uw4(sf::IntRect(192, 288, 32, 32));
	AniT uw5(sf::IntRect(0, 0, 32, 32));
	AniT uw6(sf::IntRect(288, 96, 32, 32));
	AniT uw7(sf::IntRect(0, 0, 32, 32));
	AniT uw8(sf::IntRect(0, 0, 32, 32));
	AniT uw9(sf::IntRect(0, 0, 32, 32));
	AniT uw10(sf::IntRect(0, 0, 32, 32));
	AniT uw11(sf::IntRect(0, 0, 32, 32));
	AniT uw12(sf::IntRect(0, 0, 32, 32));
	AniT uw13(sf::IntRect(0, 0, 32, 32));
	AniT uw14(sf::IntRect(0, 0, 32, 32));
	AniT uw15(sf::IntRect(0, 0, 32, 32));
	AniT uw16(sf::IntRect(0, 0, 32, 32));
	AniT uw17(sf::IntRect(256, 192, 32, 32));
	AniT uw18(sf::IntRect(320, 96, 32, 32));
	AniT uw19(sf::IntRect(416, 0, 32, 32));
	AniT uw20(sf::IntRect(416 + 32, 0, 32, 32));
	AniT uw21(sf::IntRect(416, 32, 32, 32));
	AniT uw22(sf::IntRect(416 + 32, 32, 32, 32));
	AniT uw23(sf::IntRect(352, 0, 32, 32));
	AniT uw24(sf::IntRect(352 + 32, 0, 32, 32));
	AniT uw25(sf::IntRect(352, 32, 32, 32));
	AniT uw26(sf::IntRect(352 + 32, 32, 32, 32));
	AniT uw27(sf::IntRect(480, 0, 32, 32));
	std::vector<std::vector<AniT>> uv = { { { uw1,uw2,uw3,uw4,uw5,uw6,uw7,uw8,uw9,uw10,uw11,uw12,uw13,uw14,uw15,uw16,uw17,uw18,uw19,uw20,uw21,uw22,uw23,uw24,uw25,uw26,uw27 } } };
	All_Sprites[3][0] = uv;//0
						   //Background sprites~~~
	AniT ub1(sf::IntRect(288, 128, 32, 32)); //Purple flower
	AniT ub2(sf::IntRect(288, 128 + 32, 32, 32)); //Blue flower
	AniT ub3(sf::IntRect(448, 64, 128, 128)); //Farris wheel
	AniT ub4(sf::IntRect(256, 384, 64, 32)); //Dumped radioactive waste barrel
	AniT ub5(sf::IntRect(480, 576, 96, 64)); //Dungeon two entrance
	AniT ub6(sf::IntRect(406, 64, 32, 32));
	AniT ub7(sf::IntRect(224 + 32, 128, 32, 32));
	AniT ub8(sf::IntRect(224 + 32, 128 + 32, 32, 32));
	AniT ub9(sf::IntRect(224, 128, 32, 32));
	AniT ub10(sf::IntRect(224, 128 + 32, 32, 32));
	AniT ub11(sf::IntRect(374, 128, 32, 64));
	AniT ub12(sf::IntRect(438, 224, 32, 64));
	AniT ub13(sf::IntRect(502, 128, 32, 32)); //left
	AniT ub14(sf::IntRect(320, 416, 256, 128)); //right
	AniT ub15(sf::IntRect(502, 128 + 32, 32, 32)); //up
	AniT ub16(sf::IntRect(502 + 32, 128 + 32, 32, 32)); //down
	AniT ub17(sf::IntRect(64, 96, 32, 32));
	AniT ub18(sf::IntRect(160, 0, 96, 96));
	AniT ub19(sf::IntRect(96, 96, 32, 32));
	AniT ub20(sf::IntRect(96, 96, 64, 64));
	AniT ub21(sf::IntRect(96, 96, 128, 128));
	AniT ub22(sf::IntRect(64, 0, 32, 32));
	AniT ub23(sf::IntRect(64 + 32, 0, 32, 32));
	AniT ub24(sf::IntRect(64 + 64, 0, 32, 32));
	AniT ub25(sf::IntRect(64, 32, 32, 32));
	AniT ub26(sf::IntRect(64 + 32, 32, 32, 32));
	AniT ub27(sf::IntRect(64 + 64, 32, 32, 32));
	AniT ub28(sf::IntRect(64, 64, 32, 32));
	AniT ub29(sf::IntRect(64 + 32, 64, 32, 32));
	AniT ub30(sf::IntRect(64 + 64, 64, 32, 32));
	

	std::vector<std::vector<AniT>> uv1 = { { { ub1,ub2,ub3,ub4,ub5,ub6,ub7,ub8,ub9,ub10,ub11,ub12,ub13,ub14,ub15,ub16,ub17,ub18,ub19,ub20,ub21,ub22,ub23,ub24,ub25,ub26,ub27,ub28,ub29,ub30 } } };
	All_Sprites[3][1] = uv1;//1

	//Foreground sprites~~~
	AniT ufore1(sf::IntRect(320, 416, 256, 128));
	AniT ufore2(sf::IntRect(512, 0, 32, 32));
	AniT ufore3(sf::IntRect(512 + 32, 0, 32, 32));
	AniT ufore4(sf::IntRect(512, 32, 32, 32));
	AniT ufore5(sf::IntRect(512 + 32, 32, 32, 32));
	AniT ufore6(sf::IntRect(256, 0, 96, 96));
	AniT ufore7(sf::IntRect(0, 0, 64, 96));
	AniT ufore8(sf::IntRect(320, 416, 256, 32));
	AniT ufore9(sf::IntRect(320, 416 + 32, 256, 32));
	AniT ufore10(sf::IntRect(320, 416, 32, 128));
	AniT ufore11(sf::IntRect(320 + 32, 416, 32, 128));
	AniT ufore12(sf::IntRect(320, 288, 256, 64));
	AniT ufore13(sf::IntRect(320, 288 + 64, 256, 64));
	AniT ufore14(sf::IntRect(192, 416, 64, 128));
	AniT ufore15(sf::IntRect(192 + 64, 416, 64, 128));
	
	//water banks
	AniT ufore16(sf::IntRect(64, 224, 32, 32));
	AniT ufore17(sf::IntRect(96, 224, 32, 32));
	AniT ufore18(sf::IntRect(128, 224, 32, 32));
	AniT ufore19(sf::IntRect(128, 224 + 32, 32, 32));
	AniT ufore20(sf::IntRect(128, 224 + 64, 32, 32));
	AniT ufore21(sf::IntRect(96, 224 + 64, 32, 32));
	AniT ufore22(sf::IntRect(64, 224 + 64, 32, 32));
	AniT ufore23(sf::IntRect(64, 224 + 32, 32, 32));
	//Big red mushroom
	AniT ufore24(sf::IntRect(192, 320, 64, 96));
	//Big blue/purple mushroom
	AniT ufore25(sf::IntRect(96, 320, 96, 96));
	All_Sprites[3][7] = { { { ufore1, ufore2, ufore3, ufore4, ufore5, ufore6, ufore7, ufore8, ufore9, ufore10, ufore11,ufore12,ufore13,ufore14,ufore15,
		ufore16,ufore17,ufore18,ufore19,ufore20,ufore21,ufore22,ufore23,ufore24,ufore25 } } };//7

																			  //AniBg sprites~~~
	AniT uba1(sf::IntRect(96, 96, 32, 32));
	AniT uba2(sf::IntRect(96, 96 + (32 * 1), 32, 32));
	AniT uba3(sf::IntRect(96, 96 + (32 * 2), 32, 32));
	AniT uba4(sf::IntRect(224, 96, 32, 32));
	AniT uba5(sf::IntRect(224 + 32, 96, 32, 32));
	//Water
	AniT uba6(sf::IntRect(288, 192, 32, 32));
	AniT uba7(sf::IntRect(288, 192 + 32, 32, 32));
	AniT uba8(sf::IntRect(288, 192 + 64, 32, 32));
	//Dungeon one
	AniT uba9(sf::IntRect(352, 192 - 128, 96, 64));
	AniT uba10(sf::IntRect(352, 192 - 64, 96, 64));
	AniT uba11(sf::IntRect(352, 192, 96, 64));


	All_Sprites[3][4] = { { { uba1, uba2, uba3, uba2 },{ uba4,uba5 },{ uba6,uba7,uba8 },{ uba9,uba10,uba11,uba10,uba9,uba11,uba9,uba10,uba11 } } };
	
	//SaveStation sprites~~~
	AniT usa1(sf::IntRect(64, 128, 32, 32));
	AniT usa2(sf::IntRect(64, 128 + 32, 32, 32));
	AniT usa3(sf::IntRect(64, 128 + 64, 32, 32));
	All_Sprites[3][5] = { { { usa1,usa2,usa3,usa2 } } };//5
	
	//Chest sprites~~~

	//Stream sprites~~~
	AniT ustr0(sf::IntRect(160, 256, 64, 32));
	All_Sprites[3][16] = { { { ustr0 } } };
	//TripleChest sprites~~~
	AniT uch1(sf::IntRect(256, 224, 32, 32)); //Tool box closed
	AniT uch2(sf::IntRect(256, 224 + 32, 32, 32)); //Tool box open
	AniT uch3(sf::IntRect(256, 224 + 64, 32, 32)); //Tool box empty
	All_Sprites[3][17] = { { { uch1,uch2,uch3 } } };

	//Sign sprites~~~
	//Mr. Sign
	AniT usign12(sf::IntRect(320, 96, 32, 32));
	AniT usign13(sf::IntRect(320, 96 + 32, 32, 32));
	AniT usign14(sf::IntRect(320, 96 + 64, 32, 32));
	All_Sprites[3][15] = { { usign12,usign13,usign14 } };
	//AniWall sprites~~~
	//Radioactive waste barrel
	AniT uradio1(sf::IntRect(224, 224, 32, 32));
	AniT uradio2(sf::IntRect(224, 224 + 32, 32, 32));
	AniT uradio3(sf::IntRect(224, 224 + 64, 32, 32));
	//Rock with grass swaying
	AniT urock1(sf::IntRect(288, 288, 32, 32));
	AniT urock2(sf::IntRect(288, 288 + 32, 32, 32));
	AniT urock3(sf::IntRect(288, 288 + 64, 32, 32));
	All_Sprites[3][19] = { {uradio1,uradio2,uradio3,uradio2 }, {urock1,urock2,urock3,urock2} };

	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Dungeon 2 Sprites-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	for (unsigned int i = 0; i < 25; i++) {
		All_Sprites[4].push_back({});
	}
	//Wall sprites~~~
	AniT qw1(sf::IntRect(32 * 3, 0, 32, 32));
	AniT qw2(sf::IntRect(32 * 2, 32, 32, 32));
	AniT qw3(sf::IntRect(32 * 3, 32 * 2, 32, 32));
	//Dungeon tile
	AniT qw4(sf::IntRect(224, 64, 32, 32));
	//Dungeon tile
	AniT qw5(sf::IntRect(224, 96, 32, 32));
	//Lobby tiles
	AniT qw6(sf::IntRect(406 + (32 * 0), 96 + (32 * 0), 32, 32)); //Static boulder
	AniT qw7(sf::IntRect(406 + (32 * 0), 96 + (32 * 1), 32, 32));
	AniT qw8(sf::IntRect(406 + (32 * 1), 96 + (32 * 1), 32, 32));
	AniT qw9(sf::IntRect(406 + (32 * 2), 96 + (32 * 1), 32, 32));
	AniT qw10(sf::IntRect(406 + (32 * 1), 96 + (32 * 2), 32, 32));
	AniT qw11(sf::IntRect(406 + (32 * 2), 96 + (32 * 2), 32, 32));
	////Chemistry table tile
	AniT qw12(sf::IntRect(438, 192, 64, 32));
	//Concrete tile
	AniT qw13(sf::IntRect(470, 224, 32, 32));
	AniT qw14(sf::IntRect(470 + 32, 224, 32, 32));
	AniT qw15(sf::IntRect(470 + 32, 224 + 32, 32, 32));
	AniT qw16(sf::IntRect(470, 224 + 32, 32, 32));
	AniT qw17(sf::IntRect(470 + 64, 224, 32, 32));
	AniT qw18(sf::IntRect(470 + 64, 224 + 32, 32, 32));
	//SpaceShip Lobby tiles.
	AniT qw19(sf::IntRect(470, 288, 32, 32));
	AniT qw20(sf::IntRect(470 + 32, 288, 32, 32));
	AniT qw21(sf::IntRect(470 + 64, 288, 32, 32));
	AniT qw22(sf::IntRect(470 + 32, 288 + 32, 32, 32));
	AniT qw23(sf::IntRect(470 + 64, 288 + 32, 32, 32));
	AniT qw24(sf::IntRect(64, 192, 32, 32)); //yellow radioactive barrel
	AniT qw25(sf::IntRect(32, 192, 32, 32)); //red radioactive barrel
	AniT qw26(sf::IntRect(64, 289, 32, 32));
	AniT qw27(sf::IntRect(0, 192, 32, 32));
	//Cap block
	AniT qw28(sf::IntRect(192, 224, 32, 32));
	std::vector<std::vector<AniT>> qv = { { { qw1,qw2,qw3,qw4,qw5,qw6,qw7,qw8,qw9,qw10,qw11,qw12,qw13,qw14,qw15,qw16,qw17,qw18,qw19,qw20,qw21,qw22,qw23,qw24,qw25,qw26,qw27,qw28 } } };
	All_Sprites[4][0] = qv;//0
						  //Background sprites~~~
						  //Dungeon ground tile
	AniT qb1(sf::IntRect(64, 0, 32, 32));
	//Normal grass tile
	AniT qb2(sf::IntRect(224, 0, 32, 32));
	//Flower grass tile
	AniT qb3(sf::IntRect(224, 32, 32, 32));
	//Brown Floor Dungeon tile
	AniT qb4(sf::IntRect(406, 0, 32, 32));
	//Purplesponge Floor Dungeon tile
	AniT qb5(sf::IntRect(406, 32, 32, 32));
	//Red lobby carpet tile
	AniT qb6(sf::IntRect(406, 64, 32, 32));
	//Purple mushroom tile
	AniT qb7(sf::IntRect(374, 64, 32, 32));
	//Red mushroom tile
	AniT qb8(sf::IntRect(374, 96, 32, 32));
	//Rubble tile
	AniT qb9(sf::IntRect(342, 64, 32, 32));
	//Dungeon grass sticking out of floor tile
	AniT qb10(sf::IntRect(342, 96, 32, 32));
	//Ladder up tile
	AniT qb11(sf::IntRect(374, 128, 32, 64));
	//Potted flower tile
	AniT qb12(sf::IntRect(438, 224, 32, 64));
	//Wall Lamps
	AniT qb13(sf::IntRect(502, 128, 32, 32)); //left
	AniT qb14(sf::IntRect(502 + 32, 128, 32, 32)); //right
	AniT qb15(sf::IntRect(502, 128 + 32, 32, 32)); //up
	AniT qb16(sf::IntRect(502 + 32, 128 + 32, 32, 32)); //down
													   //SpaceShip Lobby tiles
	AniT qb17(sf::IntRect(32, 160, 32, 32));
	AniT qb18(sf::IntRect(96, 256, 96, 96));
	AniT qb19(sf::IntRect(192, 0, 32, 32));
	AniT qb20(sf::IntRect(192, 256, 64, 64));
	AniT qb21(sf::IntRect(342, 416, 128, 128));
	//Lobby Path
	AniT qb22(sf::IntRect(224, 384, 32, 32));
	AniT qb23(sf::IntRect(224 + 32, 384, 32, 32));
	AniT qb24(sf::IntRect(224 + 64, 384, 32, 32));
	AniT qb25(sf::IntRect(224, 384 + 32, 32, 32));
	AniT qb26(sf::IntRect(224 + 32, 384 + 32, 32, 32));
	AniT qb27(sf::IntRect(224 + 64, 384 + 32, 32, 32));
	AniT qb28(sf::IntRect(224, 384 + 64, 32, 32));
	AniT qb29(sf::IntRect(224 + 32, 384 + 64, 32, 32));
	AniT qb30(sf::IntRect(128, 224, 32, 32));
	AniT qb31(sf::IntRect(32, 192 + 32, 64, 32));

	std::vector<std::vector<AniT>> qv1 = { { { qb1,qb2,qb3,qb4,qb5,qb6,qb7,qb8,qb9,qb10,qb11,qb12,qb13,qb14,qb15,qb16,qb17,qb18,qb19,qb20,qb21,qb22,qb23,qb24,qb25,qb26,qb27,qb28,qb29,qb30,qb31 } } };
	All_Sprites[4][1] = qv1;//1
						   //Shop sprites~~~
	AniT qs1(sf::IntRect(32 * 3, 32, 32, 32));
	All_Sprites[4][2] = { { { qs1 } } };//2
									   //Stair sprites~~~
	AniT qst1(sf::IntRect(32, 0, 32, 32));
	AniT qst1_2(sf::IntRect(32, 32, 32, 32));
	All_Sprites[4][3] = { { { qst1,qst1_2 } } };//3
											  //AniBg sprites~~~
	AniT qba1(sf::IntRect(96, 96, 32, 32));
	AniT qba2(sf::IntRect(96, 96 + (32 * 1), 32, 32));
	AniT qba3(sf::IntRect(96, 96 + (32 * 2), 32, 32));
	AniT qba4(sf::IntRect(342, 192, 32, 32));
	AniT qba5(sf::IntRect(342 + 32, 192, 32, 32));
	//Torches
	//Top square
	AniT qba6(sf::IntRect(406, 288, 32, 32)); //top left
	AniT qba7(sf::IntRect(406 + 32, 288, 32, 32)); //top right
	AniT qba8(sf::IntRect(406 + 32, 288 + 32, 32, 32)); //bottom right
	AniT qba9(sf::IntRect(406, 288 + 32, 32, 32)); //bottom left
												  //Next square down
	AniT qba10(sf::IntRect(406, 288 + (32 * 2), 32, 32)); //top left
	AniT qba11(sf::IntRect(406 + 32, 288 + (32 * 2), 32, 32)); //top right
	AniT qba12(sf::IntRect(406 + 32, 288 + 32 + (32 * 2), 32, 32)); //bottom right
	AniT qba13(sf::IntRect(406, 288 + 32 + (32 * 2), 32, 32)); //bottom left
															  //Next square down
	AniT qba14(sf::IntRect(406, 288 + (32 * 4), 32, 32)); //top left
	AniT qba15(sf::IntRect(406 + 32, 288 + (32 * 4), 32, 32)); //top right
	AniT qba16(sf::IntRect(406 + 32, 288 + 32 + (32 * 4), 32, 32)); //bottom right
	AniT qba17(sf::IntRect(406, 288 + 32 + (32 * 4), 32, 32)); //bottom left
															  //Next square down
	AniT qba18(sf::IntRect(406, 288 + (32 * 6), 32, 32)); //top left
	AniT qba19(sf::IntRect(406 + 32, 288 + (32 * 6), 32, 32)); //top right
	AniT qba20(sf::IntRect(406 + 32, 288 + 32 + (32 * 6), 32, 32)); //bottom right
	AniT qba21(sf::IntRect(406, 288 + 32 + (32 * 6), 32, 32)); //bottom left
	std::vector<std::vector<AniT>> qv2 = { { { qba1, qba2, qba3, qba2 },{ qba4,qba5 },{ qba6,qba10,qba14,qba18 },{ qba7,qba11,qba15,qba19 },{ qba8,qba12,qba16,qba20 },{ qba9,qba13,qba17,qba21 } } };
	All_Sprites[4][4] = qv2;//4

						   //SaveStation sprites~~~
	AniT qsa1(sf::IntRect(406, 192 - 32, 32, 32));
	AniT qsa2(sf::IntRect(406, 192, 32, 32));
	AniT qsa3(sf::IntRect(406, 192 + 32, 32, 32));
	All_Sprites[4][5] = { { { qsa1,qsa2,qsa3,qsa2 } } };//5

													//Door sprites~~~
	AniT qd1(sf::IntRect(32, 32, 32, 32));
	All_Sprites[4][6] = { { { qd1 } } };//6
									   //Foreground sprites~~~
	AniT qfore1(sf::IntRect(160, 96, 64, 96));
	AniT qfore2(sf::IntRect(0, 96, 32, 32));
	AniT qfore3(sf::IntRect(32, 96, 32, 32));
	AniT qfore4(sf::IntRect(0, 128, 32, 32));
	AniT qfore5(sf::IntRect(32, 128, 32, 32));
	AniT qfore6(sf::IntRect(0, 320, 96, 96));
	AniT qfore7(sf::IntRect(160, 384, 64, 96));

	All_Sprites[4][7] = { { { qfore1, qfore2, qfore3, qfore4, qfore5, qfore6, qfore7 } } };//7
																					//Chest sprites~~~
																					//Standard
	AniT qch1(sf::IntRect(256, 64, 32, 32));//Chest closed : Standard
	AniT qch2(sf::IntRect(256, 96, 32, 32));//Chest open : Standard
										   //Advanced
	AniT qch3(sf::IntRect(192, 0, 32, 32));
	AniT qch4(sf::IntRect(192, 32, 32, 32));
	All_Sprites[4][8] = { { { qch1,qch2 },{ qch3,qch4 } } };//8
														//Corner sprites~~~
														//Purple
	AniT qcr(sf::IntRect(256, 128, 32, 32));//Top left
	AniT qcr1(sf::IntRect(288, 128, 32, 32));//Top right
	AniT qcr2(sf::IntRect(288, 160, 32, 32));//Bottom right
	AniT qcr3(sf::IntRect(256, 160, 32, 32));//Bottom left
											//Red cr
	AniT qcr4(sf::IntRect(256, 128 + 64, 32, 32));//Top left
	AniT qcr5(sf::IntRect(288, 128 + 64, 32, 32));//Top right
	AniT qcr6(sf::IntRect(288, 160 + 64, 32, 32));//Bottom right
	AniT qcr7(sf::IntRect(256, 160 + 64, 32, 32));//Bottom left
	All_Sprites[4][9] = { { { qcr,qcr1,qcr2,qcr3,qcr4,qcr5,qcr6,qcr7 } } };//9
																   //PSwitch sprites~~~

																   //Up
	AniT qps(sf::IntRect(342, 224, 32, 32));
	AniT qps1(sf::IntRect(342 + 32, 224, 32, 32));
	//Right
	AniT qps2(sf::IntRect(342 + 32, 224 + 32, 32, 32));
	AniT qps3(sf::IntRect(342 + 32, 224 + 64, 32, 32));
	//Down
	AniT qps4(sf::IntRect(342, 224 + 96, 32, 32));
	AniT qps5(sf::IntRect(342 + 32, 224 + 96, 32, 32));
	//Left
	AniT qps6(sf::IntRect(342, 224 + 32, 32, 32));
	AniT qps7(sf::IntRect(342, 224 + 64, 32, 32));
	//Up Light
	AniT qps8(sf::IntRect(342, 352, 32, 32));
	//Down Light
	AniT qps9(sf::IntRect(342 + 32, 352, 32, 32));
	//Right Light
	AniT qps10(sf::IntRect(342 + 32, 352 + 32, 32, 32));
	//Left Light
	AniT qps11(sf::IntRect(342, 352 + 32, 32, 32));
	All_Sprites[4][10] = { { { qps,qps1,qps2,qps3,qps4,qps5,qps6,qps7,qps8,qps9,qps10,qps11 } } };//10
																					  //P_Spawner_Const sprites~~~
																					  //Up
	AniT qpc(sf::IntRect(256, 256, 32, 32));
	AniT qpc1(sf::IntRect(256, 256 + 64, 32, 32));
	//Right
	AniT qpc2(sf::IntRect(256 + 32, 256, 32, 32));
	AniT qpc3(sf::IntRect(256 + 32, 256 + 64, 32, 32));
	//Down
	AniT qpc4(sf::IntRect(256 + 32, 256 + 32, 32, 32));
	AniT qpc5(sf::IntRect(256 + 32, 256 + 96, 32, 32));
	//Left
	AniT qpc6(sf::IntRect(256, 256 + 32, 32, 32));
	AniT qpc7(sf::IntRect(256, 256 + 96, 32, 32));
	All_Sprites[4][13] = { { { qpc,qpc1,qpc2,qpc3,qpc4,qpc5,qpc6,qpc7 } } };//13
																	//Seal sprites~~~
	AniT qse(sf::IntRect(342, 160, 32, 32));

	All_Sprites[4][11] = { { { qse } } };//11
										//RTile sprites-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	AniT qrt0(sf::IntRect(128, 0, 32, 32)); //tile lit red
	AniT qrt1(sf::IntRect(128, 32, 32, 32)); //tile lit pink
	AniT qrt2(sf::IntRect(128, 64, 32, 32)); //tile lit nothing
	All_Sprites[4][12] = { { { qrt0, qrt1 },{ qrt2 } } };//12
													  //PTile sprites~~~
	AniT qpt0(sf::IntRect(160, 0, 32, 32));
	AniT qpt1(sf::IntRect(160, 32, 32, 32));
	AniT qpt2(sf::IntRect(160, 64, 32, 32));
	All_Sprites[4][14] = { { { qpt0,qpt1,qpt2 } } };//14
												 //Stream sprites~~~
	AniT qstr0(sf::IntRect(128, 192, 64, 32));
	All_Sprites[4][16] = { { { qstr0 } } };
	//Rock sprites~~~
	AniT qrock0(sf::IntRect(0, 128, 32, 32));
	AniT qrock1(sf::IntRect(32, 128, 32, 32));
	AniT qrock2(sf::IntRect(0, 128 + 32, 32, 32));
	AniT qrock3(sf::IntRect(32, 128 + 32, 32, 32));
	All_Sprites[4][18] = { { { qrock0,qrock1,qrock2,qrock3 } } };
	//AniT sprites~~~
	AniT qbarrel0(sf::IntRect(0, 192, 32, 32));
	AniT qbarrel1(sf::IntRect(0, 192 + 32, 32, 32));
	AniT qbarrel2(sf::IntRect(0, 192 + 64, 32, 32));
	All_Sprites[4][19] = { {{qbarrel0,qbarrel1,qbarrel2,qbarrel1}} };
	//BounceTile sprites~~~
	AniT qbounce0(sf::IntRect(288, 0, 32, 32)); //Up
	AniT qbounce1(sf::IntRect(288, 32, 32, 32)); //Right
	AniT qbounce2(sf::IntRect(288 - 32, 32, 32, 32)); //Down
	AniT qbounce3(sf::IntRect(288 - 32, 0, 32, 32)); //Left
	All_Sprites[4][20] = { { {qbounce0,qbounce1,qbounce2,qbounce3} } };
	//EyeBall sprites~~~
	AniT qeye0(sf::IntRect(502, 352, 32, 32)); //Down open
	AniT qeye1(sf::IntRect(502 + 32, 352, 32, 32)); //right open
	AniT qeye2(sf::IntRect(502 + 32, 352 + 32, 32, 32)); //up open
	AniT qeye3(sf::IntRect(502, 352 + 32, 32, 32)); //left open
	AniT qeye0_1(sf::IntRect(502, 352 + 64, 32, 32)); //Down open
	AniT qeye1_1(sf::IntRect(502 + 32, 352 + 64, 32, 32)); //right open
	AniT qeye2_1(sf::IntRect(502 + 32, 352 + 32 + 64, 32, 32)); //up open
	AniT qeye3_1(sf::IntRect(502, 352 + 32 + 64, 32, 32)); //left open
	All_Sprites[4][21] = { {{qeye2,qeye1,qeye0,qeye3}, {qeye2_1,qeye1_1,qeye0_1,qeye3_1}} };
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Lobby 3 Sprites-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	for (unsigned int i = 0; i < 200; i++) {
		All_Sprites[5].push_back({});
	}
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Lobby Sprites-=-=-=-=-=-=-=-=-=-=-
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	AniT pw1(sf::IntRect(160, 224, 32, 32));
	AniT pw2(sf::IntRect(192, 224, 32, 32));
	AniT pw3(sf::IntRect(160, 288, 32, 32));
	AniT pw4(sf::IntRect(192, 288, 32, 32));
	AniT pw5(sf::IntRect(0, 0, 32, 32));
	AniT pw6(sf::IntRect(288, 96, 32, 32));
	AniT pw7(sf::IntRect(0, 0, 32, 32));
	AniT pw8(sf::IntRect(0, 0, 32, 32));
	AniT pw9(sf::IntRect(0, 0, 32, 32));
	AniT pw10(sf::IntRect(0, 0, 32, 32));
	AniT pw11(sf::IntRect(0, 0, 32, 32));
	AniT pw12(sf::IntRect(0, 0, 32, 32));
	AniT pw13(sf::IntRect(0, 0, 32, 32));
	AniT pw14(sf::IntRect(0, 0, 32, 32));
	AniT pw15(sf::IntRect(0, 0, 32, 32));
	AniT pw16(sf::IntRect(0, 0, 32, 32));
	AniT pw17(sf::IntRect(256, 192, 32, 32));
	AniT pw18(sf::IntRect(320, 96, 32, 32));
	AniT pw19(sf::IntRect(416, 0, 32, 32));
	AniT pw20(sf::IntRect(416 + 32, 0, 32, 32));
	AniT pw21(sf::IntRect(416, 32, 32, 32));
	AniT pw22(sf::IntRect(416 + 32, 32, 32, 32));
	AniT pw23(sf::IntRect(352, 0, 32, 32));
	AniT pw24(sf::IntRect(352 + 32, 0, 32, 32));
	AniT pw25(sf::IntRect(352, 32, 32, 32));
	AniT pw26(sf::IntRect(352 + 32, 32, 32, 32));
	AniT pw27(sf::IntRect(480, 0, 32, 32));
	std::vector<std::vector<AniT>> pv = { { { pw1,pw2,pw3,pw4,pw5,pw6,pw7,pw8,pw9,pw10,pw11,pw12,pw13,pw14,pw15,pw16,pw17,pw18,pw19,pw20,pw21,pw22,pw23,pw24,pw25,pw26,pw27 } } };
	All_Sprites[5][0] = pv;//0
						   //Background sprites~~~
	AniT pb1(sf::IntRect(288, 128, 32, 32)); //Purple flower
	AniT pb2(sf::IntRect(288, 128 + 32, 32, 32)); //Blue flower
	AniT pb3(sf::IntRect(448, 64, 128, 128)); //Ferris wheel
	AniT pb4(sf::IntRect(256, 384, 64, 32)); //Dumped radioactive waste barrel
	AniT pb5(sf::IntRect(480, 576, 96, 64)); //Dungeon two entrance
	AniT pb6(sf::IntRect(256, 320, 32, 64));
	AniT pb7(sf::IntRect(224 + 32, 128, 32, 32));
	AniT pb8(sf::IntRect(224 + 32, 128 + 32, 32, 32));
	AniT pb9(sf::IntRect(224, 128, 32, 32));
	AniT pb10(sf::IntRect(224, 128 + 32, 32, 32));
	AniT pb11(sf::IntRect(374, 128, 32, 64));
	AniT pb12(sf::IntRect(438, 224, 32, 64));
	AniT pb13(sf::IntRect(502, 128, 32, 32)); //left
	AniT pb14(sf::IntRect(320, 416, 256, 128)); //right
	AniT pb15(sf::IntRect(502, 128 + 32, 32, 32)); //up
	AniT pb16(sf::IntRect(502 + 32, 128 + 32, 32, 32)); //down
	AniT pb17(sf::IntRect(64, 96, 32, 32));
	AniT pb18(sf::IntRect(160, 0, 96, 96));
	AniT pb19(sf::IntRect(96, 96, 32, 32));
	AniT pb20(sf::IntRect(96, 96, 64, 64));
	AniT pb21(sf::IntRect(96, 96, 128, 128));
	AniT pb22(sf::IntRect(64, 0, 32, 32));
	AniT pb23(sf::IntRect(64 + 32, 0, 32, 32));
	AniT pb24(sf::IntRect(64 + 64, 0, 32, 32));
	AniT pb25(sf::IntRect(64, 32, 32, 32));
	AniT pb26(sf::IntRect(64 + 32, 32, 32, 32));
	AniT pb27(sf::IntRect(64 + 64, 32, 32, 32));
	AniT pb28(sf::IntRect(64, 64, 32, 32));
	AniT pb29(sf::IntRect(64 + 32, 64, 32, 32));
	AniT pb30(sf::IntRect(64 + 64, 64, 32, 32));


	std::vector<std::vector<AniT>> pv1 = { { { pb1,pb2,pb3,pb4,pb5,pb6,pb7,pb8,pb9,pb10,pb11,pb12,pb13,pb14,pb15,pb16,pb17,pb18,pb19,pb20,pb21,pb22,pb23,pb24,pb25,pb26,pb27,pb28,pb29,pb30 } } };
	All_Sprites[5][1] = pv1;//1

							//Foreground sprites~~~
	AniT pfore1(sf::IntRect(320, 416, 256, 128));
	AniT pfore2(sf::IntRect(512, 0, 32, 32));
	AniT pfore3(sf::IntRect(512 + 32, 0, 32, 32));
	AniT pfore4(sf::IntRect(512, 32, 32, 32));
	AniT pfore5(sf::IntRect(512 + 32, 32, 32, 32));
	AniT pfore6(sf::IntRect(256, 0, 96, 96));
	AniT pfore7(sf::IntRect(0, 0, 64, 96));
	AniT pfore8(sf::IntRect(320, 416, 256, 32));
	AniT pfore9(sf::IntRect(320, 416 + 32, 256, 32));
	AniT pfore10(sf::IntRect(320, 416, 32, 128));
	AniT pfore11(sf::IntRect(320 + 32, 416, 32, 128));
	AniT pfore12(sf::IntRect(320, 288, 256, 64));
	AniT pfore13(sf::IntRect(320, 288 + 64, 256, 64));
	AniT pfore14(sf::IntRect(192, 416, 64, 128));
	AniT pfore15(sf::IntRect(192 + 64, 416, 64, 128));

	//water banks
	AniT pfore16(sf::IntRect(64, 224, 32, 32));
	AniT pfore17(sf::IntRect(96, 224, 32, 32));
	AniT pfore18(sf::IntRect(128, 224, 32, 32));
	AniT pfore19(sf::IntRect(128, 224 + 32, 32, 32));
	AniT pfore20(sf::IntRect(128, 224 + 64, 32, 32));
	AniT pfore21(sf::IntRect(96, 224 + 64, 32, 32));
	AniT pfore22(sf::IntRect(64, 224 + 64, 32, 32));
	AniT pfore23(sf::IntRect(64, 224 + 32, 32, 32));
	//Big red mushroom
	AniT pfore24(sf::IntRect(192, 320, 64, 96));
	//Big blue/purple mushroom
	AniT pfore25(sf::IntRect(96, 320, 96, 96));
	All_Sprites[5][7] = { { { pfore1, pfore2, pfore3, pfore4, pfore5, pfore6, pfore7, pfore8, pfore9, pfore10, pfore11,pfore12,pfore13,pfore14,pfore15,
		pfore16,pfore17,pfore18,pfore19,pfore20,pfore21,pfore22,pfore23,pfore24,pfore25 } } };//7

																							  //AniBg sprites~~~
	AniT pba1(sf::IntRect(96, 96, 32, 32));
	AniT pba2(sf::IntRect(96, 96 + (32 * 1), 32, 32));
	AniT pba3(sf::IntRect(96, 96 + (32 * 2), 32, 32));
	AniT pba4(sf::IntRect(224, 96, 32, 32));
	AniT pba5(sf::IntRect(224 + 32, 96, 32, 32));
	//Water
	AniT pba6(sf::IntRect(288, 192, 32, 32));
	AniT pba7(sf::IntRect(288, 192 + 32, 32, 32));
	AniT pba8(sf::IntRect(288, 192 + 64, 32, 32));
	//Dungeon one
	AniT pba9(sf::IntRect(352, 192 - 128, 96, 64));
	AniT pba10(sf::IntRect(352, 192 - 64, 96, 64));
	AniT pba11(sf::IntRect(352, 192, 96, 64));


	All_Sprites[5][4] = { { { pba1, pba2, pba3, pba2 },{ pba4,pba5 },{ pba6,pba7,pba8 },{ pba9,pba10,pba11,pba10,pba9,pba11,pba9,pba10,pba11 } } };
	
	//SaveStation sprites~~~
	AniT psa1(sf::IntRect(64, 128, 32, 32));
	AniT psa2(sf::IntRect(64, 128 + 32, 32, 32));
	AniT psa3(sf::IntRect(64, 128 + 64, 32, 32));
	All_Sprites[5][5] = { { { psa1,psa2,psa3,psa2 } } };//5
	
	
	
	//Chest sprites~~~

	//Stream sprites~~~
	AniT pstr0(sf::IntRect(160, 256, 64, 32));
	All_Sprites[5][16] = { { { pstr0 } } };
	//TripleChest sprites~~~
	AniT pch1(sf::IntRect(256, 224, 32, 32)); //Tool box closed
	AniT pch2(sf::IntRect(256, 224 + 32, 32, 32)); //Tool box open
	AniT pch3(sf::IntRect(256, 224 + 64, 32, 32)); //Tool box empty
	All_Sprites[5][17] = { { { pch1,pch2,pch3 } } };

	//Sign sprites~~~
	//Mr. Sign
	AniT psign12(sf::IntRect(320, 96, 32, 32));
	AniT psign13(sf::IntRect(320, 96 + 32, 32, 32));
	AniT psign14(sf::IntRect(320, 96 + 64, 32, 32));
	All_Sprites[5][15] = { { psign12,psign13,psign14 } };
	//AniWall sprites~~~
	//Radioactive waste barrel
	AniT pradio1(sf::IntRect(224, 224, 32, 32));
	AniT pradio2(sf::IntRect(224, 224 + 32, 32, 32));
	AniT pradio3(sf::IntRect(224, 224 + 64, 32, 32));
	//Rock with grass swaying
	AniT prock1(sf::IntRect(288, 288, 32, 32));
	AniT prock2(sf::IntRect(288, 288 + 32, 32, 32));
	AniT prock3(sf::IntRect(288, 288 + 64, 32, 32));
	All_Sprites[5][19] = { { pradio1,pradio2,pradio3,pradio2 },{ prock1,prock2,prock3,prock2 } };

	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Dungeon 3 Sprites-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	for (unsigned int i = 0; i < 25; i++) {
		All_Sprites[6].push_back({});
	}
	//Wall sprites~~~
	AniT vw1(sf::IntRect(32 * 3, 0, 32, 32));
	AniT vw2(sf::IntRect(32 * 2, 32, 32, 32));
	AniT vw3(sf::IntRect(32 * 3, 32 * 2, 32, 32));
	//Dungeon tile
	AniT vw4(sf::IntRect(224, 64, 32, 32));
	//Dungeon tile
	AniT vw5(sf::IntRect(224, 96, 32, 32));
	//Lobby tiles
	AniT vw6(sf::IntRect(406 + (32 * 0), 96 + (32 * 0), 32, 32)); //Static boulder
	AniT vw7(sf::IntRect(406 + (32 * 0), 96 + (32 * 1), 32, 32));
	AniT vw8(sf::IntRect(406 + (32 * 1), 96 + (32 * 1), 32, 32));
	AniT vw9(sf::IntRect(406 + (32 * 2), 96 + (32 * 1), 32, 32));
	AniT vw10(sf::IntRect(406 + (32 * 1), 96 + (32 * 2), 32, 32));
	AniT vw11(sf::IntRect(406 + (32 * 2), 96 + (32 * 2), 32, 32));
	////Chemistry table tile
	AniT vw12(sf::IntRect(438, 192, 64, 32));
	//Concrete tile
	AniT vw13(sf::IntRect(470, 224, 32, 32));
	AniT vw14(sf::IntRect(470 + 32, 224, 32, 32));
	AniT vw15(sf::IntRect(470 + 32, 224 + 32, 32, 32));
	AniT vw16(sf::IntRect(470, 224 + 32, 32, 32));
	AniT vw17(sf::IntRect(470 + 64, 224, 32, 32));
	AniT vw18(sf::IntRect(470 + 64, 224 + 32, 32, 32));
	//SpaceShip Lobby tiles.
	AniT vw19(sf::IntRect(470, 288, 32, 32));
	AniT vw20(sf::IntRect(470 + 32, 288, 32, 32));
	AniT vw21(sf::IntRect(470 + 64, 288, 32, 32));
	AniT vw22(sf::IntRect(470 + 32, 288 + 32, 32, 32));
	AniT vw23(sf::IntRect(470 + 64, 288 + 32, 32, 32));
	AniT vw24(sf::IntRect(64, 192, 32, 32)); //yellow radioactive barrel
	AniT vw25(sf::IntRect(32, 192, 32, 32)); //red radioactive barrel
	AniT vw26(sf::IntRect(374, 128, 32, 32));
	AniT vw27(sf::IntRect(0, 192, 32, 32));
	//Cap block
	AniT vw28(sf::IntRect(192, 224, 32, 32));
	//Metal tiles
	//Corners
	AniT vw29(sf::IntRect(342, 512, 32, 32));
	AniT vw30(sf::IntRect(342 + 32, 512, 32, 32));
	AniT vw31(sf::IntRect(342 + 32, 512 + 32, 32, 32));
	AniT vw32(sf::IntRect(342, 512 + 32, 32, 32));
	//End points
	AniT vw33(sf::IntRect(342, 512 + 64, 32, 32));
	AniT vw34(sf::IntRect(342 + 32, 512 + 64, 32, 32));
	AniT vw35(sf::IntRect(342 + 32, 512 + 32 + 64, 32, 32));
	AniT vw36(sf::IntRect(342, 512 + 32 + 64, 32, 32));
	//Sides and misc
	AniT vw37(sf::IntRect(342, 512 + 64 + 64, 32, 32));
	AniT vw38(sf::IntRect(342 + 32, 512 + 64 + 64, 32, 32));
	AniT vw39(sf::IntRect(342 + 32, 512 + 32 + 64 + 64, 32, 32));
	AniT vw40(sf::IntRect(342, 512 + 32 + 64 + 64, 32, 32));
	
	std::vector<std::vector<AniT>> vv = { { { vw1,vw2,vw3,vw4,vw5,vw6,vw7,vw8,vw9,vw10,vw11,vw12,vw13,vw14,vw15,vw16,vw17,vw18,vw19,vw20,vw21,vw22,vw23,vw24,vw25,vw26,vw27,vw28
		,vw29,vw30,vw31,vw32,vw33,vw34,vw35,vw36,vw37,vw38,vw39,vw40} } };
	All_Sprites[6][0] = vv;//0
						   //Background sprites~~~
						   //Dungeon ground tile
	AniT vb1(sf::IntRect(64, 0, 32, 32));
	//Normal grass tile
	AniT vb2(sf::IntRect(224, 0, 32, 32));
	//Flower grass tile
	AniT vb3(sf::IntRect(224, 32, 32, 32));
	//Brown Floor Dungeon tile
	AniT vb4(sf::IntRect(406, 0, 32, 32));
	//Purplesponge Floor Dungeon tile
	AniT vb5(sf::IntRect(406, 32, 32, 32));
	//Red lobby carpet tile
	AniT vb6(sf::IntRect(406, 64, 32, 32));
	//Purple mushroom tile
	AniT vb7(sf::IntRect(374, 64, 32, 32));
	//Red mushroom tile
	AniT vb8(sf::IntRect(374, 96, 32, 32));
	//Rubble tile
	AniT vb9(sf::IntRect(342, 64, 32, 32));
	//Dungeon grass sticking out of floor tile
	AniT vb10(sf::IntRect(342, 96, 32, 32));
	//Ladder up tile
	AniT vb11(sf::IntRect(374, 128, 32, 32));
	//Potted flower tile
	AniT vb12(sf::IntRect(438, 224, 32, 64));
	//Wall Lamps
	AniT vb13(sf::IntRect(502, 128, 32, 32)); //left
	AniT vb14(sf::IntRect(502 + 32, 128, 32, 32)); //right
	AniT vb15(sf::IntRect(502, 128 + 32, 32, 32)); //up
	AniT vb16(sf::IntRect(502 + 32, 128 + 32, 32, 32)); //down
														//SpaceShip Lobby tiles
	AniT vb17(sf::IntRect(32, 160, 32, 32));
	AniT vb18(sf::IntRect(96, 256, 96, 96));
	AniT vb19(sf::IntRect(192, 0, 32, 32));
	AniT vb20(sf::IntRect(192, 256, 64, 64));
	AniT vb21(sf::IntRect(342, 416, 128, 128));
	//Lobby Path
	AniT vb22(sf::IntRect(224, 384, 32, 32));
	AniT vb23(sf::IntRect(224 + 32, 384, 32, 32));
	AniT vb24(sf::IntRect(224 + 64, 384, 32, 32));
	AniT vb25(sf::IntRect(224, 384 + 32, 32, 32));
	AniT vb26(sf::IntRect(224 + 32, 384 + 32, 32, 32));
	AniT vb27(sf::IntRect(224 + 64, 384 + 32, 32, 32));
	AniT vb28(sf::IntRect(224, 384 + 64, 32, 32));
	AniT vb29(sf::IntRect(224 + 32, 384 + 64, 32, 32));
	AniT vb30(sf::IntRect(128, 224, 32, 32));
	AniT vb31(sf::IntRect(32, 192 + 32, 64, 32));
	//Floor Corner pieces
	AniT vb32(sf::IntRect(288,64,32,32));
	AniT vb33(sf::IntRect(288 + 32, 64, 32, 32));
	AniT vb34(sf::IntRect(288, 64 + 32, 32, 32));
	AniT vb35(sf::IntRect(288 + 32, 64 + 32, 32, 32));

	std::vector<std::vector<AniT>> vv1 = { { { vb1,vb2,vb3,vb4,vb5,vb6,vb7,vb8,vb9,vb10,vb11,vb12,vb13,vb14,vb15,vb16,vb17,vb18,vb19,vb20,vb21,vb22,vb23,vb24,vb25,vb26,vb27,vb28,vb29,vb30,vb31,vb32,vb33,vb34,vb35 } } };
	All_Sprites[6][1] = vv1;//1
							//Shop sprites~~~
	AniT vs1(sf::IntRect(32 * 3, 32, 32, 32));
	All_Sprites[6][2] = { { { qs1 } } };//2
										//Stair sprites~~~
	AniT vst1(sf::IntRect(32, 0, 32, 32));
	AniT vst1_2(sf::IntRect(32, 32, 32, 32));
	All_Sprites[6][3] = { { { vst1,vst1_2 } } };//3
												//AniBg sprites~~~
	AniT vba1(sf::IntRect(96, 96, 32, 32));
	AniT vba2(sf::IntRect(96, 96 + (32 * 1), 32, 32));
	AniT vba3(sf::IntRect(96, 96 + (32 * 2), 32, 32));
	AniT vba4(sf::IntRect(342, 192, 32, 32));
	AniT vba5(sf::IntRect(342 + 32, 192, 32, 32));
	
	
	//Torches
	//Top square
	AniT vba6(sf::IntRect(406, 288, 32, 32)); //top left
	AniT vba7(sf::IntRect(406 + 32, 288, 32, 32)); //top right
	AniT vba8(sf::IntRect(406 + 32, 288 + 32, 32, 32)); //bottom right
	AniT vba9(sf::IntRect(406, 288 + 32, 32, 32)); //bottom left
												   //Next square down
	AniT vba10(sf::IntRect(406, 288 + (32 * 2), 32, 32)); //top left
	AniT vba11(sf::IntRect(406 + 32, 288 + (32 * 2), 32, 32)); //top right
	AniT vba12(sf::IntRect(406 + 32, 288 + 32 + (32 * 2), 32, 32)); //bottom right
	AniT vba13(sf::IntRect(406, 288 + 32 + (32 * 2), 32, 32)); //bottom left
															   //Next square down
	AniT vba14(sf::IntRect(406, 288 + (32 * 4), 32, 32)); //top left
	AniT vba15(sf::IntRect(406 + 32, 288 + (32 * 4), 32, 32)); //top right
	AniT vba16(sf::IntRect(406 + 32, 288 + 32 + (32 * 4), 32, 32)); //bottom right
	AniT vba17(sf::IntRect(406, 288 + 32 + (32 * 4), 32, 32)); //bottom left
															   //Next square down
	AniT vba18(sf::IntRect(406, 288 + (32 * 6), 32, 32)); //top left
	AniT vba19(sf::IntRect(406 + 32, 288 + (32 * 6), 32, 32)); //top right
	AniT vba20(sf::IntRect(406 + 32, 288 + 32 + (32 * 6), 32, 32)); //bottom right
	AniT vba21(sf::IntRect(406, 288 + 32 + (32 * 6), 32, 32)); //bottom left
	//Small Snow Animation
	AniT vba22(sf::IntRect(470, 320 + (32 * 1), 32, 32)); //Snow animation
	AniT vba23(sf::IntRect(470, 320 + (32 * 2), 32, 32)); //Snow animation
	AniT vba24(sf::IntRect(470, 320 + (32 * 3), 32, 32)); //Snow animation
	AniT vba25(sf::IntRect(470, 320 + (32 * 4), 32, 32)); //Snow animation
	AniT vba26(sf::IntRect(470, 320 + (32 * 5), 32, 32)); //Snow animation
	AniT vba27(sf::IntRect(470, 320 + (32 * 6), 32, 32)); //Snow animation
	AniT vba28(sf::IntRect(470, 320 + (32 * 7), 32, 32)); //Snow animation
	//Big Snow Animation
	AniT vba29(sf::IntRect(448, 864, 128, 128)); //Snow animation
	AniT vba30(sf::IntRect(448 - (128 * 1), 864, 128, 128)); //Snow animation
	AniT vba31(sf::IntRect(448 - (128 * 2), 864, 128, 128)); //Snow animation
	AniT vba32(sf::IntRect(448 - (128 * 3), 864, 128, 128)); //Snow animation
	AniT vba33(sf::IntRect(448 - (128 * 0), 864 + 128, 128, 128)); //Snow animation
	AniT vba34(sf::IntRect(448 - (128 * 1), 864 + 128, 128, 128)); //Snow animation
	AniT vba35(sf::IntRect(448 - (128 * 2), 864 + 128, 128, 128)); //Snow animation
	AniT vba36(sf::IntRect(448 - (128 * 3), 864 + 128, 128, 128)); //Snow animation
	std::vector<std::vector<AniT>> vv2 = { { { vba1, vba2, vba3, vba2 },{ vba4,vba5 },{ vba6,vba10,vba14,vba18 },{ vba7,vba11,vba15,vba19 },{ vba8,vba12,vba16,vba20 },{ vba9,vba13,vba17,vba21 },
	{vba22,vba23,vba24,vba25,vba26,vba27,vba28}, {vba29,vba30,vba31,vba32,vba33,vba34,vba35}} };
	All_Sprites[6][4] = vv2;//4

							//SaveStation sprites~~~
	AniT vsa1(sf::IntRect(406, 192 - 32, 32, 32));
	AniT vsa2(sf::IntRect(406, 192, 32, 32));
	AniT vsa3(sf::IntRect(406, 192 + 32, 32, 32));
	All_Sprites[6][5] = { { { vsa1,vsa2,vsa3,vsa2 } } };//5

														//Door sprites~~~
	AniT vd1(sf::IntRect(32, 32, 32, 32));
	All_Sprites[6][6] = { { { vd1 } } };//6
										//Foreground sprites~~~
	AniT vfore1(sf::IntRect(160, 96, 64, 96));
	AniT vfore2(sf::IntRect(0, 96, 32, 32));
	AniT vfore3(sf::IntRect(32, 96, 32, 32));
	AniT vfore4(sf::IntRect(0, 128, 32, 32));
	AniT vfore5(sf::IntRect(32, 128, 32, 32));
	AniT vfore6(sf::IntRect(0, 320, 96, 96));
	AniT vfore7(sf::IntRect(160, 384, 64, 96));
	AniT vfore8(sf::IntRect(128, 256, 32, 32));
	AniT vfore9(sf::IntRect(128 + 32, 256, 32, 32));
	All_Sprites[6][7] = { { { vfore1, vfore2, vfore3, vfore4, vfore5, vfore6, vfore7, vfore8, vfore9 } } };//7
																						   //Chest sprites~~~
																						   //Standard
	AniT vch1(sf::IntRect(256, 64, 32, 32));//Chest closed : Standard
	AniT vch2(sf::IntRect(256, 96, 32, 32));//Chest open : Standard
											//Advanced
	AniT vch3(sf::IntRect(192, 0, 32, 32));
	AniT vch4(sf::IntRect(192, 32, 32, 32));
	All_Sprites[6][8] = { { { vch1,vch2 },{ vch3,vch4 } } };//8
															//Corner sprites~~~
															//Purple
	AniT vcr(sf::IntRect(256, 128, 32, 32));//Top left
	AniT vcr1(sf::IntRect(288, 128, 32, 32));//Top right
	AniT vcr2(sf::IntRect(288, 160, 32, 32));//Bottom right
	AniT vcr3(sf::IntRect(256, 160, 32, 32));//Bottom left
											 //Red cr
	AniT vcr4(sf::IntRect(256, 128 + 64, 32, 32));//Top left
	AniT vcr5(sf::IntRect(288, 128 + 64, 32, 32));//Top right
	AniT vcr6(sf::IntRect(288, 160 + 64, 32, 32));//Bottom right
	AniT vcr7(sf::IntRect(256, 160 + 64, 32, 32));//Bottom left
	All_Sprites[6][9] = { { { vcr,vcr1,vcr2,vcr3,vcr4,vcr5,vcr6,vcr7 } } };//9
																		   //PSwitch sprites~~~

																		   //Up
	AniT vps(sf::IntRect(342, 224, 32, 32));
	AniT vps1(sf::IntRect(342 + 32, 224, 32, 32));
	//Right
	AniT vps2(sf::IntRect(342 + 32, 224 + 32, 32, 32));
	AniT vps3(sf::IntRect(342 + 32, 224 + 64, 32, 32));
	//Down
	AniT vps4(sf::IntRect(342, 224 + 96, 32, 32));
	AniT vps5(sf::IntRect(342 + 32, 224 + 96, 32, 32));
	//Left
	AniT vps6(sf::IntRect(342, 224 + 32, 32, 32));
	AniT vps7(sf::IntRect(342, 224 + 64, 32, 32));
	//Up Light
	AniT vps8(sf::IntRect(342, 352, 32, 32));
	//Down Light
	AniT vps9(sf::IntRect(342 + 32, 352, 32, 32));
	//Right Light
	AniT vps10(sf::IntRect(342 + 32, 352 + 32, 32, 32));
	//Left Light
	AniT vps11(sf::IntRect(342, 352 + 32, 32, 32));
	All_Sprites[6][10] = { { { vps,vps1,vps2,vps3,vps4,vps5,vps6,vps7,vps8,vps9,vps10,vps11 } } };//10
																								  //P_Spawner_Const sprites~~~
																								  //Up
	AniT vpc(sf::IntRect(256, 256, 32, 32));
	AniT vpc1(sf::IntRect(256, 256 + 64, 32, 32));
	//Right
	AniT vpc2(sf::IntRect(256 + 32, 256, 32, 32));
	AniT vpc3(sf::IntRect(256 + 32, 256 + 64, 32, 32));
	//Down
	AniT vpc4(sf::IntRect(256 + 32, 256 + 32, 32, 32));
	AniT vpc5(sf::IntRect(256 + 32, 256 + 96, 32, 32));
	//Left
	AniT vpc6(sf::IntRect(256, 256 + 32, 32, 32));
	AniT vpc7(sf::IntRect(256, 256 + 96, 32, 32));
	All_Sprites[6][13] = { { { vpc,vpc1,vpc2,vpc3,vpc4,vpc5,vpc6,vpc7 } } };//13
																			//Seal sprites~~~
	AniT vse(sf::IntRect(342, 160, 32, 32));

	All_Sprites[6][11] = { { { vse } } };//11
										 //RTile sprites-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	AniT vrt0(sf::IntRect(128, 0, 32, 32)); //tile lit red
	AniT vrt1(sf::IntRect(128, 32, 32, 32)); //tile lit pink
	AniT vrt2(sf::IntRect(128, 64, 32, 32)); //tile lit nothing
	All_Sprites[6][12] = { { { vrt0, vrt1 },{ vrt2 } } };//12
														 //PTile sprites~~~
	AniT vpt0(sf::IntRect(160, 0, 32, 32));
	AniT vpt1(sf::IntRect(160, 32, 32, 32));
	AniT vpt2(sf::IntRect(160, 64, 32, 32));
	All_Sprites[6][14] = { { { vpt0,vpt1,vpt2 } } };//14
													
	//Sign sprites~~~
	//Mr. Sign
	AniT vsign12(sf::IntRect(374, 0, 32, 32));
	AniT vsign13(sf::IntRect(374, 32, 32, 32));
	AniT vsign14(sf::IntRect(374, 64, 32, 32));
	All_Sprites[6][15] = { { vsign12,vsign13,vsign14 } };
	//Stream sprites~~~
	AniT vstr0(sf::IntRect(128, 192, 64, 32));
	All_Sprites[6][16] = { { { vstr0 } } };
	//Rock sprites~~~
	AniT vrock0(sf::IntRect(0, 128, 32, 32));
	AniT vrock1(sf::IntRect(32, 128, 32, 32));
	AniT vrock2(sf::IntRect(0, 128 + 32, 32, 32));
	AniT vrock3(sf::IntRect(32, 128 + 32, 32, 32));
	All_Sprites[6][18] = { { { vrock0,vrock1,vrock2,vrock3 } } };
	//AniT sprites~~~
	AniT vbarrel0(sf::IntRect(0, 192, 32, 32));
	AniT vbarrel1(sf::IntRect(0, 192 + 32, 32, 32));
	AniT vbarrel2(sf::IntRect(0, 192 + 64, 32, 32));
	All_Sprites[6][19] = { { { vbarrel0,vbarrel1,vbarrel2,vbarrel1 } } };
	//BounceTile sprites~~~
	AniT vbounce0(sf::IntRect(288, 0, 32, 32)); //Up
	AniT vbounce1(sf::IntRect(288, 32, 32, 32)); //Right
	AniT vbounce2(sf::IntRect(288 - 32, 32, 32, 32)); //Down
	AniT vbounce3(sf::IntRect(288 - 32, 0, 32, 32)); //Left
	All_Sprites[6][20] = { { { vbounce0,vbounce1,vbounce2,vbounce3 } } };
	//EyeBall sprites~~~
	AniT veye0(sf::IntRect(502, 352, 32, 32)); //Down open
	AniT veye1(sf::IntRect(502 + 32, 352, 32, 32)); //right open
	AniT veye2(sf::IntRect(502 + 32, 352 + 32, 32, 32)); //up open
	AniT veye3(sf::IntRect(502, 352 + 32, 32, 32)); //left open
	AniT veye0_1(sf::IntRect(502, 352 + 64, 32, 32)); //Down open
	AniT veye1_1(sf::IntRect(502 + 32, 352 + 64, 32, 32)); //right open
	AniT veye2_1(sf::IntRect(502 + 32, 352 + 32 + 64, 32, 32)); //up open
	AniT veye3_1(sf::IntRect(502, 352 + 32 + 64, 32, 32)); //left open
	All_Sprites[6][21] = { { { veye2,veye1,veye0,veye3 },{ veye2_1,veye1_1,veye0_1,veye3_1 } } };
	//FlameThrower sprites~~~
	AniT vfmth(sf::IntRect(224, 544, 32, 32)); //Up
	AniT vfmth1(sf::IntRect(224 + 32, 544, 32, 32)); //Right
	AniT vfmth2(sf::IntRect(224 + 32, 544 + 32, 32, 32)); //Down
	AniT vfmth3(sf::IntRect(224, 544 + 32, 32, 32)); //Left
	All_Sprites[6][22] = { { { vfmth1,vfmth2,vfmth3,vfmth } } };
	//NPC_Spawner sprites~~~
	AniT vNPC_s(sf::IntRect(0, 800, 32, 32));
	AniT vNPC_s1(sf::IntRect(32, 800, 32, 32));
	AniT vNPC_s2(sf::IntRect(0, 800 + 32, 32, 32));
	AniT vNPC_s3(sf::IntRect(32, 800 + 32, 32, 32));
	AniT vNPC_s4(sf::IntRect(32, 608, 32, 32));
	All_Sprites[6][23] = { {{vNPC_s,vNPC_s1,vNPC_s2,vNPC_s3}, {vNPC_s4}} };

	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Lobby 4 Sprites-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	for (unsigned int i = 0; i < 200; i++) {
		All_Sprites[7].push_back({});
	}
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Lobby Sprites-=-=-=-=-=-=-=-=-=-=-
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	AniT jw1(sf::IntRect(160, 224, 32, 32));
	AniT jw2(sf::IntRect(192, 224, 32, 32));
	AniT jw3(sf::IntRect(160, 288, 32, 32));
	AniT jw4(sf::IntRect(192, 288, 32, 32));
	AniT jw5(sf::IntRect(0, 0, 32, 32));
	AniT jw6(sf::IntRect(288, 96, 32, 32));
	AniT jw7(sf::IntRect(256, 288, 32, 32));
	AniT jw8(sf::IntRect(0, 0, 32, 32));
	AniT jw9(sf::IntRect(0, 0, 32, 32));
	AniT jw10(sf::IntRect(0, 0, 32, 32));
	AniT jw11(sf::IntRect(0, 0, 32, 32));
	AniT jw12(sf::IntRect(0, 0, 32, 32));
	AniT jw13(sf::IntRect(0, 0, 32, 32));
	AniT jw14(sf::IntRect(0, 0, 32, 32));
	AniT jw15(sf::IntRect(0, 0, 32, 32));
	AniT jw16(sf::IntRect(0, 0, 32, 32));
	AniT jw17(sf::IntRect(256, 192, 32, 32));
	AniT jw18(sf::IntRect(320, 96, 32, 32));
	AniT jw19(sf::IntRect(416, 0, 32, 32));
	AniT jw20(sf::IntRect(416 + 32, 0, 32, 32));
	AniT jw21(sf::IntRect(416, 32, 32, 32));
	AniT jw22(sf::IntRect(416 + 32, 32, 32, 32));
	AniT jw23(sf::IntRect(352, 0, 32, 32));
	AniT jw24(sf::IntRect(352 + 32, 0, 32, 32));
	AniT jw25(sf::IntRect(352, 32, 32, 32));
	AniT jw26(sf::IntRect(352 + 32, 32, 32, 32));
	AniT jw27(sf::IntRect(480, 0, 32, 32));
	std::vector<std::vector<AniT>> jv = { { { jw1,jw2,jw3,jw4,jw5,jw6,jw7,jw8,jw9,jw10,jw11,jw12,jw13,jw14,jw15,jw16,jw17,jw18,jw19,jw20,jw21,jw22,jw23,jw24,jw25,jw26,jw27 } } };
	All_Sprites[7][0] = jv;//0
						   //Background sprites~~~
	AniT jb1(sf::IntRect(288, 128, 32, 32)); //Purple flower
	AniT jb2(sf::IntRect(288, 128 + 32, 32, 32)); //Blue flower
	AniT jb3(sf::IntRect(448, 64, 128, 128)); //Ferris wheel
	AniT jb4(sf::IntRect(256, 384, 64, 32)); //Dumped radioactive waste barrel
	AniT jb5(sf::IntRect(480, 576, 96, 64)); //Dungeon two entrance
	AniT jb6(sf::IntRect(256, 320, 32, 64));
	AniT jb7(sf::IntRect(224 + 32, 128, 32, 32));
	AniT jb8(sf::IntRect(224 + 32, 128 + 32, 32, 32));
	AniT jb9(sf::IntRect(224, 128, 32, 32));
	AniT jb10(sf::IntRect(224, 128 + 32, 32, 32));
	AniT jb11(sf::IntRect(374, 128, 32, 64));
	AniT jb12(sf::IntRect(438, 224, 32, 64));
	AniT jb13(sf::IntRect(502, 128, 32, 32)); //left
	AniT jb14(sf::IntRect(320, 416, 256, 128)); //right
	AniT jb15(sf::IntRect(502, 128 + 32, 32, 32)); //up
	AniT jb16(sf::IntRect(502 + 32, 128 + 32, 32, 32)); //down
	AniT jb17(sf::IntRect(64, 96, 32, 32));
	AniT jb18(sf::IntRect(160, 0, 96, 96));
	AniT jb19(sf::IntRect(96, 96, 32, 32));
	AniT jb20(sf::IntRect(96, 96, 64, 64));
	AniT jb21(sf::IntRect(96, 96, 128, 128));
	AniT jb22(sf::IntRect(64, 0, 32, 32));
	AniT jb23(sf::IntRect(64 + 32, 0, 32, 32));
	AniT jb24(sf::IntRect(64 + 64, 0, 32, 32));
	AniT jb25(sf::IntRect(64, 32, 32, 32));
	AniT jb26(sf::IntRect(64 + 32, 32, 32, 32));
	AniT jb27(sf::IntRect(64 + 64, 32, 32, 32));
	AniT jb28(sf::IntRect(64, 64, 32, 32));
	AniT jb29(sf::IntRect(64 + 32, 64, 32, 32));
	AniT jb30(sf::IntRect(64 + 64, 64, 32, 32));


	std::vector<std::vector<AniT>> jv1 = { { { jb1,jb2,jb3,jb4,jb5,jb6,jb7,jb8,jb9,jb10,jb11,jb12,jb13,jb14,jb15,jb16,jb17,jb18,jb19,jb20,jb21,jb22,jb23,jb24,jb25,jb26,jb27,jb28,jb29,jb30 } } };
	All_Sprites[7][1] = jv1;//1

							//Foreground sprites~~~
	AniT jfore1(sf::IntRect(320, 416, 256, 128));
	AniT jfore2(sf::IntRect(512, 0, 32, 32));
	AniT jfore3(sf::IntRect(512 + 32, 0, 32, 32));
	AniT jfore4(sf::IntRect(512, 32, 32, 32));
	AniT jfore5(sf::IntRect(512 + 32, 32, 32, 32));
	AniT jfore6(sf::IntRect(256, 0, 96, 96));
	AniT jfore7(sf::IntRect(0, 0, 64, 96));
	AniT jfore8(sf::IntRect(320, 416, 256, 32));
	AniT jfore9(sf::IntRect(320, 416 + 32, 256, 32));
	AniT jfore10(sf::IntRect(320, 416, 32, 128));
	AniT jfore11(sf::IntRect(320 + 32, 416, 32, 128));
	AniT jfore12(sf::IntRect(320, 288, 256, 64));
	AniT jfore13(sf::IntRect(320, 288 + 64, 256, 64));
	AniT jfore14(sf::IntRect(192, 416, 64, 128));
	AniT jfore15(sf::IntRect(192 + 64, 416, 64, 128));

	//water banks
	AniT jfore16(sf::IntRect(64, 224, 32, 32));
	AniT jfore17(sf::IntRect(96, 224, 32, 32));
	AniT jfore18(sf::IntRect(128, 224, 32, 32));
	AniT jfore19(sf::IntRect(128, 224 + 32, 32, 32));
	AniT jfore20(sf::IntRect(128, 224 + 64, 32, 32));
	AniT jfore21(sf::IntRect(96, 224 + 64, 32, 32));
	AniT jfore22(sf::IntRect(64, 224 + 64, 32, 32));
	AniT jfore23(sf::IntRect(64, 224 + 32, 32, 32));
	//Big red mushroom
	AniT jfore24(sf::IntRect(192, 320, 64, 96));
	//Big blue/purple mushroom
	AniT jfore25(sf::IntRect(96, 320, 96, 96));
	All_Sprites[7][7] = { { { jfore1, jfore2, jfore3, jfore4, jfore5, jfore6, jfore7, jfore8, jfore9, jfore10, jfore11,jfore12,jfore13,jfore14,jfore15,
		jfore16,jfore17,jfore18,jfore19,jfore20,jfore21,jfore22,jfore23,jfore24,jfore25 } } };//7

	//AniBg sprites~~~
	AniT jba1(sf::IntRect(96, 96, 32, 32));
	AniT jba2(sf::IntRect(96, 96 + (32 * 1), 32, 32));
	AniT jba3(sf::IntRect(96, 96 + (32 * 2), 32, 32));
	AniT jba4(sf::IntRect(224, 96, 32, 32));
	AniT jba5(sf::IntRect(224 + 32, 96, 32, 32));
	//Water
	AniT jba6(sf::IntRect(288, 192, 32, 32));
	AniT jba7(sf::IntRect(288, 192 + 32, 32, 32));
	AniT jba8(sf::IntRect(288, 192 + 64, 32, 32));
	//Dungeon one
	AniT jba9(sf::IntRect(352, 192 - 128, 96, 64));
	AniT jba10(sf::IntRect(352, 192 - 64, 96, 64));
	AniT jba11(sf::IntRect(352, 192, 96, 64));
	//Lightning bugs
	AniT jlight1(sf::IntRect(96, 416, 32, 32));
	AniT jlight2(sf::IntRect(96, 416 + 32, 32, 32));
	AniT jlight3(sf::IntRect(96 + 32, 416, 32, 32));
	AniT jlight4(sf::IntRect(96 + 32, 416 + 32, 32, 32));
	AniT jlight5(sf::IntRect(96 + 64, 416, 32, 32));
	AniT jlight6(sf::IntRect(96 + 64, 416 + 32, 32, 32));


	All_Sprites[7][4] = { { { jba1, jba2, jba3, jba2 },{ jba4,jba5 },{ jba6,jba7,jba8 },{ jba9,jba10,jba11,jba10,jba9,jba11,jba9,jba10,jba11 },{ jlight1,jlight2 },{ jlight3,jlight4 },{ jlight5,jlight6 } } };

	//SaveStation sprites~~~
	AniT jsa1(sf::IntRect(64, 128, 32, 32));
	AniT jsa2(sf::IntRect(64, 128 + 32, 32, 32));
	AniT jsa3(sf::IntRect(64, 128 + 64, 32, 32));
	All_Sprites[7][5] = { { { jsa1,jsa2,jsa3,jsa2 } } };//5



														//Chest sprites~~~

														//Stream sprites~~~
	AniT jstr0(sf::IntRect(160, 256, 64, 32));
	All_Sprites[7][16] = { { { jstr0 } } };
	//TripleChest sprites~~~
	AniT jch1(sf::IntRect(256, 224, 32, 32)); //Tool box closed
	AniT jch2(sf::IntRect(256, 224 + 32, 32, 32)); //Tool box open
	AniT jch3(sf::IntRect(256, 224 + 64, 32, 32)); //Tool box empty
	All_Sprites[7][17] = { { { jch1,jch2,jch3 } } };

	//Sign sprites~~~
	//Mr. Sign
	AniT jsign12(sf::IntRect(320, 96, 32, 32));
	AniT jsign13(sf::IntRect(320, 96 + 32, 32, 32));
	AniT jsign14(sf::IntRect(320, 96 + 64, 32, 32));
	All_Sprites[7][15] = { { jsign12,jsign13,jsign14 } };
	//AniWall sprites~~~
	//Radioactive waste barrel
	AniT jradio1(sf::IntRect(224, 224, 32, 32));
	AniT jradio2(sf::IntRect(224, 224 + 32, 32, 32));
	AniT jradio3(sf::IntRect(224, 224 + 64, 32, 32));
	//Rock with grass swaying
	AniT jrock1(sf::IntRect(288, 288, 32, 32));
	AniT jrock2(sf::IntRect(288, 288 + 32, 32, 32));
	AniT jrock3(sf::IntRect(288, 288 + 64, 32, 32));
	
	All_Sprites[7][19] = { { jradio1,jradio2,jradio3,jradio2 },{ jrock1,jrock2,jrock3,jrock2 }  };
}

bool Basic_Tile_MOTHER::deletetile(int x, int y) {
	//This is used for looping through all the tiles in the class's tile vectors.
	//It deletes which ever one equals your cursor's x and y cordinates.
	for (unsigned int i = 0; i < ColTiles.size(); i++) {
		if (x == ColTiles[i]->getx() && y == ColTiles[i]->gety()) {

			delete ColTiles[i];
			ColTiles.erase(ColTiles.begin() + i);
			return true;
		}
	}
	for (unsigned int i = 0; i < NonColTiles_FORE.size(); i++) {
		if (x == NonColTiles_FORE[i]->getx() && y == NonColTiles_FORE[i]->gety()) {
			delete NonColTiles_FORE[i];
			NonColTiles_FORE.erase(NonColTiles_FORE.begin() + i);
			return true;
		}
	}
	for (unsigned int i = 0; i < NonColAniTiles.size(); i++) {
		if (x == NonColAniTiles[i]->getx() && y == NonColAniTiles[i]->gety()) {
			delete NonColAniTiles[i];
			NonColAniTiles.erase(NonColAniTiles.begin() + i);
			return true;
		}
	}
	for (unsigned int i = 0; i < NonColTiles.size(); i++) {
		if (x == NonColTiles[i]->getx() && y == NonColTiles[i]->gety()) {
			delete NonColTiles[i];
			NonColTiles.erase(NonColTiles.begin() + i);
			return true;
		}
	}
	for (unsigned int i = 0; i < ColProjectiles.size(); i++) {
		if (x == ColProjectiles[i]->getx() && y == ColProjectiles[i]->gety()) {
			delete ColProjectiles[i];
			ColProjectiles.erase(ColProjectiles.begin() + i);
			return true;
		}
	}
	for (unsigned int i = 0; i < ColAniTiles.size(); i++) {
		if (x == ColAniTiles[i]->getx() && y == ColAniTiles[i]->gety()) {
			delete ColAniTiles[i];
			ColAniTiles.erase(ColAniTiles.begin() + i);
			return true;
		}
	}
	for (unsigned int i = 0; i < NonColAniTiles_FORE.size(); i++) {
		if (x == NonColAniTiles_FORE[i]->getx() && y == NonColAniTiles_FORE[i]->gety()) {
			delete NonColAniTiles_FORE[i];
			NonColAniTiles_FORE.erase(NonColAniTiles_FORE.begin() + i);
			return true;
		}
	}
	return false;
}

void Basic_Tile_MOTHER::deleteAll() {
	for (unsigned int i = 0; i < ColTiles.size(); i++) {
		delete ColTiles[i];
	}
	for (unsigned int i = 0; i < NonColTiles.size(); i++) {
		delete NonColTiles[i];
	}
	for (unsigned int i = 0; i < NonColAniTiles.size(); i++) {
		delete NonColAniTiles[i];
	}
	for (unsigned int i = 0; i < NonColTiles_FORE.size(); i++) {
		delete NonColTiles_FORE[i];
	}
	for (unsigned int i = 0; i < ColProjectiles.size(); i++) {
		delete ColProjectiles[i];
	}
	for (unsigned int i = 0; i < ColAniTiles.size(); i++) {
		delete ColAniTiles[i];
	}
	for (unsigned int i = 0; i < NonColAniTiles_FORE.size(); i++) {
		delete NonColAniTiles_FORE[i];
	}
	ColTiles.clear();
	NonColTiles.clear();
	NonColAniTiles.clear();
	NonColTiles_FORE.clear();
	ColProjectiles.clear();
	ColAniTiles.clear();
	NonColAniTiles_FORE.clear();
}

std::string Basic_Tile_MOTHER::GetSave() {
	std::string r = "&0&";
	for (unsigned int i = 0; i < NonColAniTiles.size(); i++) {
		r.append(":");
		//typeID
		r.append(std::to_string(NonColAniTiles[i]->gettypeID()) + ",");

		for (unsigned int b = 0; b < NonColAniTiles[i]->getSavedParameters().size(); b++) {
			r.append(std::to_string(NonColAniTiles[i]->getSavedParameters()[b]) + ",");
		}
		r.append(":");
	}
	for (unsigned int i = 0; i < NonColTiles.size(); i++) {
		r.append(":");
		//typeID
		r.append(std::to_string(NonColTiles[i]->gettypeID()) + ",");
		
		for (unsigned int b = 0; b < NonColTiles[i]->getSavedParameters().size(); b++) {
			r.append(std::to_string(NonColTiles[i]->getSavedParameters()[b]) + ",");
		}
		r.append(":");
	}
	
	
	for (unsigned int i = 0; i < NonColTiles_FORE.size(); i++) {
		r.append(":");
		//typeID
		r.append(std::to_string(NonColTiles_FORE[i]->gettypeID()) + ",");

		for (unsigned int b = 0; b < NonColTiles_FORE[i]->getSavedParameters().size(); b++) {
			r.append(std::to_string(NonColTiles_FORE[i]->getSavedParameters()[b]) + ",");
		}
		r.append(":");
	}
	for (unsigned int i = 0; i < ColTiles.size(); i++) {
		r.append(":");
		//typeID
		r.append(std::to_string(ColTiles[i]->gettypeID()) + ",");

		for (unsigned int b = 0; b < ColTiles[i]->getSavedParameters().size(); b++) {
			r.append(std::to_string(ColTiles[i]->getSavedParameters()[b]) + ",");
		}
		r.append(":");
	}
	
	for (unsigned int i = 0; i < ColProjectiles.size(); i++) {
		r.append(":");
		//typeID
		r.append(std::to_string(ColProjectiles[i]->gettypeID()) + ",");
		
		for (unsigned int b = 0; b < ColProjectiles[i]->getSavedParameters().size(); b++) {
			r.append(std::to_string(ColProjectiles[i]->getSavedParameters()[b]) + ",");
		}
		r.append(":");
	}
	for (unsigned int i = 0; i < ColAniTiles.size(); i++) {
		r.append(":");
		//typeID
		r.append(std::to_string(ColAniTiles[i]->gettypeID()) + ",");
		
		for (unsigned int b = 0; b < ColAniTiles[i]->getSavedParameters().size(); b++) {
			r.append(std::to_string(ColAniTiles[i]->getSavedParameters()[b]) + ",");
		}
		r.append(":");
	}
	for (unsigned int i = 0; i < NonColAniTiles_FORE.size(); i++) {
		r.append(":");
		//typeID
		r.append(std::to_string(NonColAniTiles_FORE[i]->gettypeID()) + ",");

		for (unsigned int b = 0; b < NonColAniTiles_FORE[i]->getSavedParameters().size(); b++) {
			r.append(std::to_string(NonColAniTiles_FORE[i]->getSavedParameters()[b]) + ",");
		}
		r.append(":");
	}
	return r;
}

unsigned int Basic_Tile_MOTHER::gettypeID() {
	return typeID;
}

unsigned int Basic_Tile_MOTHER::getspriteID() {
	return spriteID;
	
}

std::vector<int> Basic_Tile_MOTHER::getSavedParameters() {
	return SavedParameters;
}

bool Basic_Tile_MOTHER::Check_Overlap(int Yourx_pos, int Youry_pos) {
	for (unsigned int i = 0; i < ColTiles.size(); i++) {
		if (Yourx_pos == ColTiles[i]->getx() && Youry_pos == ColTiles[i]->gety()) {
			return true;
		}
	}
	for (unsigned int i = 0; i < NonColTiles.size(); i++) {
		if (Yourx_pos == NonColTiles[i]->getx() && Youry_pos == NonColTiles[i]->gety()) {
			return true;
		}
	}
	for (unsigned int i = 0; i < NonColAniTiles.size(); i++) {
		if (Yourx_pos == NonColAniTiles[i]->getx() && Youry_pos == NonColAniTiles[i]->gety()) {
			return true;
		}
	}
	for (unsigned int i = 0; i < NonColTiles_FORE.size(); i++) {
		if (Yourx_pos == NonColTiles_FORE[i]->getx() && Youry_pos == NonColTiles_FORE[i]->gety()) {
			return true;
		}
	}
	for (unsigned int i = 0; i < ColProjectiles.size(); i++) {
		if (Yourx_pos == ColProjectiles[i]->getx() && Youry_pos == ColProjectiles[i]->gety()) {
			return true;
		}
	}
	for (unsigned int i = 0; i < ColAniTiles.size(); i++) {
		if (Yourx_pos == ColAniTiles[i]->getx() && Youry_pos == ColAniTiles[i]->gety()) {
			return true;
		}
	}
	for (unsigned int i = 0; i < NonColAniTiles_FORE.size(); i++) {
		if (Yourx_pos == NonColAniTiles_FORE[i]->getx() && Youry_pos == NonColAniTiles_FORE[i]->gety()) {
			return true;
		}
	}
	return false;
}


bool Basic_Tile_MOTHER::CheckSpecialCollision(int PlayerChannel) {
	
	for (unsigned int i = 0; i < NonColTiles.size(); i++) {
		if (NonColTiles[i]->getx() == Player::PlayerObjects[PlayerChannel]->getx() && NonColTiles[i]->gety() == Player::PlayerObjects[PlayerChannel]->gety()) {
			if (NonColTiles[i]->ifCollision(PlayerChannel) == true) {
				return true;
			}
		}
		
	}
	for (unsigned int i = 0; i < NonColAniTiles.size(); i++) {
		if (NonColAniTiles[i]->getx() == Player::PlayerObjects[PlayerChannel]->getx() && NonColAniTiles[i]->gety() == Player::PlayerObjects[PlayerChannel]->gety()) {
			if (NonColAniTiles[i]->ifCollision(PlayerChannel) == true) {
				return true;
			}
		}
		
	}
	for (unsigned int i = 0; i < NonColAniTiles_FORE.size(); i++) {
		if (NonColAniTiles_FORE[i]->getx() == Player::PlayerObjects[PlayerChannel]->getx() && NonColAniTiles_FORE[i]->gety() == Player::PlayerObjects[PlayerChannel]->gety()) {
			if (NonColAniTiles_FORE[i]->ifCollision(PlayerChannel) == true) {
				return true;
			}
		}
	}
	if (Invisible_MOTHER::checkSpecialCollision(PlayerChannel) == true) {
		return true;
	};
	return false;
}

void Basic_Tile_MOTHER::mainanimate() {
	for (unsigned int i = 0; i < NonColAniTiles.size(); i++) {
		NonColAniTiles[i]->animate();
	}
	for (unsigned int i = 0; i < ColProjectiles.size(); i++) {
		ColProjectiles[i]->animate();
	}
	for (unsigned int i = 0; i < ColAniTiles.size(); i++) {
		ColAniTiles[i]->animate();
	}
	for (unsigned int i = 0; i < NonColAniTiles_FORE.size(); i++) {
		NonColAniTiles_FORE[i]->animate();
	}
}

void Basic_Tile_MOTHER::animate() {
	ticks += GF::getDelta();
	if (ticks >= max_ticks) {
		svectorindex += 1;
		if (svectorindex >= Sprites.size()) {
			svectorindex = 0;
			//Setting the texture rectangle to the correct position for proper animation.
		}
			sprite *= Sprites[svectorindex];
		ticks -= max_ticks;
	}
}

bool Basic_Tile_MOTHER::ifCollisionBefore(bool isPlayer) {
	return true;
}

bool Basic_Tile_MOTHER::elseCollisionBefore(int PlayerChannel) {
	return true;
}

void Basic_Tile_MOTHER::DrawForeGround(sf::RenderWindow &win) {
	for (unsigned int i = 0; i < NonColTiles_FORE.size(); i++) {
		NonColTiles_FORE[i]->Draw(win);
	}
	for (unsigned int i = 0; i < NonColAniTiles_FORE.size(); i++) {
		NonColAniTiles_FORE[i]->Draw(win);
	}
}

bool Basic_Tile_MOTHER::CheckProjectileCollision(Projectile &P, int direction) {
	for (unsigned int i = 0; i < ColProjectiles.size(); i++) {
		if (ColProjectiles[i]->getx() == P.getcx() && ColProjectiles[i]->gety() == P.getcy()) {
			ColProjectiles[i]->ifProjectileCollision(P, direction);
			return true;
		}
		
	}
	return false;
}

void Basic_Tile_MOTHER::ifProjectileCollision(Projectile &P, int direction) {
	
}

float Basic_Tile_MOTHER::getx() {
	return x;
}
float Basic_Tile_MOTHER::gety() {
	return y;
}

void Basic_Tile_MOTHER::changeAni(std::vector<AniT> new_Ani) {
	svectorindex = 0;
	Sprites = new_Ani;
}

ST *Basic_Tile_MOTHER::getSpritePointer() {
	return &sprite;
}
