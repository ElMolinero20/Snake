#include "Playground.h"

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
	for (int i = 0; i < getWidth(); i++)
	{
		std::cout << "#";
	}

	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			if (j == 0)
			{
				std::cout << "#";
				std::cout << " ";
			}
			if (j == getWidth() - 1)
			{
				std::cout << "#";
			}
		}
	}

	for (int i = 0; i < getWidth(); i++)
	{
		std::cout << "#";
	}
}

int Playground::getWidth()
{
	return width;
}

int Playground::getHeight()
{
	return height;
}
