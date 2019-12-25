#include <random>
#include <iostream>
#include <thread>
#include "Control.h"

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
	std::uniform_int_distribution<> dis(1, width);
	foodX = dis(gen);
	foodY = dis(gen);
}

void Playground::moveSnake()
{
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
	}
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
	if (checkForGameover())
	{
		system("cls");
		std::cout << "You lost the game" << std::endl;
	}
}

bool Playground::checkForGameover()
{
	if (headX < 0 || headX > width || headY < 0 || headY > height)
	{
		return true;
	}
	// TODO: When snake bites itself -> gameover
	return false;
}
