#include <stdio.h>
#include <iostream>
#include <sstream>
#include "RWFile.h"

using namespace std;


int main()
{
    
    RWFile rw("input.txt", "output.txt");
    rw.Start();

    rw.WriteFile();
    /*QInt t1("1C7D", 16);
    t1.ROR();
    QInt t2("80000000000000000000000000000E3E", 16);

    cout << t1.toHexStr() << endl
        << t2.toBinStr() << endl;*/
    return 0;
}