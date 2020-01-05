#include <iostream>
#include "../ConsoleAccess/ConsoleAccessor.h"
#include "../BusinessLogic/Playground.h"
#include "../Data/Highscore.h"

int main()
{
	ConsoleAccessor* csAccessor = new ConsoleAccessor();
	Playground* playground = new Playground();
	Highscore* highscore = new Highscore();

	//Switch-Case muss noch in einer Schleife gebaut werden damit das Hauptmenu immer angezeigt wird
	//nachdem Gameover ist oder die Highscore-Tabelle angezeigt wurde und nur mit der Nummer 3 wird 
	//dann das Spiel beendet!

	switch (csAccessor->showMainMenu())
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
		std::cout << "Invalid Selection! Please select a corresponding number" << std::endl;
		break;
	}
	delete csAccessor;
	delete playground;
	delete highscore;
}