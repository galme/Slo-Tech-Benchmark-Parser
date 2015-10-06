#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <Shlobj.h>
#include <string>
#include <cstring>
#include "windows.h"
#include <shellapi.h>
#include "OpenFileDialog.h"
#include <fstream>
#include <sstream>
#include "Result.h"
#include <vector>
#include <algorithm>
#pragma comment(lib,"shell32.lib") 

using namespace std;

// cleans the string of all strong tags and strips the hyperlink
void clean_string(string &str)
{

	// remove <strong> tags
	int strong_start = str.find("<strong>");
	while (strong_start != string::npos)
	{
		str.erase(strong_start, 8);
		strong_start = str.find("<strong>");
	}

	// remove </strong> tags
	int strong_end = str.find("</strong>");
	while (strong_end != string::npos)
	{
		str.erase(strong_end, 9);
		strong_end = str.find("</strong>");
	}

	// strip the hyperlink
	int start = -1;
	int end = -1;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '<' && str[i + 1] == 'a' && str[i + 2] == ' ')
			start = i;
		else if (start > 0 && str[i] == 'h' && str[i + 1] == 't' && str[i + 2] == 't' && str[i + 3] == 'p')
		{
			end = i;
			str.erase(start, end - start);
			int end_trim_delim = str.rfind('"');
			str.erase(end_trim_delim, str.size());
			break;
		}
	}
}

// trimms the string on both ends
string trim(string s)
{
	stringstream ss;
	ss << s;
	s.clear();
	ss >> s;
	return s;
}

// parses file into a vector of structures
void parse_file(string fname, vector<Result> &vec)
{
	cout << "parsing file...";

	char seperator = '|';
	ifstream input(fname);
	stringstream ss;
	string line;
	string nickname;
	string score_str;
	string middle;
	string last_string;
	string link;
	int first_i;
	int last_i;
	int mid_end;
	double score;

	while (getline(input, line))
	{
		clean_string(line);

		int first_i = line.find(seperator);
		int last_i = line.rfind(seperator);
		nickname = trim(line.substr(0, first_i));
		last_string = trim(line.substr(last_i + 1, line.size() - last_i + 1));

		// link parsing handling
		if (last_string.find("http") != string::npos) // if we've found a link in the last place
		{
			mid_end = line.rfind('|', last_i - 1);
			link = last_string;
			score_str = line.substr(mid_end + 1, last_i - mid_end);
		}
		else // otherwise the last string is the score
		{
			score_str = last_string;
			mid_end = last_i;
			link = "";
		}

		score = stod(score_str);
		middle = line.substr(first_i, mid_end - first_i + 1);

		vec.push_back(Result(nickname, middle, score, link));
	}

	cout << " success!" << endl;
}

bool compare_desc(Result res1, Result res2)
{
	return res1.score > res2.score;
}

bool compare_asc(Result res1, Result res2)
{
	return res1.score < res2.score;
}

// makes a new file with processed results
void print_file(string fname, vector<Result> vec, bool is_numbered = true)
{
	cout << "printing file (" << fname << "); numbered version: " << (is_numbered ? "yes" : "no") << endl;
	ofstream output(fname);

	for (int i = 0; i != vec.size(); i++)
	{
		if (is_numbered)
		{
			output << (i + 1) << ". "; // print position
			output << "<strong>" << vec[i].nickname << "</strong> "; // print nickname in bold
		}
		else
			output << vec[i].nickname << " "; // print nickname

		output << vec[i].middle; // print the middle string
		output << " <strong>" << vec[i].score << "</strong>"; // print the score

		if (vec[i].link.size() > 0) // if a link is available
			output << " | <a href=\"" << vec[i].link << "\">link</a>"; // print the link

		output << endl;
	}
	cout << "success!" << endl;
}

// removes duplicates, so that only one (the best of all) submission from the user is kept.
// sorting the vector before running this is mandatory!
void remove_duplicates(vector<Result> &vec)
{
	cout << "removing duplicates...";
	for (int i = 0; i < vec.size() - 1; i++)
	{
		for (int j = i + 1; j < vec.size(); j++)
		{
			if (vec[i].nickname == vec[j].nickname)
			{
				vec.erase(vec.begin() + j);
				j--;
			}
		}
	}
	cout << " success!" << endl;
}

// removes the file extension from the path
string no_extension(string path)
{
	return path.substr(0, path.rfind('.'));
}

int main()
{
	OpenFileDialog* openFileDialog = new OpenFileDialog();
	vector<Result> vec;

	if (openFileDialog->ShowDialog())
	{
		string option;
		string input_file = openFileDialog->FileName;

		while (!(option == "1" || option == "2"))
		{
			cout << "options: " << endl;
			cout << "1 - ASCENDING order (lower result is better)" << endl;
			cout << "2 - DESCENDING order (higher result is better)" << endl;
			cout << "enter choice: ";
			cin >> option;
			if (!(option == "1" || option == "2"))
				cout << "whoops, wrong input, try again!" << endl;
		}
		
		string ofname1 = no_extension(input_file) + "_sorted.txt";
		string ofname2 = no_extension(input_file) + "_sorted_filtered_numbered.txt";

		parse_file(input_file, vec); // read, parse and fill vector with the data

		if (vec.size() > 0)
		{

			cout << "sorting data... ";

			if (option == "1")
				sort(vec.begin(), vec.end(), compare_asc);
			else
				sort(vec.begin(), vec.end(), compare_desc);

			cout << " success!" << endl;

			print_file(ofname1, vec, false); // make a file of all results

			remove_duplicates(vec); // remove duplicates

			print_file(ofname2, vec); // make a file of unique & best results for every user

			cout << endl << "--- OPERATION SUCCESSFUL ---" << endl;
		}
		else
		{
			cout << "No real data - exiting..." << endl;
			cout << endl << "--- OPERATION FAILED ---" << endl;
		}
			
	}
	else
		cout << "no file chosen" << endl;

	system("pause");
	return 0;
}