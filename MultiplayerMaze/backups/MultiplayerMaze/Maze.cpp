#include "Maze.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include<stdlib.h>

Maze::Maze()
{
	height_ = 20;
	width_ = 20;
	start_num_ = 1;

	count_exit_ = 2;
	array_ = nullptr;

	//count_player_ = 0;
	no_player_cur_ = 0;
	count_player_finish = 0;
}

Maze::~Maze()
{
	ReleaseMemory();
}



void Maze::Generate()
{
	//srand((unsigned)time(NULL));
	

	array_ = new char* [height_];
	for (int i = 0; i < height_; i++)
	{
		array_[i] = new char[width_];
	}


	for (int i = 0; i < height_; i++)
	{
		for (int j = 0; j < width_; j++)
		{
			array_[i][j] = 'X';
		}
	}

	int height_mid = height_ / 2;
	int width_mid = width_ / 2;
	list_start_.push_back(new Point(height_mid, width_mid));
	for (int i = height_mid - 1; i <= height_mid + 1; i++)
	{
		for (int j = width_mid - 1; j <= width_mid + 1; j++)
		{
			array_[i][j] = ' ';
			AddWall(i, j);
		}
	}
	array_[height_mid][width_mid] = kFinish; //If use #define?

	int count_exit_cur = 0;
	while (!wall_list_.empty())
	{
		int length = wall_list_.size();
		int rand_num = rand() % length;

		int y_cur = wall_list_[rand_num].y_;
		int x_cur = wall_list_[rand_num].x_;
		Direction dir_cur = wall_list_[rand_num].dir_;

		switch (dir_cur)
		{
		case kNorth:
			y_cur--;

			break;
		case kEast:
			x_cur++;
			break;
		case kSouth:
			y_cur++;
			break;
		case kWest:
			x_cur--;
			break;
		}
		if (y_cur > 0 && y_cur < (height_ - 1) && x_cur > 0 && x_cur < (width_ - 1))
		{
			if (array_[y_cur][x_cur] == kWall)
			{
				if (bPassable(y_cur, x_cur, dir_cur))
				{
					array_[y_cur][x_cur] = kEmpty;
					AddWall(y_cur, x_cur);
				}
			}
		}
		else
		{
			if ((count_exit_ - count_exit_cur) > 0)
			{
				//adjacency problem? 

				if (bSuitableExit(y_cur, x_cur))
				{
					array_[y_cur][x_cur] = kExit;
					list_exit_.push_back(new Point(y_cur, x_cur));
					count_exit_cur++;
				}
			}
		}
		wall_list_.erase(wall_list_.begin() + rand_num);
	}

	UpdateMazeBase();
	Draw();

//	Player::SetArrayMaze(this); //If need to move to other place?
}

void Maze::Regenerate(int height, int width, int count_exit)
{
	ReleaseMemory();
	Reset(height, width, count_exit);
	Generate();
	
	//Draw();
}


bool Maze::bPassable(const int y, const int x, const Direction dir)
{
	switch (dir)
	{
	case kEast:
		if (array_[y][x + 1] != kWall || array_[y - 1][x] != kWall || array_[y + 1][x] != kWall)
		{
			return false;
		}
		break;
	case kNorth:
		if (array_[y - 1][x + 1] != kWall || array_[y][x - 1] != kWall || array_[y][x + 1] != kWall)
		{
			return false;
		}
		break;
	case kSouth:
		if (array_[y + 1][x] != kWall || array_[y][x - 1] != kWall || array_[y][x + 1] != kWall)
		{
			return false;
		}
		break;
	case kWest:
		if (array_[y][x - 1] != kWall || array_[y - 1][x] != kWall || array_[y + 1][x] != kWall)
		{
			return false;
		}
		break;
	}
	return true;
}

void Maze::AddWall(const int y, const int x)
{
	if (y - 1 >= 0 && (array_[y - 1][x] == kWall))
		wall_list_.push_back(Wall(y, x, Direction::kNorth));
	if (y + 1 <= (height_ - 1) && (array_[y + 1][x] == kWall))
		wall_list_.push_back(Wall(y, x, Direction::kSouth));
	if (x - 1 >= 0 && (array_[y][x - 1] == kWall))
		wall_list_.push_back(Wall(y, x, Direction::kWest));
	if (x + 1 <= (width_ - 1) && (array_[y][x + 1] == kWall))
		wall_list_.push_back(Wall(y, x, Direction::kEast));
}

void Maze::ReleaseMemory()
{
	//If validation is needed?
	//cout << array_[2][0] << endl;
	if (array_ != nullptr) {
		for (int i = 0; i < height_; i++)
		{
			delete[] array_[i];
		}
		delete[] array_;
	}
	array_ = nullptr;

	if (array_base_ != nullptr) {
		for (int i = 0; i < height_; i++)
		{
			delete[] array_base_[i];
		}
		delete[] array_base_;
	}
	array_base_ = nullptr;

	if (!list_start_.empty())
	{
		for (auto point : list_start_)
		{
			delete point;
		}
		list_start_.clear();
	}

	if (!list_exit_.empty()) 
	{
		for (auto point : list_exit_)
		{
			delete point;
		}
		list_exit_.clear();
	}

	if (path_)
	{
		delete path_;
	}
	path_ = nullptr;

	if (!list_player_.empty())
	{
		for (auto player : list_player_)
		{
			delete player;
		}
		list_player_.clear();
	}
}

void Maze::UpdateMazeBase()
{
	array_base_ = new char* [height_];
	for (int i = 0; i < height_; i++)
	{
		array_base_[i] = new char[width_];
	}

	for (int i = 0; i < height_; i++)
	{
		for (int j = 0; j < width_; j++)
		{
			array_base_[i][j] = array_[i][j];
		}
	}
}

void Maze::Draw()
{
	for (int i = 0; i < height_; i++)
	{
		for (int j = 0; j < width_; j++)
		{
			cout << array_[i][j];
		}
		cout << endl;
	}
}

void Maze::SaveToFile(const string& name)
{
	ofstream out_file(name, fstream::out);
	try 
	{
		if (out_file.fail())
			throw name;
	}
	catch (string s)
	{
		cout << "save file:[" << s << "] failed" << endl;
		//exit(1);
		return;
	}
	if (out_file.is_open())
	{
		for (int i = 0; i < height_; i++)
		{
			for (int j = 0; j < width_; j++)
			{
				out_file << array_base_[i][j];
			}
			out_file << endl;
		}
	}
	out_file.close();
}

void Maze::LoadFromFile(string name)
{
	ifstream in_file;
	in_file.open(name);

	try {
		if (in_file.fail())
			throw name;
	}
	catch (string s)
	{
		 cout << "open file:[" << s << "] failed" << endl;
		 //exit(1);
		 return;
	}

	//while(infile.get())
	if (in_file.is_open())
	{
		string line;
		in_file >> line;
		int size = line.size();
		ReleaseMemory();
		Reset();
		array_ = new char* [size];
		for (int i = 0; i < size; i++)
		{
			array_[i] = new char[size];
		}
		for (int i = 0; i < size; i++)
		{
			array_[0][i] = line[i];
		}

		in_file.get();
		for (int i = 1; i < size; i++)
		{
			//infile >> line;
			for (int j = 0; j < size; j++)
				//in_file.getline(array_[i], size + 1);
				in_file.get(array_[i][j]);
			in_file.get();
		}

		height_ = size;
		width_ = size;
		for (int i = 0; i < height_; i++)
		{
			for (int j = 0; j < width_; j++)
			{
				if (array_[i][j] == kExit) //kExit to kEntry
				{
					count_exit_++;
					list_exit_.push_back(new Point(i, j));
				}
				if (array_[i][j] == kFinish)
				{
					start_num_++;
					list_start_.push_back(new Point(i, j));
				}
			}
		}
		UpdateMazeBase();

		Draw();
	}
	in_file.close();
	//in_file.clear();
}

bool Maze::bSuitableExit(const int y, const int x) const
{
	if (array_[y][x] == kExit)
	{
		return false;
	}
	if (y == 0 || y == height_ - 1)
	{
		if (x + 1 < width_)
		{
			if (array_[y][x + 1] == kExit)
				return false;
		}
		if ((x - 1) > 0)
		{
			if (array_[y][x - 1] == kExit)
				return false;
		}
	}

	if (x == 0 || x == width_ - 1)
	{
		if (y + 1 < width_)
		{
			if (array_[y + 1][x] == kExit)
				return false;
		}
		if ((y - 1) > 0)
		{
			if (array_[y - 1][x] == kExit)
				return false;
		}
	}

	return true;
}

void Maze::GeneratePath(bool b_generate_player)
{
	path_ = new Path(this);

	for (auto point_start : list_start_)
	{
		for (auto point_exit : list_exit_)
		{
			//PathPoint* point_path = path_->FindPath(&PathPoint(point_exit), &PathPoint(point_start));

			//if (b_generate_player)
			//{
			//	GeneratePlayer(point_path);
			//}
			//path_->ReleaseMemory();

			list<PathPoint*> list_path = path_->GetPath(&PathPoint(point_exit), &PathPoint(point_start));
			if (b_generate_player)
			{
				list_player_.push_back(new Player(list_path, array_));
			}
			else
			{
				DrawPath(list_path);
			}

			path_->ReleaseMemory();
		}
	}

	b_end_normal_ = true;
	list_turn_wait_.resize(list_player_.size());
	Draw();
	ResetToMazeBase();
	//while (MoveInTurns(true))
	//{
	//}
}

void Maze::DrawPath(list<PathPoint*> list_path)
{

		for (auto point : list_path)
		{
			//if(point == path.front()&& point == path.back())
			//	continue;
			array_[point->y_][point->x_] = Maze::kPath;
		}
		array_[list_path.front()->y_][list_path.front()->x_] = Maze::kExit;
		array_[list_path.back()->y_][list_path.back()->x_] = Maze::kFinish; 
		
}

void Maze::ResetToMazeBase()
{

	for (int i = 0; i < height_; i++)
	{
		for (int j = 0; j < width_; j++)
		{
			array_[i][j] = array_base_[i][j]; 
		}
	}
	for (int i = 0; i < height_; i++)
	{
		for (int j = 0; j < width_; j++)
		{
			if (array_[i][j] == kExit) //kExit to kEntry
			{
				count_exit_++;
				list_exit_.push_back(new Point(i, j));
			}
			if (array_[i][j] == kFinish)
			{
				start_num_++;
				list_start_.push_back(new Point(i, j));
			}
		}
	}
}

void Maze::GeneratePlayer(list<PathPoint*> list_path)
{
	list_player_.push_back(new Player(list_path, array_));
}

bool Maze::MoveInTurns(bool b_show)
{
	if (count_player_finish >= list_player_.size())
	{
		return false;
	}

	if (!list_player_[no_player_cur_]->bFinished())
	{
		list_turn_wait_[no_player_cur_] = list_player_[no_player_cur_]->Move();

		if (list_player_[no_player_cur_]->bFinished())
		{
			count_player_finish++;
		}
		if (b_show)
		{
			system("cls");
			Draw();
		}
	}
	no_player_cur_++;
	if (no_player_cur_ >= list_player_.size())
	{
		no_player_cur_ = 0;
		if (bDeadLock())
		{
			cout << "DeadLock!" << endl;
			b_end_normal_ = false;
			return false;
		}
	}
	//if (bDeadLock())
	//{
	//	cout << "DeadLock!" << endl;
	//	b_end_normal_ = false;
	//	return false;
	//}

	return true;
}

void Maze::Reset(int height, int width, int count_exit)
{
	height_ = height;
	width_ = width;
	count_exit_ = count_exit;
	start_num_ = 0;
	no_player_cur_ = 0;
	count_player_finish = 0;
}

bool Maze::bDeadLock()
{
	//if (Player::kCountPlayerWait >= list_player_.size())
	//{
	//	return true;
	//}
	//return false;
	for (auto count_turn_wait : list_turn_wait_)
	{
		if (count_turn_wait <= 1)
			return false;
	}
	return true;
}

















