#include <stdio.h>
#include <iostream>
#include <sstream>
#include "QInt.h"

using namespace std;


int main()
{
    QInt demo("1111010010101110", BIN);
    QInt test("092EE35ACF4716A6F4AE", HEX);

    cout << "Size of QInt: " << sizeof(demo) << endl;
    cout << demo.toString();
    cout << test.toString();

    demo.ROR();
    cout << "ROR demo: \n" << demo.toString();

    test.ROL();
    cout << "ROL test: \n" << test.toString();

    return 0;
}