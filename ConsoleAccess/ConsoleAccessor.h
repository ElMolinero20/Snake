#pragma once

#include <vector>

class ConsoleAccessor
{
public:
	ConsoleAccessor();
	~ConsoleAccessor();
	int showMainMenu();
	void showHighscore(std::vector<std::string> names, std::vector<int> scores);
private:

};

ConsoleAccessor::ConsoleAccessor()
{
}

ConsoleAccessor::~ConsoleAccessor()
{
}

int ConsoleAccessor::showMainMenu()
{
	int selection = 0;
	std::cout << "Please select the corresponding number: " << std::endl;
	std::cout << "1 --> Play" << std::endl;
	std::cout << "2 --> Show Highscoretable" << std::endl;
	std::cout << "3 --> Exit" << std::endl;
	std::cin >> selection;
	return selection;
}

void ConsoleAccessor::showHighscore(std::vector<std::string> names, std::vector<int> scores)
{
	std::cout << "Name" << "\t\t" << "Score" << std::endl;
	
	for (int i = 0; i < names.size(); i++)
	{
		std::cout << names.at(i) << "\t\t" << scores.at(i) << std::endl;
	}
}