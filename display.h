#pragma region Belong to Nhat
#include "engine.h"
// print result and decorate to screen
class display
{
private:
	int height = 25;
	int width = getWidth() - 1;
	int key = 0;
	int cX, cY;
	int m_choice = 0;  //menu choice
	void penguins();	
	void penguins1();
	// interface shaping
	void init();
	int menu(int type, int choice);
public:

	display(Database data);
};