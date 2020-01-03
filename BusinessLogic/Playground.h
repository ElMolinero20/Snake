#pragma once

#include <random>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include "Control.h"
#include "../Data/Highscore.h"

class Playground
{
public:
	Playground();
	~Playground();
	void drawPlayground();
	int getWidth();
	int getHeight();
	void getNewFood();
	void moveSnake();
	void startGame();
	bool checkForGameover();
	void moveTail();
	void incrementSnake();
	std::vector<int> tailX;
	std::vector<int> tailY;

private:
	bool gameOver;
	int width;
	int height;
	int headX;
	int headY;
	int foodX;
	int foodY;
	int score;
	int lengthTail;
	Control control;
	std::string name;
	Highscore* highscore;
};

Playground::Playground()
{
	width = 20;
	height = 20;
}

Playground::~Playground()
{
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

void Playground::moveSnake()
{
	int previousX = headX;
	int previousY = headY;
	int helperX;
	int helperY;
	for (int i = 1; i < lengthTail; i++)
	{
		helperX = tailX.at(i);
		helperY = tailY.at(i);
		tailX.at(i) = previousX;
		tailY.at(i) = previousY;
		previousX = helperX;
		previousY = helperY;
	}
	// Move head of snake
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
		lengthTail++;
		// incrementSnake();
	}

	// Move tail of snake
	/*if (!(tailX.empty() && tailY.empty()))
	{
		moveTail();
	}*/

	// Reduce the speed of the game by delaying the thread
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Playground::startGame()
{
	gameOver = false;
	control.setDirection(STOP);
	headX = width / 2;
	headY = height / 2;
	getNewFood();
	score = 0;
	while (!checkForGameover())
	{
		drawPlayground();
		control.getKey();
		moveSnake();
		checkForGameover();
	}

	system("cls");
	std::cout << "You lost the game" << std::endl << "Your Score: " << score << std::endl;
	std::cout << "Please enter your name: ";
	std::cin >> name;

	highscore->ReadData();
	highscore->WriteHighscore(name, score);
}

bool Playground::checkForGameover()
{
	if (headX < 0 || headX > width - 1 || headY < 0 || headY > height - 1)
	{
		return true;
	}
	// TODO: When snake bites itself -> gameover
	return false;
}

void Playground::moveTail()
{
	for (int i = tailX.size() - 1; i >= 0; i--)
	{
		if (i == 0)
		{
			tailX.at(0) = headX;
		}
		else
		{
			tailX.at(i) = tailX.at(i - 1);
		}
	}

	for (int i = tailY.size() - 1; i >= 0; i--)
	{
		if (i == 0)
		{
			tailY.at(0) = headY;
		}
		else
		{
			tailX.at(i) = tailX.at(i - 1);
		}
	}
}

void Playground::incrementSnake()
{
	if ((tailX.empty() && tailY.empty()) || tailX.size() == 1)
	{
		switch (control.getDirection())
		{
		case UP:
			tailX.push_back(headX);
			tailY.push_back(headY + 1);
			break;
		case DOWN:
			tailX.push_back(headX);
			tailY.push_back(headY - 1);
			break;
		case LEFT:
			tailX.push_back(headX + 1);
			tailY.push_back(headY);
			break;
		case RIGHT:
			tailX.push_back(headX - 1);
			tailY.push_back(headY);
			break;
		default:
			system("cls");
			std::cout << "An error ocurred" << std::endl;
			break;
		}
	}
	else
	{
		Direction tailDir;
		if (tailX.at(tailX.size()) == tailX.at(tailX.size() - 1))
		{
			if (tailY.at(tailY.size()) > tailY.at(tailY.size() - 1))
			{
				tailDir = UP;
			}
			else if (tailY.at(tailY.size()) < tailY.at(tailY.size() - 1))
			{
				tailDir = DOWN;
			}
		}
		else if (tailY.at(tailY.size()) == tailY.at(tailY.size() - 1))
		{
			if (tailX.at(tailX.size()) > tailX.at(tailX.size() - 1))
			{
				tailDir = LEFT;
			}
			else if (tailX.at(tailX.size()) < tailX.at(tailX.size() - 1))
			{
				tailDir = RIGHT;
			}
		}
		else
		{

		}

		switch (tailDir)
		{
		case UP:
			tailX.push_back(tailX.at(tailX.size()));
			tailY.push_back(tailY.at(tailY.size()) + 1);
			break;
		case DOWN:
			tailX.push_back(tailX.at(tailX.size()));
			tailY.push_back(tailY.at(tailY.size()) - 1);
			break;
		case RIGHT:
			tailX.push_back(tailX.at(tailX.size()) - 1);
			tailY.push_back(tailY.at(tailY.size()));
			break;
		case LEFT:
			tailX.push_back(tailX.at(tailX.size()) + 1);
			tailY.push_back(tailY.at(tailY.size()));
			break;
		default:
			system("cls");
			std::cout << "An error ocurred" << std::endl;
			break;
		}
	}
}
