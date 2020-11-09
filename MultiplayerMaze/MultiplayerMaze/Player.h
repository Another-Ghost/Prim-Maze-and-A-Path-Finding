#pragma once
//#include "Path.h"
#include <list>
#include <vector>

using namespace std;

class Maze;
class Path;
struct PathPoint;

class Player
{

private:
	char** array_maze_;

	int count_turn_wait_;
	PathPoint* point_pos_;

	vector<PathPoint*> list_path_;
	vector<PathPoint*>::iterator ite_path_;

	bool b_finish;

private:
	int WaitaTurn();

	int SetCountTurnWait(int count_turn_wait);


public:

	Player(list<PathPoint*> path, char** array_maze);

	~Player();

	int Move();

	bool bFinished();

	//static int kCountPlayerWait;
	//static Maze* maze_;
	//bool b_waiting_;

	//static void SetArrayMaze(Maze* maze);

};

