#include <iostream>

class Playground
{
public:
	Playground();
	~Playground();
	void drawPlayground();
	int getWidth();
	int getHeight();

private:
	int width;
	int height;
};