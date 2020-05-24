#include <stdio.h>
#include <iostream>
#include <sstream>
#include "QInt.h"

using namespace std;


int main()
{
    QInt demo("10101110", BIN);

    QInt test = demo;

	QInt demo1("123", DEC);
	QInt demo2("1", DEC);

	demo1.setBit(7, 0);
	cout << demo1.toString() << endl;
	cout << demo1.getBit(0) << " - " << demo1.getBit(1) << endl;

	cout << demo2.toString();
	cout << (demo1 + demo2).toString();
    return 0;
}