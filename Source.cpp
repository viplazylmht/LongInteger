#include <stdio.h>
#include <iostream>
#include <sstream>
#include "QInt.h"
#include "RWFile.h"

using namespace std;


int main()
{
    QInt demoBIN("01111011", BIN);
    QInt demoHEX("7B", HEX);
    QInt demoDEC("123", DEC);

	cout << demoBIN.toString();
	cout << demoHEX.toString();
	cout << demoDEC.toString();
	
	QInt t = 100;
	cout << (demoDEC - t).toString();

	return 0;
}