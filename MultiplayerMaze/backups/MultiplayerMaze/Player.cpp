#include "Player.h"
#include "Maze.h"
//#include "Path.h"

Player::Player(PathPoint* point, char** array_maze)
{
	point_pos_ = nullptr;

	//if (point != nullptr)
	//{
	//	PathPoint* point_pre = point;
	//	point = point->parent_;
	//	point_pre->parent_ = nullptr;
	//	PathPoint* point_next;
	//	while (point->parent_ != nullptr)
	//	{
	//		point_next = point->parent_;
	//		point->parent_ = point_pre;
	//		point_pre = point;
	//		point = point_next;
	//	}
	//	point->parent_ = point_pre;
	//	point_pos_ = point;
	//}

	b_finish = false;
	count_turn_wait_ = 0;
	array_maze_ = array_maze;
	
	PathPoint* point_pre;
	while (point)
	{
		PathPoint* point_pre;
		list_path_.push_back(new PathPoint(point->y_, point->x_));
		point_pre = point;
		point = point->parent_;
		delete point_pre;
	}

}

Player::Player(list<PathPoint*> path, char** array_maze)
{
	b_finish = false;
	count_turn_wait_ = 0;
	array_maze_ = array_maze;
	point_pos_ = nullptr;
	no_path_ = -1;

	for (auto point_path : path)
	{
		list_path_.push_back(new PathPoint(point_path->y_, point_path->x_));
	}

	ite_path_ = list_path_.begin();
}

//Player::Player(list<PathPoint*> & path, char** array_maze)
//{
//	PathPoint* point_pre = nullptr;
//	
//	for (auto point_path : path)
//	{
//		point_pos_ =  new PathPoint(point_path->x_, point_path->y_);
//		point_pos_->parent_ = point_pre;
//		point_pre = point_pos_;
//	}
//	b_finish = false;
//	num_turn_wait_ = 0;
//
//	array_maze_ = array_maze;
//}

Player::~Player()
{
	//if (point_pos_ != nullptr)
	//{
	//	delete point_pos_;
	//}
	if (!list_path_.empty())
	{
		
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
		//else
		//{
		//	ite_path_--;
		//	array_maze_[(*ite_path_)->y_][(*ite_path_)->x_] = Maze::kFinish;
		//	b_finish = true;
		//}
	}
	return SetCountTurnWait(0);
}

//	if (point_pos_)
//	{
//		if (point_pos_->parent_)
//		{
//			if (array_maze_)
//			{
//				if (array_maze_[point_pos_->parent_->y_][point_pos_->parent_->x_] != Maze::kPlayer)
//				{
//					//if (array_maze_[point_pos_->parent_->y_][point_pos_->parent_->x_] == Maze::kFinish)
//					//{
//					//	b_finish = true;
//					//}
//					//else
//					//{
//					if (array_maze_[point_pos_->y_][point_pos_->x_] != Maze::kExit)
//					{
//						array_maze_[point_pos_->y_][point_pos_->x_] = Maze::kEmpty;
//					}
//					PathPoint* point_pre = point_pos_;
//					point_pos_ = point_pos_->parent_;
//					delete point_pre;
//					array_maze_[point_pos_->y_][point_pos_->x_] = Maze::kPlayer;
//					//}
//					num_turn_wait_ = 0;
//				}
//				else
//				{
//					WaitaTurn();
//					return false;
//				}
//			}
//		}
//		else
//		{
//			b_finish = true;
//			array_maze_[point_pos_->y_][point_pos_->x_] = Maze::kFinish;
//		}
//	}
//	else
//	{
//		//b_finish = true;
//	}
//	return true;
//}

int Player::WaitaTurn()
{
	count_turn_wait_++;
	return count_turn_wait_;
}

bool Player::bFinished()
{
	return b_finish;
}

int Player::GetNumTurnWait()
{
	return count_turn_wait_;
}

int Player::SetCountTurnWait(int count_turn_wait)
{
	if (count_turn_wait == 0 && count_turn_wait_ >= 2)
	{
		kCountPlayerWait--;
	}

	count_turn_wait_ = count_turn_wait;
	if (count_turn_wait_ >= 2)
	{
		kCountPlayerWait++;
	}
	return count_turn_wait_;
}

//void Player::SetArrayMaze(Maze* maze)
//{
//	maze_->array_ = maze->array_;
//}

