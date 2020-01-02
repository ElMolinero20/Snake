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
	int lengthTail;
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
	Control control;
	std::string name;
	//Highscore* highscore = new Highscore();
};

Playground::Playground()
{
	width = 20;
	height = 20;
}

Playground::~Playground()
{
	//delete highscore;
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
				bool printed = false;
				for (int k = 0; k < lengthTail; k++)
				{
					if (tailX.at(k) == j && tailY.at(k) == i)
					{
						std::cout << "o";
						printed = true;
					}
				}
				if (!printed)
				{
					std::cout << " ";
				}
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
	tailX.push_back(headX);
	tailY.push_back(headY);
	int previousX = tailX.at(0);
	int previousY = tailY.at(0);
	int helperX;
	int helperY;
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
	}
	// Move tail of snake
	for (int i = 0; i < lengthTail; i++)
	{
		helperX = tailX.at(i);
		helperY = tailY.at(i);
		tailX.at(i) = previousX;
		tailY.at(i) = previousY;
		previousX = helperX;
		previousY = helperY;
	}
	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
	std::cout << "You lost the game" << std::endl << "Your Score: " << score;
	std::cout << "Please enter your name: ";
	std::cin >> name;

	//highscore->ReadData();
	//highscore->WriteHighscore(name, score);
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