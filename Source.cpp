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

	cout << "\nMIN: \n" << QInt::MIN_VALUE().toString();
	//cout << "\nLength MIN: " << QInt::MIN_VALUE().toBinStr().length();

	cout << "\nMAX: \n" << QInt::MAX_VALUE().toString();
	//cout << "\nLength MAX: " << QInt::MAX_VALUE().toBinStr().length();

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
	system("pause");
	return 0;
}