#pragma once
#include <vector>
#include "GF.h"
namespace random2
{
	//This is the seed of the random number generator.
	extern unsigned int g_seed;
	//This will take a high number and a low number.
	//And will return a random integer between the two numbers.
	int randomrange(unsigned int lownum, unsigned int highnum);
	//This will take two numbers that can be negative.
	//This is a little slower then calling just randomrange();
	int randomrange_complex(int lownum, int highnum);
	//This is used to set the seed of the generator.
	void fast_srand(int seed);
	//This will is the bare geneterator used to find random numbers.
	//This should only be used if you know what you are doing.
	//Use randomrange and randomrange_complex for easier usage.
	int fastrand();
	//This gets a random number between 0 and 1.
	bool getBool();
	//This class will create a specified number of random numbers that will be put in an an array to be used later.
	//This should be used if you want quick access to random numbers.
	//This will be looped through, so it will not create new numbers as you use them.
	class RandomStorage {
		
		private:
			//This tells you what number index you are on.
			int index = -1;
			//This is a vector full of random numbers that can be used later.
			std::vector<int> random_numbers;
		public:
			//This takes a lot of time to do.
			//So make sure that you call this function when nothing exciting is happening.
			//This can be called more then once if you want the numbers to be refreshed.
			void setup(unsigned int how_many_numbers, int lownum, int highnum) {
				random_numbers.clear();
				for (unsigned int i = 0; i < how_many_numbers; i++) {
					random_numbers.push_back(lownum + (fastrand() % (highnum - lownum)));
				}
				index = -1;
			}

			int getNum() {
				index++;
				if (GF::does_exist(index, random_numbers.size()) == false) {
					index = 0;
				}
				return random_numbers[index];
			}
	};

	
}

