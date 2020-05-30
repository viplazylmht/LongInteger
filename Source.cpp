#include <stdio.h>
#include <iostream>
#include <sstream>
#include "QInt.h"
#include "RWFile.h"

using namespace std;


int main(int argc, char** argv)
{
	if (argc == 3)
	{
		// read instruction from command line
		char* input = argv[1];
		char* output = argv[2];
		RWFile rw(input, output);
		rw.Start();
		rw.WriteFile();
	}

	//string str1 = "129999954545645";
	//string str2 = "198111212";

	/*
	QInt demo = 1299925;
	QInt demo1 = 198;

	//QInt demo1(str2, DEC);
	//cout << demo.add2Str(str1, str2) << "\n";
	//cout << demo.Power(20, 9) << "\n";

	//cout << demo.toString();
	//cout << demo1.toString();
	//cout << (demo + demo1).toString();
	//cout << (demo - demo1).toString();
	cout << (demo * demo1).toString();
	cout << (demo / demo1).toString();

	//QInt M = QInt::MIN_VALUE();
	//QInt Q = -1;
	//cout << (M / Q).toString();
	//cout << (M * Q).toString();
	*/
	try {
		QInt tk1 = QInt::MIN_VALUE();
		QInt s2 = tk1;
		QInt tk = tk1 + 1;
		QInt cz = QInt::MAX_VALUE();

		QInt cc = -100;
		//tk1.sub(-50);
		tk1.add(1);

		//cout << tk1.toString();
		cout << "MIN: " << tk1.exportData(HEX) << endl;
		cout << "MAX: " << cz.exportData(HEX) << endl;
		cout << (cc / -50).exportData(DEC);
		//cout << (tk1 + cz).toString();

	}
	catch (const char* msg) {
		cout << msg << endl;
	}

	return 0;
}