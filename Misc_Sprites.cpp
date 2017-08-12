#include "stdafx.h"
#include "Misc_Sprites.h"
std::vector<std::vector<std::vector<std::vector<AniT>>>> Misc_Sprites::All_Sprites;

void Misc_Sprites::init() {
	for (unsigned int i = 0; i < 10; i++) {
		All_Sprites.push_back({});
		for (unsigned int b = 0; b < 15; b++) {
			All_Sprites[i].push_back({});
		}
	}
	//-=-=-=-=-=-=-=-=-
	//Lobby 2 Sprites
	//-=-=-=-=-=-=-=-=-

	//Flame sprites:
	//Up:
	AniT uf0(sf::IntRect(192, 576, 32, 64)); //Flame frame
	AniT uf1(sf::IntRect(192 - (32 * 1), 576, 32, 64)); //Flame frame
	AniT uf2(sf::IntRect(192 - (32 * 2), 576, 32, 64)); //Flame frame
	AniT uf3(sf::IntRect(192 - (32 * 3), 576, 32, 64)); //Flame frame
	AniT uf4(sf::IntRect(192 - (32 * 4), 576, 32, 64)); //Flame frame
	AniT uf5(sf::IntRect(192 - (32 * 0), 576 + 64, 32, 64)); //Flame frame
	AniT uf6(sf::IntRect(192 - (32 * 1), 576 + 64, 32, 64)); //Flame frame
	AniT uf7(sf::IntRect(192 - (32 * 2), 576 + 64, 32, 64)); //Flame frame
	//Right:
	AniT uf0_1(sf::IntRect(224, 768, 64, 32)); //Flame frame
	AniT uf1_1(sf::IntRect(224, 768 - (32 * 1), 64, 32)); //Flame frame
	AniT uf2_1(sf::IntRect(224, 768 - (32 * 2), 64, 32)); //Flame frame
	AniT uf3_1(sf::IntRect(224, 768 - (32 * 3), 64, 32)); //Flame frame
	AniT uf4_1(sf::IntRect(224, 768 - (32 * 4), 64, 32)); //Flame frame
	AniT uf5_1(sf::IntRect(224 - 64, 768 - (32 * 0), 64, 32)); //Flame frame
	AniT uf6_1(sf::IntRect(224 - 64, 768 - (32 * 1), 64, 32)); //Flame frame
	AniT uf7_1(sf::IntRect(224 - 64, 768 - (32 * 2), 64, 32)); //Flame frame
	//Down
	AniT uf0_2(sf::IntRect(64, 800, 32, 64)); //Flame frame
	AniT uf1_2(sf::IntRect(64 + (32 * 1), 800, 32, 64)); //Flame frame
	AniT uf2_2(sf::IntRect(64 + (32 * 2), 800, 32, 64)); //Flame frame
	AniT uf3_2(sf::IntRect(64 + (32 * 3), 800, 32, 64)); //Flame frame
	AniT uf4_2(sf::IntRect(64 + (32 * 4), 800, 32, 64)); //Flame frame
	AniT uf5_2(sf::IntRect(64 + (32 * 0), 800 - 64, 32, 64)); //Flame frame
	AniT uf6_2(sf::IntRect(64 + (32 * 1), 800 - 64, 32, 64)); //Flame frame
	AniT uf7_2(sf::IntRect(64 + (32 * 2), 800 - 64, 32, 64)); //Flame frame
	//Left
	AniT uf0_3(sf::IntRect(0, 640, 64, 32)); //Flame frame
	AniT uf1_3(sf::IntRect(0, 640 + (32 * 1), 64, 32)); //Flame frame
	AniT uf2_3(sf::IntRect(0, 640 + (32 * 2), 64, 32)); //Flame frame
	AniT uf3_3(sf::IntRect(0, 640 + (32 * 3), 64, 32)); //Flame frame
	AniT uf4_3(sf::IntRect(0, 640 + (32 * 4), 64, 32)); //Flame frame
	AniT uf5_3(sf::IntRect(64, 640 + (32 * 0), 64, 32)); //Flame frame
	AniT uf6_3(sf::IntRect(64, 640 + (32 * 1), 64, 32)); //Flame frame
	AniT uf7_3(sf::IntRect(64, 640 + (32 * 2), 64, 32)); //Flame frame

	All_Sprites[3][0].push_back({ uf0,uf1,uf2,uf3,uf4,uf5,uf6,uf7 });
	All_Sprites[3][0].push_back({ uf0_1,uf1_1,uf2_1,uf3_1,uf4_1,uf5_1,uf6_1,uf7_1 });
	All_Sprites[3][0].push_back({ uf0_2,uf1_2,uf2_2,uf3_2,uf4_2,uf5_2,uf6_2,uf7_2 });
	All_Sprites[3][0].push_back({ uf0_3,uf1_3,uf2_3,uf3_3,uf4_3,uf5_3,uf6_3,uf7_3 });

	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Dungeon 2 Sprites
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	

	//Flame sprites:
	//Up:
	AniT quf0(sf::IntRect(192, 576, 32, 64)); //Flame frame
	AniT quf1(sf::IntRect(192 - (32 * 1), 576, 32, 64)); //Flame frame
	AniT quf2(sf::IntRect(192 - (32 * 2), 576, 32, 64)); //Flame frame
	AniT quf3(sf::IntRect(192 - (32 * 3), 576, 32, 64)); //Flame frame
	AniT quf4(sf::IntRect(192 - (32 * 4), 576, 32, 64)); //Flame frame
	AniT quf5(sf::IntRect(192 - (32 * 0), 576 + 64, 32, 64)); //Flame frame
	AniT quf6(sf::IntRect(192 - (32 * 1), 576 + 64, 32, 64)); //Flame frame
	AniT quf7(sf::IntRect(192 - (32 * 2), 576 + 64, 32, 64)); //Flame frame
	//Right:
	AniT quf0_1(sf::IntRect(224, 768, 64, 32)); //Flame frame
	AniT quf1_1(sf::IntRect(224, 768 - (32 * 1), 64, 32)); //Flame frame
	AniT quf2_1(sf::IntRect(224, 768 - (32 * 2), 64, 32)); //Flame frame
	AniT quf3_1(sf::IntRect(224, 768 - (32 * 3), 64, 32)); //Flame frame
	AniT quf4_1(sf::IntRect(224, 768 - (32 * 4), 64, 32)); //Flame frame
	AniT quf5_1(sf::IntRect(224 - 64, 768 - (32 * 0), 64, 32)); //Flame frame
	AniT quf6_1(sf::IntRect(224 - 64, 768 - (32 * 1), 64, 32)); //Flame frame
	AniT quf7_1(sf::IntRect(224 - 64, 768 - (32 * 2), 64, 32)); //Flame frame
	//Down
	AniT quf0_2(sf::IntRect(64, 800, 32, 64)); //Flame frame
	AniT quf1_2(sf::IntRect(64 + (32 * 1), 800, 32, 64)); //Flame frame
	AniT quf2_2(sf::IntRect(64 + (32 * 2), 800, 32, 64)); //Flame frame
	AniT quf3_2(sf::IntRect(64 + (32 * 3), 800, 32, 64)); //Flame frame
	AniT quf4_2(sf::IntRect(64 + (32 * 4), 800, 32, 64)); //Flame frame
	AniT quf5_2(sf::IntRect(64 + (32 * 0), 800 - 64, 32, 64)); //Flame frame
	AniT quf6_2(sf::IntRect(64 + (32 * 1), 800 - 64, 32, 64)); //Flame frame
	AniT quf7_2(sf::IntRect(64 + (32 * 2), 800 - 64, 32, 64)); //Flame frame
	//Left
	AniT quf0_3(sf::IntRect(0, 640, 64, 32)); //Flame frame
	AniT quf1_3(sf::IntRect(0, 640 + (32 * 1), 64, 32)); //Flame frame
	AniT quf2_3(sf::IntRect(0, 640 + (32 * 2), 64, 32)); //Flame frame
	AniT quf3_3(sf::IntRect(0, 640 + (32 * 3), 64, 32)); //Flame frame
	AniT quf4_3(sf::IntRect(0, 640 + (32 * 4), 64, 32)); //Flame frame
	AniT quf5_3(sf::IntRect(64, 640 + (32 * 0), 64, 32)); //Flame frame
	AniT quf6_3(sf::IntRect(64, 640 + (32 * 1), 64, 32)); //Flame frame
	AniT quf7_3(sf::IntRect(64, 640 + (32 * 2), 64, 32)); //Flame frame

	All_Sprites[4][0].push_back({ quf0,quf1,quf2,quf3,quf4,quf5,quf6,quf7 });
	All_Sprites[4][0].push_back({ quf0_1,quf1_1,quf2_1,quf3_1,quf4_1,quf5_1,quf6_1,quf7_1 });
	All_Sprites[4][0].push_back({ quf0_2,quf1_2,quf2_2,quf3_2,quf4_2,quf5_2,quf6_2,quf7_2 });
	All_Sprites[4][0].push_back({ quf0_3,quf1_3,quf2_3,quf3_3,quf4_3,quf5_3,quf6_3,quf7_3 });

	//Blast sprites:
	AniT qb0(sf::IntRect(256, 384, 32, 32));
	AniT qb1(sf::IntRect(256, 384 + 32, 32, 32));
	AniT qb2(sf::IntRect(256, 384 + 64, 32, 32));
	AniT qb3(sf::IntRect(256, 384 + 96, 32, 32));
	AniT qb4(sf::IntRect(256, 384 + 128, 32, 32));

	All_Sprites[4][1].push_back({ qb0,qb1,qb2,qb3,qb4 });

	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Lobby 3 Sprites
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=



	//Flame sprites:
	//Up:
	AniT puf0(sf::IntRect(192, 576, 32, 64)); //Flame frame
	AniT puf1(sf::IntRect(192 - (32 * 1), 576, 32, 64)); //Flame frame
	AniT puf2(sf::IntRect(192 - (32 * 2), 576, 32, 64)); //Flame frame
	AniT puf3(sf::IntRect(192 - (32 * 3), 576, 32, 64)); //Flame frame
	AniT puf4(sf::IntRect(192 - (32 * 4), 576, 32, 64)); //Flame frame
	AniT puf5(sf::IntRect(192 - (32 * 0), 576 + 64, 32, 64)); //Flame frame
	AniT puf6(sf::IntRect(192 - (32 * 1), 576 + 64, 32, 64)); //Flame frame
	AniT puf7(sf::IntRect(192 - (32 * 2), 576 + 64, 32, 64)); //Flame frame
															  //Right:
	AniT puf0_1(sf::IntRect(224, 768, 64, 32)); //Flame frame
	AniT puf1_1(sf::IntRect(224, 768 - (32 * 1), 64, 32)); //Flame frame
	AniT puf2_1(sf::IntRect(224, 768 - (32 * 2), 64, 32)); //Flame frame
	AniT puf3_1(sf::IntRect(224, 768 - (32 * 3), 64, 32)); //Flame frame
	AniT puf4_1(sf::IntRect(224, 768 - (32 * 4), 64, 32)); //Flame frame
	AniT puf5_1(sf::IntRect(224 - 64, 768 - (32 * 0), 64, 32)); //Flame frame
	AniT puf6_1(sf::IntRect(224 - 64, 768 - (32 * 1), 64, 32)); //Flame frame
	AniT puf7_1(sf::IntRect(224 - 64, 768 - (32 * 2), 64, 32)); //Flame frame
																//Down
	AniT puf0_2(sf::IntRect(64, 800, 32, 64)); //Flame frame
	AniT puf1_2(sf::IntRect(64 + (32 * 1), 800, 32, 64)); //Flame frame
	AniT puf2_2(sf::IntRect(64 + (32 * 2), 800, 32, 64)); //Flame frame
	AniT puf3_2(sf::IntRect(64 + (32 * 3), 800, 32, 64)); //Flame frame
	AniT puf4_2(sf::IntRect(64 + (32 * 4), 800, 32, 64)); //Flame frame
	AniT puf5_2(sf::IntRect(64 + (32 * 0), 800 - 64, 32, 64)); //Flame frame
	AniT puf6_2(sf::IntRect(64 + (32 * 1), 800 - 64, 32, 64)); //Flame frame
	AniT puf7_2(sf::IntRect(64 + (32 * 2), 800 - 64, 32, 64)); //Flame frame
															   //Left
	AniT puf0_3(sf::IntRect(0, 640, 64, 32)); //Flame frame
	AniT puf1_3(sf::IntRect(0, 640 + (32 * 1), 64, 32)); //Flame frame
	AniT puf2_3(sf::IntRect(0, 640 + (32 * 2), 64, 32)); //Flame frame
	AniT puf3_3(sf::IntRect(0, 640 + (32 * 3), 64, 32)); //Flame frame
	AniT puf4_3(sf::IntRect(0, 640 + (32 * 4), 64, 32)); //Flame frame
	AniT puf5_3(sf::IntRect(64, 640 + (32 * 0), 64, 32)); //Flame frame
	AniT puf6_3(sf::IntRect(64, 640 + (32 * 1), 64, 32)); //Flame frame
	AniT puf7_3(sf::IntRect(64, 640 + (32 * 2), 64, 32)); //Flame frame

	All_Sprites[5][0].push_back({ puf0,puf1,puf2,puf3,puf4,puf5,puf6,puf7 });
	All_Sprites[5][0].push_back({ puf0_1,puf1_1,puf2_1,puf3_1,puf4_1,puf5_1,puf6_1,puf7_1 });
	All_Sprites[5][0].push_back({ puf0_2,puf1_2,puf2_2,puf3_2,puf4_2,puf5_2,puf6_2,puf7_2 });
	All_Sprites[5][0].push_back({ puf0_3,puf1_3,puf2_3,puf3_3,puf4_3,puf5_3,puf6_3,puf7_3 });

	//Blast sprites:
	AniT pb0(sf::IntRect(256, 384, 32, 32));
	AniT pb1(sf::IntRect(256, 384 + 32, 32, 32));
	AniT pb2(sf::IntRect(256, 384 + 64, 32, 32));
	AniT pb3(sf::IntRect(256, 384 + 96, 32, 32));
	AniT pb4(sf::IntRect(256, 384 + 128, 32, 32));

	All_Sprites[5][1].push_back({ pb0,pb1,pb2,pb3,pb4 });

	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Dungeon 3 sprites
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=



	//Flame sprites:
	//Up:
	AniT vuf0(sf::IntRect(192, 576, 32, 64)); //Flame frame
	AniT vuf1(sf::IntRect(192 - (32 * 1), 576, 32, 64)); //Flame frame
	AniT vuf2(sf::IntRect(192 - (32 * 2), 576, 32, 64)); //Flame frame
	AniT vuf3(sf::IntRect(192 - (32 * 3), 576, 32, 64)); //Flame frame
	AniT vuf4(sf::IntRect(192 - (32 * 4), 576, 32, 64)); //Flame frame
	AniT vuf5(sf::IntRect(192 - (32 * 0), 576 + 64, 32, 64)); //Flame frame
	AniT vuf6(sf::IntRect(192 - (32 * 1), 576 + 64, 32, 64)); //Flame frame
	AniT vuf7(sf::IntRect(192 - (32 * 2), 576 + 64, 32, 64)); //Flame frame
															  //Right:
	AniT vuf0_1(sf::IntRect(224, 768, 64, 32)); //Flame frame
	AniT vuf1_1(sf::IntRect(224, 768 - (32 * 1), 64, 32)); //Flame frame
	AniT vuf2_1(sf::IntRect(224, 768 - (32 * 2), 64, 32)); //Flame frame
	AniT vuf3_1(sf::IntRect(224, 768 - (32 * 3), 64, 32)); //Flame frame
	AniT vuf4_1(sf::IntRect(224, 768 - (32 * 4), 64, 32)); //Flame frame
	AniT vuf5_1(sf::IntRect(224 - 64, 768 - (32 * 0), 64, 32)); //Flame frame
	AniT vuf6_1(sf::IntRect(224 - 64, 768 - (32 * 1), 64, 32)); //Flame frame
	AniT vuf7_1(sf::IntRect(224 - 64, 768 - (32 * 2), 64, 32)); //Flame frame
																//Down
	AniT vuf0_2(sf::IntRect(64, 800, 32, 64)); //Flame frame
	AniT vuf1_2(sf::IntRect(64 + (32 * 1), 800, 32, 64)); //Flame frame
	AniT vuf2_2(sf::IntRect(64 + (32 * 2), 800, 32, 64)); //Flame frame
	AniT vuf3_2(sf::IntRect(64 + (32 * 3), 800, 32, 64)); //Flame frame
	AniT vuf4_2(sf::IntRect(64 + (32 * 4), 800, 32, 64)); //Flame frame
	AniT vuf5_2(sf::IntRect(64 + (32 * 0), 800 - 64, 32, 64)); //Flame frame
	AniT vuf6_2(sf::IntRect(64 + (32 * 1), 800 - 64, 32, 64)); //Flame frame
	AniT vuf7_2(sf::IntRect(64 + (32 * 2), 800 - 64, 32, 64)); //Flame frame
															   //Left
	AniT vuf0_3(sf::IntRect(0, 640, 64, 32)); //Flame frame
	AniT vuf1_3(sf::IntRect(0, 640 + (32 * 1), 64, 32)); //Flame frame
	AniT vuf2_3(sf::IntRect(0, 640 + (32 * 2), 64, 32)); //Flame frame
	AniT vuf3_3(sf::IntRect(0, 640 + (32 * 3), 64, 32)); //Flame frame
	AniT vuf4_3(sf::IntRect(0, 640 + (32 * 4), 64, 32)); //Flame frame
	AniT vuf5_3(sf::IntRect(64, 640 + (32 * 0), 64, 32)); //Flame frame
	AniT vuf6_3(sf::IntRect(64, 640 + (32 * 1), 64, 32)); //Flame frame
	AniT vuf7_3(sf::IntRect(64, 640 + (32 * 2), 64, 32)); //Flame frame

	All_Sprites[6][0].push_back({ vuf0,vuf1,vuf2,vuf3,vuf4,vuf5,vuf6,vuf7 });
	All_Sprites[6][0].push_back({ vuf0_1,vuf1_1,vuf2_1,vuf3_1,vuf4_1,vuf5_1,vuf6_1,vuf7_1 });
	All_Sprites[6][0].push_back({ vuf0_2,vuf1_2,vuf2_2,vuf3_2,vuf4_2,vuf5_2,vuf6_2,vuf7_2 });
	All_Sprites[6][0].push_back({ vuf0_3,vuf1_3,vuf2_3,vuf3_3,vuf4_3,vuf5_3,vuf6_3,vuf7_3 });

	//Blast sprites:
	AniT vb0(sf::IntRect(256, 384, 32, 32));
	AniT vb1(sf::IntRect(256, 384 + 32, 32, 32));
	AniT vb2(sf::IntRect(256, 384 + 64, 32, 32));
	AniT vb3(sf::IntRect(256, 384 + 96, 32, 32));
	AniT vb4(sf::IntRect(256, 384 + 128, 32, 32));

	All_Sprites[6][1].push_back({ vb0,vb1,vb2,vb3, vb4 });

	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Lobby 4 Sprites
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=



	//Flame sprites:
	//Up:
	AniT juf0(sf::IntRect(192, 576, 32, 64)); //Flame frame
	AniT juf1(sf::IntRect(192 - (32 * 1), 576, 32, 64)); //Flame frame
	AniT juf2(sf::IntRect(192 - (32 * 2), 576, 32, 64)); //Flame frame
	AniT juf3(sf::IntRect(192 - (32 * 3), 576, 32, 64)); //Flame frame
	AniT juf4(sf::IntRect(192 - (32 * 4), 576, 32, 64)); //Flame frame
	AniT juf5(sf::IntRect(192 - (32 * 0), 576 + 64, 32, 64)); //Flame frame
	AniT juf6(sf::IntRect(192 - (32 * 1), 576 + 64, 32, 64)); //Flame frame
	AniT juf7(sf::IntRect(192 - (32 * 2), 576 + 64, 32, 64)); //Flame frame
															  //Right:
	AniT juf0_1(sf::IntRect(224, 768, 64, 32)); //Flame frame
	AniT juf1_1(sf::IntRect(224, 768 - (32 * 1), 64, 32)); //Flame frame
	AniT juf2_1(sf::IntRect(224, 768 - (32 * 2), 64, 32)); //Flame frame
	AniT juf3_1(sf::IntRect(224, 768 - (32 * 3), 64, 32)); //Flame frame
	AniT juf4_1(sf::IntRect(224, 768 - (32 * 4), 64, 32)); //Flame frame
	AniT juf5_1(sf::IntRect(224 - 64, 768 - (32 * 0), 64, 32)); //Flame frame
	AniT juf6_1(sf::IntRect(224 - 64, 768 - (32 * 1), 64, 32)); //Flame frame
	AniT juf7_1(sf::IntRect(224 - 64, 768 - (32 * 2), 64, 32)); //Flame frame
																//Down
	AniT juf0_2(sf::IntRect(64, 800, 32, 64)); //Flame frame
	AniT juf1_2(sf::IntRect(64 + (32 * 1), 800, 32, 64)); //Flame frame
	AniT juf2_2(sf::IntRect(64 + (32 * 2), 800, 32, 64)); //Flame frame
	AniT juf3_2(sf::IntRect(64 + (32 * 3), 800, 32, 64)); //Flame frame
	AniT juf4_2(sf::IntRect(64 + (32 * 4), 800, 32, 64)); //Flame frame
	AniT juf5_2(sf::IntRect(64 + (32 * 0), 800 - 64, 32, 64)); //Flame frame
	AniT juf6_2(sf::IntRect(64 + (32 * 1), 800 - 64, 32, 64)); //Flame frame
	AniT juf7_2(sf::IntRect(64 + (32 * 2), 800 - 64, 32, 64)); //Flame frame
															   //Left
	AniT juf0_3(sf::IntRect(0, 640, 64, 32)); //Flame frame
	AniT juf1_3(sf::IntRect(0, 640 + (32 * 1), 64, 32)); //Flame frame
	AniT juf2_3(sf::IntRect(0, 640 + (32 * 2), 64, 32)); //Flame frame
	AniT juf3_3(sf::IntRect(0, 640 + (32 * 3), 64, 32)); //Flame frame
	AniT juf4_3(sf::IntRect(0, 640 + (32 * 4), 64, 32)); //Flame frame
	AniT juf5_3(sf::IntRect(64, 640 + (32 * 0), 64, 32)); //Flame frame
	AniT juf6_3(sf::IntRect(64, 640 + (32 * 1), 64, 32)); //Flame frame
	AniT juf7_3(sf::IntRect(64, 640 + (32 * 2), 64, 32)); //Flame frame

	All_Sprites[7][0].push_back({ juf0,juf1,juf2,juf3,juf4,juf5,juf6,juf7 });
	All_Sprites[7][0].push_back({ juf0_1,juf1_1,juf2_1,juf3_1,juf4_1,juf5_1,juf6_1,juf7_1 });
	All_Sprites[7][0].push_back({ juf0_2,juf1_2,juf2_2,juf3_2,juf4_2,juf5_2,juf6_2,juf7_2 });
	All_Sprites[7][0].push_back({ juf0_3,juf1_3,juf2_3,juf3_3,juf4_3,juf5_3,juf6_3,juf7_3 });

	//Blast sprites:
	AniT jb0(sf::IntRect(256, 384, 32, 32));
	AniT jb1(sf::IntRect(256, 384 + 32, 32, 32));
	AniT jb2(sf::IntRect(256, 384 + 64, 32, 32));
	AniT jb3(sf::IntRect(256, 384 + 96, 32, 32));
	AniT jb4(sf::IntRect(256, 384 + 128, 32, 32));

	All_Sprites[7][1].push_back({ jb0,jb1,jb2,jb3,jb4 });
}