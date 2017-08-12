#pragma once
#include <vector>
#include <string>
/*This class keeps track of the score you have in a level, also the time.
It can store variables into a file for later use.*/
class Scoring
{
private:
	//This is the boolean telling it whether or not to use the timer.
	bool should_time = false;
	//This is the high score that was put into memory.
	int high_score = 0;
	//This is a vector full of file names to store the scores.
	static std::vector<std::string> Scoring::files;
	//This is the time that it takes to complete the dungeon.
	float total_time = 0;
	//This is your score.
	int score = 0;
	//This is the total calculated score.
	int total_score = 0;
	//This reads off the selected file and returns the score.
	int read_score(int FileID);
	
	
public:
	//This is used to set the score to a given integer.
	void setScore(int new_score);
	//This sets the boolean as to whether or not the timer should be on or off.
	void setTimer(bool TF);
	//This tells you if the timer is active or not.
	bool isTimerActive();
	//This gets the amount of score the object has.
	int getScore();
	//This resets all the variables in memory.
	void reset();
	//This sets the score you calculated to a variable within this object that can be referred to later.
	void setCal_Score(int new_cal_score);
	//This gets the calculated score variable.
	int getCal_Score();
	//This returns the time variable.
	float getTime();
	//This sets the time variable.
	void setTime(float new_time);
	//This returns the high score variable made during the set_high_score function.
	int get_high_score();
	//This reads from a file and sets the high_score variable within this class to that score in the file.
	void set_high_score(int FileID);
	//This function puts the score into a file.
	void deposit(int FileID, int total_score);
	//This ticks the scoring object.
	//Allowing for understanding time through delta.
	//Should call this every frame.
	void tick();
	//This adds the score to the object.
	void add_score(int addend);
	//This directly sets the high score variable to what you have provided, no reading from files.
	void set_High_Score_Direct(int new_high_score);
	Scoring();
	
};

