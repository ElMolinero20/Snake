#include <iostream>
#include "../ConsoleAccess/ConsoleAccessor.cpp"
#include "../BusinessLogic/Playground.cpp"
#include "../Data/Highscore.cpp"

int main()
{
	/*ConsoleAccessor* csAccessor = new ConsoleAccessor();
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
	delete playground;*/

	Highscore* highscore = new Highscore();

	highscore->ReadData();
	highscore->WriteHighscore("Müller", 12);
}