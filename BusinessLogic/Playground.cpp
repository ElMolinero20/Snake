#include <random>
#include "Control.cpp"
#include <iostream>

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

private:
	int width;
	int height;
	int headX;
	int headY;
	int foodX;
	int foodY;
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
			if (j == foodX && i == foodY)
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
}

void Playground::startGame()
{
	drawPlayground();
}
