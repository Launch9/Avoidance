#include "stdafx.h"
#include "random2.h"
#include <iostream>
#include "GF.h"
using namespace random2;

extern unsigned int random2::g_seed = 0;

void random2::fast_srand(int seed)
{
	g_seed = seed;
}

int random2::fastrand()
{
	g_seed = (214013 * g_seed + 2531011);
	return (g_seed >> 16) & 0x7FFF;
}

int random2::randomrange(unsigned int lownum, unsigned int highnum) {
	int f = (fastrand() % highnum) + lownum;
	return f;
}

int random2::randomrange_complex(int lownum, int highnum) {
	int dif = highnum - lownum;
	dif = (fastrand() % dif) + 0;
	return lownum + dif;
}

bool random2::getBool() {
	return (fastrand() % 2);
}
