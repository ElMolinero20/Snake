#include <conio.h>

enum Direction {
	UP,
	DOWN,
	RIGHT,
	LEFT
};

class Control
{
public:
	Control();
	~Control();
	void getKey();
	Direction getDirection();

private:
	Direction direction;
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
		case 'W':
			direction = UP;
			break;
		case 'A':
			direction = LEFT;
			break;	
		case 'S':
			direction = DOWN;
			break;
		case 'D':
			direction = RIGHT;
			break;
		case 'X':
			//TODO: Go back to main menu
			break;
		case 'ESC':
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
