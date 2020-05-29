#include "RWFile.h"

vector<string> RWFile::Tokenlizer(string const& line, char SEPERATOR)
{
	vector<string> out;
	if (line.length() <= 0) return out;

	int start = 0;
	int pos;

	string temp = "";

	pos = line.find_first_of(SEPERATOR, start);

	while (pos >= 0) {
		temp = line.substr(+start, pos - start);
		out.push_back(temp);
		start = pos + 1;
		pos = line.find_first_of(SEPERATOR, start);
	}

	if (start < line.length()) out.push_back(line.substr(start, line.length()));

	return out;
}

RWFile::RWFile(const string& in, const string& out)
{
	this->filein = in;
	this->fileout = out;
}

RWFile::RWFile(const char* in, const char* out)
{
	this->filein = in;
	this->fileout = out;
}

bool RWFile::Start()
{
	ifstream fin(this->filein);

	if (!fin.is_open()) return false;

	results.clear();
	string line;
	int count = 0;

	while (getline(fin, line))
	{
		count++;
		if (line.length() <= 0 || line[0] == '#') continue;

		string result;
		bool check = ExecALine(line, result);
		if (check)
		{
			this->results.push_back(result);
		}
		else
		{
			stringstream exeption;
			exeption << "ERROR Line " << count << ": " << result;
			this->results.push_back(exeption.str());
		}
	}

	fin.close();
	return true;
}

bool RWFile::ExecALine(const string& line, string& result)
{
	bool res = true;
	vector<string> tokens = Tokenlizer(line);

	QInt* t1 = nullptr;
	QInt* t2 = nullptr;
	QInt* kq = nullptr;

	try {
		// first token is I/O base
		int basein = parseInt(tokens[0]);

		// baseout is needed only when transform base
		int baseout = 0;

		string opt;
		string opr1, opr2;
		
		// use this var because c/c++ doesn't support switch case with string 
		bool isValidOpt = false;

		if (tokens.size() == 3) {

			// here just 1 opr
			if (tokens[1] == "2" || tokens[1] == "10" || tokens[1] == "16")
			{
				// this only transform with known base
				baseout = parseInt(tokens[1]);
				opr1 = tokens[2];
			}
			else
			{
				if (isOperator(tokens[1], basein))
				{
					opt = tokens[1];
					opr1 = tokens[2];
				}
				else
				{
					// transform with unknown base
				}
			}
		}

		else {
			// opt stored at tokens[2], tokens size == 4
			if (isOperator(tokens[2], basein))
			{
				opt = tokens[2];
				opr1 = tokens[1];
				opr2 = tokens[3];
			}
			else {
				// is there any else case?
			}
		}

		// init oprs
		t1 = new QInt(opr1, basein);

		// run opt

		if (opt == "ror") {
			isValidOpt = true;
			t1->ROR();
			kq = new QInt(*t1);
		}

		if (opt == "rol") {
			isValidOpt = true;
			t1->ROL();
			kq = new QInt(*t1);
		}

		if (opt == ">>") {
			isValidOpt = true;

			int count = parseInt(opr2);
			kq = new QInt(*t1 >> count);
		}

		if (opt == "<<") {
			isValidOpt = true;

			int count = parseInt(opr2);
			kq = new QInt(*t1 << count);
		}

		if (opt == "|") {
			isValidOpt = true;

			t2 = new QInt(opr2, basein);
			kq = new QInt(*t1 | *t2);
		}

		if (opt == "&") {
			isValidOpt = true;

			t2 = new QInt(opr2, basein);
			kq = new QInt(*t1 & *t2);
		}

		if (opt == "^") {
			isValidOpt = true;

			t2 = new QInt(opr2, basein);
			kq = new QInt(*t1 ^ *t2);
		}

		if (opt == "~") {
			isValidOpt = true;

			kq = new QInt(~*t1);
		}

		if (opt == "+") {
			isValidOpt = true;

			t2 = new QInt(opr2, basein);
			kq = new QInt(*t1 + *t2);
		}

		if (opt == "-") {
			isValidOpt = true;

			t2 = new QInt(opr2, basein);
			kq = new QInt(*t1 - *t2);
		}
		if (opt == "*") {
			isValidOpt = true;

			t2 = new QInt(opr2, basein);
			kq = new QInt(*t1 * *t2);
		}
		if (opt == "/") {
			isValidOpt = true;

			t2 = new QInt(opr2, basein);
			kq = new QInt(*t1 / *t2);
		}
		if (baseout != 0) {
			// transform base

			isValidOpt = true;
			kq = new QInt(*t1);
		}

		// result object was stored at kq
		if (isValidOpt) {
			// export as basein by default, but when baseout dercaled, use baseout (transform)
			result = kq->exportData((baseout == 0) ? basein : baseout);
		}
		else
		{
			result = "Operator not found!";
			res = false;
		}
	}
	catch (const char* msg)
	{
		result = msg;
		res = false;
	}

	if (!t1) {
		delete t1;
		t1 = nullptr;
	}
	if (!t2) {
		delete t2;
		t2 = nullptr;
	}

	if (!kq) {
		delete kq;
		kq = nullptr;
	}

	return res;
}

bool RWFile::WriteFile()
{
	ofstream fout(fileout);

	if (!fout.is_open()) return false;

	for (string& line : results)
	{
		fout << line << endl;
	}

	fout.close();
	return true;
}

int RWFile::parseInt(string const& intStr)
{
	try
	{
		int i = std::stoi(intStr);
		return i;
	}
	catch (std::invalid_argument const& e)
	{
		throw "This is not a number";
	}
	catch (std::out_of_range const& e)
	{
		throw "Number out of range";
	}
}

bool RWFile::isOperator(string const& str, int base)
{
	for (const char& c : str)
	{
		// if at least 1 char is a valid value in base, return false
		if (base == 10) {
			if (c >= '0' && c <= '9') return false;
		}

		if (base == 16) {
			if (((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
				return false;
		}

		if (base == 2) {
			if (c == '0' || c == '1') return false;
		}
	}

	return true;
}
