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
	void moveSnake();
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
	int stateTail;
	int stateBomb;
	Control control;
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
	system("cls");
	for (int i = 0; i < getWidth() + 2; i++)
	{
		std::cout << "#";
	}
	std::cout << " Score " << score;
	std::cout << std::endl;

	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			if (j == 0)
			{
				std::cout << "#";
			}
			if (i == headY && j == headX)
			{
				std::cout << "O";
			}
			else if (j == foodX && i == foodY)
			{
				std::cout << "N";
			}
			else if (!tailX.empty())
			{
				stateTail = 0;

				for (int k = 0; k < tailX.size(); k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						std::cout << "o";
						stateTail = 1;
						break;
					}
				}

				if (stateTail == 0)
				{
					std::cout << " ";
				}
			}
			else if (!(bombX.empty() && bombY.empty()))
			{
				stateBomb = 0;

				for (int m = 0; m < bombX.size(); m++)
				{
					if (bombX.at(m) == i && bombY.at(m) == j)
					{
						std::cout << "B";
						stateBomb = 1;
						break;
					}
				}

				if (stateBomb == 0)
				{
					std::cout << " ";
				}
			}
			else
			{
				std::cout << " ";
			}
			if (j == getWidth() - 1)
			{
				std::cout << "#";
			}
		}

		std::cout << std::endl;
	}

	for (int i = 0; i < getWidth() + 2; i++)
	{
		std::cout << "#";
	}
	std::cout << std::endl;
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
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, width - 1);
	foodX = dis(gen);
	foodY = dis(gen);
}

void Playground::getNewBombs()
{
	for (int i = 0; i < 2; i++)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(1, width - 1);
		bombX.push_back(dis(gen));
	}
	for (int i = 0; i < 2; i++)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(1, width - 1);
		bombY.push_back(dis(gen));
	}
}

void Playground::moveSnake()
{
	oldHeadX = headX;
	oldHeadY = headY;

	switch (control.getDirection())
	{
	case UP:
		headY--;
		break;
	case DOWN:
		headY++;
		break;
	case RIGHT:
		headX++;
		break;
	case LEFT:
		headX--;
		break;
	default:
		break;
	}

	if (headX == foodX && headY == foodY)
	{
		score++;
		getNewFood();
		getNewBombs();

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

	Sleep(100);
}

bool Playground::checkForGameover()
{
	bool check = false;

	if (headX < 1 || headX >= width - 1 || headY < 1 || headY >= height - 1)
	{
		check = true;
	}
	else
	{
		for (int k = 0; k < tailX.size(); k++)
		{
			if (tailX[k] == headX && tailY[k] == headY)
			{
				check = true;
			}
		}
	}
	for (int l = 0; l < bombX.size() - 1; l++)
	{
		if (headX == bombX.at(l) && headY == bombY.at(l))
		{
			check = true;
		}
	}

	return check;
}

void Playground::startGame()
{
	control.setDirection(RIGHT);
	headX = width / 2;
	headY = height / 2;
	getNewFood();
	getNewBombs();
	score = 0;

	while (!checkForGameover())
	{
		drawPlayground();
		control.getKey();
		moveSnake();
	}

	system("cls");
	std::cout << "You lost the game" << std::endl << "Your Score: " << score << std::endl;
	std::cout << "Please enter your name: ";
	std::cin >> name;

	highscore->ReadData();
	highscore->WriteHighscore(name, score);
}