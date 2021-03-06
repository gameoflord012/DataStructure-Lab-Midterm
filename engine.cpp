#include "engine.h"

//----------------ENGINE-----------------------
vector<string> searchResults(string query, SearchResult& results, Database database)
{
	vector<string> data;
	stringstream ss(query);
	string tmp, get;
	string _get;
	while (ss >> tmp)
	{
		tmp = SentenceFilter(tmp);  //lowercase
		get = tmp.substr(0, 8);//intitle:
		
		if (tmp[0] == '$') //search range
		{
			if (!_get.empty()) _get.pop_back();
			data.push_back(_get);
			_get = "";
		}

		if (tmp[0] == '#') // Hashtag
		{
			if (!_get.empty()) _get.pop_back();
			data.push_back(_get);
			_get = "";
		}

		if (get == "intitle:")
		{
			get = tmp.substr(8);
			if (!_get.empty()) _get.pop_back();
			data.push_back(_get);
			data.push_back("intitle:");
			data.push_back(get);
			_get = "";
			continue;
		}

		get = tmp.substr(0, 9);//filetype:
		if (get == "filetype:")
		{
			get = tmp.substr(9);
			if (!_get.empty()) _get.pop_back();
			data.push_back(_get);
			data.push_back("filetype:");
			data.push_back(get);
			_get = "";
			continue;
		}

		if (tmp[0] == '"') //exact match and wildcard
		{
			//if (!_get.empty()) _get.pop_back();
			//data.push_back(_get);
			tmp.erase(tmp.begin(), tmp.begin() + 1);
			if (tmp.back() != '"')
			{
				bool check = false;
				do
				{
					if (tmp.back() == '"')
					{
						check = true;
						tmp.erase(tmp.end() - 1, tmp.end());
					}

					data.push_back(tmp);
					data.push_back("AND");

					if (check)
						break;
				} while (ss >> tmp);
			}
			else
			{
				tmp.erase(tmp.end() - 1, tmp.end());
				data.push_back(tmp);
			}				
		}
		else if (tmp[0] == '~')
		{
			data.push_back("sym");
			tmp.erase(tmp.begin(), tmp.begin() + 1);
			data.push_back(tmp);
		}

		else if (tmp == "or")
		{
			if (!_get.empty()) _get.pop_back();
			data.push_back(_get);
			data.push_back("OR");
			_get = "";
		}
		else if (tmp == "and" || tmp == "+")
		{
			if (!_get.empty()) _get.pop_back();
			data.push_back(_get);
			data.push_back("AND");
			_get = "";
		}
		else if (tmp == "-")
		{
			if (!_get.empty()) _get.pop_back();
			data.push_back(_get);
			data.push_back("-");
			_get = "";
		}
		else if (database.CointainStopWord(wstring(tmp.begin(), tmp.end())))
			continue;
		else
			_get += tmp + " ";
	}

	if (!_get.empty()) _get.pop_back();
	data.push_back(_get);

	for (int i = 0; i < data.size(); i++) if (data[i] == "" || data[i] == " ") data.erase(data.begin() + i);

	searchData(data, results, database);

	return data;  //don't care it ??\_(???)_/??
}

void searchData(vector<string>& data, SearchResult& result, Database database)
{
	int choice = -1;
	int type = 0;
	string tmp, get;
	for (auto i = data.begin(); i != data.end(); ++i)
	{
		//cout << "DEBUG: " << *i << endl;

		tmp = *i;
		if (tmp == "OR")
		{
			choice = 0;
		}
		else if (tmp == "AND")
		{
			choice = 1;
		}
		else if (tmp == "-")
		{
			choice = 2;
		}
		else if (tmp == "intitle:")
		{
			type = 1;
		}
		else if (tmp == "sym")
		{
			type = 2;
		}
		else if (tmp == "filetype:")
		{
			type = 5;
		}
		else if (tmp != " " || tmp != "")
		{
			int num1, num2;
			bool num = false;
			if (tmp[0] == '$')
			{
				num = getRange(tmp, num1, num2);
				if (num) type = 3;
			}
			if (tmp[0] == '#')
			{
				tmp.erase(tmp.begin(), tmp.begin() + 1);
				type = 4;
			}
			wstring _get;
			_get = wstring(tmp.begin(), tmp.end());
			SearchResult tmp_result;

			switch (type) {
			case 0:
				tmp_result = database.GetResults(SearchInfo(_get, SearchType::word));
				type = 0;
				break;
			case 1:
				tmp_result = database.GetResults(SearchInfo(_get, SearchType::title));
				type = 0;
				break;
			case 2:
				tmp_result = database.GetResults(SearchInfo(_get, SearchType::synonyms));
				type = 0;
				break;
			case 3:
				tmp_result = database.GetResults(SearchInfo(num1, num2));
				type = 0;
				break;
			case 4:
				tmp_result = database.GetResults(SearchInfo(_get, SearchType::hashTag));
				type = 0;
				break;
			case 5:
				tmp_result = database.GetResults(SearchInfo(_get, SearchType::extension));
				type = 0;
				break;
			default:
				tmp_result = database.GetResults(SearchInfo(_get, SearchType::word));
				type = 0;
				break;
			};

			if (choice == -1) 
			{
				result = tmp_result;
			}
			else if (choice == 0)
			{
				result = result.OR(tmp_result);
			}
			else if (choice == 1)
			{
				result = result.AND(tmp_result);
			}
			else if (choice == 2)
			{
				result = result.EXCLUDE(tmp_result);
			}
		}
	}
}

//------------GET NUMBER----------------------
bool getRange(string tmp, int& num1, int& num2)
{
	string n1, n2;
	string get;
	bool check = false;

	reverse(tmp.begin(), tmp.end());
	while (!tmp.empty())
	{
		if (tmp.back() == '$')
		{
			tmp.pop_back();
			continue;
		}
		if (tmp.back() == '-')
		{
			check = true;
			tmp.pop_back();
			continue;
		}

		if (!check)
		{
			n1 += tmp.back();
		}
		else
		{
			n2 += tmp.back();
		}
		tmp.pop_back();
	}

	n1.empty() ? n1 = n2 : n1;
	n2.empty() ? n2 = n1 : n2;

	num1 = atof(n1.c_str());
	num2 = atof(n2.c_str());

	return true;
}

//-----------------HISTORY---------------------
int History(vector<string>& res, string query, int choice)
{
	res.clear();
	query = SentenceFilter(query);
	res.push_back(query);
	if (query.empty())
		return 0;
	TextColor(ColorCode_Green);
	cout << "Suggestions:";
	TextColor(default_ColorCode);
	gotoXY(1, whereY() + 1);

	choice == 0 ? TextColor(20) : TextColor(7);
	cout << "0. " << query;
	TextColor(default_ColorCode);
	int i = 1;
	ifstream input; input.open("history.txt");
	string tmp;
	while (!input.eof())
	{
		getline(input, tmp);
		tmp = SentenceFilter(tmp);

		if (tmp == "" || query == tmp || tmp.find(query) == -1 || any_of(res.begin(), res.end(), [&](string& elem) { return elem == tmp; }))
		{
			continue;
		}

		res.push_back(tmp);
		gotoXY(1, whereY() + 1);
		if (choice == i)
			TextColor(20);
		cout << i << ". " << tmp;
		TextColor(default_ColorCode);
		++i;
	}
	input.close();
	return i;
}

void clearHistory()
{
	ifstream file;
	file.open("history.txt", ios::out | ios::trunc);
	file.close();
}


//------------------OPTIONS------------------------
void OutputResult(wstring data, vector<string> word)
{
	if (word.empty())
		return;

	string tmp;
	stringstream _ss(string(data.begin(), data.end()));

	while (!_ss.eof())
	{
		tmp.clear();
		getline(_ss, tmp, '.');  //take 2 sentences
		if (tmp.length() && is_Number(tmp.back()))  //decimal number case
		{
			string next; getline(_ss, next, '.');
			if (next.length() && is_Number(next[0]))
			{
				tmp = tmp + '.' + next;
			}
			else
				tmp = tmp + " " + next;
		}

		tmp = SentenceFilter(tmp);

		//if (!any_of(word.begin(), word.end(), [&](string elem) {if (tmp.find(elem) != -1) return true; return false;}))
		//	continue;

		bool check = false;
		string s;
		stringstream _ss_(tmp);
		vector<string> _word_;
		while (_ss_ >> s)
		{
			for (int i = 0; i < word.size(); i++)
			{
				if (s == word[i])
				{
					check = true;
					_word_.push_back(word[i]);
					word.erase(word.begin() + i);
					break;
				}
			}
		}

		if (!check)
			continue;

		cout << "...";
		stringstream ss(tmp);
		while (ss >> tmp)
		{
			bool _check_ = false;
			for (string _tmp_ : _word_)
			{
				_tmp_ = SentenceFilter(_tmp_);
				if (_tmp_ == tmp)
				{
					_check_ = true;
					break;
				}
			}

			if (_check_)
			{
				for (int i = 0; i < tmp.length(); ++i)
					is_Word(tmp[i]) ? tmp[i] -= 32 : int(); //Uppercase

				TextColor(ColorCode_Red);  //RED
				cout << tmp << " ";
				TextColor(default_ColorCode);  //DarkWhite
			}
			else
				cout << tmp << " ";
		}
		cout << "..." << endl;
	}
}

string SentenceFilter(string s)  //lowercase
{
	string rs;
	int len = s.length();
	for (int i = 0; i < len; ++i)
	{
		if (!is_accept(s[i]))
		{
			if (s[i] == 39 && s[i + 1] == 's' && s[i + 2] == ' ')  //problem ???s at file 0.txt
			{
				++i;
			}
			else if (i + 1 != len && s[i] == '.' && is_Number(s[i - 1]) && is_Number(s[i + 1]))  //decimal
			{
				rs.append(s, i, 1);
			}
		}
		else
			rs.append(s, i, 1); //get one char
	}
	return rs;
}

bool is_accept(char& k)  //convert to lowercase
{
	if (k >= 65 && k <= 90)
	{
		k = int(k) + 32;
		return true;
	}
	else if ((k >= 48 && k <= 57) || (k >= 97 && k <= 122))
	{
		return true;
	}
	else if (k == '\n')
	{
		k = ' ';
		return true;
	}
	else if (k == '???')
	{
		k = '-';
		return true;
	}
	else if (k == ' ' || k == '$' || k == '%' || k == '#' || k == '-' || k == '"' || k == ':' || k == '$' || k == '~' || k == '+')
	{
		return true;
	}

	return false;
}

bool is_Number(char k)
{
	bool check;
	k >= 48 && k <= 57 ? check = true : check = false;
	return check;
}

bool is_Word(char k)
{
	bool check;
	(k >= 65 && k <= 90) || (k >= 97 && k <= 122) ? check = true : check = false;
	return check;
}