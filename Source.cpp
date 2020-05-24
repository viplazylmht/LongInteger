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

    cout << "Size of QInt: " << sizeof(demo) << endl;
    cout << test.toString();
	cout << demo1.toString();
    return 0;
}