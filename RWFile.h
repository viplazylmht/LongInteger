#pragma once
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "QInt.h"

using namespace std;

class RWFile
{
public:
	static const char SEPERATOR = ' ';
	static vector<string> Tokenlizer(string const& line, char SEPERATOR = SEPERATOR);

private:
	string filein;
	string fileout;
	vector<string> results;

public:
	RWFile(const string& in, const string& out);
	RWFile(char const* in, char const* out);

	bool Start();
	bool ExecALine(const string& line, string& result);
	bool WriteFile();

	int parseInt(string const&);
	bool isOperator(string const&, int base = 10);
};

