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
	int stateNewFoodBomb;
	int stateBlank;
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
				std::cout << "O";
				stateBlank = 1;
			}
			else if (j == foodX && i == foodY)
			{
				std::cout << "N";
				stateBlank = 1;
			}
			else
			{
				for (int m = 0; m < bombX.size(); m++)
				{
					if (bombX.at(m) == i && bombY.at(m) == j)
					{
						std::cout << "B";
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
						std::cout << "o";
						stateBlank = 1;
						break;
					}
				}
			}

			if(stateBlank == 0 && j != getWidth() - 1)
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

	for (int i = 0; i < getWidth(); i++)
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
	int stateFood = 1;

	while (stateFood == 1)
	{
		stateFood = 0;

		unsigned rd = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine gen(rd);
    	std::uniform_int_distribution<> dis(1, width - 2);
    	foodX = dis(gen);
		foodY = dis(gen);

		if(foodX == headX && foodY == headY)
		{
			stateFood = 1;
			continue;
		}

		if(!tailX.empty())
		{
			for(int i = 0; i < tailX.size(); i++)
			{
				if(foodX == tailX[i] && foodY == tailY[i])
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

	while(stateBomb == 1)
	{
		stateBomb = 0;

		bombX.clear();
		bombY.clear();

		unsigned rd = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine gen(rd);
    	std::uniform_int_distribution<> dis(1, width - 2);
    	bombX.push_back(dis(gen));
		bombX.push_back(dis(gen));
		bombY.push_back(dis(gen));
		bombY.push_back(dis(gen));

		if(bombX[0] == bombX[1] && bombY[0] == bombY[1])
		{
			stateBomb = 1;
			continue;
		}

		for(int i = 0; i < 2; i++)
		{
			if((bombX[i] == foodX && bombY[i] == foodY) || (bombX[i] == headX && bombY[i] == headY))
			{
				stateBomb = 1;
				break;
			}

			if(!tailX.empty())
			{
				for(int k = 0; k < tailX.size(); k++)
				{
					if(bombX[i] == tailX[k] && bombY[i] == tailY[k])
					{
						stateBomb = 1;
						break;
					}
				}

				if(stateBomb == 1)
				{
					break;
				}
			}
		}
	}
}

void Playground::moveSnake()
{
	stateNewFoodBomb = 0;

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

	if(stateNewFoodBomb == 1)
	{
		getNewFood();
		getNewBombs();
	}

	Sleep(100);
}

bool Playground::checkForGameover()
{
	bool check = false;

	if (headX < 1 || headX >= width - 1 || headY < 0 || headY >= height)
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
	for (int l = 0; l < bombX.size(); l++)
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
		moveSnake();
	}

	tailY.clear();
	tailX.clear();

	system("cls");
	std::cout << "You lost the game" << std::endl << "Your Score: " << score << std::endl;
	std::cout << "Please enter your name: ";
	std::cin >> name;

	std::cout << std::endl;

	highscore->ReadData();
	highscore->WriteHighscore(name, score);
}