#include "display.h"
using namespace std;


void display::init()  //create box
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

int display::menu(int type, int choice)  //menu
{
	if (type == 1)
	{
		const int max_choice = 4;
		int color[max_choice];

		choice < 0 ? choice = 0 : int();
		choice > max_choice - 1 ? choice = max_choice - 1 : int();

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
	return 0;
}

display::display(Database data)
{
	penguins1(); //show logo

	clock_t begin, end;
	int max_choice;
	init();
	max_choice = menu(1, -1);

	vector<string> res;		//store history choice
	vector<FileInfo> info;
	SearchResult result;
	vector<string> tmp;
	vector<int> y_pos;  //store positions

	for (;;)
	{
		key = inputKey();

		if (key == key_Up)
			m_choice < 0 ? m_choice = 0 : m_choice--;
		if (key == key_Down)
			m_choice > max_choice - 1 ? m_choice = max_choice - 1 : m_choice++;

		if (key != -1)
			menu(1, m_choice);

		if (key == 13)
		{
			if (m_choice == 0)
			{
				clrscr();
				init();
				max_choice = menu(1, 0);  //max of menu choice

				int X, Y, X1, Y1 = 0, X_INPUT, Y_END;
				int HM_CHOICE = 0;		//max of history choice
				int choice = -1;		//history choice

				gotoXY(1, whereY() + 1);
				cout << "Query > ";
				X_INPUT = whereX();

				string query = "";
				int key = ' ';
				
				res.clear();
				info.clear();

				while (key != key_enter)
				{						
					key = inputKey();
					if (key == key_none)
						continue;

					if (key == key_esc)
						break;

					if (key == key_backspace)
					{			
						choice = -1;
						query.empty() ? void() : query.pop_back();

						cout << char(key);			
						cout << ' ';
						whereX() > X_INPUT ? gotoXY(whereX() - 1, whereY()) : void();						
					}
					else if (key < 1000 && key != key_enter)
					{
						query.push_back(char(key));
						cout << char(key);
					}
					else if (key == key_Up)
						choice < -1 ? choice = -1 : choice--;

					else if (key == key_Down)
						choice > HM_CHOICE ? choice = HM_CHOICE : choice++;
						
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
						if (choice >= 1)
							query = res[choice];

						if ((choice == 0 || choice == -1) && !query.empty())
						{
							ofstream output; output.open("history.txt", ios::app);	//store history
							output << query << endl;
							output.close();
						}
						continue;
					}						
					
					HM_CHOICE = History(res, query, choice);	
					Y1 = whereY();
					gotoXY(X, Y);
				}

				if (query.empty())		//if the user does not enter anything, they will return to the homepage
				{
					clrscr();
					init();
					menu(1, 0);
					continue;
				}

				tmp.clear();

				begin = clock();
				tmp = searchResults(query, result, data);
				end = clock();
				info = result.GetInfos();

			goBack:						//go back here

				for (int i = 0; i < width; i++)
				{
					gotoXY(i, whereY());
					cout << "*";
				}
			
				gotoXY(int(width/2) -3, whereY() + 1);
				TextColor(ColorCode_Green);
				cout << "RESULT              <'ESC' key to exit search>" << endl;		
				gotoXY(int(width / 2) - 3, whereY());
				cout << "                    <'BACKSPACE' key to go back>" << endl;			//it's like chrome go back button
				TextColor(default_ColorCode);

				Y = whereY();

				y_pos.clear();

				int NumOfRes = 0;
				for (int i = 0; i < info.size(); i++)
				{
					gotoXY(1, whereY());

					y_pos.push_back(whereY());

					TextColor(ColorCode_Green);					
					cout << "Title: ";
					TextColor(ColorCode_Blue);
					cout << string(info[i].title.begin(), info[i].title.end()) << "." << string(info[i].extension.begin(), info[i].extension.end());

					gotoXY(1, whereY() + 1);
					TextColor(ColorCode_Green);
					cout << "Content: ";
					TextColor(default_ColorCode);
					gotoXY(1, whereY() + 1);
					OutputResult(info[i].content, tmp);  //stealing part of the content

					for (int i = 0; i < width; i++)
					{
						gotoXY(i, whereY());
						cout << "-";
					}
					gotoXY(1, whereY() + 1);
					NumOfRes++;
				}
				Y_END = whereY();
				cY > whereY() ? gotoXY(1, cY + 1) : gotoXY(1, whereY() + 1);
				TextColor(ColorCode_Green);
				cout << "Total result(s): " << NumOfRes << endl;
				cout << " Search time: " << (float)(end - begin) / CLOCKS_PER_SEC << "s" << endl;
				cout << " Output time: " << (float)(clock() - begin) / CLOCKS_PER_SEC << "s";

				if (info.size() <= 0)
				{
					gotoXY(3, Y+3);
					TextColor(ColorCode_Red);
					cout << "Your search - ";
					TextColor(ColorCode_Green);
					cout << query;
					TextColor(ColorCode_Red);
					cout << " - did not match any documents." << endl;
					TextColor(default_ColorCode);
					gotoXY(3, whereY());
					cout << "Suggestions:" << endl;
					gotoXY(5, whereY());
					cout << "+ Make sure all words are spelled correctly. " << endl;
					gotoXY(5, whereY());
					cout << "+ Try different keywords." << endl;
					gotoXY(5, whereY());
					cout << "+ Try more general keywords." << endl;
					gotoXY(5, whereY());
					cout << "+ Try fewer keywords." << endl;
					continue;
				}
					

				int r_choice = 0; // r_choice : result choice
				for(;;)  // results
				{
					key = inputKey();

					if (key == key_none)
						continue;

					if (key == key_Up)
					{
						r_choice <= 0 ? r_choice = 0 : r_choice--;
					}

					if (key == key_Down)
					{
						r_choice >= info.size() - 1 ? r_choice = info.size() - 1 : r_choice++;
					}
				

					for (int i = 0; i < info.size(); i++)
					{
						gotoXY(1, y_pos[i]);
						TextColor(ColorCode_Green);
						cout << "Title: ";
						i == r_choice ? TextColor(20) : TextColor(ColorCode_Blue);
						wcout << info[i].title.c_str() << L"." << info[i].extension.c_str();
						TextColor(default_ColorCode);
					}

					if (key == key_enter)
					{
						for(int i = y_pos[0]; i <= Y_END; i++)
							for (int z = 1; z < width; z++)
							{
								TextColor(default_ColorCode);
								gotoXY(z, i); cout << ' ';
							}

						gotoXY(1, y_pos[0]);

						TextColor(ColorCode_Green);
						cout << "Title: ";
						TextColor(ColorCode_Blue);
						cout << string(info[r_choice].title.begin(), info[r_choice].title.end()) << "." << string(info[r_choice].extension.begin(), info[r_choice].extension.end());
						TextColor(ColorCode_Green);
						cout << "Content: " << endl;
						TextColor(default_ColorCode);
						cout << string(info[r_choice].content.begin(), info[r_choice].content.end()) << endl;
						//convert Wstring to String because Wstring can't print spectial character

						for (int i = 0; i < width; i++)
						{
							gotoXY(i, whereY());
							cout << "=";
						}

						while (key != key_esc)
						{
							key = inputKey();

							if (key == key_backspace || key == key_enter)  // go back
							{
								clrscr();
								init();
								max_choice = menu(1, 0);
								goto goBack;
							}								
						}							
					}

					if (key == key_esc)			// 'ESC' key to break
					{
						clrscr();
						init();
						max_choice = menu(1, 0);
						break;
					}
				}
			}
			else if (m_choice == 1)
			{
				clrscr();
				init();
				max_choice = menu(1, 0);
				clearHistory();
				cY > whereY() ?	gotoXY(1, cY + 1) : gotoXY(1, whereY() + 1);
				TextColor(ColorCode_Green);
				cout << "History has been cleared...............!!!";
				TextColor(default_ColorCode);
			}
			else if (m_choice == 2)
			{
				clrscr();
				init();
				max_choice = menu(1, 0);
				cY > whereY() ? gotoXY(1, cY + 1) : gotoXY(1, whereY() + 1);
				TextColor(ColorCode_Green);
				cout << "Screen has been cleared...............!!!";
				TextColor(default_ColorCode);
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