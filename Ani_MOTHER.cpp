#include "stdafx.h"
#include "Ani_MOTHER.h"
#include "Cam.h"
#include "GF.h"

Ani_MOTHER::Ani_MOTHER(int x_pos, int y_pos, std::vector<sf::Sprite> AnimationSprites, float requiredticks)
{
	x = x_pos;
	y = y_pos;
	Sprites = AnimationSprites;
	maxtick = requiredticks;
	for (unsigned int i = 0; i < Sprites.size(); i++) {
		Sprites[i].setPosition(x, y);
	}
}



int Ani_MOTHER::getx() {
	return x;
}
int Ani_MOTHER::gety() {
	return y;
}
float Ani_MOTHER::gettick() {
	return tick;
}
float Ani_MOTHER::getmaxtick() {
	return maxtick;
}
std::vector<sf::Sprite> &Ani_MOTHER::getsprites() {
	return Sprites;
}
void Ani_MOTHER::setx(int x_pos) {
	x = x_pos;
}
void Ani_MOTHER::sety(int y_pos) {
	y = y_pos;
}
void Ani_MOTHER::settick(int newtick) {
	tick = newtick;
}
void Ani_MOTHER::setmaxtick(int newmaxtick) {
	maxtick = newmaxtick;
}
void Ani_MOTHER::setsprites(std::vector<sf::Sprite> newsprites) {
	Sprites = newsprites;
}

void Ani_MOTHER::animate(sf::RenderWindow &win, const bool &isStatic) {
	
	if (tick >= maxtick) {
		tick = 0;
		if (index >= Sprites.size() - 1) {
			index = 0;
		}
		else {
			index += 1;
		}
		
	}
	else {
		tick += GF::getDelta();
	}
	if (isStatic == true) {
		Cam::drawGUI_chan(0, win, Sprites[index]);
	}
	else {
		win.draw(Sprites[index]);
	}
	
}