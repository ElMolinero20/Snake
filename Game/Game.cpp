#include <iostream>
#include "../ConsoleAccess/ConsoleAccessor.cpp"
#include "../BusinessLogic/Playground.cpp"

int main()
{
	ConsoleAccessor* csAccessor = new ConsoleAccessor();
	Playground playground;
	playground.drawPlayground();
	delete csAccessor;
}