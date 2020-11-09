#include "Player.h"
#include "Maze.h"

Player::Player(list<PathPoint*> path, char** array_maze)
{
	b_finish = false;
	count_turn_wait_ = 0;
	array_maze_ = array_maze;
	point_pos_ = nullptr;

	for (auto point_path : path)
	{
		list_path_.push_back(new PathPoint(point_path->y_, point_path->x_));
	}

	ite_path_ = list_path_.begin();
}

Player::~Player()
{
	if (!list_path_.empty())
	{
		for (auto point : list_path_)
		{
			delete point;
		}
		list_path_.clear();
	}

}

int Player::Move()
{
	if (!list_path_.empty())
	{
		if (ite_path_ != list_path_.end())
		{
			//cout<< (*(list_path_.end())->y_) << (*(list_path_.end())->x_)
			if (ite_path_ == list_path_.begin())
			{
				if (array_maze_[(*ite_path_)->y_][(*ite_path_)->x_] == Maze::kExit)
				{
					array_maze_[(*ite_path_)->y_][(*ite_path_)->x_] = Maze::kPlayer;
					//count_turn_wait_ = 0;
					return SetCountTurnWait(0);

				}
				else
				{
					if (array_maze_[(*ite_path_)->y_][(*ite_path_)->x_] == Maze::kPlayer)
					{
						array_maze_[(*ite_path_)->y_][(*ite_path_)->x_] = Maze::kExit;
					}

				}
			}

			ite_path_++;
			if (ite_path_ == list_path_.end())
			{
				ite_path_--;
				array_maze_[(*ite_path_)->y_][(*ite_path_)->x_] = Maze::kFinish;
				b_finish = true;
				return SetCountTurnWait(0);
			}
			if (array_maze_[(*ite_path_)->y_][(*ite_path_)->x_] != Maze::kPlayer)
			{
				ite_path_--;
				if (array_maze_[(*ite_path_)->y_][(*ite_path_)->x_] != Maze::kExit)
				{
					array_maze_[(*ite_path_)->y_][(*ite_path_)->x_] = Maze::kEmpty;
				}
				ite_path_++;
				array_maze_[(*ite_path_)->y_][(*ite_path_)->x_] = Maze::kPlayer;
				SetCountTurnWait(0);
			}
			else
			{
				ite_path_--;
				count_turn_wait_++;
				return SetCountTurnWait(count_turn_wait_);
				//return count_turn_wait_;
			}
		}
	}
	return SetCountTurnWait(0);
}

int Player::WaitaTurn()
{
	count_turn_wait_++;
	return count_turn_wait_;
}

bool Player::bFinished()
{
	return b_finish;
}

int Player::SetCountTurnWait(int count_turn_wait)
{
	//if (count_turn_wait == 0 && count_turn_wait_ >= 2)
	//{
	//	kCountPlayerWait--;
	//}
	count_turn_wait_ = count_turn_wait;
	//if (count_turn_wait_ >= 2)
	//{
	//	kCountPlayerWait++;
	//}
	return count_turn_wait_;
}


