#include "stdafx.h"
#include "Scoring.h"
#include "GF.h"
#include "GUI.h"
#include <vector>
#include <string>
#include <fstream>

#include <iostream>

#include <vector>

#include <iostream>
#include <fstream>
#include <string>





#define time_multiplier 5
std::vector<std::string> Scoring::files;

Scoring::Scoring()
{
	files = { "R/Scores/Dungeon_1_score.txt", "R/Scores/Dungeon_2_score.txt", "R/Scores/Dungeon_3_score.txt", "R/Scores/Dungeon_4_score.txt" };
}

float Scoring::getTime() {
	return total_time;
}

int Scoring::get_high_score() {
	return high_score;
}

void Scoring::set_high_score(int FileID) {
	high_score = read_score(FileID);
}

void Scoring::tick() {
	if (should_time == true) {
		total_time += GF::getDelta();
		GUI::update();
	}
	
}

void Scoring::add_score(int addend) {
	score += addend;
	GUI::update();
}

int Scoring::getScore() {
	return score;
}



void Scoring::setScore(int new_score) {
	score = new_score;
}

void Scoring::setTime(float new_time) {
	total_time = new_time;
}

void Scoring::deposit(int FileID, int total_score) {	
	if (total_score > read_score(FileID)) {
		std::fstream file;
		file.open(files[FileID]);
		file.clear();
		file << GF::str(total_score);
		file << "*";
		file.close();
		std::cout << "Finished depositing scores to file: " << files[FileID] << std::endl;
	}
	
	
}

int Scoring::getCal_Score() {
	return total_score;
}

void Scoring::setCal_Score(int new_cal_score) {
	total_score = new_cal_score;
}

void Scoring::reset() {
	setTimer(false);
	total_score = 0;
	total_time = 0;
	high_score = 0;
	score = 0;
	GUI::update();
}

int Scoring::read_score(int FileID) {
	std::string number;
	std::ifstream file;
	char CurrentChar;
	file.open(files[FileID]);
	while (file.good()) {
		file.seekg(0, std::ios::cur);
		file >> CurrentChar;
		if (CurrentChar == *"*") {
			break;
		}
		number.push_back(CurrentChar);
	}
	file.close();
	
	if (number == "") {
		return 0;
	}
	else {
		return GF::StringtoInt(number);
	}
	
}

void Scoring::setTimer(bool TF) {
	should_time = TF;
}

void Scoring::set_High_Score_Direct(int new_high_score) {
	high_score = new_high_score;
}

bool Scoring::isTimerActive() {
	return should_time;
}