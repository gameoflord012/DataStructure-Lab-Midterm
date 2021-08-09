#include "engine.h"

bool searchStopWord(string tmp, Database _data)
{
	wstring get = wstring(tmp.begin(), tmp.end());
	SearchResult result = _data.GetResults(SearchInfo(get, SearchType::word));
	for (FileInfo info : result.GetInfos())
	{
		if (info.title + L"." + info.extension == L"stopword.txt")
			return true;
	}
	return false;
}

vector<string> searchResults(string query, SearchResult& results, Database database)
{
	vector<string> data;
	stringstream ss(query);
	string tmp, get;
	string _get;
	while (ss >> tmp)
	{
		if (tmp[0] == '$') //search range
		{
			if (!_get.empty()) _get.pop_back();
			data.push_back(_get);
			//data.push_back("NUM");
			//ss >> tmp;
			//data.push_back(tmp);
			_get = "";
		}
		
		get = tmp.substr(0, 8);//intitle:
		if (get == "intitle:")
		{
			get = tmp.substr(8);
			if (!_get.empty()) _get.pop_back();
			data.push_back(_get);
			data.push_back("intitle:");
			data.push_back(get);
			_get = "";
		}
		else if (tmp[0] == '"') //exact match and wildcard
		{
			//if (!_get.empty()) _get.pop_back();
			//data.push_back(_get);
			if (tmp.back() != '"')
			{
				tmp.erase(tmp.begin(), tmp.begin() + 1);
				do
				{
					if (tmp.back() == '"')
						tmp.erase(tmp.end() - 1, tmp.end());

					_get += tmp + ' ';

					if (tmp.back() == '"')
						break;
				} while (ss >> tmp);
			}
		}
		else if (tmp[0] == '~')
		{
			data.push_back("sym");
			tmp.erase(tmp.begin(), tmp.begin() + 1);
			data.push_back(tmp);
		}
		else if (tmp == "OR")
		{
			if (!_get.empty()) _get.pop_back();
			data.push_back(_get);
			data.push_back("OR");
			_get = "";
		}
		else if (tmp == "AND" || tmp == "filetype:txt")
		{
			if (!_get.empty()) _get.pop_back();
			data.push_back(_get);
			data.push_back("AND");
			_get = "";
		}
		else if (searchStopWord(tmp, database))
			continue;
		else
			_get += tmp + " ";
	}
	if (!_get.empty()) _get.pop_back();
	if (!_get.empty()) data.push_back(_get);
	searchData(data, results, database);
	return data;  //don't care it ¯\_(ツ)_/¯
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
		else if (tmp == "intitle:")
		{
			type = 1;
		}
		else if (tmp == "sym")
		{
			type = 2;
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
			default:
				tmp_result = database.GetResults(SearchInfo(_get, SearchType::word));
				type = 0;
				break;
			};

			if (choice == -1) {
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

//-----------------HISTORY---------------
void History(vector<string>& res, string query)
{
	res.push_back(query);
	cout << "Choose query:" << endl << "0. " << query << endl;

	int i = 1;
	ifstream input; input.open("history.txt");
	string tmp;
	while (!input.eof())
	{
		getline(input, tmp);
		if (tmp == "" || query == tmp || tmp.find(query) == -1)
		{
			continue;
		}

		cout << i << ". " << tmp << endl;

		res.push_back(tmp);
		++i;
	}
	input.close();
	ofstream output; output.open("history.txt", ios::app);
	output << query << endl;
	output.close();
}

void clearHistory()
{
	ifstream file; file.open("history.txt", ios::out | ios::trunc);
	file.close();
}


//------------------OPTIONS----------------
bool checkOperator(string query) {
	stringstream ss(query);
	string tmp;
	while (ss >> tmp)
	{
		string get; get = tmp.substr(0, 8);
		if (get == "intitle:") return false;
		if (tmp == "AND" || tmp == "OR" || tmp[0] == '-' || tmp == "*" || tmp == "filetype:txt" || tmp[0] == '"' || tmp.back() == '*')
		{
			return false;
		}
		int length = tmp.length();
		for (int i = 0; i <= length - 3; ++i)
		{
			if (tmp[i] == '.' && tmp[i + 1] == '.')
			{
				return false;
			}
		}
	}
	return true;
}

void OutputResult(wstring fn, vector<int> pos)
{
	if (!pos.size())
		return;

	ifstream f;
	f.open(fn);
	if (!f.is_open())
	{
		cout << "Error" << endl;
		return;
	}

	string title;
	getline(f, title);
	cout << title << endl;

	f.clear();
	f.seekg(0, ios::beg);
	int cnt = 0, cur = 0, totalLength = -1;
	while (!f.eof())
	{
		string tmp;
		getline(f, tmp, '.');
		if (tmp.length() && is_Number(tmp.back()))  //decimal number case
		{
			string next; getline(f, next, '.');
			if (next.length() && is_Number(next[0]))
			{
				tmp = tmp + '.' + next;
			}
			else
				tmp = tmp + " " + next;
		}

		tmp = SenFilter(tmp);
		int NumWord = WordinSen(tmp);
		totalLength += NumWord;

		if (pos[cur] > totalLength)
		{
			cnt += NumWord;
			continue;
		}
		cout << "...";
		stringstream ss(tmp);
		while (ss >> tmp)
		{
			if (cur < pos.size() && pos[cur] == cnt)
			{
				++cur;
				for (int i = 0; i < tmp.length(); ++i) if (is_Word(tmp[i]))
				{
					tmp[i] -= 32;
				}
				//TextColor(10);
				cout << tmp << " ";
				//TextColor(7);
			}
			else cout << tmp << " ";
			++cnt;
		}
		cout << "..." << endl;
		if (cur >= pos.size())
		{
			f.close();
			return;
		}
	}
	f.close();
}

bool is_accept(char& k)
{
	if (k >= 65 && k <= 90)
	{
		k = int(k) + 32;
		return true;
	}
	if ((k >= 48 && k <= 57) || (k >= 97 && k <= 122))
	{
		return true;
	}
	if (k == '\n')
	{
		k = ' ';
		return true;
	}
	if (k == '—') {
		k = '-';
		return true;
	}
	if (k == ' ' || k == '$' || k == '%' || k == '#' || k == '-')
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

string SenFilter(string s)
{
	string rs;
	int len = s.length();
	for (int i = 0; i < len; ++i)
	{
		if (!is_accept(s[i]))
		{
			if (s[i] == 39 && s[i + 1] == 's' && s[i + 2] == ' ')
			{
				++i;
			}
			else if (i + 1 != len && s[i] == '.' && is_Number(s[i - 1]) && is_Number(s[i + 1]))  //so thap phan
			{
				rs.append(s, i, 1);
			}
		}
		else
			rs.append(s, i, 1); //get 1 
	}
	return rs;
}

int WordinSen(string sen)
{
	stringstream ss(sen);
	int cnt = 0;
	string tmp;

	while (ss >> tmp)
	{
		++cnt;
	}
	return cnt;
}

