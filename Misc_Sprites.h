#pragma once
#include "AniT.h"
///This is a class that just contains misc sprites that will be used on things that aren't BTM, and also aren't NM.
class Misc_Sprites
{
protected:
	//This vector full of vectors that contain vectors which posses vectors, which, in turn, contain AniT sprites.
	static std::vector<std::vector<std::vector<std::vector<AniT>>>> Misc_Sprites::All_Sprites;
public:
	//This makes all the sprites.
	static void init();
};

