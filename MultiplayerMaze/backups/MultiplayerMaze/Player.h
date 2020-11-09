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

	int count_turn_wait_;
	PathPoint* point_pos_;
	vector<PathPoint*> list_path_;
	vector<PathPoint*>::iterator ite_path_;

	bool b_finish;

	char** array_maze_;

	int no_path_;


public:

	Player(PathPoint* point, char** array_maze);

	Player(list<PathPoint*> path, char** array_maze);

	~Player();

	int Move();

	int WaitaTurn();

	bool bFinished();

	int GetNumTurnWait();


	int SetCountTurnWait(int count_turn_wait);
	//static Maze* maze_;
	//bool b_waiting_;

	static int kCountPlayerWait; //name criteria?

	//static void SetArrayMaze(Maze* maze);

};

