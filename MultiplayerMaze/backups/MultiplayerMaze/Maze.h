#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "Path.h"
#include "Player.h"

using namespace std;

enum Direction
{
	kNull,
	kNorth,
	kEast,
	kSouth,
	kWest,
};

struct Wall
{
	int y_;
	int x_;
	Direction dir_;
	Wall(int y = 0, int x = 0, Direction dir = Direction::kNull)
	{
		y_ = y;
		x_ = x;
		dir_ = dir;
	}
};



class Maze
{
private:

	int height_;
	int width_;
	//int x_cur_; //position of currently selected  vertex
	//int y_cur_;
	//Direction dir_cur_; //Orientation of the wall

	int start_num_;
	vector<Point*> list_start_; //Is Finish List for cw2
	int count_exit_;
	vector<Point*> list_exit_; //Is Entry List for cw2

	char** array_;

	char** array_base_;
	vector<Wall> wall_list_; //use BST(set) instead of vector?

	Path* path_;
	vector<Player*> list_player_;
	//int count_player_;
	int no_player_cur_;
	int count_player_finish;

	static const char kWall = 'X';
	static const char kStart = 'S';
	static const char kFinish = 'F';
	static const char kExit = 'E';
	static const char kEmpty = ' ';
	static const char kPath = 'o';
	static const char kPlayer = 'P';
	
public:


	//Initialization list?
	Maze();

	Maze(int height, int width, int count_exit) :height_(height), width_(width), count_exit_(count_exit), start_num_(1), array_(nullptr), no_player_cur_(0),count_player_finish(0),path_(nullptr)
	{
	}

	~Maze();

	void Generate();

	void Regenerate(int height, int width, int count_exit);

	bool bPassable(const int y, const int x, const Direction dir);

	void AddWall(const int y_cur_, const int x_cur_);

	void ReleaseMemory();

	//void GenerateRandomExit();
	void UpdateMazeBase();

	void Draw();

	void SaveToFile(const string& name = "NewFile");

	void LoadFromFile(string name);

	bool bSuitableExit(const int y, const int x) const;

	

	void GeneratePath(bool b_generate_player);

	void DrawPath(list<PathPoint*> list_path);

	void ResetToMazeBase();

	void GeneratePlayer(list<PathPoint*> list_path);

	bool MoveInTurns(bool b_how);

	vector<int> list_turn_wait_;

	void Reset(int height = 0, int width = 0, int count_exit = 0);

	bool bDeadLock();


	bool b_end_normal_;

	friend class Path;

	friend class Player;

};


