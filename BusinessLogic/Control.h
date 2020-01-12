#pragma once

#include <conio.h>
#include "../ConsoleAccess/ConsoleAccessor.h"

enum Direction {
	UP,
	DOWN,
	RIGHT,
	LEFT,
	STOP
};

class Control
{
public:
	Control();
	~Control();
	void getKey();
	Direction getDirection();
	void setDirection(Direction dir);

private:
	Direction direction;
	ConsoleAccessor consoleAccessor;
};

Control::Control()
{
}

Control::~Control()
{
}

void Control::getKey()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			direction = UP;
			break;
		case 'a':
			direction = LEFT;
			break;	
		case 's':
			direction = DOWN;
			break;
		case 'd':
			direction = RIGHT;
			break;
		case 'x':
			// pause the game
			
		case 'esc':
			// terminate the game
			system("exit");
			break;
		default:
			break;
		}
	}
}

Direction Control::getDirection()
{
	return direction;
}

void Control::setDirection(Direction dir)
{
	direction = dir;
}