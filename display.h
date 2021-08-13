#pragma once
#include "engine.h"

class display
{
private:
	int height = 28;
	int width = getWidth() - 1;
	int key = 0;
	int cX, cY;
	int m_choice = 0;  //menu choice
	void penguins();	
	void penguins1();

	void init();
	int menu(int type, int choice);
public:

	display(Database data);	
};