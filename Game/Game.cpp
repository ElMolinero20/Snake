#include <iostream>
#include "../ConsoleAccess/ConsoleAccessor.h"
#include "../BusinessLogic/Playground.h"
#include "../Data/Highscore.h"

int main()
{
	ConsoleAccessor* csAccessor = new ConsoleAccessor();
	Playground* playground = new Playground();

	switch (csAccessor->showMainMenu())
	{
	case 1:
		playground->startGame();
		break;
	case 2:
		//csAccessor->showHighscore();
		break;
	case 3:
		system("exit");
		break;
	default:
		std::cout << "Invalid Selection! Please select a corresponding number" << std::endl;
		break;
	}
	delete csAccessor;
	delete playground;
}