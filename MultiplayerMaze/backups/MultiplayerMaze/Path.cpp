#include "Path.h"
#include "Maze.h"
#include <fstream>



void Path::Generate(Maze* maze)
{
	//maze_ = maze;
	//open_array_.resize(maze_->height_);
	//for (int i = 0; i < open_array_.size(); i++)
	//{
	//	open_array_[i].resize(maze_->width_);
	//}
	//close_array_.resize(maze_->height_);
	//for (int i = 0; i < close_array_.size(); i++)
	//{
	//	close_array_[i].resize(maze_->width_);
	//}


	//for (auto point_start : maze_->list_start_)
	//{
	//	for (auto point_exit : maze_->list_exit_)
	//	{
	//		auto path = GetPath(&PathPoint(point_exit), &PathPoint(point_start));
	//		for (auto point : path)
	//		{
	//			//if(point == path.front()&& point == path.back())
	//			//	continue;
	//			maze_->array_[point->y_][point->x_] = Maze::kPath;
	//		}
	//		maze_->array_[path.front()->y_][path.front()->x_] = Maze::kExit;
	//		maze_->array_[path.back()->y_][path.back()->x_] = Maze::kFinish;
	//		
	//	}
	//}
	//Draw();
}

PathPoint* Path::FindPath(const PathPoint* point_start, const PathPoint* point_exit)
{
	//shared_ptr<PathPoint> point(new PathPoint(point_start->x_, point_start->y_));
	open_list_.push_back(new PathPoint(point_start->y_, point_start->x_)); //release?
	while (!open_list_.empty())
	{
		auto point_cur = GetLeastFPoint();
		open_list_.remove(point_cur); //If cause begin point released?
		close_list_.push_back(point_cur);

		auto surrounding_point_list = GetSurroundingPoint(point_cur);
		for (auto point_tar : surrounding_point_list)
		{
			auto point_open = InList(open_list_, point_tar);
			point_tar->parent_ = point_cur;

			if (!point_open)
			{

				point_tar->G_ = CalcG(point_tar);
				point_tar->H_ = CalcH(point_tar, point_exit);
				point_tar->F_ = CalcF(point_tar);

				open_list_.push_back(point_tar);

				if ((point_tar->y_ == point_exit->y_) && (point_tar->x_ == point_exit->x_))
				{
					PathPoint* point_res = InList(open_list_, point_exit);
					if (point_res)
					{
						return point_res;
					}

				}
			}
			else
			{
				int G_cur = CalcG(point_tar);
				if (G_cur < point_open->G_)
				{
					point_open->parent_ = point_cur;

					point_open->G_ = G_cur;
					point_open->F_ = CalcF(point_open);
				}
				delete point_tar;
			}
		}
	}
	//ReleaseMemory();
	return nullptr;
}

list<PathPoint*> Path::GetPath(const PathPoint* point_start, const PathPoint* point_exit)
{
	PathPoint* point_result = FindPath(point_start, point_exit);
	//list<PathPoint*> path;

	PathPoint* point_pre;
	while (point_result)
	{
		list_path_.push_front(new PathPoint(point_result->y_, point_result->x_));
		point_pre = point_result;
		point_result = point_result->parent_;
		//delete point_pre;
	}

	return list_path_;
}

vector<PathPoint*> Path::GetSurroundingPoint(const PathPoint* point) const
{
	vector<PathPoint*> surounding_point_list;
	int y = point->y_;
	int x = point->x_;
	if (bReachable(&PathPoint(y - 1, x)))
	{
		surounding_point_list.push_back(new PathPoint(y - 1, x)); //Unreleased?
	}
	if (bReachable(&PathPoint(y + 1, x)))
	{
		surounding_point_list.push_back(new PathPoint(y + 1, x));
	}
	if (bReachable(&PathPoint(y, x - 1)))
	{
		surounding_point_list.push_back(new PathPoint(y, x - 1));
	}
	if (bReachable(&PathPoint(y, x + 1)))
	{
		surounding_point_list.push_back(new PathPoint(y, x + 1));
	}
	return surounding_point_list;
}

bool Path::bReachable(const PathPoint* point_tar) const
{
	if (point_tar->y_ < 0 || point_tar->y_ >(maze_->height_ - 1) ||
		point_tar->x_ < 0 || point_tar->x_ >(maze_->width_ - 1) ||
		maze_->array_[point_tar->y_][point_tar->x_] == Maze::kWall ||
		maze_->array_[point_tar->y_][point_tar->x_] == Maze::kPlayer ||
		//maze_->array_[point_tar->y_][point_tar->x_] == Maze::kExit ||
//		maze_->array_[point_tar->y_][point_tar->x_] == Maze::kPath ||
InList(close_list_, point_tar))
	{
		return false;
	}
	return true;
}

PathPoint* Path::GetLeastFPoint()
{
	if (!open_list_.empty())
	{
		auto point_res = open_list_.front();
		for (auto& point : open_list_)
		{
			if (point->F_ < point_res->F_)
			{
				point_res = point;
			}
		}
		return point_res;
	}
	return nullptr;
}

PathPoint* Path::InList(const list<PathPoint*>& list, const PathPoint* point_tar) const
{
	for (auto point : list)
	{
		if (point->y_ == point_tar->y_ && point->x_ == point_tar->x_)
		{
			return point;
		}
	}
	return nullptr;
}

int Path::CalcG(PathPoint* point)
{
	if (point->parent_)
		return point->parent_->G_ + 1;
	return 0;
}

int Path::CalcH(const PathPoint* point, const PathPoint* point_exit) const
{
	return abs(point->y_ - point_exit->y_) + abs(point->x_ - point_exit->x_);
}

int Path::CalcF(const PathPoint* point) const
{
	return point->G_ + point->H_;
}

void Path::Draw()
{
	for (int i = 0; i < maze_->height_; i++)
	{
		for (int j = 0; j < maze_->width_; j++)
		{
			cout << maze_->array_[i][j];
		}
		cout << endl;
	}
}

void Path::ReleaseMemory()
{
	if (!open_list_.empty())
	{
		for (auto point : open_list_)
		{
			delete point;
		}
		open_list_.clear(); // If it will release memory?
	}
	if (!close_list_.empty())
	{
		for (auto point : close_list_)
		{
			delete point;
		}
		close_list_.clear();
	}

	if (!list_path_.empty())
	{
		for (auto point : list_path_)
		{
			delete point;
		}
		list_path_.clear();
	}
}







