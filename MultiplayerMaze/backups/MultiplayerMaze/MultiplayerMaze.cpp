#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Maze.h"
#include "Path.h"
#include <string>

using namespace std;

int Player::kCountPlayerWait = 0;

int count_dead_lock = 0;
int num_run = 50;

int main()
{

	Player::kCountPlayerWait = 0;
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
	cout << "Please tell me the number of the exits:" << endl;
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
	maze.GeneratePath(true);
	//Path path;
	//path.Generate(&maze);
	//maze.Draw();

	string input;
	string maze_name_pre;
	//while (num_run--)
	//{
	//	Player::kCountPlayerWait = 0;
	//	maze.Regenerate(maze_size, maze_size, exit_num);
	//	maze.GeneratePath(true);
	//	if (!maze.b_end_normal_)
	//	{
	//		cout << ++count_dead_lock;
	//	}
	//}

		while (true)
		{
			cout << "Menu:" << endl;
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
				if (!maze_name_pre.empty())
				{
					maze.LoadFromFile(maze_name_pre);
				}
				else
				{
					cout << "Please save first. " << endl;
				}
			}
			if (input == "p")
			{
				maze.GeneratePath(false);
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
				cout << "Good day! " << endl;
				exit(0);
			}
			if (input == "o")
			{
				maze.GeneratePath(true);
				bool b_finish;
				string input_o;
				while (1)
				{
					cin >> input_o;
					if (input_o == "n")
					{
						if (!maze.MoveInTurns(true))
						{
							break;
						}
					}
					if (input_o == "q")
					{

					}
					
				}				
			}
		}
	
	//system("pause");
	return 0;
}


