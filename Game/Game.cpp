#include <iostream>
#include "../ConsoleAccess/ConsoleAccessor.h"
#include "../BusinessLogic/Playground.h"
#include "../Data/Highscore.h"

int main()
{
	ConsoleAccessor* csAccessor = new ConsoleAccessor();
	Playground* playground = new Playground();
	Highscore* highscore = new Highscore();

	system("color 06");

	int stateMenu = 0;

	while (stateMenu != 3)
	{
		stateMenu = csAccessor->showMainMenu();

		switch (stateMenu)
		{
		case 1:
			playground->startGame();
			break;
		case 2:
			highscore->ReadData();
			csAccessor->showHighscore(highscore->names, highscore->scores);
			break;
		case 3:
			system("exit");
			break;
		default:
			std::cout << "Invalid Selection! Please select a corresponding number!" << std::endl;
			break;
		}
	}

	delete csAccessor;
	delete playground;
	delete highscore;
}