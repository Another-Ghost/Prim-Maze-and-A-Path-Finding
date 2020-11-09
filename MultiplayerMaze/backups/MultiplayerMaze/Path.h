#pragma once
//#include <iostream>
#include <list>
#include <vector>
//#include "Maze.h"
using namespace std;
//using namespace std;
class Maze;

struct Point
{
	int x_;
	int y_;
	Point()
	{
		y_ = 0;
		x_ = 0;
	}
	Point(int y, int x) : y_(y), x_(x)
	{
	}
};

struct PathPoint : Point
{
	int y_;
	int x_;
	int F_;
	int G_;
	int H_;
	PathPoint* parent_;
	PathPoint(int y, int x) : y_(y), x_(x), F_(0), G_(0), H_(0), parent_(nullptr)
	{
	}
	//If need Deep Copy?
	//operatpr=()
	PathPoint(Point* point) :y_(point->y_), x_(point->x_), F_(0), G_(0), H_(0), parent_(nullptr)
	{
	}

	friend bool operator<(const PathPoint& p1, const PathPoint& p2)
	{
		return p1.F_ < p2.F_;
	}

	//friend class FLess;
};


class Path
{
	//using A* algorithm
private:

	Maze* maze_;
	list<PathPoint*> open_list_;
	list<PathPoint*> close_list_;

	vector<vector<PathPoint*>> open_array_;
	vector<vector<PathPoint*>> close_array_;

	//vector<PathPoint*> point_start_;
	//vector<PathPoint*> point_exit_;
	list<PathPoint*> list_path_;

public:
	//Path();
	Path(Maze* maze) :maze_(maze)
	{
	}

	void Generate(Maze* maze); //change to use &maze?

	PathPoint* FindPath(const PathPoint* point_start_, const PathPoint* point_exit_);

	list<PathPoint*> GetPath(const PathPoint* point_start, const PathPoint* point_exit);

	vector<PathPoint*> GetSurroundingPoint(const PathPoint* point) const;

	bool bReachable(const PathPoint* point_tar) const;

	PathPoint* GetLeastFPoint();

	PathPoint* InList(const list<PathPoint*>& list, const PathPoint* point_tar) const;

	int CalcG(PathPoint* point);
	int CalcH(const PathPoint* point, const PathPoint* point_exit) const;
	int CalcF(const PathPoint* point) const;

	void Draw();


	void ReleaseMemory();

};



