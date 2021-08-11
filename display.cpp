#include "display.h"
using namespace std;


void display::init()
{
	width = getWidth() - 1;
	TextColor(ColorCode_Yellow);
	for (int i = 0; i < width; i++) 
	{
		gotoXY(i, 0);
		cout << "=";
	}
	for (int i = 1; i < height; i++)
	{
		gotoXY(0, i);
		i % 2 ? cout << "|" : cout << "+";
		gotoXY(width, i);
		i % 2 ? cout << "|" : cout << "+";
	}
	//gotoXY(0, height);
	for (int i = 0; i < width; i++)
	{
		gotoXY(i, height);
		cout << "=";
	}
	cX = whereX(); cY = whereY();
	TextColor(default_ColorCode);
}

int display::menu(int type, int choice)
{
	if (type == 1)
	{
		const int max_choice = 4;
		int color[max_choice];

		choice < 0 ? choice = 0 : choice;
		choice > max_choice - 1 ? choice = max_choice - 1 : choice;

		for (int i = 0; i < max_choice; i++)
			color[i] = default_ColorCode;
		color[choice] = 20; 
				
		for (int i = 1; i < width; i++)
		{
			gotoXY(i, 1);
			TextColor(ColorCode_Green);
			cout << '-';
		}
		gotoXY(int(width / 2) - 2, 1);
		TextColor(ColorCode_Green);
		cout << "MENU";
		gotoXY(1, 2);
		TextColor(color[0]);
		cout << "1. Input query ";
		gotoXY(1, 3);
		TextColor(color[1]);
		cout << "2. Clear history ";
		gotoXY(1, 4);
		TextColor(color[2]);
		cout << "3. Clear screen ";
		gotoXY(1, 5);
		TextColor(color[3]);
		cout << "4. Exit ";
		return max_choice;
	}
	else if(type == 2)
	{
		//options
	}
}

display::display(Database data)
{
	penguins1(); //show logo

	clock_t begin, end;
	int max_choice;
	init();
	max_choice = menu(1, 0);
	for (;;)
	{
		key = inputKey();

		if (key == key_Up)
			choice < 0 ? choice = 0 : choice--;
		if (key == key_Down)
			choice > max_choice - 1 ? choice = max_choice - 1 : choice++;

		if (key != -1)
			menu(1, choice);

		if (key == 13)
		{
			SearchResult result;
			if (choice == 0)
			{
				clrscr();
				init();
				max_choice = menu(1, 0);

				int X, Y, X1, Y1 = 0, X_INPUT;
				int HM_CHOICE = 0;
				int _choice = -1;

				gotoXY(1, whereY() + 1);
				cout << "Query > ";
				X_INPUT = whereX();

				string query, s_tmp;
				int key = ' ';
				vector<string> res;
				while (key != '\r')
				{						
					key = inputKey();
					if (key == -1)
						continue;

					if (key < 1000)
					{
						s_tmp.push_back(char(key));
						cout << char(key);
					}
					if (key == 8)
					{			
						_choice = -1;
						s_tmp.clear();
						for (int i = X_INPUT; i < width; i++)
						{
							gotoXY(i, whereY());
							cout << ' ';							
						}
						gotoXY(X_INPUT, whereY());
					}

					else if (key == key_Up)
						_choice < -1 ? _choice = -1 : _choice--;

					else if (key == key_Down)
						_choice > HM_CHOICE ? _choice = HM_CHOICE : _choice++;
						
					X = whereX();  Y = whereY();
					
					if(Y1) for (int y = Y + 1; y <= Y1; y++)
						for (int i = 1; i < width - 1; i++)
						{
							gotoXY(i, y);
							cout << ' ';
						}
				
					gotoXY(1, Y + 1);

					if (key == key_enter)
					{ 
						if (_choice >= 1)
							query = res[_choice];
						else
							query = s_tmp;
						if ((_choice == 0 || _choice == -1) && !query.empty())
						{
							ofstream output; output.open("history.txt", ios::app);
							output << query << endl;
							output.close();
						}
						continue;
					}						
					
					HM_CHOICE = History(res, s_tmp, _choice);
					Y1 = whereY();
					gotoXY(X, Y);
				}
				Y = whereY() + 1;
				for (int i = 0; i < width; i++)
				{
					gotoXY(i, whereY());
					cout << "*";
				}

				gotoXY(int(width/2) -3, whereY() + 1);
				TextColor(ColorCode_Green);
				cout << "RESULT" << endl;
				TextColor(default_ColorCode);
				vector<string> tmp;

				begin = clock();
				tmp = searchResults(query, result, data);
				end = clock();

				int NumOfRes = 0;
				for (FileInfo info : result.GetInfos())
				{
					gotoXY(1, whereY());
					TextColor(ColorCode_Green);
					cout << "Title: ";
					TextColor(ColorCode_Blue);
					wcout << info.title << L"." << info.extension;
					gotoXY(1, whereY() + 1);
					TextColor(ColorCode_Green);
					cout << "Content: ";
					TextColor(default_ColorCode);
					gotoXY(1, whereY() + 1);
					OutputResult(info.content, tmp);
					for (int i = 0; i < width; i++)
					{
						gotoXY(i, whereY());
						cout << "-";
					}
					gotoXY(1, whereY() + 1);
					NumOfRes++;
				}

				cY > whereY() ? gotoXY(1, cY + 1) : gotoXY(1, whereY() + 1);
				TextColor(ColorCode_Green);
				cout << "Total result(s): " << NumOfRes << endl;
				cout << " Search time: " << (float)(end - begin) / CLOCKS_PER_SEC << "s" << endl;
				cout << " Output time: " << (float)(clock() - begin) / CLOCKS_PER_SEC << "s";
			}
			else if (choice == 1)
			{
				clrscr();
				init();
				clearHistory();
				cY > whereY() ?	gotoXY(1, cY + 1) : gotoXY(1, whereY() + 1);
				TextColor(ColorCode_Green);
				cout << "History has been cleared...............!!!";
				TextColor(default_ColorCode);
			}
			else if (choice == 2)
			{
				clrscr();
				init();
			}
			else
			{
				cY > whereY() ? gotoXY(1, cY + 1) : gotoXY(1, whereY() + 1);
				TextColor(10);
				penguins(); //show logo
				break; //exit
			}				
		}
	}
}

void display::penguins()
{
	cout << "                                           .&@@@@@@@@@@@@&                                " << endl;
	cout << "                                      *@@@@@@@@@@@@@@@@@@@@@@.                            " << endl;
	cout << "                                /&@@@@@@@@@@@@@@@#    @@@@@@@@@#                          " << endl;
	cout << "                                     .@@@@@@@@@@@@&,/@@@@@@@@@@@@(                        " << endl;
	cout << "                                        .@@@@@@@@@@@@@@@@@@@@@@@@@@.                      " << endl;
	cout << "                                         @@@@@@@@@@@@@@@@@@@@@@@@@@@@                     " << endl;
	cout << "                                         @@@@@@@@@@@@@@@@@@@@@@@@@@@@@,                   " << endl;
	cout << "                                        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                  " << endl;
	cout << "                                       @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                 " << endl;
	cout << "                                     .@@@@@@@@                  ,@@@@@@@@@*               " << endl;
	cout << "                                    /@@@@@@@.                     @@@@@@@@@%              " << endl;
	cout << "                                   %@@@@@@@@                     .@@@@@@@@@@%             " << endl;
	cout << "                                  &@@@@@@@@@@                   .@@@@@@@@@@@@(            " << endl;
	cout << "                                 &@@@@@@@@@@@@                 &@@@@@@@@@@@@@@.           " << endl;
	cout << "                                (@@@@@@@@@@@@@@,             (@@@@@@@@@@@@@@@@@           " << endl;
	cout << "                                @@@@@@# @@@@@@@@@          #@@@@@@@@@@@@@@@@@@@,          " << endl;
	cout << "                               *@@@@@@      &@@@@@%      @@@@@@@@@@@@*   @@@@@@%          " << endl;
	cout << "                               (@@@@@&                 @@@@@@@@@/        @@@@@@&          " << endl;
	cout << "                               ,@@@@@*                                   &@@@@@%          " << endl;
	cout << "                                @@@@@*                                   &@@@@@           " << endl;
	cout << "                                 @@@@(                                   @@@@@#           " << endl;
	cout << "                                  &@@@                                   @@@@(            " << endl;
	cout << "                                    @@.                                 (@@@              " << endl;
	cout << "                                      @                                 @@                " << endl;
	cout << "                                                                       *                  " << endl;
	cout << "                                            ////////,     ////////,                       " << endl;
	cout << "                                          .***********  ,***********                      " << endl;
}

void display::penguins1()
{	
	cout << "                                                                  ..                                     " << endl;
	cout << "                                                          ./&&%&&&&%&&/                                  " << endl;
	cout << "                                                      ,&&&&&&&&&&&&&&&&&&&,                              " << endl;
	cout << "                                                    /%&&&&&&&&&&&&&&&&&&&&&%/                            " << endl;
	cout << "                                                   &&&&#    ,&&&&&#      (&&&&                           " << endl;
	cout << "                                                  &&&%        .&&(        ,%&&&                          " << endl;
	cout << "                                                 %&&&          *&.   /.    #%&&%                         " << endl;
	cout << "                                                ,&&&*    /%(    @   /&&.   .&&&&,                        " << endl;
	cout << "                                                #&&&,    .&&  ,&#&/  (.     &&&&#                        " << endl;
	cout << "                                               .&&&&.      /&      %&       #&&&&                        " << endl;
	cout << "                                               &&&&           ,%&&*           &&%,                       " << endl;
	cout << "                                              %&&&                            .&&&(                      " << endl;
	cout << "                                            %&&&&&*                          /&&&&&&&*                   " << endl;
	cout << "                                          &&&&&&&&&&(.                    &%&&&&&&&&&&&&                 " << endl;
	cout << "                                        ,&&&&&&&%&&&&,                      /&&&&&%&&&&&&#               " << endl;
	cout << "                                       .&&&&&%.&&&,                             .%&&/%&&&&%              " << endl;
	cout << "                                       @&&&%.&&#                                   *&&/#&&&*             " << endl;
	cout << "                                       &&%/#&&                                       %&&,%&#             " << endl;
	cout << "                                       &&*%&&                                         %&%*&%             " << endl;
	cout << "                                       &#*&&.                                          &&/&%             " << endl;
	cout << "                                       & #&#                                           &&,&*             " << endl;
	cout << "                                         (&%                                          %&#                " << endl;
	cout << "                                          &&%                                        %%#                 " << endl;
	cout << "                                           .&&&,                                   .&%                   " << endl;
	cout << "                                              *&&&.                               (&.                    " << endl;
	cout << "                                                 %&#*//.       .(%%%#*.     *%&&&&,                      " << endl;
	cout << "                                              &&&&&&&&&&&&&&&&#       *&&&&&&&&&&&&%%##.                 " << endl;
	cout << "                                                                                                        " << endl;
}