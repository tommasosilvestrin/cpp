#include "Maze.h"
#include <iostream>
#include <RandomRobot.h>
#include <RightHandRuleRobot.h>
using namespace std;

int main() {
	Maze myMaze("map1.txt");

	RightHandRuleRobot robot {};

	int randomMoveCount = 0;

	while (!myMaze.is_exit()) {
		robot.move(myMaze);
		cout << "Position: (" << myMaze.get_current_position()[0] << ", " << myMaze.get_current_position()[1] << ")" << endl;
		randomMoveCount++;
	}

	cout << "Robot took " << randomMoveCount << " moves to exit the maze." << endl;

	
	return 0;
}