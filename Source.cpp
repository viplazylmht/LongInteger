#include <stdio.h>
#include <iostream>
#include <sstream>
#include "QInt.h"

using namespace std;


int main()
{
    QInt demo("10101110", BIN);

    QInt test = demo;

    cout << "Size of QInt: " << sizeof(demo) << endl;
    cout << test.toString();
    return 0;
}