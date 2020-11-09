#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Maze.h"
#include "Path.h"
#include <string>

using namespace std;

//int Player::kCountPlayerWait = 0;

int main()
{
	while (true)
	{
		srand((unsigned)time(NULL));

		cout << "A venturer! Welcome." << endl;
		cout << "Please tell me the size of the maze:" << endl;
		int maze_size;
		cin >> maze_size;
		while (cin.fail() || maze_size < 5)
		{
			cout << "The size must be a number not less than 5, please input again: " << endl;
			cin.clear();
			cin.ignore();
			cin >> maze_size;
		}
		cout << "Next,tell me the number of the exits:" << endl;
		int exit_num;
		cin >> exit_num;
		while (cin.fail() || exit_num < 1)
		{
			cout << "The number of the exits must be a number not less than 1, please input again: " << endl;
			cin.clear();
			cin.ignore();
			cin >> exit_num;
		}


		Maze maze(maze_size, maze_size, exit_num);
		maze.Generate();
		maze.Draw();
		//maze.GeneratePath(true);
		//Path path;
		//path.Generate(&maze);

		string input;
		string maze_name_pre;

		while (true)
		{
			//maze.Draw();
			cout <<endl << "Menu:" << endl;
			cout << "s: save current maze" << endl;
			cout << "l: load previous saved maze" << endl;
			cout << "p: generate paths" << endl;
			cout << "o: operate the maze with players" << endl;
			cout << "i: show some interesting things" << endl;
			cout << "r: restart" << endl;
			cout << "q: quit the game" << endl;

			//cout << "Input 's' to save, 'l' to load, 'r' to restart and 'q' to quit: ";
			cin >> input;
			if (input == "s")
			{
				string maze_name;
				cout << "Please input the name of the maze: " << endl;
				cin >> maze_name;
				maze_name += ".txt";
				maze.SaveToFile(maze_name);
				maze_name_pre = maze_name;
			}
			if (input == "l")
			{
				//if (!maze_name_pre.empty())
				//{
					maze.LoadFromFile(maze_name_pre);
					maze.Draw();
				//}
				//else
				//{
					//cout << "Please save first. " << endl;
				//}
			}
			if (input == "p")
			{
				maze.GeneratePath(false);
				maze.Draw();
				maze.ResetToMazeBase();
			}
			if (input == "r")
			{
				//maze.Regenerate(10, 10, 2);
				maze.ReleaseMemory();
				system("cls");
				break;
			}
			if (input == "q")
			{
				maze.ReleaseMemory();
				system("cls");
				cout << "Good day! " << endl;
				exit(0);
			}
			if (input == "o")
			{
				maze.GeneratePath(true);
				bool b_finish;
				string input_o;
				while (true)
				{
					maze.Draw();
					cout << endl << "Menu:" << endl;
					cout << "n: next turn" << endl;
					cout << "q: quit" << endl;
					cin >> input_o;
					if (input_o == "n")
					{
						if (!maze.MoveInTurns(true))
						{
							cout << "All players have finished." << endl;
							break;
						}
					}
					if (input_o == "q")
					{
						maze.ResetToMazeBase();
						break;
					}

				}
			}
			if (input == "i")
			{
				system("cls");
				cout << "Please tell me the size of the maze:" << endl;
				int size_maze_i;
				cin >> size_maze_i;
				while (cin.fail() || size_maze_i < 5)
				{
					cout << "The size must be a number not less than 5, please input again: " << endl;
					cin.clear();
					cin.ignore();
					cin >> size_maze_i;
				}
				cout << "Next,tell me the number of players:" << endl;
				int num_exit_i;
				cin >> num_exit_i;
				while (cin.fail() || num_exit_i < 1)
				{
					cout << "The number of players must be a number not less than 1, please input again: " << endl;
					cin.clear();
					cin.ignore();
					cin >> num_exit_i;
				}
				cout << "Finally,tell me time of generating new maze and operating with players:" << endl;
				int times_operate_i;
				cin >> times_operate_i;
				while (cin.fail() || times_operate_i < 1)
				{
					cout << "The time must be a number not less than 1, please input again: " << endl;
					cin.clear();
					cin.ignore();
					cin >> times_operate_i;
				}
				int count_dead_lock = 0;
				int times_i = times_operate_i;
				while (times_i--)
				{
					maze.Regenerate(size_maze_i, size_maze_i, num_exit_i);
					maze.GeneratePath(true);
					maze.AutoOperate();
					if (maze.bEndNormal() == false)
					{
						count_dead_lock++;
					}
				}
				float percent_deadlock = (count_dead_lock / times_operate_i) * 100;
				cout << "Randomly generated mazes of size " << size_maze_i << " x " << size_maze_i << " " << times_operate_i << " times." << endl
					<< "There are " << count_dead_lock << " times deadlock scenario happened, accounting for " << percent_deadlock << "%." << endl
					<< "p.s. There will not be any deadlock or livelock scenarios happening in this program in view of testing. " << endl;
			}
		}
	}
	//system("pause");
	return 0;
}


