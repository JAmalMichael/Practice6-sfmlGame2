#ifndef  CONFIGREADER_H
#define  CONFIGREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class CongReader {
	vector<string> lines;

public:
	bool load(string & filename)
	{
		ifstream file(filename);
		if (!file.is_open())
		{
			return false;
			cout << " Filename error" << endl;
		}
		string line;

		while (getline(file, line))
		{
			if (!line.empty()) lines.push_back(line);
			return true;
		};
		}
		
		const string& getLine(size_t index) const {
		return lines.at(index);
	}
};


#endif
