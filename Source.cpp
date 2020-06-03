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

		return 0;
	}
  
	// RWFile rw("input.txt", "output.txt");

	// rw.Start();
	// rw.WriteFile();

	// return 0;

	try {
		QInt tk1 = QInt::MIN_VALUE();
		QInt s2 = tk1;
		QInt tk = tk1 + 1;
		QInt cz = QInt::MAX_VALUE();

		QInt cc("-1222222", DEC);

		//cout << tk1.toString();
		cout << "MIN: " << tk1.exportData(DEC) << endl;
		cout << "MAX: " << cz.exportData(HEX) << endl;
		cout << (cc / -20).exportData(HEX) << endl;
		//cout << (tk1 + cz).toString();

		cout << cc.toDecStr();
	}
	catch (const char* msg) {
		cout << msg << endl;
	}

	return 0;
}