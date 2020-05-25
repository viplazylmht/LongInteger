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

	QInt t = 0;
	for (int i = 0; i < 80; ++i)
	{
		if (i % 2 == 0 || i % 5 == 0) t.setBit(i);
	}
	//t.ROR();
	
	cout << t.toString();

	cout << "MIN: \n" << QInt::MIN_VALUE().toString();
	cout << "MAX: \n" << QInt::MAX_VALUE().toString();
	return 0;
}