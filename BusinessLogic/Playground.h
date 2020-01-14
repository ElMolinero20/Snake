#pragma once

#include <chrono>
#include <random>
#include <iostream>
#include <thread>
#include <vector>
#include "Control.h"
#include "../Data/Highscore.h"
#include <windows.h>

class Playground
{
public:
	Playground();
	~Playground();
	void drawPlayground();
	int getWidth();
	int getHeight();
	void getNewFood();
	void getNewBombs();
	bool moveSnake();
	void startGame();
	bool checkForGameover();

private:
	std::vector<int> tailX;
	std::vector<int> tailY;
	int width;
	int height;
	int headX;
	int headY;
	int oldHeadX;
	int oldHeadY;
	int foodX;
	int foodY;
	std::vector<int> bombX;
	std::vector<int> bombY;
	int score;
	int stateX;
	int stateY;
	int stateNewFoodBomb;
	int stateBlank;
	int stateGameover;
	Control control;
	Control oldDirection;
	std::string name;
	Highscore* highscore = new Highscore();
};

Playground::Playground()
{
	width = 20;
	height = 20;
}

Playground::~Playground()
{
	delete highscore;
}

void Playground::drawPlayground()
{
	int stateLiveHighscore;
	int stateDrawLiveHighscore = 0;
	int stateCountScores = 0;

	highscore->ReadData();
	highscore->SaveOldScores();
	highscore->WriteLiveScore(score);

	if (highscore->scores.size() < 10)
	{
		stateLiveHighscore = highscore->scores.size();
	}
	else
	{
		stateLiveHighscore = 10;
	}

	system("cls");

	for (int i = 0; i < getWidth(); i++)
	{
		std::cout << "#";
	}
	std::cout << " Score " << score;
	std::cout << std::endl;

	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			stateBlank = 0;

			if (j == 0)
			{
				std::cout << "#";
				stateBlank = 1;
			}

			if (i == headY && j == headX)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
				std::cout << "O";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				stateBlank = 1;
			}
			else if (j == foodX && i == foodY)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
				std::cout << "N";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				stateBlank = 1;
			}
			else
			{
				for (int m = 0; m < bombX.size(); m++)
				{
					if (bombX.at(m) == j && bombY.at(m) == i)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						std::cout << "B";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
						stateBlank = 1;
						break;
					}
				}
			}

			if (!tailX.empty())
			{
				for (int k = 0; k < tailX.size(); k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
						std::cout << "o";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
						stateBlank = 1;
						break;
					}
				}
			}

			if (stateBlank == 0 && j != getWidth() - 1)
			{
				std::cout << " ";
			}

			if (j == getWidth() - 1)
			{
				std::cout << "#";

				if (stateDrawLiveHighscore == 0)
				{
					std::cout << "\t\tLIVE-HIGHSCORE-TABLE";
					stateDrawLiveHighscore++;
				}
				else if (stateDrawLiveHighscore == 1)
				{
					std::cout << "\t\tName" << "\t\t" << "Score";
					stateDrawLiveHighscore++;
				}
				else if (stateLiveHighscore > 0)
				{
					if(highscore->stateName == stateCountScores && highscore->names[stateCountScores] == "LIVE")
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 36);
						std::cout << "\t\t" << highscore->names[stateCountScores] << "\t\t" << highscore->scores[stateCountScores];
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
					}
					else
					{
						std::cout << "\t\t" << highscore->names[stateCountScores] << "\t\t" << highscore->scores[stateCountScores];
					}

					stateCountScores++;
					stateLiveHighscore--;
				}
			}
		}

		std::cout << std::endl;
	}

	for (int i = 0; i < getWidth(); i++)
	{
		std::cout << "#";
	}
	std::cout << std::endl;

	highscore->DropLiveScore();
}

int Playground::getWidth()
{
	return width;
}

int Playground::getHeight()
{
	return height;
}

void Playground::getNewFood()
{
	int stateFood = 1;

	while (stateFood == 1)
	{
		stateFood = 0;

		srand(std::chrono::system_clock::now().time_since_epoch().count());
		foodX = (rand() % 18) + 1;
		foodY = (rand() % 18) + 1;

		if (foodX == headX && foodY == headY)
		{
			stateFood = 1;
			continue;
		}

		if (!tailX.empty())
		{
			for (int i = 0; i < tailX.size(); i++)
			{
				if (foodX == tailX[i] && foodY == tailY[i])
				{
					stateFood = 1;
					break;
				}
			}
		}
	}
}

void Playground::getNewBombs()
{
	int stateBomb = 1;

	while (stateBomb == 1)
	{
		stateBomb = 0;

		bombX.clear();
		bombY.clear();

		srand(std::chrono::system_clock::now().time_since_epoch().count());
		bombX.push_back((rand() % 18) + 1);
		bombX.push_back((rand() % 18) + 1);
		bombY.push_back((rand() % 18) + 1);
		bombY.push_back((rand() % 18) + 1);

		if (bombX[0] == bombX[1] && bombY[0] == bombY[1])
		{
			stateBomb = 1;
			continue;
		}

		for (int i = 0; i < 2; i++)
		{
			if ((bombX[i] == foodX && bombY[i] == foodY) || (bombX[i] == headX && bombY[i] == headY))
			{
				stateBomb = 1;
				break;
			}

			if (!tailX.empty())
			{
				for (int k = 0; k < tailX.size(); k++)
				{
					if (bombX[i] == tailX[k] && bombY[i] == tailY[k])
					{
						stateBomb = 1;
						break;
					}
				}

				if (stateBomb == 1)
				{
					break;
				}
			}
		}
	}
}

bool Playground::moveSnake()
{
	bool quitGame = false;
	stateNewFoodBomb = 0;

	oldHeadX = headX;
	oldHeadY = headY;

	if (control.getDirection() == BREAK)
	{
		std::cout << "Press a key to return" << std::endl;
		char selection;
		std::cin >> selection;
		control.setDirection(oldDirection.getDirection());
	}

	if (control.getDirection() == EXIT)
	{
		quitGame = true;
	}

	if (control.getDirection() == UP)
	{
		if (oldDirection.getDirection() == DOWN && !tailX.empty())
		{
			control.setDirection(oldDirection.getDirection());
			headY++;
		}
		else
		{
			headY--;
		}
	}
	else if (control.getDirection() == DOWN)
	{
		if (oldDirection.getDirection() == UP && !tailX.empty())
		{
			control.setDirection(oldDirection.getDirection());
			headY--;
		}
		else
		{
			headY++;
		}
	}
	else if (control.getDirection() == LEFT)
	{
		if (oldDirection.getDirection() == RIGHT && !tailX.empty())
		{
			control.setDirection(oldDirection.getDirection());
			headX++;
		}
		else
		{
			headX--;
		}
	}
	else if (control.getDirection() == RIGHT)
	{
		if (oldDirection.getDirection() == LEFT && !tailX.empty())
		{
			control.setDirection(oldDirection.getDirection());
			headX--;
		}
		else
		{
			headX++;
		}
	}

	if (headX == foodX && headY == foodY)
	{
		score++;
		stateNewFoodBomb = 1;

		if (tailX.size() < 2)
		{
			if (control.getDirection() == UP)
			{
				tailX.push_back(headX);
				tailY.push_back(headY + 1);
			}

			if (control.getDirection() == DOWN)
			{
				tailX.push_back(headX);
				tailY.push_back(headY - 1);
			}

			if (control.getDirection() == LEFT)
			{
				tailX.push_back(headX + 1);
				tailY.push_back(headY);
			}

			if (control.getDirection() == RIGHT)
			{
				tailX.push_back(headX - 1);
				tailY.push_back(headY);
			}
		}
		else
		{
			if (tailX[tailX.size() - 1] == tailX[tailX.size() - 2] && tailY[tailY.size() - 1] < tailY[tailY.size() - 2])
			{
				tailX.push_back(tailX[tailX.size() - 1]);
				tailY.push_back(tailY[tailY.size() - 1] - 1);
			}

			if (tailX[tailX.size() - 1] == tailX[tailX.size() - 2] && tailY[tailY.size() - 1] > tailY[tailY.size() - 2])
			{
				tailX.push_back(tailX[tailX.size() - 1]);
				tailY.push_back(tailY[tailY.size() - 1] + 1);
			}

			if (tailY[tailY.size() - 1] == tailY[tailY.size() - 2] && tailX[tailX.size() - 1] < tailX[tailX.size() - 2])
			{
				tailX.push_back(tailX[tailX.size() - 1] - 1);
				tailY.push_back(tailY[tailY.size() - 1]);
			}

			if (tailY[tailY.size() - 1] == tailY[tailY.size() - 2] && tailX[tailX.size() - 1] > tailX[tailX.size() - 2])
			{
				tailX.push_back(tailX[tailX.size() - 1] + 1);
				tailY.push_back(tailY[tailY.size() - 1]);
			}
		}
	}

	if (!tailX.empty())
	{
		for (int i = 0; i < tailX.size(); i++)
		{
			stateX = tailX[i];
			tailX[i] = oldHeadX;
			oldHeadX = stateX;

			stateY = tailY[i];
			tailY[i] = oldHeadY;
			oldHeadY = stateY;
		}
	}

	if (stateNewFoodBomb == 1)
	{
		getNewFood();
		getNewBombs();
	}

	oldDirection.setDirection(control.getDirection());

	Sleep(100);
	return quitGame;
}

bool Playground::checkForGameover()
{
	bool check = false;

	if (headX < 1 || headX >= width - 1 || headY < 0 || headY >= height)
	{
		check = true;
		stateGameover = 1;
	}
	else
	{
		for (int l = 0; l < bombX.size(); l++)
		{
			if (headX == bombX.at(l) && headY == bombY.at(l))
			{
				check = true;
				stateGameover = 2;
			}
		}
	}

	if (check == false)
	{
		for (int k = 0; k < tailX.size(); k++)
		{
			if (tailX[k] == headX && tailY[k] == headY)
			{
				check = true;
				stateGameover = 3;
			}
		}
	}

	return check;
}

void Playground::startGame()
{
	control.setDirection(STOP);
	headX = width / 2;
	headY = height / 2;
	getNewFood();
	getNewBombs();
	score = 0;

	while (!checkForGameover())
	{
		drawPlayground();
		control.getKey();
		if (moveSnake() == true)
		{
			break;
		}
	}

	tailY.clear();
	tailX.clear();

	system("cls");

	if (stateGameover == 1)
	{
		std::cout << "GAME OVER!" << std::endl << "You hit the wall!" << std::endl << "Your Score: " << score << std::endl;
	}

	if (stateGameover == 2)
	{
		std::cout << "GAME OVER!" << std::endl << "You exploded!" << std::endl << "Your Score: " << score << std::endl;
	}

	if (stateGameover == 3)
	{
		std::cout << "GAME OVER!" << std::endl << "You have bitten yourself!" << std::endl << "Your Score: " << score << std::endl;
	}

	std::cout << "Please enter your name: ";
	std::cin >> name;

	std::cout << std::endl;

	highscore->ReadData();
	highscore->WriteHighscore(name, score);
}